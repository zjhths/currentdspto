#include "comm_core_ad.h"
#include "interface_ad.h"
Ad_interface* m_ad_interface = 0;
//多态接口实现
static void ad_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void ad_process(struct Base_Core* core)
{

}

Ad_Core* new_Ad_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Ad_Core* real_core	 = (Ad_Core*)malloc(sizeof(Ad_Core));
	
	printf("ad_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = ad_speaker;
	real_core->process   = ad_process;

	base_core->core_type	 = CORE_AD;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_ad_interface = new_ad_interface();
	base_core->up_in_data_list = m_ad_interface->recv_fifo;
	return real_core;
}

void delete_Ad_Core(struct Ad_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("ad_Core delete\n");
}




