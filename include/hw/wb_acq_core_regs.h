/*
  Register definitions for slave core: BPM FSM Acquisition registers

  * File           : wb_acq_core_regs.h
  * Author         : auto-generated by wbgen2 from acq_core.wb
  * Created        : Wed Aug 17 12:04:55 2016
  * Standard       : ANSI C

    THIS FILE WAS GENERATED BY wbgen2 FROM SOURCE FILE acq_core.wb
    DO NOT HAND-EDIT UNLESS IT'S ABSOLUTELY NECESSARY!

*/

/* This file has been modified! */

#ifndef __WBGEN2_REGDEFS_ACQ_CORE_WB
#define __WBGEN2_REGDEFS_ACQ_CORE_WB

#include <inttypes.h>

#if defined( __GNUC__)
#define PACKED __attribute__ ((packed))
#else
#error "Unsupported compiler?"
#endif

#ifndef __WBGEN2_MACROS_DEFINED__
#define __WBGEN2_MACROS_DEFINED__
#define WBGEN2_GEN_MASK(offset, size) (((1<<(size))-1) << (offset))
#define WBGEN2_GEN_WRITE(value, offset, size) (((value) & ((1<<(size))-1)) << (offset))
#define WBGEN2_GEN_READ(reg, offset, size) (((reg) >> (offset)) & ((1<<(size))-1))
#define WBGEN2_SIGN_EXTEND(value, bits) (((value) & (1<<bits) ? ~((1<<(bits))-1): 0 ) | (value))
#endif


/* definitions for register: Control register */

/* definitions for field: State machine acquisition_start command (ignore on read) in reg: Control register */
#define ACQ_CORE_CTL_FSM_START_ACQ            WBGEN2_GEN_MASK(0, 1)

/* definitions for field: State machine stop command (ignore on read) in reg: Control register */
#define ACQ_CORE_CTL_FSM_STOP_ACQ             WBGEN2_GEN_MASK(1, 1)

/* definitions for field: Reserved1 in reg: Control register */
#define ACQ_CORE_CTL_RESERVED1_MASK           WBGEN2_GEN_MASK(2, 14)
#define ACQ_CORE_CTL_RESERVED1_SHIFT          2
#define ACQ_CORE_CTL_RESERVED1_W(value)       WBGEN2_GEN_WRITE(value, 2, 14)
#define ACQ_CORE_CTL_RESERVED1_R(reg)         WBGEN2_GEN_READ(reg, 2, 14)

/* definitions for field: Acquire data immediately and don't wait for any trigger (ignore on read) in reg: Control register */
#define ACQ_CORE_CTL_FSM_ACQ_NOW              WBGEN2_GEN_MASK(16, 1)

/* definitions for field: Reserved2 in reg: Control register */
#define ACQ_CORE_CTL_RESERVED2_MASK           WBGEN2_GEN_MASK(17, 15)
#define ACQ_CORE_CTL_RESERVED2_SHIFT          17
#define ACQ_CORE_CTL_RESERVED2_W(value)       WBGEN2_GEN_WRITE(value, 17, 15)
#define ACQ_CORE_CTL_RESERVED2_R(reg)         WBGEN2_GEN_READ(reg, 17, 15)

/* definitions for register: Status register */

/* definitions for field: State machine status in reg: Status register */
#define ACQ_CORE_STA_FSM_STATE_MASK           WBGEN2_GEN_MASK(0, 3)
#define ACQ_CORE_STA_FSM_STATE_SHIFT          0
#define ACQ_CORE_STA_FSM_STATE_W(value)       WBGEN2_GEN_WRITE(value, 0, 3)
#define ACQ_CORE_STA_FSM_STATE_R(reg)         WBGEN2_GEN_READ(reg, 0, 3)

/* definitions for field: FSM acquisition status in reg: Status register */
#define ACQ_CORE_STA_FSM_ACQ_DONE             WBGEN2_GEN_MASK(3, 1)

/* definitions for field: Reserved in reg: Status register */
#define ACQ_CORE_STA_RESERVED1_MASK           WBGEN2_GEN_MASK(4, 4)
#define ACQ_CORE_STA_RESERVED1_SHIFT          4
#define ACQ_CORE_STA_RESERVED1_W(value)       WBGEN2_GEN_WRITE(value, 4, 4)
#define ACQ_CORE_STA_RESERVED1_R(reg)         WBGEN2_GEN_READ(reg, 4, 4)

/* definitions for field: External flow control transfer status in reg: Status register */
#define ACQ_CORE_STA_FC_TRANS_DONE            WBGEN2_GEN_MASK(8, 1)

/* definitions for field: External flow control FIFO full status in reg: Status register */
#define ACQ_CORE_STA_FC_FULL                  WBGEN2_GEN_MASK(9, 1)

