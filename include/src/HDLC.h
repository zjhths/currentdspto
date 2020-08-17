/*
 * HDLC.h
 *
 *  Created on: 2018-3-14
 *      Author: BXX
 */

#ifndef HDLC_H_
#define HDLC_H_

extern unsigned char HDLC_RDATA_A[255];
extern unsigned char HDLC_RDATA_B[255];
void DSJ_initA(void);
void DSJ_initB(void);
void Cmd4_ProcA();
void Cmd4_ProcB();


#endif /* HDLC_H_ */
