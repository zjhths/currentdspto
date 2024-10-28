#include "comm_core_fusion.h"
#include "interface_fusion.h"
Fusion_interface* m_fusion_interface = 0;
//多态接口实现
static void fusion_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void fusion_process(struct Base_Core* core)
{

}

Fusion_Core* new_Fusion_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Fusion_Core* real_core	 = (Fusion_Core*)malloc(sizeof(Fusion_Core));
	
	printf("fusion_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = fusion_speaker;
	real_core->process   = fusion_process;

	base_core->core_type	 = CORE_FUSION;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_fusion_interface = new_fusion_interface();
	base_core->up_in_data_list = m_fusion_interface->recv_fifo;
	return real_core;
}

void delete_Fusion_Core(struct Fusion_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("fusion_Core delete\n");
}




