#ifndef _DDR3_MAP_AFCV3_H_
#define _DDR3_MAP_AFCV3_H_

#include "acq_chan_afcv3.h"
#include "hal_varg.h"

/* Does the acquisition channel gets a memory region? */
#define DDR3_MEM_BOOL(MEM_SIZE)         IF(MEM_SIZE > 0)(1, 0)

/* Start of the acquisition memory address */
#define DDR3_ACQ_START_ADDR             0x0

/* Dummy region
 * Size: 0 DDR3 regions */
#define DDR3_DUMMY_INIT0_SAMPLE_SIZE    0
#define DDR3_DUMMY_INIT0_MEM_SIZE       0

#define DDR3_DUMMY_INIT0_MEM_BOOL       DDR3_MEM_BOOL(DDR3_DUMMY_INIT0_MEM_SIZE)
#define DDR3_DUMMY_INIT0_START_ADDR     DDR3_ACQ_START_ADDR
#define DDR3_DUMMY_INIT0_END_ADDR       (DDR3_DUMMY_INIT0_START_ADDR + DDR3_DUMMY_INIT0_MEM_SIZE*MEM_REGION_SIZE)
#define DDR3_DUMMY_INIT0_MAX_SAMPLES    (DDR3_DUMMY_INIT0_END_ADDR-DDR3_DUMMY_INIT0_START_ADDR)

/************************ Acquistion 0 Channel Parameters **************/

/* ADC 0
 * Size: 2 DDR3 regions */
#define DDR3_ADC0_SAMPLE_SIZE           ADC0_SAMPLE_SIZE
#define DDR3_ADC0_MEM_SIZE              2

#define DDR3_ADC0_MEM_BOOL              DDR3_MEM_BOOL(DDR3_ADC0_MEM_SIZE)
#define DDR3_ADC0_START_ADDR            (DDR3_DUMMY_INIT0_START_ADDR + DDR3_ADC0_MEM_BOOL*DDR3_DUMMY_INIT0_SAMPLE_SIZE)
#define DDR3_ADC0_END_ADDR              (DDR3_ADC0_START_ADDR + DDR3_ADC0_MEM_SIZE*MEM_REGION_SIZE - DDR3_ADC0_MEM_BOOL*DDR3_ADC0_SAMPLE_SIZE)
#define DDR3_ADC0_MAX_SAMPLES           ((DDR3_ADC0_END_ADDR-DDR3_ADC0_START_ADDR) / DDR3_ADC0_SAMPLE_SIZE)

/* MIXER 0
 * Size: 1 DDR3 regions */
#define DDR3_MIX0_SAMPLE_SIZE           MIX0_SAMPLE_SIZE
#define DDR3_MIX0_MEM_SIZE              1

#define DDR3_MIX0_MEM_BOOL              DDR3_MEM_BOOL(DDR3_MIX0_MEM_SIZE)
#define DDR3_MIX0_START_ADDR            (DDR3_ADC0_END_ADDR + DDR3_MIX0_MEM_BOOL*DDR3_ADC0_SAMPLE_SIZE)
#define DDR3_MIX0_END_ADDR              (DDR3_MIX0_START_ADDR + DDR3_MIX0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MIX0_MEM_BOOL*DDR3_MIX0_SAMPLE_SIZE)
#define DDR3_MIX0_MAX_SAMPLES           ((DDR3_MIX0_END_ADDR-DDR3_MIX0_START_ADDR) / DDR3_MIX0_SAMPLE_SIZE)

/* TBT 0 AMP
 * Size: 2 DDR3 regions */
#define DDR3_TBTAMP0_SAMPLE_SIZE        TBTAMP0_SAMPLE_SIZE
#define DDR3_TBTAMP0_MEM_SIZE           2

#define DDR3_TBTAMP0_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTAMP0_MEM_SIZE)
#define DDR3_TBTAMP0_START_ADDR         (DDR3_MIX0_END_ADDR + DDR3_TBTAMP0_MEM_BOOL*DDR3_MIX0_SAMPLE_SIZE)
#define DDR3_TBTAMP0_END_ADDR           (DDR3_TBTAMP0_START_ADDR + DDR3_TBTAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTAMP0_MEM_BOOL*DDR3_TBTAMP0_SAMPLE_SIZE)
#define DDR3_TBTAMP0_MAX_SAMPLES        ((DDR3_TBTAMP0_END_ADDR-DDR3_TBTAMP0_START_ADDR) / DDR3_TBTAMP0_SAMPLE_SIZE)

