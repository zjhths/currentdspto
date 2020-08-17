
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
    CORE_NONE

}CoreType;

//类似于C++ 基类
typedef struct Base_Core
{
	CoreType core_type;
	int up_in_data_list;
	int up_out_data_list;
    int down_in_data_list;
    int down_out_data_list;
	void(*speaker)(struct Base_Core* core);		//类似于基类虚函数   函数指针
	void(*process)(struct Base_Core* core);     //类似于基类虚函数   函数指针
	void* parent_core;							//基类指针，如果没有基类，则为NULL
}Base_Core;



//工厂类
typedef struct Core_Factory
{
	Base_Core* (*create_new_core)(CoreType core_type);	//创建的接口，用接口固体封装和隐藏实现细节
}Core_Factory;


//工厂模式构造和析构
Core_Factory* new_core_factory();
void delete_core_factory(Core_Factory* core_factory);

Base_Core*    new_Base_Core();
void delete_Base_Core(struct Base_Core* core);


#endif /* CORE_H_ */


