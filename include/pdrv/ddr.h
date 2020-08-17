/*
 * ddr.h
 *
 *  Created on: 2015-12-6
 *      Author: SUN
 */

#ifndef DDR_H_
#define DDR_H_

#define DDR2_SDRCR_CLEAR           0xC0000000
#define VTPIO_CTL_HIGH             0x00080000
#define DDR2_SDRCR                 0xC0000459

void DDRInit(unsigned int freq);

#endif /* DDR_H_ */
