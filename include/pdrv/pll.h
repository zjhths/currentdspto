/*
 * pll.h
 *
 *  Created on: 2015-12-5
 *      Author: SUN
 */

#ifndef PLL_H_
#define PLL_H_

#define PLL0_BASE       0x01C11000                              /*SYSTEM PLL BASE ADDRESS*/
#define PLL0_PID        *(unsigned int*) (PLL0_BASE + 0x00)     /*PID*/
#define PLL0_FUSERR     *(unsigned int*) (PLL0_BASE + 0xE0)     /*x*FuseFarm Error Reg*/
#define PLL0_RSTYPE     *(unsigned int*) (PLL0_BASE + 0xE4)     /*Reset Type status Reg*/
#define PLL0_PLLCTL     *(unsigned int*) (PLL0_BASE + 0x100)    /*PLL Control Register*/
#define PLL0_OCSEL      *(unsigned int*) (PLL0_BASE + 0x104)    /*OBSCLK Select Register*/
#define PLL0_SECCTL     *(unsigned int*) (PLL0_BASE + 0x108)    /*PLL Secondary Control Register*/
#define PLL0_PLLM       *(unsigned int*) (PLL0_BASE + 0x110)    /*PLL Multiplier*/
#define PLL0_PREDIV     *(unsigned int*) (PLL0_BASE + 0x114)    /*Pre divider*/
#define PLL0_PLLDIV1    *(unsigned int*) (PLL0_BASE + 0x118)    /*Divider-1*/
#define PLL0_PLLDIV2    *(unsigned int*) (PLL0_BASE + 0x11C)    /*Divider-2*/
#define PLL0_PLLDIV3    *(unsigned int*) (PLL0_BASE + 0x120)    /*Divider-3*/
#define PLL0_OSCDIV1    *(unsigned int*) (PLL0_BASE + 0x124)    /*Oscilator Divider*/
#define PLL0_POSTDIV    *(unsigned int*) (PLL0_BASE + 0x128)    /*Post Divider*/
#define PLL0_BPDIV      *(unsigned int*) (PLL0_BASE + 0x12C)    /*Bypass Divider*/
#define PLL0_WAKEUP     *(unsigned int*) (PLL0_BASE + 0x130)    /*Wakeup Reg*/
#define PLL0_PLLCMD     *(unsigned int*) (PLL0_BASE + 0x138)    /*Command Reg*/
#define PLL0_PLLSTAT    *(unsigned int*) (PLL0_BASE + 0x13C)    /*Status Reg*/
#define PLL0_ALNCTL     *(unsigned int*) (PLL0_BASE + 0x140)    /*Clock Align Control Reg*/
#define PLL0_DCHANGE    *(unsigned int*) (PLL0_BASE + 0x144)    /*PLLDIV Ratio Chnage status*/
#define PLL0_CKEN       *(unsigned int*) (PLL0_BASE + 0x148)    /*Clock Enable Reg*/
#define PLL0_CKSTAT     *(unsigned int*) (PLL0_BASE + 0x14C)    /*Clock Status Reg*/
#define PLL0_SYSTAT     *(unsigned int*) (PLL0_BASE + 0x150)    /*Sysclk status reg*/
#define PLL0_PLLDIV4    *(unsigned int*) (PLL0_BASE + 0x160)    /*Divider 4*/
#define PLL0_PLLDIV5    *(unsigned int*) (PLL0_BASE + 0x164)    /*Divider 5*/
#define PLL0_PLLDIV6    *(unsigned int*) (PLL0_BASE + 0x168)    /*Divider 6*/
#define PLL0_PLLDIV7    *(unsigned int*) (PLL0_BASE + 0x16C)    /*Divider 7*/
#define PLL0_PLLDIV8    *(unsigned int*) (PLL0_BASE + 0x170)    /*Divider 8*/
#define PLL0_PLLDIV9    *(unsigned int*) (PLL0_BASE + 0x174)    /*Divider 9*/
#define PLL0_PLLDIV10   *(unsigned int*) (PLL0_BASE + 0x178)    /*Divider 10*/
#define PLL0_PLLDIV11   *(unsigned int*) (PLL0_BASE + 0x17C)    /*Divider 11*/
#define PLL0_PLLDIV12   *(unsigned int*) (PLL0_BASE + 0x180)    /*Divider 12*/
#define PLL0_PLLDIV13   *(unsigned int*) (PLL0_BASE + 0x184)    /*Divider 13*/
#define PLL0_PLLDIV14   *(unsigned int*) (PLL0_BASE + 0x188)    /*Divider 14*/
#define PLL0_PLLDIV15   *(unsigned int*) (PLL0_BASE + 0x18C)    /*Divider 15*/
#define PLL0_PLLDIV16   *(unsigned int*) (PLL0_BASE + 0x190)    /*Divider 16*/

