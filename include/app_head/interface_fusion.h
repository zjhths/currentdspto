
#ifndef _INTERFACE_FUSION_H_
#define _INTERFACE_FUSION_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"

typedef struct Fusion_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Fusion_interface* interface);
    void(*send)(struct Fusion_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Fusion_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Fusion_interface;


//函数
void Fusion_Init(Fusion_interface* interface);
void Fusion_Send(Fusion_interface* interface, unsigned char* data,unsigned int length);
void Fusion_Recv(Fusion_interface* interface, unsigned char* data,unsigned int* length);

void Fusion_Interface_Process(Fusion_interface* interface);

Fusion_interface* new_fusion_interface();
#endif /* CORE_H_ */
