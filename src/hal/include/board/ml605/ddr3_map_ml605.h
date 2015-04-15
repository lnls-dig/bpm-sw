#ifndef _DDR3_MAP_ML605_H_
#define _DDR3_MAP_ML605_H_

#include "acq_chan_ml605.h"
#include "varg_macros.h"

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
#define DDR3_ADC0_START_ADDR            (DDR3_DUMMY_INIT0_START_ADDR + DDR3_DUMMY_INIT0_MEM_BOOL*DDR3_DUMMY_INIT0_SAMPLE_SIZE)
#define DDR3_ADC0_END_ADDR              (DDR3_ADC0_START_ADDR + DDR3_ADC0_MEM_SIZE*MEM_REGION_SIZE - DDR3_ADC0_MEM_BOOL*DDR3_ADC0_SAMPLE_SIZE)
#define DDR3_ADC0_MAX_SAMPLES           ((DDR3_ADC0_END_ADDR-DDR3_ADC0_START_ADDR) / DDR3_ADC0_SAMPLE_SIZE)

/* TBT 0 AMP
 * Size: 2 DDR3 regions */
#define DDR3_TBTAMP0_SAMPLE_SIZE        TBTAMP0_SAMPLE_SIZE
#define DDR3_TBTAMP0_MEM_SIZE           2

#define DDR3_TBTAMP0_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTAMP0_MEM_SIZE)
#define DDR3_TBTAMP0_START_ADDR         (DDR3_ADC0_END_ADDR + DDR3_ADC0_MEM_BOOL*DDR3_ADC0_SAMPLE_SIZE)
#define DDR3_TBTAMP0_END_ADDR           (DDR3_TBTAMP0_START_ADDR + DDR3_TBTAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTAMP0_MEM_BOOL*DDR3_TBTAMP0_SAMPLE_SIZE)
#define DDR3_TBTAMP0_MAX_SAMPLES        ((DDR3_TBTAMP0_END_ADDR-DDR3_TBTAMP0_START_ADDR) / DDR3_TBTAMP0_SAMPLE_SIZE)

/* TBT 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_TBTPOS0_SAMPLE_SIZE        TBTPOS0_SAMPLE_SIZE
#define DDR3_TBTPOS0_MEM_SIZE           0

#define DDR3_TBTPOS0_MEM_BOOL           DDR3_MEM_BOOL(DDR3_TBTPOS0_MEM_SIZE)
#define DDR3_TBTPOS0_START_ADDR         (DDR3_TBTAMP0_END_ADDR + DDR3_TBTAMP0_MEM_BOOL*DDR3_TBTAMP0_SAMPLE_SIZE)
#define DDR3_TBTPOS0_END_ADDR           (DDR3_TBTPOS0_START_ADDR + DDR3_TBTPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_TBTPOS0_MEM_BOOL*DDR3_TBTPOS0_SAMPLE_SIZE)
#define DDR3_TBTPOS0_MAX_SAMPLES        ((DDR3_TBTPOS0_END_ADDR-DDR3_TBTPOS0_START_ADDR) / DDR3_TBTPOS0_SAMPLE_SIZE)

/* FOFB 0 AMP
 * Size: 2 DDR3 regions */
#define DDR3_FOFBAMP0_SAMPLE_SIZE       FOFBAMP0_SAMPLE_SIZE
#define DDR3_FOFBAMP0_MEM_SIZE          2

#define DDR3_FOFBAMP0_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBAMP0_MEM_SIZE)
#define DDR3_FOFBAMP0_START_ADDR        (DDR3_TBTPOS0_END_ADDR + DDR3_TBTPOS0_MEM_BOOL*DDR3_TBTPOS0_SAMPLE_SIZE)
#define DDR3_FOFBAMP0_END_ADDR          (DDR3_FOFBAMP0_START_ADDR + DDR3_FOFBAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBAMP0_MEM_BOOL*DDR3_FOFBAMP0_SAMPLE_SIZE)
#define DDR3_FOFBAMP0_MAX_SAMPLES       ((DDR3_FOFBAMP0_END_ADDR-DDR3_FOFBAMP0_START_ADDR) / DDR3_FOFBAMP0_SAMPLE_SIZE)