/* TBT 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_TBTPOS0_SAMPLE_SIZE        TBTPOS0_SAMPLE_SIZE
#define DDR3_TBTPOS0_MEM_SIZE           0

#define DDR3_TBTPOS0_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTPOS0_MEM_SIZE)
#define DDR3_TBTPOS0_START_ADDR         (DDR3_TBTAMP0_END_ADDR + DDR3_TBTPOS0_MEM_BOOL*DDR3_TBTAMP0_SAMPLE_SIZE)
#define DDR3_TBTPOS0_END_ADDR           (DDR3_TBTPOS0_START_ADDR + DDR3_TBTPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTPOS0_MEM_BOOL*DDR3_TBTPOS0_SAMPLE_SIZE)
#define DDR3_TBTPOS0_MAX_SAMPLES        ((DDR3_TBTPOS0_END_ADDR-DDR3_TBTPOS0_START_ADDR) / DDR3_TBTPOS0_SAMPLE_SIZE)

/* FOFB 0 AMP
 * Size: 2 DDR3 regions */
#define DDR3_FOFBAMP0_SAMPLE_SIZE       FOFBAMP0_SAMPLE_SIZE
#define DDR3_FOFBAMP0_MEM_SIZE          2

#define DDR3_FOFBAMP0_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBAMP0_MEM_SIZE)
#define DDR3_FOFBAMP0_START_ADDR        (DDR3_TBTPOS0_END_ADDR + DDR3_FOFBAMP0_MEM_BOOL*DDR3_TBTPOS0_SAMPLE_SIZE)
#define DDR3_FOFBAMP0_END_ADDR          (DDR3_FOFBAMP0_START_ADDR + DDR3_FOFBAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBAMP0_MEM_BOOL*DDR3_FOFBAMP0_SAMPLE_SIZE)
#define DDR3_FOFBAMP0_MAX_SAMPLES       ((DDR3_FOFBAMP0_END_ADDR-DDR3_FOFBAMP0_START_ADDR) / DDR3_FOFBAMP0_SAMPLE_SIZE)

/* FOFB 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_FOFBPOS0_SAMPLE_SIZE       FOFBPOS0_SAMPLE_SIZE
#define DDR3_FOFBPOS0_MEM_SIZE          0

#define DDR3_FOFBPOS0_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBPOS0_MEM_SIZE)
#define DDR3_FOFBPOS0_START_ADDR        (DDR3_FOFBAMP0_END_ADDR + DDR3_FOFBPOS0_MEM_BOOL*DDR3_FOFBAMP0_SAMPLE_SIZE)
#define DDR3_FOFBPOS0_END_ADDR          (DDR3_FOFBPOS0_START_ADDR + DDR3_FOFBPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBPOS0_MEM_BOOL*DDR3_FOFBPOS0_SAMPLE_SIZE)
#define DDR3_FOFBPOS0_MAX_SAMPLES       ((DDR3_FOFBPOS0_END_ADDR-DDR3_FOFBPOS0_START_ADDR) / DDR3_FOFBPOS0_SAMPLE_SIZE)

 /* MONIT 0 AMP
 * Size: 0 DDR3 regions */
#define DDR3_MONITAMP0_SAMPLE_SIZE      MONITAMP0_SAMPLE_SIZE
#define DDR3_MONITAMP0_MEM_SIZE         0

#define DDR3_MONITAMP0_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITAMP0_MEM_SIZE)
#define DDR3_MONITAMP0_START_ADDR       (DDR3_FOFBPOS0_END_ADDR + DDR3_MONITAMP0_MEM_BOOL*DDR3_FOFBPOS0_SAMPLE_SIZE)
#define DDR3_MONITAMP0_END_ADDR         (DDR3_MONITAMP0_START_ADDR + DDR3_MONITAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITAMP0_MEM_BOOL*DDR3_MONITAMP0_SAMPLE_SIZE)
#define DDR3_MONITAMP0_MAX_SAMPLES      ((DDR3_MONITAMP0_END_ADDR-DDR3_MONITAMP0_START_ADDR) / DDR3_MONITAMP0_SAMPLE_SIZE)

