
#ifndef _INTERFACE_DA_H_
#define _INTERFACE_DA_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "fifo.h"


 #define          PID_KP_HH            (*(unsigned short int *)0x62000228)
 #define          PID_KP_HL            (*(unsigned short int *)0x6200022C)
 #define          PID_KP_LH            (*(unsigned short int *)0x62000230)
 #define          PID_KP_LL            (*(unsigned short int *)0x62000234)

 #define          PID_KI_HH            (*(unsigned short int *)0x62000238)
 #define          PID_KI_HL            (*(unsigned short int *)0x6200023C)
 #define          PID_KI_LH            (*(unsigned short int *)0x62000240)
 #define          PID_KI_LL            (*(unsigned short int *)0x62000244)

 #define          PID_KD_HH            (*(unsigned short int *)0x62000248)
 #define          PID_KD_HL            (*(unsigned short int *)0x6200024C)
 #define          PID_KD_LH            (*(unsigned short int *)0x62000250)
 #define          PID_KD_LL            (*(unsigned short int *)0x62000254)



 #define          SET_POINT_HH            (*(unsigned short int *)0x62000298)
 #define          SET_POINT_HL            (*(unsigned short int *)0x6200029C)
 #define          SET_POINT_LH            (*(unsigned short int *)0x620002A0)
 #define          SET_POINT_LL            (*(unsigned short int *)0x620002A4)

 #define	 DA_CONFIG_SEL          (*(unsigned short int *)0x62000060)  //选择dsp控制：0  fpga控制：1
#define          WAVE_SEL                (*(unsigned short int *)0x620002A8)   //1 常值  2方波  4 三角  8正弦波

 #define          SQUARE_HIGH_DUTY        (*(unsigned short int *)0x620002E8)
 #define          SQUARE_LOW_DUTY         (*(unsigned short int *)0x620002EC)
 #define          SQUARE_HIGH_AMP_HH      (*(unsigned short int *)0x620002F0)
 #define          SQUARE_HIGH_AMP_HL      (*(unsigned short int *)0x620002F4)
 #define          SQUARE_HIGH_AMP_LH      (*(unsigned short int *)0x620002F8)
 #define          SQUARE_HIGH_AMP_LL      (*(unsigned short int *)0x620002FC)
 #define          SQUARE_LOW_AMP_HH       (*(unsigned short int *)0x62000300)
 #define          SQUARE_LOW_AMP_HL       (*(unsigned short int *)0x62000304)
 #define          SQUARE_LOW_AMP_LH       (*(unsigned short int *)0x62000308)
 #define          SQUARE_LOW_AMP_LL       (*(unsigned short int *)0x6200030C)


 #define          SIN_FRQ_H               (*(unsigned short int *)0x620002AC)   //2^32*x/128000
 #define          SIN_FRQ_L               (*(unsigned short int *)0x620002B0)
 #define          SIN_AMP_HH              (*(unsigned short int *)0x620002B4)   //amp double
 #define          SIN_AMP_HL              (*(unsigned short int *)0x620002B8)
 #define          SIN_AMP_LH              (*(unsigned short int *)0x620002BC)
 #define          SIN_AMP_LL              (*(unsigned short int *)0x620002C0)


 #define          TRIANGLE_FRQ               (*(unsigned short int *)0x620002C4)  //64000/fre
 #define          TRIANGLE_AMP_HH         (*(unsigned short int *)0x620002C8)  //double
 #define          TRIANGLE_AMP_HL         (*(unsigned short int *)0x620002CC)   //amp
 #define          TRIANGLE_AMP_LH         (*(unsigned short int *)0x620002D0)
 #define          TRIANGLE_AMP_LL         (*(unsigned short int *)0x620002D4)
 #define          TRIANGLE_ITV_HH         (*(unsigned short int *)0x620002D8)   //amp*2/fre
 #define          TRIANGLE_ITV_HL         (*(unsigned short int *)0x620002DC)
 #define          TRIANGLE_ITV_LH         (*(unsigned short int *)0x620002E0)
 #define          TRIANGLE_ITV_LL         (*(unsigned short int *)0x620002E4)

 #define	 DA_VI_SEL              (*(unsigned short int *)0x62000064)  //电流电压控制切换    0：电流       1：电压
#define DA_CMD_SIZE                       128



typedef struct Da_interface
{
    unsigned int recv_fifo;
    unsigned int send_fifo;
    void(*init)(struct Da_interface* interface);
    void(*send)(struct Da_interface* interface, unsigned char* data,unsigned int length);
    void(*recv)(struct Da_interface* interface, unsigned char* data,unsigned int* length);     //类似于基类虚函数   函数指针
}Da_interface;


//函数
void Da_Init(Da_interface* interface );
void Da_Send(Da_interface* interface, unsigned char* data,unsigned int length);
void Da_Recv(Da_interface* interface, unsigned char* data,unsigned int* length);


Da_interface* new_da_interface();
#endif /* CORE_H_ */