#define PLL1_BASE       0x01E1A000                              /*SYSTEM PLL1 BASE ADDRESS*/
#define PLL1_PID        *(unsigned int*) (PLL1_BASE + 0x00)     /*PID*/
#define PLL1_FUSERR     *(unsigned int*) (PLL1_BASE + 0xE0)     /*x*FuseFarm Error Reg*/
#define PLL1_RSTYPE     *(unsigned int*) (PLL1_BASE + 0xE4)     /*Reset Type status Reg*/
#define PLL1_PLLCTL     *(unsigned int*) (PLL1_BASE + 0x100)    /*PLL Control Register*/
#define PLL1_OCSEL      *(unsigned int*) (PLL1_BASE + 0x104)    /*OBSCLK Select Register*/
#define PLL1_SECCTL     *(unsigned int*) (PLL1_BASE + 0x108)    /*PLL Secondary Control Register*/
#define PLL1_PLLM       *(unsigned int*) (PLL1_BASE + 0x110)    /*PLL Multiplier*/
#define PLL1_PREDIV     *(unsigned int*) (PLL1_BASE + 0x114)    /*Pre divider*/
#define PLL1_PLLDIV1    *(unsigned int*) (PLL1_BASE + 0x118)    /*Divider-1*/
#define PLL1_PLLDIV2    *(unsigned int*) (PLL1_BASE + 0x11C)    /*Divider-2*/
#define PLL1_PLLDIV3    *(unsigned int*) (PLL1_BASE + 0x120)    /*Divider-3*/
#define PLL1_OSCDIV1    *(unsigned int*) (PLL1_BASE + 0x124)    /*Oscilator Divider*/
#define PLL1_POSTDIV    *(unsigned int*) (PLL1_BASE + 0x128)    /*Post Divider*/
#define PLL1_BPDIV      *(unsigned int*) (PLL1_BASE + 0x12C)    /*Bypass Divider*/
#define PLL1_WAKEUP     *(unsigned int*) (PLL1_BASE + 0x130)    /*Wakeup Reg*/
#define PLL1_PLLCMD     *(unsigned int*) (PLL1_BASE + 0x138)    /*Command Reg*/
#define PLL1_PLLSTAT    *(unsigned int*) (PLL1_BASE + 0x13C)    /*Status Reg*/
#define PLL1_ALNCTL     *(unsigned int*) (PLL1_BASE + 0x140)    /*Clock Align Control Reg*/
#define PLL1_DCHANGE    *(unsigned int*) (PLL1_BASE + 0x144)    /*PLLDIV Ratio Chnage status*/
#define PLL1_CKEN       *(unsigned int*) (PLL1_BASE + 0x148)    /*Clock Enable Reg*/
#define PLL1_CKSTAT     *(unsigned int*) (PLL1_BASE + 0x14C)    /*Clock Status Reg*/
#define PLL1_SYSTAT     *(unsigned int*) (PLL1_BASE + 0x150)    /*Sysclk status reg*/
#define PLL1_PLLDIV4    *(unsigned int*) (PLL1_BASE + 0x160)    /*Divider 4*/
#define PLL1_PLLDIV5    *(unsigned int*) (PLL1_BASE + 0x164)    /*Divider 5*/
#define PLL1_PLLDIV6    *(unsigned int*) (PLL1_BASE + 0x168)    /*Divider 6*/
#define PLL1_PLLDIV7    *(unsigned int*) (PLL1_BASE + 0x16C)    /*Divider 7*/
#define PLL1_PLLDIV8    *(unsigned int*) (PLL1_BASE + 0x170)    /*Divider 8*/
#define PLL1_PLLDIV9    *(unsigned int*) (PLL1_BASE + 0x174)    /*Divider 9*/
#define PLL1_PLLDIV10   *(unsigned int*) (PLL1_BASE + 0x178)    /*Divider 10*/
#define PLL1_PLLDIV11   *(unsigned int*) (PLL1_BASE + 0x17C)    /*Divider 11*/
#define PLL1_PLLDIV12   *(unsigned int*) (PLL1_BASE + 0x180)    /*Divider 12*/
#define PLL1_PLLDIV13   *(unsigned int*) (PLL1_BASE + 0x184)    /*Divider 13*/
#define PLL1_PLLDIV14   *(unsigned int*) (PLL1_BASE + 0x188)    /*Divider 14*/
#define PLL1_PLLDIV15   *(unsigned int*) (PLL1_BASE + 0x18C)    /*Divider 15*/
#define PLL1_PLLDIV16   *(unsigned int*) (PLL1_BASE + 0x190)    /*Divider 16*/

#define PLLEN_MUX_SWITCH         4
#define PLL_LOCK_TIME_CNT        2400
#define PLL_STABILIZATION_TIME   2000
#define PLL_RESET_TIME_CNT       200

void Set_Core_456MHz();
void Set_Core_384MHz();
void Set_Core_300MHz();
void Set_Core_200MHz();
void Set_Core_100MHz();
void Set_DDRPLL_150MHz();
void Set_DDRPLL_132MHz();
void Set_DDRPLL_126MHz();

#endif /* PLL_H_ */
