/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU GPL, version 3 or any later version.
 */

#ifndef _BPM_CLIENT_RW_PARAM_H_
#define _BPM_CLIENT_RW_PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define READ_MODE                   1
#define WRITE_MODE                  0

#define MSG_FULL_SIZE               3       /* 3 frames */
#define MSG_ERR_CODE_SIZE           1       /* 1 frame */

/* Write function name */
#define PARAM_FUNC_CLIENT_NAME_WRITE(reg)                                       \
    bpm_set ## _ ## reg

/* Read function name */
#define PARAM_FUNC_CLIENT_NAME_READ(reg)                                        \
    bpm_get ## _ ## reg

/* Write function declaration */
#define PARAM_FUNC_CLIENT_WRITE(reg)                                            \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_WRITE(reg) (bpm_client_t *self,     \
            char *service, uint32_t reg)

#define PARAM_FUNC_CLIENT_WRITE_DOUBLE(reg)                                     \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_WRITE(reg) (bpm_client_t *self,     \
            char *service, double reg)

#define PARAM_FUNC_CLIENT_WRITE2(reg, param1, param2)                           \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_WRITE(reg) (bpm_client_t *self,     \
            char *service, uint32_t param1, uint32_t param2)

#define PARAM_FUNC_CLIENT_WRITE_GEN(param)                                      \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_WRITE(param) (bpm_client_t *self,     \
            char *service, void *param, size_t size)

/* Read function declaration */
#define PARAM_FUNC_CLIENT_READ(reg)                                             \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_READ(reg) (bpm_client_t *self,      \
            char *service, uint32_t *reg)

#define PARAM_FUNC_CLIENT_READ_DOUBLE(reg)                                      \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_READ(reg) (bpm_client_t *self,      \
            char *service, double *reg)

#define PARAM_FUNC_CLIENT_READ2(reg, param1, param2)                            \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_READ(reg) (bpm_client_t *self,      \
            char *service, uint32_t *param1, uint32_t *param2)

#define PARAM_FUNC_CLIENT_WRITE_READ(reg, param1, param_out)                    \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_READ(reg) (bpm_client_t *self,      \
            char *service, uint32_t param1, uint32_t *param_out)

#define PARAM_FUNC_CLIENT_READ_GEN(param)                                       \
    bpm_client_err_e PARAM_FUNC_CLIENT_NAME_READ(param) (bpm_client_t *self,    \
            char *service, void *param, size_t size)

/* Low-level protocol functions */
bpm_client_err_e param_client_send_gen_rw (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t rw, void *param1, size_t size1,
        void *param2, size_t size2);
bpm_client_err_e param_client_recv_rw (bpm_client_t *self, char *service,
    zmsg_t **report);

/* Write functions */
bpm_client_err_e param_client_write_gen (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t rw, void *param1, size_t size1,
        void *param2, size_t size2);
bpm_client_err_e param_client_write_raw (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t param1, uint32_t param2);

bpm_client_err_e param_client_write (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t param1);
bpm_client_err_e param_client_write2 (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t param1, uint32_t param2);
bpm_client_err_e param_client_write_double (bpm_client_t *self, char *service,
        uint32_t operation, double param1);
bpm_client_err_e param_client_write_double2 (bpm_client_t *self, char *service,
        uint32_t operation, double param1, double param2);

/* Read functions */
bpm_client_err_e param_client_read_gen (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t rw, void *param1, size_t size1,
        void *param2, size_t size2, void *param_out, size_t size_out);

bpm_client_err_e param_client_read (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t *param_out);
bpm_client_err_e param_client_write_read (bpm_client_t *self, char *service,
        uint32_t operation, uint32_t param1, uint32_t *param_out);
bpm_client_err_e param_client_read_double (bpm_client_t *self, char *service,
        uint32_t operation, double *param_out);
bpm_client_err_e param_client_write_read_double (bpm_client_t *self, char *service,
        uint32_t operation, double param1, double *param_out);

/* Utility functions */
zmsg_t *param_client_recv_timeout (bpm_client_t *self);

#ifdef __cplusplus
}
#endif

#endif
