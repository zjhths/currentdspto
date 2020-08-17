

/*
 * tms320c6748_sysconfiig.h
 *
 *  Created on: 2015-4-25
 *      Author: SUN
 */

#ifndef TMS320C6748_SYSCONFIIG_H_
#define TMS320C6748_SYSCONFIIG_H_

#include "types.h"
//-----------------------------------------------------------------------------
// Register Structure & Defines
//-----------------------------------------------------------------------------

#define SYS_BASE           0x01C14000
#define HOST0CFG           *(unsigned int*)(SYS_BASE + 0x040)  //ARM HOST0CFG
#define KICK0R             *(unsigned int*)(SYS_BASE + 0x038)
#define KICK1R             *(unsigned int*)(SYS_BASE + 0x03c)
#define PINMUX0            *(unsigned int*)(SYS_BASE + 0x120)  //PINMUX0
#define PINMUX1            *(unsigned int*)(SYS_BASE + 0x124)  //PINMUX1
#define PINMUX2            *(unsigned int*)(SYS_BASE + 0x128)  //PINMUX2
#define PINMUX3            *(unsigned int*)(SYS_BASE + 0x12C)  //PINMUX3
#define PINMUX4            *(unsigned int*)(SYS_BASE + 0x130)  //PINMUX4
#define PINMUX5            *(unsigned int*)(SYS_BASE + 0x134)  //PINMUX5
#define PINMUX6            *(unsigned int*)(SYS_BASE + 0x138)  //PINMUX6
#define PINMUX7            *(unsigned int*)(SYS_BASE + 0x13C)  //PINMUX7
#define PINMUX8            *(unsigned int*)(SYS_BASE + 0x140)  //PINMUX8
#define PINMUX9            *(unsigned int*)(SYS_BASE + 0x144)  //PINMUX9
#define PINMUX10           *(unsigned int*)(SYS_BASE + 0x148)  //PINMUX10
#define PINMUX11           *(unsigned int*)(SYS_BASE + 0x14C)  //PINMUX11
#define PINMUX12           *(unsigned int*)(SYS_BASE + 0x150)  //PINMUX12
#define PINMUX13           *(unsigned int*)(SYS_BASE + 0x154)  //PINMUX13
#define PINMUX14           *(unsigned int*)(SYS_BASE + 0x158)  //PINMUX14
#define PINMUX15           *(unsigned int*)(SYS_BASE + 0x15C)  //PINMUX15
#define PINMUX16           *(unsigned int*)(SYS_BASE + 0x160)  //PINMUX16
#define PINMUX17           *(unsigned int*)(SYS_BASE + 0x164)  //PINMUX17
#define PINMUX18           *(unsigned int*)(SYS_BASE + 0x168)  //PINMUX18
#define PINMUX19           *(unsigned int*)(SYS_BASE + 0x16C)  //PINMUX19
#define CFGCHIP0           *(unsigned int*)(SYS_BASE + 0x17C)
#define CFGCHIP1           *(unsigned int*)(SYS_BASE + 0x180)
#define CFGCHIP2           *(unsigned int*)(SYS_BASE + 0x184)
#define CFGCHIP3           *(unsigned int*)(SYS_BASE + 0x188)
#define PD0                0   /*Power Domain-0*/
#define PD1                1   /*Power Domain-1*/

//I2C
#define SYSCFG_PINMUX4_PINMUX4_15_12_I2C0_SDA (0x00000002u)
#define SYSCFG_PINMUX4_PINMUX4_15_12_SHIFT (0x0000000Cu)
#define SYSCFG_PINMUX4_PINMUX4_11_8_I2C0_SCL (0x00000002u)
#define SYSCFG_PINMUX4_PINMUX4_11_8_SHIFT (0x00000008u)
#define SYSCFG_PINMUX4_PINMUX4_23_20_I2C1_SDA (0x00000004u)
#define SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT (0x00000014u)
#define SYSCFG_PINMUX4_PINMUX4_19_16_I2C1_SCL (0x00000004u)
#define SYSCFG_PINMUX4_PINMUX4_19_16_SHIFT (0x00000010u)
#define SYSCFG0_PINMUX(n)	(0x120 + (n * 4))
#define SYSCFG_PINMUX4_PINMUX4_15_12 (0x0000F000u)
#define SYSCFG_PINMUX4_PINMUX4_11_8 (0x00000F00u)
/** \brief Base address of DEV memory mapped registers                        */
#define SOC_SYSCFG_0_REGS                   (0x01C14000)
#define SYSCFG_PINMUX4_PINMUX4_23_20 (0x00F00000u)
#define SYSCFG_PINMUX4_PINMUX4_19_16 (0x000F0000u)




typedef struct
{
   volatile uint32_t REVID;            // 0x0000
   volatile uint32_t RSVD0;            // 0x0004
   volatile uint32_t DIEIDR[4];        // 0x0008
   volatile uint32_t RSVD1[2];         // 0x0018
   volatile uint32_t BOOTCFG;          // 0x0020
   volatile uint32_t RSVD2[5];         // 0x0024
   volatile uint32_t KICKR[2];         // 0x0038
   volatile uint32_t HOST0CFG0;         // 0x0040
   volatile uint32_t HOST1CFG;         // 0x0044
   volatile uint32_t RSVD3[38];        // 0x0048
   volatile uint32_t IRAWSTAT;         // 0x00E0
   volatile uint32_t IENSTAT;          // 0x00E4
   volatile uint32_t IENSET;           // 0x00E8
   volatile uint32_t IENCLR;           // 0x00EC
   volatile uint32_t EOI;              // 0x00F0
   volatile uint32_t FLTADDRR;         // 0x00F4
   volatile uint32_t FLTSTAT;          // 0x00F8
   volatile uint32_t RSVD4[5];         // 0x00FC
   volatile uint32_t MSTPRI[3];        // 0x0110
   volatile uint32_t RSVD5;            // 0x011C
   volatile uint32_t PINMUX[20];       // 0x0120
   volatile uint32_t SUSPSRC;          // 0x0170
   volatile uint32_t CHIPSIG;          // 0x0174
   volatile uint32_t CHIPSIG_CLR;      // 0x0178
   volatile uint32_t CFGCHIP[5];       // 0x017C
} sysconfig_regs_t;

// define the one and only system config module.
#define SYSCONFIG          ((sysconfig_regs_t *)SYSCONFIG_REG_BASE)

// unlock/lock kick registers defines.
#define KICK0R_UNLOCK      (0x83E70B13)
#define KICK1R_UNLOCK      (0x95A4F1E0)
#define KICK0R_LOCK        (0x00000000)
#define KICK1R_LOCK        (0x00000000)

// bitmask defines for cfgchip[0].
#define PLL0_MASTER_LOCK   (0x00000010)   // bit 4

// bitmask defines for cfgchip[3].
#define CLK2XSRC           (0x00000080)   // bit 7
#define PLL1_MASTER_LOCK   (0x00000020)   // bit 5
#define DIV4P5ENA          (0x00000004)   // bit 2
#define EMA_CLKSRC         (0x00000002)   // bit 1

// defines for hostcfg.
#define BOOTRDY            (0x00000001)   // bit 0

// defines for pinmux0.
#define MASK_EMB_WE        (0xF0000000) // bits 31-28
#define MASK_EMB_RAS       (0x0F000000) // bits 27-24


#endif /* TMS320C6748_SYSCONFIIG_H_ */


