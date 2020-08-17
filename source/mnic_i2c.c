/*
 * mnic_i2c.c
 *
 *  Created on: 2019-11-15
 *      Author: Administrator
 */

#include "pll.h"
#include "psc.h"
#include "ddr.h"
#include "timer.h"
#include "hw_syscfg0_C6748.h"
#include "interrupt.h"
#include "soc_C6748.h"
#include "mnic_C6748.h"
#include "mnic_timer.h"
#include "mnic_gpio.h"
#include "mnic_emif.h"
#include "mnic_test.h"
#include "hw_types.h"
#include "fpga.h"
#include "Init.h"
#include "rs232_rs422.h"
#include "mnic_nor.h"
#include "spi.h"
#include "mini_spi.h"
#include "AD.h"
#include "Data_Exchange.h"
#include "Nav.h"
#include "stdio.h"
#include "MBox.h"
#include "HDLC.h"
#include "pid_func.h"
#include "mnic_i2c.h"
#include "i2c.h"
#include "hw_i2c.h"
#include "tms320c6748_sysconfig.h"
#include "types.h"
#include "mnic_interrupt.h"
//#include "include.h"
#include "gpio.h"
extern unsigned int count;
extern unsigned int flag;
extern unsigned char dataToSlave[2];

/* I2C address of TCA6416 expander. */
#define I2C_SLAVE_ADDR            (0x48u)

void SetupI2C(void);
void SetupIntc(void);
void SetupI2CTransmit(void);
void BlinkDelay(void);

void i2c_init()
{
	long long i;
	unsigned int m ;
    //reset DA
	DA_RST_EN=0x1;
    for(i=0;i<500;i++);
    DA_RST_EN=0x0;
    for(i=0;i<500;i++);

    I2CPinMuxSetup(0);
    SetupIntc();

    count = 0;
    flag  = 1;
    dataToSlave[0] = 0x26;//first reguster address(38) DAC1-2MAPPING
    dataToSlave[1] = 0x00;// DAC1-2MAPPING TO INPUT1
	Delay1();
    SetupI2C();
    while(flag==1)//wait for interrupt
    {
     m=1;
    }
    m=0;

    count = 0;
    flag  = 1;
    dataToSlave[0] = 0x27;//SECOND reguster address(39) DAC3-4MAPPING
    dataToSlave[1] = 0x00;//SECOND DAC3-4MAPPING TO INPUT1
	Delay1();
    SetupI2C();
    while(flag==1)//wait for interrupt
    {
     m=1;
    }
    m=0;

    count = 0;
    flag  = 1;
    dataToSlave[0] = 0x28;//THIRD reguster address(40) DAC5-6MAPPING
    dataToSlave[1] = 0x00;//THIRD DAC5-6MAPPING TO INPUT1
	Delay1();
    SetupI2C();
    while(flag==1)//wait for interrupt
    {
     m=1;
    }
    m=0;

    flag=1;
    count=0;
    dataToSlave[0] = 0x29;//FOURTH reguster address(41) DAC7-8MAPPING
    dataToSlave[1] = 0x00;//FOURTH DAC7-8MAPPING TO INPUT1
	Delay1();
	SetupI2CTransmit();

    while(flag==1)//wait for interrupt
    {
    m=1;
    }


    return;

}

void SetupI2C(void)
{
    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C_0_REGS);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C_0_REGS, 24000000, 8000000, 100000);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C_0_REGS, I2C_SLAVE_ADDR);


    /* Enable transmit data ready and stop condition interrupt */
    I2CMasterIntEnableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY|I2C_INT_STOP_CONDITION);

    /* Set i2c data count register to number of data to be transmit */
    I2CSetDataCount(SOC_I2C_0_REGS, 2);

    /*
    ** Configure i2c has master-transmitter and to generate stop condition
    ** when value in internal data count register count down to zero
    */
    I2CMasterControl(SOC_I2C_0_REGS, I2C_CFG_MST_TX | I2C_CFG_STOP);


    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C_0_REGS);

    /* Generate start condition on i2c bus */
    I2CMasterStart(SOC_I2C_0_REGS);

}


void SetupIntc(void)
{

	// Initialize the DSP interrupt controller
	IntDSPINTCInit();

	// Register I2C ISR in the vector table
	IntRegister(C674X_MASK_INT4, I2CIsr);

	// Map I2C interrupt to DSP maskable interrupt
	IntEventMap(C674X_MASK_INT4, SYS_INT_I2C0_INT);

	// Enable DSP maskable interrupt
	IntEnable(C674X_MASK_INT4);

	// Enable DSP interrupts globally
	IntGlobalEnable();
}


void SetupI2CTransmit(void)
{
    I2CSetDataCount(SOC_I2C_0_REGS, 2);

    I2CMasterControl(SOC_I2C_0_REGS, I2C_CFG_MST_TX | I2C_CFG_STOP);

    I2CMasterIntEnableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY|I2C_INT_STOP_CONDITION);

    I2CMasterStart(SOC_I2C_0_REGS);
}


void BlinkDelay(void)
{
#ifdef _TMS320C6X
	volatile unsigned int delay = 0xFFFFF;
#else
    volatile unsigned int delay = 0x7FFFF;
#endif

    while(delay--);
}
