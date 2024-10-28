#include "comm_core_variable.h"
#include "interface_variable.h"
Variable_interface* m_variable_interface = 0;
//多态接口实现
static void variable_speaker(struct Base_Core* core)
{
	//printf("this is ad Core, core type is :%d\n",core->core_type);

}

static void variable_process(struct Base_Core* core)
{

}

Variable_Core* new_Variable_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Variable_Core* real_core	 = (Variable_Core*)malloc(sizeof(Variable_Core));
	
	printf("variable_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = variable_speaker;
	real_core->process   = variable_process;

	base_core->core_type	 = CORE_VARIABLE;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	m_variable_interface = new_variable_interface();
	base_core->up_in_data_list = m_variable_interface->recv_fifo;
	return real_core;
}

void delete_Variable_Core(struct Variable_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("variable_Core delete\n");
}




