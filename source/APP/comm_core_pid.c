#include "comm_core_pid.h"
#include "interface_pid.h"
Pid_interface* m_pid_interface = 0;
//多态接口实现
static void pid_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void pid_process(struct Base_Core* core)
{

}

Pid_Core* new_Pid_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Pid_Core* real_core	 = (Pid_Core*)malloc(sizeof(Pid_Core));
	
	printf("pid_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = pid_speaker;
	real_core->process   = pid_process;

	base_core->core_type	 = CORE_PID;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_pid_interface = new_pid_interface();
	base_core->up_in_data_list = m_pid_interface->recv_fifo;
	return real_core;
}

void delete_Pid_Core(struct Pid_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("pid_Core delete\n");
}




