sm_io_afc_diag_DIR = hal/sm_io/modules/afc_diag

sm_io_afc_diag_OBJS = $(sm_io_afc_diag_DIR)/sm_io_afc_diag_core.o \
		 $(sm_io_afc_diag_DIR)/sm_io_afc_diag_exp.o \
		 $(sm_io_afc_diag_DIR)/sm_io_afc_diag_exports.o \
		 $(sm_io_afc_diag_DIR)/sm_io_afc_diag_defaults.o

sm_io_afc_diag_INCLUDE_DIRS = $(sm_io_afc_diag_DIR)
