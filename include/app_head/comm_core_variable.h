
#ifndef _COMM_VARIABLE_H_
#define _COMM_VARIABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "comm_factory.h"

//绫讳技浜嶤++ 瀛愮被
typedef struct Variable_Core
{
	Base_Core* core;
	void (* speaker)(struct Base_Core* core);
	void (* process)(struct Base_Core* core);     //绫讳技浜庡熀绫昏櫄鍑芥暟   鍑芥暟鎸囬拡

}Variable_Core;

//绫讳技浜庢瀯閫犲嚱鏁�
Variable_Core*  new_Variable_Core();

//绫讳技浜庢瀽鏋勫嚱鏁�
void delete_Variable_Core(struct Variable_Core* core);

#endif /* CORE_H_ */
