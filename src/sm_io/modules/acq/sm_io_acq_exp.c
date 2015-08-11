/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU LGPL, version 3 or any later version.
 */

#include "bpm_server.h"
/* Private headers */
#include "ddr3_map.h"
#include "sm_io_acq_codes.h"
#include "sm_io_acq_exports.h"
#include "sm_io_acq_core.h"
#include "sm_io_acq_exp.h"
#include "hw/wb_acq_core_regs.h"

/* Undef ASSERT_ALLOC to avoid conflicting with other ASSERT_ALLOC */
#ifdef ASSERT_TEST
#undef ASSERT_TEST
#endif
#define ASSERT_TEST(test_boolean, err_str, err_goto_label, /* err_core */ ...) \
    ASSERT_HAL_TEST(test_boolean, SM_IO, "[sm_io:acq_exp]", \
            err_str, err_goto_label, /* err_core */ __VA_ARGS__)

#ifdef ASSERT_ALLOC
#undef ASSERT_ALLOC
#endif
#define ASSERT_ALLOC(ptr, err_goto_label, /* err_core */ ...) \
    ASSERT_HAL_ALLOC(ptr, SM_IO, "[sm_io:acq_exp]", \
            smio_err_str(SMIO_ERR_ALLOC),           \
            err_goto_label, /* err_core */ __VA_ARGS__)

#ifdef CHECK_ERR
#undef CHECK_ERR
#endif
#define CHECK_ERR(err, err_type)                    \
    CHECK_HAL_ERR(err, SM_IO, "[sm_io:acq_exp]",    \
            smio_err_str (err_type))

/* FIXME: Usage of reserved, undocumented bits */
/* Acquisition can start if FSM is in IDLE state, if Flow Control FIFO
 * is not FULL, dbg_source_pl_stall (RESERVED BIT, UNDOCUMENTED) is not asserted
 * and there is no data in the FIFOs (ACQ_CORE_STA_RESERVED3_MASK)*/
#define ACQ_CORE_IDLE_MASK      (ACQ_CORE_STA_FSM_STATE_MASK | ACQ_CORE_STA_FC_FULL | \
                                    ACQ_CORE_STA_RESERVED2_W(1 << 3) | ACQ_CORE_STA_RESERVED3_MASK)

#define ACQ_CORE_IDLE_VALUE     ACQ_CORE_STA_FSM_STATE_W(0x1)

/* Acquisition is completed when FSM is in IDLE state, FSM is with DONE
 * flag asserted, Flow Control FIFO is with DOME flag asserted and DDR3 has
 * its DONE flag asserted */
#define ACQ_CORE_COMPLETE_MASK  (ACQ_CORE_STA_FSM_STATE_MASK | ACQ_CORE_STA_FSM_ACQ_DONE | \
                                    ACQ_CORE_STA_FC_TRANS_DONE | ACQ_CORE_STA_DDR3_TRANS_DONE)

#define ACQ_CORE_COMPLETE_VALUE (ACQ_CORE_STA_FSM_STATE_W(0x1) | ACQ_CORE_STA_FSM_ACQ_DONE | \
                                    ACQ_CORE_STA_FC_TRANS_DONE | ACQ_CORE_STA_DDR3_TRANS_DONE)

static int _acq_check_status (SMIO_OWNER_TYPE *self, uint32_t status_mask,
        uint32_t status_value);

/************************************************************/
/***************** Specific ACQ Operations ******************/
/************************************************************/

