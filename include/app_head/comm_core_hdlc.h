
#ifndef _COMM_HDLC_H_
#define _COMM_HDLC_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//类似于C++ 子类
typedef struct Hdlc_Core
{
	Base_Core* core;								//类似于继承基类，用结构体包含实现 基类继承必须放在第一成员位置处
	void (* speaker)(struct Base_Core* core);		//类似于重写基类虚函数,这里访问
	void (* process)(struct Base_Core* core);     //类似于基类虚函数   函数指针
}Hdlc_Core;


//类似于构造函数

Hdlc_Core*   new_Hdlc_Core();

//类似于析构函数
void delete_Hdlc_Core(struct Hdlc_Core* core);

#endif /* CORE_H_ */