/* MONIT 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_MONITPOS0_SAMPLE_SIZE      MONITPOS0_SAMPLE_SIZE
#define DDR3_MONITPOS0_MEM_SIZE         0

#define DDR3_MONITPOS0_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITPOS0_MEM_SIZE)
#define DDR3_MONITPOS0_START_ADDR       (DDR3_MONITAMP0_END_ADDR + DDR3_MONITPOS0_MEM_BOOL*DDR3_MONITAMP0_SAMPLE_SIZE)
#define DDR3_MONITPOS0_END_ADDR         (DDR3_MONITPOS0_START_ADDR + DDR3_MONITPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITPOS0_MEM_BOOL*DDR3_MONITPOS0_SAMPLE_SIZE)
#define DDR3_MONITPOS0_MAX_SAMPLES      ((DDR3_MONITPOS0_END_ADDR-DDR3_MONITPOS0_START_ADDR) / DDR3_MONITPOS0_SAMPLE_SIZE)

/* MONIT1 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_MONIT1POS0_SAMPLE_SIZE     MONIT1POS0_SAMPLE_SIZE
#define DDR3_MONIT1POS0_MEM_SIZE        0

#define DDR3_MONIT1POS0_MEM_BOOL        DDR3_MEM_BOOL(DDR3_MONIT1POS0_MEM_SIZE)
#define DDR3_MONIT1POS0_START_ADDR      (DDR3_MONITPOS0_END_ADDR + DDR3_MONIT1POS0_MEM_BOOL*DDR3_MONITPOS0_SAMPLE_SIZE)
#define DDR3_MONIT1POS0_END_ADDR        (DDR3_MONIT1POS0_START_ADDR + DDR3_MONIT1POS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONIT1POS0_MEM_BOOL*DDR3_MONIT1POS0_SAMPLE_SIZE)
#define DDR3_MONIT1POS0_MAX_SAMPLES     ((DDR3_MONIT1POS0_END_ADDR-DDR3_MONIT1POS0_START_ADDR) / DDR3_MONIT1POS0_SAMPLE_SIZE)

/* End 0 Dummy region
 * Size: 0 DDR3 regions */
#define DDR3_DUMMY_END0_SAMPLE_SIZE     MONIT1POS0_SAMPLE_SIZE
#define DDR3_DUMMY_END0_MEM_SIZE        0

#define DDR3_DUMMY_END0_MEM_BOOL        DDR3_MEM_BOOL(DDR3_DUMMY_END0_MEM_SIZE)
#define DDR3_DUMMY_END0_START_ADDR      DDR3_MONIT1POS0_END_ADDR
#define DDR3_DUMMY_END0_END_ADDR        (DDR3_DUMMY_END0_START_ADDR + DDR3_DUMMY_END0_MEM_SIZE*MEM_REGION_SIZE)
#define DDR3_DUMMY_END0_MAX_SAMPLES     (DDR3_DUMMY_END0_END_ADDR-DDR3_DUMMY_END0_START_ADDR)

/************************ Acquistion 1 Channel Parameters **************/

/* ADC 1
 * Size: 2 DDR3 regions */
#define DDR3_ADC1_SAMPLE_SIZE           ADC1_SAMPLE_SIZE
#define DDR3_ADC1_MEM_SIZE              2

#define DDR3_ADC1_MEM_BOOL              DDR3_MEM_BOOL(DDR3_ADC1_MEM_SIZE)
#define DDR3_ADC1_START_ADDR            (DDR3_DUMMY_END0_START_ADDR + DDR3_ADC1_MEM_BOOL*DDR3_DUMMY_END0_SAMPLE_SIZE)
#define DDR3_ADC1_END_ADDR              (DDR3_ADC1_START_ADDR + DDR3_ADC1_MEM_SIZE*MEM_REGION_SIZE - DDR3_ADC1_MEM_BOOL*DDR3_ADC1_SAMPLE_SIZE)
#define DDR3_ADC1_MAX_SAMPLES           ((DDR3_ADC1_END_ADDR-DDR3_ADC1_START_ADDR) / DDR3_ADC1_SAMPLE_SIZE)

/* MIXER 1
 * Size: 1 DDR3 regions */
#define DDR3_MIX1_SAMPLE_SIZE           MIX1_SAMPLE_SIZE
#define DDR3_MIX1_MEM_SIZE              1

