
#ifndef _INTERFACE_VARIABLE_H_
#define _INTERFACE_VARIABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"


typedef struct Variable_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Variable_interface* interface);
    void(*send)(struct Variable_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Variable_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Variable_interface;


//函数
void Variable_Init(Variable_interface* interface);
void Variable_Send(Variable_interface* interface, unsigned char* data,unsigned int length);
void Variable_Recv(Variable_interface* interface, unsigned char* data,unsigned int* length);

void Variable_Interface_Process(Variable_interface* interface);

Variable_interface* new_variable_interface();
#endif /* CORE_H_ */