/* definitions for field: Reserved in reg: Status register */
#define ACQ_CORE_STA_RESERVED2_MASK           WBGEN2_GEN_MASK(10, 6)
#define ACQ_CORE_STA_RESERVED2_SHIFT          10
#define ACQ_CORE_STA_RESERVED2_W(value)       WBGEN2_GEN_WRITE(value, 10, 6)
#define ACQ_CORE_STA_RESERVED2_R(reg)         WBGEN2_GEN_READ(reg, 10, 6)

/* definitions for field: DDR3 transfer status in reg: Status register */
#define ACQ_CORE_STA_DDR3_TRANS_DONE          WBGEN2_GEN_MASK(16, 1)

/* definitions for field: Reserved in reg: Status register */
#define ACQ_CORE_STA_RESERVED3_MASK           WBGEN2_GEN_MASK(17, 15)
#define ACQ_CORE_STA_RESERVED3_SHIFT          17
#define ACQ_CORE_STA_RESERVED3_W(value)       WBGEN2_GEN_WRITE(value, 17, 15)
#define ACQ_CORE_STA_RESERVED3_R(reg)         WBGEN2_GEN_READ(reg, 17, 15)

/* definitions for register: Trigger configuration */

/* definitions for field: Hardware trigger selection in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_HW_TRIG_SEL         WBGEN2_GEN_MASK(0, 1)

/* definitions for field: Hardware trigger polarity in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_HW_TRIG_POL         WBGEN2_GEN_MASK(1, 1)

/* definitions for field: Hardware trigger enable in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_HW_TRIG_EN          WBGEN2_GEN_MASK(2, 1)

/* definitions for field: Software trigger enable in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_SW_TRIG_EN          WBGEN2_GEN_MASK(3, 1)

/* definitions for field: Channel selection for internal trigger in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_INT_TRIG_SEL_MASK   WBGEN2_GEN_MASK(4, 5)
#define ACQ_CORE_TRIG_CFG_INT_TRIG_SEL_SHIFT  4
#define ACQ_CORE_TRIG_CFG_INT_TRIG_SEL_W(value) WBGEN2_GEN_WRITE(value, 4, 5)
#define ACQ_CORE_TRIG_CFG_INT_TRIG_SEL_R(reg) WBGEN2_GEN_READ(reg, 4, 5)

/* definitions for field: Reserved in reg: Trigger configuration */
#define ACQ_CORE_TRIG_CFG_RESERVED_MASK       WBGEN2_GEN_MASK(9, 23)
#define ACQ_CORE_TRIG_CFG_RESERVED_SHIFT      9
#define ACQ_CORE_TRIG_CFG_RESERVED_W(value)   WBGEN2_GEN_WRITE(value, 9, 23)
#define ACQ_CORE_TRIG_CFG_RESERVED_R(reg)     WBGEN2_GEN_READ(reg, 9, 23)

/* definitions for register: Trigger data config threshold */

/* definitions for field: Internal trigger threshold glitch filter in reg: Trigger data config threshold */
#define ACQ_CORE_TRIG_DATA_CFG_THRES_FILT_MASK WBGEN2_GEN_MASK(0, 8)
#define ACQ_CORE_TRIG_DATA_CFG_THRES_FILT_SHIFT 0
#define ACQ_CORE_TRIG_DATA_CFG_THRES_FILT_W(value) WBGEN2_GEN_WRITE(value, 0, 8)
#define ACQ_CORE_TRIG_DATA_CFG_THRES_FILT_R(reg) WBGEN2_GEN_READ(reg, 0, 8)

/* definitions for field: Reserved in reg: Trigger data config threshold */
#define ACQ_CORE_TRIG_DATA_CFG_RESERVED_MASK  WBGEN2_GEN_MASK(8, 24)
#define ACQ_CORE_TRIG_DATA_CFG_RESERVED_SHIFT 8
#define ACQ_CORE_TRIG_DATA_CFG_RESERVED_W(value) WBGEN2_GEN_WRITE(value, 8, 24)
#define ACQ_CORE_TRIG_DATA_CFG_RESERVED_R(reg) WBGEN2_GEN_READ(reg, 8, 24)

/* definitions for register: Trigger data threshold */

/* definitions for register: Trigger delay */

/* definitions for register: Software trigger */

/* definitions for register: Number of shots */

/* definitions for field: Number of shots in reg: Number of shots */
#define ACQ_CORE_SHOTS_NB_MASK                WBGEN2_GEN_MASK(0, 16)
#define ACQ_CORE_SHOTS_NB_SHIFT               0
#define ACQ_CORE_SHOTS_NB_W(value)            WBGEN2_GEN_WRITE(value, 0, 16)
#define ACQ_CORE_SHOTS_NB_R(reg)              WBGEN2_GEN_READ(reg, 0, 16)

/* definitions for field: Reserved in reg: Number of shots */
#define ACQ_CORE_SHOTS_RESERVED_MASK          WBGEN2_GEN_MASK(16, 16)
#define ACQ_CORE_SHOTS_RESERVED_SHIFT         16
#define ACQ_CORE_SHOTS_RESERVED_W(value)      WBGEN2_GEN_WRITE(value, 16, 16)
#define ACQ_CORE_SHOTS_RESERVED_R(reg)        WBGEN2_GEN_READ(reg, 16, 16)

