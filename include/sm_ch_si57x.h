/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU LGPL, version 3 or any later version.
 */

#ifndef _SM_CH_SI57X_H_
#define _SM_CH_SI57X_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************** Our methods *****************/

/* Creates a new instance of the SMCH SI57X */
smch_si57x_t * smch_si57x_new (smio_t *parent, uint64_t base, uint32_t addr,
        int verbose);
/* Destroy an instance of the SMCH SI57X */
smch_err_e smch_si57x_destroy (smch_si57x_t **self_p);

/* Read/Write to SI57X */
smch_err_e smch_si57x_write_8 (smch_si57x_t *self, uint8_t addr,
        const uint8_t *data);
smch_err_e smch_si57x_write_block (smch_si57x_t *self, uint8_t addr,
        const uint8_t *data, size_t size);
smch_err_e smch_si57x_read_8 (smch_si57x_t *self, uint8_t addr,
        uint8_t *data);
smch_err_e smch_si57x_read_block (smch_si57x_t *self, uint8_t addr,
        uint8_t *data, size_t size);

/* Probe bus for I2C devices */
ssize_t smch_si57x_probe_bus (smch_si57x_t *self);

/* Get Si57X divider values */
smch_err_e smch_si57x_get_divs (smch_si57x_t *self, uint64_t *rfreq,
        unsigned int *n1, unsigned int *hs_div);
/* Reset Si57X to its default factory values */
smch_err_e smch_si57x_get_defaults (smch_si57x_t *self, double fout);

/* Setup new frequency */
smch_err_e smch_si57x_set_freq (smch_si57x_t *self, double frequency);

#ifdef __cplusplus
}
#endif

#endif