static int _acq_data_acquire (void *owner, void *args, void *ret)
{
    (void) ret;
    assert (owner);
    assert (args);
    int err = -ACQ_OK;

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] "
            "Calling _acq_data_acquire\n");
    SMIO_OWNER_TYPE *self = SMIO_EXP_OWNER(owner);
    smio_acq_t *acq = smio_get_handler (self);
    ASSERT_TEST(acq != NULL, "Could not get SMIO ACQ handler",
            err_get_acq_handler, -ACQ_ERR);

    /* First step is to check if the FPGA is already doing an acquisition. If it
     * is, then return an error. Otherwise proceed normally. */
    err = _acq_check_status (self, ACQ_CORE_IDLE_MASK, ACQ_CORE_IDLE_VALUE);
    ASSERT_TEST(err == -ACQ_OK, "Previous acquisition in progress. "
            "New acquisition not started", err_acq_not_completed);

    /* Message is:
     * frame 0: operation code
     * frame 1: number of samples
     * frame 2: channel                 */
    uint32_t num_samples = *(uint32_t *) EXP_MSG_ZMQ_FIRST_ARG(args);
    uint32_t chan = *(uint32_t *) EXP_MSG_ZMQ_NEXT_ARG(args);

    /* channel required is out of the limit */
    if (chan > SMIO_ACQ_NUM_CHANNELS-1) {
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_WARN, "[sm_io:acq] data_acquire: "
                "Channel required is out of the maximum limit\n");

        return -ACQ_NUM_CHAN_OOR;
    }

    /* number of samples required is out of the maximum limit */
    if (num_samples > acq->acq_buf[chan].max_samples) {
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_WARN, "[sm_io:acq] data_acquire: "
                "Number of samples required is out of the maximum limit\n");
        return -ACQ_NUM_SAMPLES_OOR;
    }

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "\n\tCurrent acq params for channel #%u: number of samples = %u\n",
            chan, num_samples);

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "\n\tPrevious acq params for channel #%u: number of samples = %u\n",
            chan, acq->acq_params[chan].num_samples);

    /* Set the parameters: number of samples of this channel */
    acq->acq_params[chan].num_samples = num_samples;

    /* Default SHOTS value is 1 */
    uint32_t acq_core_shots = ACQ_CORE_SHOTS_NB_W(1);
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Number of shots = %u\n", acq_core_shots);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_SHOTS, &acq_core_shots);

    /* FIXME FPGA Firmware requires number of samples to be divisible by
     * acquisition channel sample size */
    uint32_t num_samples_div_pre =
        DDR3_PAYLOAD_SIZE/acq->acq_buf[chan].sample_size;
    uint32_t num_samples_aligned_pre = num_samples + num_samples_div_pre -
        (num_samples % num_samples_div_pre);
    /* Pre trigger samples */
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Number of pre-trigger samples (aligned to sample size) = %u\n",
            num_samples_aligned_pre);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_PRE_SAMPLES, &num_samples_aligned_pre);

    /* Post trigger samples */
    uint32_t num_samples_post = 0;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Number of post-trigger samples = %u\n",
            num_samples_post);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_POST_SAMPLES, &num_samples_post);

    /* DDR3 start address. Convert Byte address to Word address, as this address
     * is written to the DDR controller, which is 32-bit (word) addressed */
    uint32_t start_addr = (uint32_t)
        acq->acq_buf[chan].start_addr/DDR3_ADDR_WORD_2_BYTE;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "DDR3 start address: 0x%08x\n", start_addr);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_DDR3_START_ADDR, &start_addr);

    /* Prepare core_ctl register */
    uint32_t acq_core_ctl_reg = ACQ_CORE_CTL_FSM_ACQ_NOW;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Control register is: 0x%08x\n",
            acq_core_ctl_reg);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_CTL, &acq_core_ctl_reg);

    /* Prepare acquisition channel control */
    uint32_t acq_chan_ctl = ACQ_CORE_ACQ_CHAN_CTL_WHICH_W(chan);
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Channel control register is: 0x%08x\n",
            acq_chan_ctl);
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_ACQ_CHAN_CTL, &acq_chan_ctl);

    /* Starting acquisition... */
    acq_core_ctl_reg |= ACQ_CORE_CTL_FSM_START_ACQ;
    smio_thsafe_client_write_32 (self, ACQ_CORE_REG_CTL, &acq_core_ctl_reg);

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Acquisition Started!\n");

    return -ACQ_OK;

