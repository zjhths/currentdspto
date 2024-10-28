
#ifndef _INTERFACE_PID_H_
#define _INTERFACE_PID_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"

typedef struct Pid_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Pid_interface* interface);
    void(*send)(struct Pid_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Pid_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Pid_interface;


//函数
void Pid_Init(Pid_interface* interface);
void Pid_Send(Pid_interface* interface, unsigned char* data,unsigned int length);
void Pid_Recv(Pid_interface* interface, unsigned char* data,unsigned int* length);

void Pid_Interface_Process(Pid_interface* interface);

Pid_interface* new_pid_interface();
#endif /* CORE_H_ */
