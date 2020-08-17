
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

//������C++ ����
typedef struct Base_Core
{
	CoreType core_type;
	int up_in_data_list;
	int up_out_data_list;
    int down_in_data_list;
    int down_out_data_list;
	void(*speaker)(struct Base_Core* core);		//�����ڻ����麯��   ����ָ��
	void(*process)(struct Base_Core* core);     //�����ڻ����麯��   ����ָ��
	void* parent_core;							//����ָ�룬���û�л��࣬��ΪNULL
}Base_Core;



//������
typedef struct Core_Factory
{
	Base_Core* (*create_new_core)(CoreType core_type);	//�����Ľӿڣ��ýӿڹ����װ������ʵ��ϸ��
}Core_Factory;


//����ģʽ���������
Core_Factory* new_core_factory();
void delete_core_factory(Core_Factory* core_factory);

Base_Core*    new_Base_Core();
void delete_Base_Core(struct Base_Core* core);


#endif /* CORE_H_ */


