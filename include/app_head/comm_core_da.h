
#ifndef _COMM_DA_H_
#define _COMM_DA_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//������C++ ����
typedef struct Da_Core
{
	Base_Core* core;
	void (* speaker)(struct Base_Core* core);
	void (* process)(struct Base_Core* core);     //�����ڻ����麯��   ����ָ��

}Da_Core;

//�����ڹ��캯��
Da_Core*     new_Da_Core();

//��������������
void delete_Da_Core(struct Da_Core* core);

#endif /* CORE_H_ */