/* FOFB 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_FOFBPOS0_SAMPLE_SIZE       FOFBPOS0_SAMPLE_SIZE
#define DDR3_FOFBPOS0_MEM_SIZE          0

#define DDR3_FOFBPOS0_MEM_BOOL          DDR3_MEM_BOOL(DDR3_FOFBPOS0_MEM_SIZE)
#define DDR3_FOFBPOS0_START_ADDR        (DDR3_FOFBAMP0_END_ADDR + DDR3_FOFBAMP0_MEM_BOOL*DDR3_FOFBAMP0_SAMPLE_SIZE)
#define DDR3_FOFBPOS0_END_ADDR          (DDR3_FOFBPOS0_START_ADDR + DDR3_FOFBPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_FOFBPOS0_MEM_BOOL*DDR3_FOFBPOS0_SAMPLE_SIZE)
#define DDR3_FOFBPOS0_MAX_SAMPLES       ((DDR3_FOFBPOS0_END_ADDR-DDR3_FOFBPOS0_START_ADDR) / DDR3_FOFBPOS0_SAMPLE_SIZE)

 /* MONIT 0 AMP
 * Size: 0 DDR3 regions */
#define DDR3_MONITAMP0_SAMPLE_SIZE      MONITAMP0_SAMPLE_SIZE
#define DDR3_MONITAMP0_MEM_SIZE         0

#define DDR3_MONITAMP0_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITAMP0_MEM_SIZE)
#define DDR3_MONITAMP0_START_ADDR       (DDR3_FOFBPOS0_END_ADDR + DDR3_FOFBPOS0_MEM_BOOL*DDR3_FOFBPOS0_SAMPLE_SIZE)
#define DDR3_MONITAMP0_END_ADDR         (DDR3_MONITAMP0_START_ADDR + DDR3_MONITAMP0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITAMP0_MEM_BOOL*DDR3_MONITAMP0_SAMPLE_SIZE)
#define DDR3_MONITAMP0_MAX_SAMPLES      ((DDR3_MONITAMP0_END_ADDR-DDR3_MONITAMP0_START_ADDR) / DDR3_MONITAMP0_SAMPLE_SIZE)

/* MONIT 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_MONITPOS0_SAMPLE_SIZE      MONITPOS0_SAMPLE_SIZE
#define DDR3_MONITPOS0_MEM_SIZE         0

#define DDR3_MONITPOS0_MEM_BOOL         DDR3_MEM_BOOL(DDR3_MONITPOS0_MEM_SIZE)
#define DDR3_MONITPOS0_START_ADDR       (DDR3_MONITAMP0_END_ADDR + DDR3_MONITAMP0_MEM_BOOL*DDR3_MONITAMP0_SAMPLE_SIZE)
#define DDR3_MONITPOS0_END_ADDR         (DDR3_MONITPOS0_START_ADDR + DDR3_MONITPOS0_MEM_SIZE*MEM_REGION_SIZE - DDR3_MONITPOS0_MEM_BOOL*DDR3_MONITPOS0_SAMPLE_SIZE)
#define DDR3_MONITPOS0_MAX_SAMPLES      ((DDR3_MONITPOS0_END_ADDR-DDR3_MONITPOS0_START_ADDR) / DDR3_MONITPOS0_SAMPLE_SIZE)

/* MONIT1 0 POS
 * Size: 0 DDR3 regions */
#define DDR3_MONIT1POS0_SAMPLE_SIZE     MONIT1POS0_SAMPLE_SIZE
#define DDR3_MONIT1POS0_MEM_SIZE        0

#define DDR3_MONIT1POS0_MEM_BOOL        DDR3_MEM_BOOL(DDR3_MONIT1POS0_MEM_SIZE)
#define DDR3_MONIT1POS0_START_ADDR      (DDR3_MONITPOS0_END_ADDR + DDR3_MONITPOS0_MEM_BOOL*DDR3_MONITPOS0_SAMPLE_SIZE)
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

#endif

