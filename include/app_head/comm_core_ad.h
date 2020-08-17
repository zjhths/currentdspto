
#ifndef _COMM_AD_H_
#define _COMM_AD_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//类似于C++ 子类
typedef struct Ad_Core
{
	Base_Core* core;
	void (* speaker)(struct Base_Core* core);
	void (* process)(struct Base_Core* core);     //类似于基类虚函数   函数指针

}Ad_Core;

//类似于构造函数
Ad_Core*     new_Ad_Core();

//类似于析构函数
void delete_Ad_Core(struct Ad_Core* core);

#endif /* CORE_H_ */
