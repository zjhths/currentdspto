
#ifndef _COMM_UART_H_
#define _COMM_UART_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"
//������C++ ����
typedef struct Uart_Core
{
	Base_Core* core;
	void (* speaker)(struct Base_Core* core);
	void (* process)(struct Base_Core* core);     //�����ڻ����麯��   ����ָ��

}Uart_Core;

//�����ڹ��캯��
Uart_Core*     new_Uart_Core();

//��������������
void delete_Uart_Core(struct Uart_Core* core);

#endif /* CORE_H_ */
