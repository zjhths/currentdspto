
#ifndef _COMM_HDLC_H_
#define _COMM_HDLC_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//������C++ ����
typedef struct Hdlc_Core
{
	Base_Core* core;								//�����ڼ̳л��࣬�ýṹ�����ʵ�� ����̳б�����ڵ�һ��Աλ�ô�
	void (* speaker)(struct Base_Core* core);		//��������д�����麯��,�������
	void (* process)(struct Base_Core* core);     //�����ڻ����麯��   ����ָ��
}Hdlc_Core;


//�����ڹ��캯��

Hdlc_Core*   new_Hdlc_Core();

//��������������
void delete_Hdlc_Core(struct Hdlc_Core* core);

#endif /* CORE_H_ */
