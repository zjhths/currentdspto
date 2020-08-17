/*
 * ddr.c
 *
 *  Created on: 2015-12-6
 *      Author: SUN
 */
#include "hw_types.h"
#include "hw_syscfg0_C6748.h"
#include "hw_ddr2_mddr.h"
#include "hw_syscfg1_C6748.h"
/* Device/Platform lib headers */
#include "soc_C6748.h"
#include "psc.h"
#include "hw_psc_C6748.h"

#include "ddr.h"

/*
 * \brief Delay function.
 *
 * \param  count - Halts execution depend upon the value of the variable.
 *
 * \return none
*/
static void Delay(volatile unsigned int count)
{
    while(count--);

}
/*
 * \brief This function is used to initialize and configure DDR.
 *
 * \param  none.
 *
 * \return none
*/
void DDRInit(unsigned int freq)
{
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR,
    		PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);
    if (HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &
                                                SYSCFG1_VTPIO_CTL_POWERDN)
    {
		 /* Set IOPWRDN bit, powerdown enable mode */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=
										  SYSCFG1_VTPIO_CTL_IOPWRDN;
		 /* Clear POWERDN bit (enable VTP) */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &=
										  ~(SYSCFG1_VTPIO_CTL_POWERDN);
		 /* Clear CLRZ bit */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=
										  SYSCFG1_VTPIO_CTL_CLKRZ;
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &=
										 ~(SYSCFG1_VTPIO_CTL_CLKRZ);
		/* CLRZ bit should be low at least for 2ns */
		Delay(2);
		/* Set CLRZ bit */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=
										   SYSCFG1_VTPIO_CTL_CLKRZ;
		/* Poll ready bit in VTPIO_CTL Untill it is high */
		while (!(( HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &
			VTPIO_CTL_HIGH ) >> 15));
		/* Set Lock bit for static mode */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |= SYSCFG1_VTPIO_CTL_LOCK;
		/* set PWRSAVE bit to save Power */
		HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=
										  SYSCFG1_VTPIO_CTL_PWRSAVE;
		/* VTP Calibration ends */
    }

    /* Set BOOTUNLOCK */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) |= DDR2_MDDR_SDCR_BOOTUNLOCK;


    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_DRPYC1R) =
					(0x0               << 8)   |  // Reserved
					(0x1               << 7)   |  // EXT_STRBEN
					(0x1               << 6)   |  // PWRDNEN
					(0x0               << 3)   |  // Reserved
					(0x6               << 0);     // RL;

    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) =
					(HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) & 0xF0000000) |  // Reserved
					(0x0               << 27)   |  // DDR2TERM1
					(0x0               << 26)   |  // IBANK_POS
					(0x0               << 25)   |  // MSDRAMEN
					(0x0               << 24)   |  // DDRDRIVE1
					(0x0               << 23)   |  // BOOTUNLOCK
					(0x0               << 22)   |  // DDR2DDQS
					(0x0               << 21)   |  // DDR2TERM0
					(0x1               << 20)   |  // DDR2EN
					(0x0               << 19)   |  // DDRDLL_DIS
					(0x0               << 18)   |  // DDRDRIVE0
					(0x1               << 17)   |  // DDREN
					(0x1               << 16)   |  // SDRAMEN
					(0x1               << 15)   |  // TIMUNLOCK
					(0x1               << 14)   |  // NM
					(0x0               << 12)   |  // Reserved
					(0x4               << 9)    |  // CL
					(0x0               << 7)    |  // Reserved
					(0x3               << 4)    |  // IBANK
					(0x0               << 3)    |  // Reserved
					(0x2               << 0);      // PAGESIZE

    /* Let float -> integer truncate handle minus 1; Safer to round up for timings */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR1) =
					(((unsigned int) ((127.5 * freq / 1000) - 0)) << 25)	|  	// tRFC
					(((unsigned int) ((15.0 * freq / 1000) - 0)) << 22) 	|  	// tRP
					(((unsigned int) ((15.0 * freq / 1000) - 0)) << 19)		|  	// tRCD
					(((unsigned int) ((15.0 * freq / 1000) - 0)) << 16)		|  	// tWR
					(((unsigned int) ((45.0 * freq / 1000) - 0)) << 11) 	|  	// tRAS
					(((unsigned int) ((55.0 * freq / 1000) - 0)) << 6)  	|  	// tRC
					(((unsigned int) ((10.0 * freq / 1000) - 0)) << 3)  	|  	// tRRD
					(HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR1) & 0x4) |  	// Reserved
					(((unsigned int) ((7.5 * freq / 1000) - 0))  << 0);    		// tWTR

    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR2) =
    				(HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR2) & 0x80000000) 	|	// Reserved
					(((unsigned int) ((70 / 3.9607) - 1))   		<< 27)  		|	// tRASMAX
					(0x2                                            << 25)  		|	// tXP	 3-1
					(0x0                                            << 23)  		|	// tODT (Not supported)
					(((unsigned int) ((137.5 * freq / 1000) - 0.5)) << 16)  		|	// tXSNR
					((200 - 1)                                      << 8)   		|	// tXSRD (200 Cycles)
					(((unsigned int) ((7.5 * freq / 1000) - 0.5))	<< 5)	 		|  	// tRTP
					(0x2                                            << 0);    			// tCKE  3-1

    /* CLEAR TIMINGUNLOCK */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) &= ~0x00008000;

    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR2)   = 0x00000000; // IBANK_POS set to 0 so this register does not apply

    // Let float -> integer truncate handle RR round-down; Safer to round down for refresh rate
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDRCR) =
					(0x1                                          << 31)  |  // LPMODEN
					(0x1                                          << 30)  |  // MCLKSTOPEN
					(0x0                                          << 24)  |  // Reserved
					(0x0                                          << 23)  |  // SR_PD
					(0x0                                          << 16)  |  // Reserved
					(((unsigned int) ((3.9607 * freq) + 0.5))     << 0);     // RR

    /* SyncReset the Clock to SDRAM */
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR,
                              0,PSC_MDSTAT_STATE_SYNCRST);
    /* Enable clock to SDRAM */
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR, 0,PSC_MDCTL_NEXT_ENABLE);
    /* Disable Self refresh rate */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDRCR ) &= ~DDR2_SDRCR_CLEAR;
}