err_acq_not_completed:
err_get_acq_handler:
    return err;
}

static int _acq_check_data_acquire (void *owner, void *args, void *ret)
{
    (void) ret;
    assert (owner);
    assert (args);
    int err = -ACQ_OK;

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] "
            "Calling _acq_check_data_acquire\n");

    SMIO_OWNER_TYPE *self = SMIO_EXP_OWNER(owner);
    smio_acq_t *acq = smio_get_handler (self);
    ASSERT_TEST(acq != NULL, "Could not get SMIO ACQ handler",
            err_get_acq_handler, -ACQ_ERR);

    err = _acq_check_status (self, ACQ_CORE_COMPLETE_MASK, ACQ_CORE_COMPLETE_VALUE);
    ASSERT_TEST(err == -ACQ_OK, "Acquisition has not completed yet",
            err_acq_not_completed);

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] acq_check_data_acquire: "
            "Acquisition is done\n");

err_acq_not_completed:
err_get_acq_handler:
    return err;
}

static int _acq_check_status (SMIO_OWNER_TYPE *self, uint32_t status_mask,
        uint32_t status_value)
{
    int err = -ACQ_OK;
    uint32_t status_done = 0;

    /* Check for completion */
    smio_thsafe_client_read_32 (self, ACQ_CORE_REG_STA, &status_done);
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] data_acquire: "
            "Status done = 0x%08x\n", status_done);

    if ((status_done & status_mask) != status_value) {
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] acq_check_data_acquire: "
                "Acquisition is not done\n");
        err = -ACQ_NOT_COMPLETED;
        goto err_not_completed;
    }

    err = -ACQ_OK;

err_not_completed:
    return err;
}

