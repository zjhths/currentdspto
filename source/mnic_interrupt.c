/*
 * mnic_interrupt.c
 *
 *  Created on: 2019-11-15
 *      Author: Administrator
 */

#include "interrupt.h"
#include "soc_C6748.h"

#include "mnic_i2c.h"
#include "hw_i2c.h"




extern unsigned int count;
extern unsigned int flag;
extern unsigned char dataToSlave[2];

void I2CIsr()
{
    unsigned int intCode = 0;

    /* Get interrupt vector code */
    intCode = I2CInterruptVectorGet(SOC_I2C_0_REGS);

    /* Clear status of interrupt */
#ifdef _TMS320C6X
    IntEventClear(SYS_INT_I2C0_INT);
#else
    IntSystemStatusClear(SYS_INT_I2CINT0);
#endif

    if (intCode == I2C_INTCODE_TX_READY)
    {
         /* Put data to data transmit register of i2c */
         I2CMasterDataPut(SOC_I2C_0_REGS, dataToSlave[count++]);
    }

    if (intCode == I2C_INTCODE_STOP)
    {
	/* Disable transmit data ready register */
        I2CMasterIntDisableEx(SOC_I2C_0_REGS,I2C_INT_TRANSMIT_READY);
        flag = 0;
    }
}
