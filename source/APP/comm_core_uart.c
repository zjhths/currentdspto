#include "comm_core_uart.h"
Uart_interface my_uart=0;

//多态接口实现
static void Uart_speaker(struct Base_Core* core)
{
	//printf("this is Uart Core, core type is :%d\n",core->core_type);

}

static void Uart_process(struct Base_Core* core)
{


}

Uart_Core* new_Uart_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Uart_Core* real_core	 = (Uart_Core*)malloc(sizeof(Uart_Core));
	
	printf("Uart_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = Uart_speaker;
	real_core->process   = Uart_process;

	base_core->core_type	 = CORE_UART;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	//my_uart = new_uart_interface();
	return real_core;
}

void delete_Uart_Core(struct Uart_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("Uart_Core delete\n");
}