#define DDR3_MIX1_MEM_BOOL              DDR3_MEM_BOOL(DDR3_MIX1_MEM_SIZE)
#define DDR3_MIX1_START_ADDR            (DDR3_ADC1_END_ADDR + DDR3_MIX1_MEM_BOOL*DDR3_ADC1_SAMPLE_SIZE)
#define DDR3_MIX1_END_ADDR              (DDR3_MIX1_START_ADDR + DDR3_MIX1_MEM_SIZE*MEM_REGION_SIZE - DDR3_MIX1_MEM_BOOL*DDR3_MIX1_SAMPLE_SIZE)
#define DDR3_MIX1_MAX_SAMPLES           ((DDR3_MIX1_END_ADDR-DDR3_MIX1_START_ADDR) / DDR3_MIX1_SAMPLE_SIZE)

/* TBT 1 AMP
 * Size: 2 DDR3 regions */
#define DDR3_TBTAMP1_SAMPLE_SIZE        TBTAMP1_SAMPLE_SIZE
#define DDR3_TBTAMP1_MEM_SIZE           2

#define DDR3_TBTAMP1_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTAMP1_MEM_SIZE)
#define DDR3_TBTAMP1_START_ADDR         (DDR3_MIX1_END_ADDR + DDR3_TBTAMP1_MEM_BOOL*DDR3_MIX1_SAMPLE_SIZE)
#define DDR3_TBTAMP1_END_ADDR           (DDR3_TBTAMP1_START_ADDR + DDR3_TBTAMP1_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTAMP1_MEM_BOOL*DDR3_TBTAMP1_SAMPLE_SIZE)
#define DDR3_TBTAMP1_MAX_SAMPLES        ((DDR3_TBTAMP1_END_ADDR-DDR3_TBTAMP1_START_ADDR) / DDR3_TBTAMP1_SAMPLE_SIZE)

/* TBT 1 POS
 * Size: 1 DDR3 regions */
#define DDR3_TBTPOS1_SAMPLE_SIZE        TBTPOS1_SAMPLE_SIZE
#define DDR3_TBTPOS1_MEM_SIZE           0

#define DDR3_TBTPOS1_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTPOS1_MEM_SIZE)
#define DDR3_TBTPOS1_START_ADDR         (DDR3_TBTAMP1_END_ADDR + DDR3_TBTPOS1_MEM_BOOL*DDR3_TBTAMP1_SAMPLE_SIZE)
#define DDR3_TBTPOS1_END_ADDR           (DDR3_TBTPOS1_START_ADDR + DDR3_TBTPOS1_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTPOS1_MEM_BOOL*DDR3_TBTPOS1_SAMPLE_SIZE)
#define DDR3_TBTPOS1_MAX_SAMPLES        ((DDR3_TBTPOS1_END_ADDR-DDR3_TBTPOS1_START_ADDR) / DDR3_TBTPOS1_SAMPLE_SIZE)

/* FOFB 1 AMP
 * Size: 2 DDR3 regions */
#define DDR3_FOFBAMP1_SAMPLE_SIZE       FOFBAMP1_SAMPLE_SIZE
#define DDR3_FOFBAMP1_MEM_SIZE          2

#define DDR3_FOFBAMP1_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBAMP1_MEM_SIZE)
#define DDR3_FOFBAMP1_START_ADDR        (DDR3_TBTPOS1_END_ADDR + DDR3_FOFBAMP1_MEM_BOOL*DDR3_TBTPOS1_SAMPLE_SIZE)
#define DDR3_FOFBAMP1_END_ADDR          (DDR3_FOFBAMP1_START_ADDR + DDR3_FOFBAMP1_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBAMP1_MEM_BOOL*DDR3_FOFBAMP1_SAMPLE_SIZE)
#define DDR3_FOFBAMP1_MAX_SAMPLES       ((DDR3_FOFBAMP1_END_ADDR-DDR3_FOFBAMP1_START_ADDR) / DDR3_FOFBAMP1_SAMPLE_SIZE)

/* FOFB 1 POS
 * Size: 1 DDR3 regions */
#define DDR3_FOFBPOS1_SAMPLE_SIZE       FOFBPOS1_SAMPLE_SIZE
#define DDR3_FOFBPOS1_MEM_SIZE          0

#define DDR3_FOFBPOS1_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBPOS1_MEM_SIZE)
#define DDR3_FOFBPOS1_START_ADDR        (DDR3_FOFBAMP1_END_ADDR + DDR3_FOFBPOS1_MEM_BOOL*DDR3_FOFBAMP1_SAMPLE_SIZE)
#define DDR3_FOFBPOS1_END_ADDR          (DDR3_FOFBPOS1_START_ADDR + DDR3_FOFBPOS1_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBPOS1_MEM_BOOL*DDR3_FOFBPOS1_SAMPLE_SIZE)
#define DDR3_FOFBPOS1_MAX_SAMPLES       ((DDR3_FOFBPOS1_END_ADDR-DDR3_FOFBPOS1_START_ADDR) / DDR3_FOFBPOS1_SAMPLE_SIZE)

 /* MONIT 1 AMP
 * Size: 1 DDR3 regions */