static int _acq_get_data_block (void *owner, void *args, void *ret)
{
    assert (owner);
    assert (args);

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] "
            "Calling _acq_get_data_block\n");

    SMIO_OWNER_TYPE *self = SMIO_EXP_OWNER(owner);
    smio_acq_t *acq = smio_get_handler (self);
    ASSERT_TEST(acq != NULL, "Could not get SMIO ACQ handler",
            err_get_acq_handler);

    /* Message is:
     * frame 0: channel
     * frame 1: block required      */
    uint32_t chan = *(uint32_t *) EXP_MSG_ZMQ_FIRST_ARG(args);
    uint32_t block_n = *(uint32_t *) EXP_MSG_ZMQ_NEXT_ARG(args);
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "chan = %u, block_n = %u\n", chan, block_n);

    /* channel required is out of the limit */
    if (chan > SMIO_ACQ_NUM_CHANNELS-1) {
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_WARN, "[sm_io:acq] data_acquire: "
                "Channel required is out of the maximum limit\n");

        return -ACQ_NUM_CHAN_OOR;
    }

    /* Channel features */
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "\t[channel = %u], id = %u, start addr = 0x%08x\n"
            "\tend addr = 0x%08x, max samples = %u, sample size = %u\n",
            chan,
            acq->acq_buf[chan].id,
            acq->acq_buf[chan].start_addr,
            acq->acq_buf[chan].end_addr,
            acq->acq_buf[chan].max_samples,
            acq->acq_buf[chan].sample_size);

    uint32_t block_n_max = ( acq->acq_buf[chan].end_addr -
            acq->acq_buf[chan].start_addr +
            acq->acq_buf[chan].sample_size) / BLOCK_SIZE;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "block_n_max = %u\n", block_n_max);

    if (block_n > block_n_max) {    /* block required out of the limits */
        /* TODO error level in this case */
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_ERR, "[sm_io:acq] get_data_block: "
                "Block %u of channel %u is out of range\n", block_n, chan);
        return -ACQ_BLOCK_OOR;
    }

    /* Get number of samples */
    uint32_t num_samples =
        acq->acq_params[chan].num_samples;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "last num_samples = %u\n", num_samples);

    uint32_t n_max_samples = BLOCK_SIZE/acq->acq_buf[chan].sample_size;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "n_max_samples = %u\n", n_max_samples);

    uint32_t over_samples = num_samples % n_max_samples;
    uint32_t block_n_valid = num_samples / n_max_samples;
    /* When the last block is full 'block_n_valid' exceeds by one */
    if (block_n_valid != 0 && over_samples == 0) {
        block_n_valid--;
    }
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "block_n_valid= %u, over_samples= %u\n",
            block_n_valid, over_samples);

    /* check if block required is valid and if it is full or not */
    if (block_n > block_n_valid) {
        /* TODO error level in this case */
        DBE_DEBUG (DBG_SM_IO | DBG_LVL_ERR, "[sm_io:acq] get_data_block: "
                "Block %u of channel %u is not valid\n", block_n, chan);
        return -ACQ_BLOCK_OOR;
    }   /* Last valid data conditions check done */

    uint32_t reply_size;
    if (block_n == block_n_valid && over_samples > 0){
        reply_size = over_samples*acq->acq_buf[chan].sample_size;
    }
    else { /* if block_n < block_n_valid */
        reply_size = BLOCK_SIZE;
    }

    DBE_DEBUG (DBG_SM_IO | DBG_LVL_INFO, "[sm_io:acq] get_data_block: "
            "Reading block %u of channel %u with %u valid samples\n",
            block_n, chan, reply_size);

    uint32_t addr_i = acq->acq_buf[chan].start_addr +
        block_n * BLOCK_SIZE;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "Block %u of channel %u start address = 0x%08x\n", block_n,
            chan, addr_i);

    smio_acq_data_block_t *data_block = (smio_acq_data_block_t *) ret;

    /* Here we must use the "raw" version, as we can't have
     * LARGE_MEM_ADDR mangled with the bas address of this SMIO */
    ssize_t valid_bytes = smio_thsafe_raw_client_read_block (self, LARGE_MEM_ADDR | addr_i,
            reply_size, (uint32_t *) data_block->data);
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq] get_data_block: "
            "%ld bytes read\n", valid_bytes);

    /* Check if we could read successfully */
    int retf = 0;
    if (valid_bytes >= 0) {
        data_block->valid_bytes = (uint32_t) valid_bytes;
        retf = valid_bytes + (ssize_t) sizeof (data_block->valid_bytes);
    }
    else {
        data_block->valid_bytes = 0;
        retf = -ACQ_COULD_NOT_READ;
    }

    return retf;

err_get_acq_handler:
    return -ACQ_ERR;
}

/* Exported function pointers */
const disp_table_func_fp acq_exp_fp [] = {
    _acq_data_acquire,
    _acq_check_data_acquire,
    _acq_get_data_block,
    NULL
};

/************************************************************/
/***************** Export methods functions *****************/
/************************************************************/

static smio_err_e _acq_do_op (void *owner, void *msg);

/* Attach an instance of sm_io to dev_io function pointer */
smio_err_e acq_attach (smio_t *self, devio_t *parent)
{
    (void) self;
    (void) parent;
    return SMIO_ERR_FUNC_NOT_IMPL;
}

/* Deattach an instance of sm_io to dev_io function pointer */
smio_err_e acq_deattach (smio_t *self)
{
    (void) self;
    return SMIO_ERR_FUNC_NOT_IMPL;
}

/* Export (register) sm_io to handle operations function pointer */
smio_err_e acq_export_ops (smio_t *self,
        const disp_op_t** smio_exp_ops)
{
    (void) self;
    (void) smio_exp_ops;
    return SMIO_ERR_FUNC_NOT_IMPL;
}

/* Unexport (unregister) sm_io to handle operations function pointer */
smio_err_e acq_unexport_ops (smio_t *self)
{
    (void) self;
    return SMIO_ERR_FUNC_NOT_IMPL;
}

