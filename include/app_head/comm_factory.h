
#ifndef _COMM_FACTORY_H_
#define _COMM_FACTORY_H_

#include <stdio.h>
#include <stdlib.h>
#include "define_imput.h"
#include "interface_uart.h"
extern Uart_interface* pc_uart;



typedef enum CoreType
{

	CORE_HDLC = 0,
    CORE_UART,
    CORE_AD,
    CORE_DA,
	CORE_PHASE,
	CORE_VARIABLE,
	CORE_FUSION,
	CORE_CALIB,
	CORE_PID,
    CORE_NONE

}CoreType;

//锟斤拷锟斤拷锟斤拷C++ 锟斤拷锟斤拷
typedef struct Base_Core
{
	CoreType core_type;
	int up_in_data_list;
	int up_out_data_list;
    int down_in_data_list;
    int down_out_data_list;
	void(*speaker)(struct Base_Core* core);		//锟斤拷锟斤拷锟节伙拷锟斤拷锟介函锟斤拷   锟斤拷锟斤拷指锟斤拷
	void(*process)(struct Base_Core* core);     //锟斤拷锟斤拷锟节伙拷锟斤拷锟介函锟斤拷   锟斤拷锟斤拷指锟斤拷
	void* parent_core;							//锟斤拷锟斤拷指锟诫，锟斤拷锟矫伙拷谢锟斤拷啵拷锟轿狽ULL
}Base_Core;



//锟斤拷锟斤拷锟斤拷
typedef struct Core_Factory
{
	Base_Core* (*create_new_core)(CoreType core_type);	//锟斤拷锟斤拷锟侥接口ｏ拷锟矫接口癸拷锟斤拷锟阶帮拷锟斤拷锟斤拷锟绞碉拷锟较革拷锟�
}Core_Factory;


//锟斤拷锟斤拷模式锟斤拷锟斤拷锟斤拷锟斤拷锟�
Core_Factory* new_core_factory();
void delete_core_factory(Core_Factory* core_factory);

Base_Core*    new_Base_Core();
void delete_Base_Core(struct Base_Core* core);


#endif /* CORE_H_ */


