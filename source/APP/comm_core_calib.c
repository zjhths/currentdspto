#include "comm_core_calib.h"
#include "interface_calib.h"
Calib_interface* m_calib_interface = 0;
//多态接口实现
static void calib_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void calib_process(struct Base_Core* core)
{

}

Calib_Core* new_Calib_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Calib_Core* real_core	 = (Calib_Core*)malloc(sizeof(Calib_Core));
	
	printf("calib_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = calib_speaker;
	real_core->process   = calib_process;

	base_core->core_type	 = CORE_CALIB;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_calib_interface = new_calib_interface();
	base_core->up_in_data_list = m_calib_interface->recv_fifo;
	return real_core;
}

void delete_Calib_Core(struct Calib_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("calib_Core delete\n");
}




