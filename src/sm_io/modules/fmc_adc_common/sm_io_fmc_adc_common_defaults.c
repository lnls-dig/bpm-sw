/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU GPL, version 3 or any later version.
 */

#include "bpm_server.h"
/* Private headers */
#include "sm_io_fmc_adc_common_defaults.h"

/* Undef ASSERT_ALLOC to avoid conflicting with other ASSERT_ALLOC */
#ifdef ASSERT_TEST
#undef ASSERT_TEST
#endif
#define ASSERT_TEST(test_boolean, err_str, err_goto_label, /* err_core */ ...)  \
    ASSERT_HAL_TEST(test_boolean, SM_IO, "[sm_io:fmc_adc_common_defaults]",     \
            err_str, err_goto_label, /* err_core */ __VA_ARGS__)

#ifdef ASSERT_ALLOC
#undef ASSERT_ALLOC
#endif
#define ASSERT_ALLOC(ptr, err_goto_label, /* err_core */ ...)                   \
    ASSERT_HAL_ALLOC(ptr, SM_IO, "[sm_io:fmc_adc_common_defaults]",             \
            smio_err_str(SMIO_ERR_ALLOC),                                       \
            err_goto_label, /* err_core */ __VA_ARGS__)

#ifdef CHECK_ERR
#undef CHECK_ERR
#endif
#define CHECK_ERR(err, err_type)                                                \
    CHECK_HAL_ERR(err, SM_IO, "[sm_io:fmc_adc_common_defaults]",                \
            smio_err_str (err_type))

#define SMIO_FMC_ADC_COMMON_LIBBPMCLIENT_LOG_MODE                "a"

/* We use the actual libclient to send and configure our default values,
 * maintaining internal consistency. So, in fact, we are sending ourselves
 * a message containing the default values. Because of this approach, we
 * only get to default our values when the functions are already exported
 * to the broker, which happens on a late stage. This could cause a fast
 * client to get an inconsistent state from our server */
/* TODO: Avoid exporting the functions before we have initialized
 * our server with the default values */
smio_err_e fmc_adc_common_config_defaults (char *broker_endp, char *service,
       const char *log_file_name)
{
    (void) log_file_name;
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_INFO, "[sm_io:fmc_adc_common_defaults] Configuring SMIO "
            "FMC_ADC_COMMON with default values ...\n");
    bpm_client_err_e client_err = BPM_CLIENT_SUCCESS;
    smio_err_e err = SMIO_SUCCESS;

    bpm_client_t *config_client = bpm_client_new_log_mode (broker_endp, 0,
            log_file_name, SMIO_FMC_ADC_COMMON_LIBBPMCLIENT_LOG_MODE);
    ASSERT_ALLOC(config_client, err_alloc_client);

    client_err = bpm_set_trig_dir (config_client, service, FMC_ADC_COMMON_DFLT_TRIG_DIR);
    ASSERT_TEST(client_err == BPM_CLIENT_SUCCESS, "Could not set FMC TRIG DIR function",
            err_param_set, SMIO_ERR_CONFIG_DFLT);

err_param_set:
    bpm_client_destroy (&config_client);
err_alloc_client:
    DBE_DEBUG (DBG_SM_IO | DBG_LVL_INFO, "[sm_io:fmc_adc_common_defaults] Exiting Config thread %s\n",
        service);
    return err;
}