/* Generic wrapper for receiving opcodes and arguments to specific funtions function pointer */
/* FIXME: Code repetition! _devio_do_smio_op () function does almost the same!!! */
smio_err_e _acq_do_op (void *owner, void *msg)
{
    (void) owner;
    (void) msg;
    return SMIO_ERR_FUNC_NOT_IMPL;
}

smio_err_e acq_do_op (void *self, void *msg)
{
    return _acq_do_op (self, msg);
}

const smio_ops_t acq_ops = {
    .attach             = acq_attach,          /* Attach sm_io instance to dev_io */
    .deattach           = acq_deattach,        /* Deattach sm_io instance to dev_io */
    .export_ops         = acq_export_ops,      /* Export sm_io operations to dev_io */
    .unexport_ops       = acq_unexport_ops,    /* Unexport sm_io operations to dev_io */
    .do_op              = acq_do_op            /* Generic wrapper for handling specific operations */
};

/************************************************************/
/****************** Bootstrap Operations ********************/
/************************************************************/

smio_err_e acq_init (smio_t * self)
{
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq_exp] Initializing acq\n");

    smio_err_e err = SMIO_SUCCESS;

    err = smio_set_id (self, ACQ_SDB_DEVID);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO id", err_set_id);
    err = smio_set_name (self, ACQ_SDB_NAME);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO name", err_set_name);

    /* Set SMIO ops pointers */
    err = smio_set_ops (self, &acq_ops);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO operations",
            err_smio_set_ops);
    err = smio_set_thsafe_client_ops (self, &smio_thsafe_client_zmq_ops);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO thsafe operations",
            err_smio_set_thsafe_ops);

    /* Fill the disp_op_t description structure with the callbacks. */

    /* disp_op_t structure is const and all of the functions performing on it
     * obviously receives a const argument, but here (and only on the SMIO
     * initialization) we need to make an exception if we want to keep the
     * functions' description and the function pointers separate */
    err = smio_init_exp_ops (self, (disp_op_t **) acq_exp_ops, acq_exp_fp);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not fill SMIO "
            "function descriptors with the callbacks", err_fill_desc);

    err = smio_set_exp_ops (self, acq_exp_ops);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO exported operations",
            err_smio_set_exp_ops);

    /* Initialize specific structure */
    smio_acq_t *smio_handler = smio_acq_new (self, 0); /* Default: num_samples = 0 */
    ASSERT_ALLOC(smio_handler, err_smio_handler_alloc, SMIO_ERR_ALLOC);
    err = smio_set_handler (self, smio_handler);
    ASSERT_TEST(err == SMIO_SUCCESS, "Could not set SMIO handler",
            err_smio_set_handler);

    return err;

err_smio_set_handler:
    smio_acq_destroy (&smio_handler);
err_smio_handler_alloc:
    smio_set_exp_ops (self, NULL);
err_smio_set_exp_ops:
err_fill_desc:
    smio_set_thsafe_client_ops (self, NULL);
err_smio_set_thsafe_ops:
    smio_set_ops (self, NULL);
err_smio_set_ops:
err_set_name:
err_set_id:
    return err;
}

/* Destroy sm_io instance of acq */
smio_err_e acq_shutdown (smio_t *self)
{
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_TRACE, "[sm_io:acq_exp] Shutting down acq\n");

    smio_err_e err = SMIO_SUCCESS;
    smio_acq_t *acq = smio_get_handler (self);
    ASSERT_TEST(acq != NULL, "Could not get ACQ handler",
            err_acq_handler, SMIO_ERR_ALLOC /* FIXME: improve return code */);

    /* Destroy SMIO instance */
    smio_acq_destroy (&acq);
    /* Nullify operation pointers */
    smio_set_exp_ops (self, NULL);
    smio_set_thsafe_client_ops (self, NULL);
    smio_set_ops (self, NULL);

err_acq_handler:
    return err;
}

const smio_bootstrap_ops_t acq_bootstrap_ops = {
    .init = acq_init,
    .shutdown = acq_shutdown
};
