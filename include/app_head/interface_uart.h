
#ifndef _INTERFACE_UART_H_
#define _INTERFACE_UART_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"
#ifdef MAIN
#define PC_UART 0
#define L_UART 2
#else
#define PC_UART 2
#define L_UART 0
#endif

#define Uart_ctrl0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 130 + x*10)))
#define Uart_Tx_Data0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 132 + x*10)))
#define Uart_Rx_Data0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 134 + x*10)))
#define Uart_Status0_H_addr(x)   (*((volatile unsigned short *)(0x62000000 + 136 + x*10)))
#define Uart_Status0_L_addr(x)   (*((volatile unsigned short *)(0x62000000 + 138 + x*10)))
#define div_uart_0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 176 + x*2)))
#define clk_select_0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 184 + x*2)))
#define Uart_set_0_addr(x)   (*((volatile unsigned short *)(0x62000000 + 192 + x*2)))
#define UART_EN_addr            (*((volatile unsigned short *)(0x62000000 + 174 )))
#define Clr_UART_INT_addr       (*((volatile unsigned short *)(0x62000000 + 170 )))
#define INT_Status_uart_addr       (*((volatile unsigned short *)(0x62000000 + 172 )))


typedef struct Uart_interface
{
    unsigned int channel;
    unsigned int speed;
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Uart_interface* interface, unsigned int channel,unsigned int speed);
    void(*send)(struct Uart_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Uart_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
    void(*process)(struct Uart_interface* interface);
}Uart_interface;


//函数
void Uart_Init(Uart_interface* interface, unsigned int channel,unsigned int speed);
void Uart_Send(Uart_interface* interface, unsigned char* data,unsigned int length);
void Uart_Recv(Uart_interface* interface, unsigned char* data,unsigned int* length);

void Uart_Interface_Process(Uart_interface* interface);

Uart_interface* new_uart_interface(unsigned int channel,unsigned int speed);
#endif /* CORE_H_ */
