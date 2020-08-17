#ifndef RS232_RS422_H_
#define RS232_RS422_H_
#include "stdint.h"

    extern void COM_Init(unsigned char  COmNum,unsigned int  baudrate,unsigned char cStopBits,
		 unsigned char Parity_En,char cParity,unsigned char INT_Mode,
		 unsigned char  Recv_Length,unsigned char Send_Length);
    extern void COM_Send(unsigned char  COmNum,unsigned char  *SendData,unsigned char  Length);
    extern void COM_Recv(unsigned char COmNum,unsigned char RecvData[255]);
    extern void Interrupt_UART_Mask(uint16_t Mask);
    extern uint16_t Interrupt_UART_Query();


    extern unsigned char rx_Data_RS485_0[255];
    extern unsigned char rx_Data_RS485_1[255];
	extern unsigned char rx_Data_RS485_2[255];
    extern unsigned char rx_Data_RS485_3[255];
    extern unsigned char rx_Data_RS422_0[255];
    extern unsigned char rx_Data_RS422_1[255];
    extern unsigned char rx_Data_RS422_2[255];
    extern unsigned char rx_Data_RS422_3[255];
    extern unsigned char rx_Data_RS422_4[255];
    extern unsigned char rx_Data_RS422_5[255];
    extern unsigned char rx_Data_RS422_6[255];
    extern unsigned char rx_Data_RS422_7[255];
    extern unsigned char rx_Data_RS422_8[255];
    extern unsigned char rx_Data_RS422_9[255];

#endif /* RS232_PROCESS_H_ */
