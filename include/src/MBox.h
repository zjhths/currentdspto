/*
 * MBox.h
 *
 *  Created on: 2017-7-31
 *      Author: Administrator
 */

#ifndef MBOX_H_
#define MBOX_H_


void MailBox_Send(int Type,double A1,double A2,double A3);
void MailBox_Recevice();
extern unsigned short mailbox_rx_buff[];


#endif /* MBOX_H_ */
