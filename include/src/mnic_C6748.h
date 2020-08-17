/*
 * mni_C6748.h
 *
 *  Created on: 2015-12-5
 *      Author: SUN
 */

#ifndef __MNI_C6748_H__
#define __MNI_C6748_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      FUNCTION DEFINITIONS
******************************************************************************/

#define _DEBUG

extern void UARTPinMuxSetup(unsigned int instanceNum,
                            unsigned int modemCtrlChoice);
extern void SPI0CSPinMuxSetup(unsigned int csPinNum);
extern void SPI1CSPinMuxSetup(unsigned int csPinNum); 
extern void I2CPinMuxSetup(unsigned int instanceNum);
extern void SPIPinMuxSetup(unsigned int instanceNum);
extern void GPIOBank4Pin0PinMuxSetup(void);
extern void SysCfgRegistersUnlock(void);
extern void SysCfgRegistersLock(void);
extern void EMACPinMuxSetup(void);
extern void EMIFPinMuxSetup(void);

#ifdef __cplusplus
}
#endif
#endif