/* definitions for register: Trigger address register */

/* definitions for register: Pre-trigger samples */

/* definitions for register: Post-trigger samples */

/* definitions for register: Samples counter */

/* definitions for register: DDR3 Start Address */

/* definitions for register: DDR3 End Address */

/* definitions for register: Acquisition channel control */

/* definitions for field: Acquisition channel selection in reg: Acquisition channel control */
#define ACQ_CORE_ACQ_CHAN_CTL_WHICH_MASK      WBGEN2_GEN_MASK(0, 5)
#define ACQ_CORE_ACQ_CHAN_CTL_WHICH_SHIFT     0
#define ACQ_CORE_ACQ_CHAN_CTL_WHICH_W(value)  WBGEN2_GEN_WRITE(value, 0, 5)
#define ACQ_CORE_ACQ_CHAN_CTL_WHICH_R(reg)    WBGEN2_GEN_READ(reg, 0, 5)

/* definitions for field: Reserved in reg: Acquisition channel control */
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED_MASK   WBGEN2_GEN_MASK(5, 3)
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED_SHIFT  5
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED_W(value) WBGEN2_GEN_WRITE(value, 5, 3)
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED_R(reg) WBGEN2_GEN_READ(reg, 5, 3)

/* definitions for field: Data-driven channel selection in reg: Acquisition channel control */
#define ACQ_CORE_ACQ_CHAN_CTL_DTRIG_WHICH_MASK WBGEN2_GEN_MASK(8, 5)
#define ACQ_CORE_ACQ_CHAN_CTL_DTRIG_WHICH_SHIFT 8
#define ACQ_CORE_ACQ_CHAN_CTL_DTRIG_WHICH_W(value) WBGEN2_GEN_WRITE(value, 8, 5)
#define ACQ_CORE_ACQ_CHAN_CTL_DTRIG_WHICH_R(reg) WBGEN2_GEN_READ(reg, 8, 5)

/* definitions for field: Reserved1 in reg: Acquisition channel control */
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED1_MASK  WBGEN2_GEN_MASK(13, 19)
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED1_SHIFT 13
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED1_W(value) WBGEN2_GEN_WRITE(value, 13, 19)
#define ACQ_CORE_ACQ_CHAN_CTL_RESERVED1_R(reg) WBGEN2_GEN_READ(reg, 13, 19)
/* FIXME: The FPGA firmware is BYTE/WORD addressed depending on the board */
/* [0x0]: REG Control register */
#define ACQ_CORE_REG_CTL (0x00000000 >> __WR_SHIFT_FIX__)
/* [0x4]: REG Status register */
#define ACQ_CORE_REG_STA (0x00000004 >> __WR_SHIFT_FIX__)
/* [0x8]: REG Trigger configuration */
#define ACQ_CORE_REG_TRIG_CFG (0x00000008 >> __WR_SHIFT_FIX__)
/* [0xc]: REG Trigger data config threshold */
#define ACQ_CORE_REG_TRIG_DATA_CFG (0x0000000c >> __WR_SHIFT_FIX__)
/* [0x10]: REG Trigger data threshold */
#define ACQ_CORE_REG_TRIG_DATA_THRES (0x00000010 >> __WR_SHIFT_FIX__)
/* [0x14]: REG Trigger delay */
#define ACQ_CORE_REG_TRIG_DLY (0x00000014 >> __WR_SHIFT_FIX__)
/* [0x18]: REG Software trigger */
#define ACQ_CORE_REG_SW_TRIG (0x00000018 >> __WR_SHIFT_FIX__)
/* [0x1c]: REG Number of shots */
#define ACQ_CORE_REG_SHOTS (0x0000001c >> __WR_SHIFT_FIX__)
/* [0x20]: REG Trigger address register */
#define ACQ_CORE_REG_TRIG_POS (0x00000020 >> __WR_SHIFT_FIX__)
/* [0x24]: REG Pre-trigger samples */
#define ACQ_CORE_REG_PRE_SAMPLES (0x00000024 >> __WR_SHIFT_FIX__)
/* [0x28]: REG Post-trigger samples */
#define ACQ_CORE_REG_POST_SAMPLES (0x00000028 >> __WR_SHIFT_FIX__)
/* [0x2c]: REG Samples counter */
#define ACQ_CORE_REG_SAMPLES_CNT (0x0000002c >> __WR_SHIFT_FIX__)
/* [0x30]: REG DDR3 Start Address */
#define ACQ_CORE_REG_DDR3_START_ADDR (0x00000030 >> __WR_SHIFT_FIX__)
/* [0x34]: REG DDR3 End Address */
#define ACQ_CORE_REG_DDR3_END_ADDR (0x00000034 >> __WR_SHIFT_FIX__)
/* [0x38]: REG Acquisition channel control */
#define ACQ_CORE_REG_ACQ_CHAN_CTL (0x00000038 >> __WR_SHIFT_FIX__)
#endif
