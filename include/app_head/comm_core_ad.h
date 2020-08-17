
#ifndef _COMM_AD_H_
#define _COMM_AD_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//������C++ ����
typedef struct Ad_Core
{
	Base_Core* core;
	void (* speaker)(struct Base_Core* core);
	void (* process)(struct Base_Core* core);     //�����ڻ����麯��   ����ָ��

}Ad_Core;

//�����ڹ��캯��
Ad_Core*     new_Ad_Core();

//��������������
void delete_Ad_Core(struct Ad_Core* core);

#endif /* CORE_H_ */