#define DDR3_MONITAMP1_SAMPLE_SIZE      MONITAMP1_SAMPLE_SIZE
#define DDR3_MONITAMP1_MEM_SIZE         0

#define DDR3_MONITAMP1_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITAMP1_MEM_SIZE)
#define DDR3_MONITAMP1_START_ADDR       (DDR3_FOFBPOS1_END_ADDR + DDR3_MONITAMP1_MEM_BOOL*DDR3_FOFBPOS1_SAMPLE_SIZE)
#define DDR3_MONITAMP1_END_ADDR         (DDR3_MONITAMP1_START_ADDR + DDR3_MONITAMP1_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITAMP1_MEM_BOOL*DDR3_MONITAMP1_SAMPLE_SIZE)
#define DDR3_MONITAMP1_MAX_SAMPLES      ((DDR3_MONITAMP1_END_ADDR-DDR3_MONITAMP1_START_ADDR) / DDR3_MONITAMP1_SAMPLE_SIZE)

/* MONIT 1 POS
 * Size: 1 DDR3 regions */
#define DDR3_MONITPOS1_SAMPLE_SIZE      MONITPOS1_SAMPLE_SIZE
#define DDR3_MONITPOS1_MEM_SIZE         0

#define DDR3_MONITPOS1_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITPOS1_MEM_SIZE)
#define DDR3_MONITPOS1_START_ADDR       (DDR3_MONITAMP1_END_ADDR + DDR3_MONITPOS1_MEM_BOOL*DDR3_MONITAMP1_SAMPLE_SIZE)
#define DDR3_MONITPOS1_END_ADDR         (DDR3_MONITPOS1_START_ADDR + DDR3_MONITPOS1_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITPOS1_MEM_BOOL*DDR3_MONITPOS1_SAMPLE_SIZE)
#define DDR3_MONITPOS1_MAX_SAMPLES      ((DDR3_MONITPOS1_END_ADDR-DDR3_MONITPOS1_START_ADDR) / DDR3_MONITPOS1_SAMPLE_SIZE)

/* MONIT1 1 POS
 * Size: 1 DDR3 regions */
#define DDR3_MONIT1POS1_SAMPLE_SIZE     MONIT1POS1_SAMPLE_SIZE
#define DDR3_MONIT1POS1_MEM_SIZE        0

#define DDR3_MONIT1POS1_MEM_BOOL        DDR3_MEM_BOOL(DDR3_MONIT1POS1_MEM_SIZE)
#define DDR3_MONIT1POS1_START_ADDR      (DDR3_MONITPOS1_END_ADDR + DDR3_MONIT1POS1_MEM_BOOL*DDR3_MONITPOS1_SAMPLE_SIZE)
#define DDR3_MONIT1POS1_END_ADDR        (DDR3_MONIT1POS1_START_ADDR + DDR3_MONIT1POS1_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONIT1POS1_MEM_BOOL*DDR3_MONIT1POS1_SAMPLE_SIZE)
#define DDR3_MONIT1POS1_MAX_SAMPLES     ((DDR3_MONIT1POS1_END_ADDR-DDR3_MONIT1POS1_START_ADDR) / DDR3_MONIT1POS1_SAMPLE_SIZE)

/* End 1 Dummy region
 * Size: 0 DDR3 regions */
#define DDR3_DUMMY_END1_SAMPLE_SIZE     MONIT1POS1_SAMPLE_SIZE
#define DDR3_DUMMY_END1_MEM_SIZE        0

#define DDR3_DUMMY_END1_MEM_BOOL        DDR3_MEM_BOOL(DDR3_DUMMY_END1_MEM_SIZE)
#define DDR3_DUMMY_END1_START_ADDR      DDR3_MONIT1POS1_END_ADDR
#define DDR3_DUMMY_END1_END_ADDR        (DDR3_DUMMY_END1_START_ADDR + DDR3_DUMMY_END1_MEM_SIZE*MEM_REGION_SIZE)
#define DDR3_DUMMY_END1_MAX_SAMPLES     (DDR3_DUMMY_END1_END_ADDR-DDR3_DUMMY_END1_START_ADDR)

#endif

