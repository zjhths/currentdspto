/*
 * func.h
 *
 *  Created on: 2015-11-26
 *      Author: Administrator
 */

#ifndef FUNC_H_
#define FUNC_H_


#define TMR_addr (0x01C20000)    //by  Hannie


#define PI 3.1415926

#define Own_Add 0x41

union data_buffer
{
	volatile unsigned char c_data[4];
	volatile float f_data;
};

#endif /* FUNC_H_ */
