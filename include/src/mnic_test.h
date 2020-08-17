/*
 * mnic_test.h
 *
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#ifndef MNIC_TEST_H_
#define MNIC_TEST_H_

#define LEDADDR  				0x62000008
#define RWADDR					0x62000004
#define SET_GPIO_INIT_ADDR      0x62000006

#define DDR2STARTADDR			0xC0000000
//#define DDR2STARTADDR			0x60000000
extern int get_init_count;
extern int set_init_count;
extern int timer_test_flag;

void EmifFpgaTest(void);
void DDR2Test(void);
void NorFlashTest(void);


#endif /* MNIC_TEST_H_ */
