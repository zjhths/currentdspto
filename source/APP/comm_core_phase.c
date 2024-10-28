#include "comm_core_phase.h"
#include "interface_phase.h"
Phase_interface* m_phase_interface = 0;
//澶氭�佹帴鍙ｅ疄鐜�
static void phase_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void phase_process(struct Base_Core* core)
{

}

Phase_Core* new_Phase_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Phase_Core* real_core	 = (Phase_Core*)malloc(sizeof(Phase_Core));
	
	printf("Phase_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = phase_speaker;
	real_core->process   = phase_process;

	base_core->core_type	 = CORE_PHASE;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_phase_interface = new_phase_interface();
	base_core->up_in_data_list = m_phase_interface->recv_fifo;
	return real_core;
}

void delete_Phase_Core(struct Phase_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("phase_Core delete\n");
}
