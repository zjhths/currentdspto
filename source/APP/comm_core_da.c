#include "comm_core_da.h"
#include "interface_da.h"
Da_interface* m_da_interface;
unsigned int testflag=0;
//多态接口实现
static void da_speaker(struct Base_Core* core)
{
	//printf("this is da Core, core type is :%d\n",core->core_type);

}

static void da_process(struct Base_Core* core)
{
	unsigned char temp[DA_CMD_SIZE];
	    //if(fifo_readable(core->up_out_data_list))
	    if(testflag == 1)
	    {testflag=0;
	        //fifo_read(core->up_out_data_list, (void *)temp);
	        m_da_interface->send(m_da_interface,temp,DA_CMD_SIZE);
	    }
}

Da_Core* new_Da_Core()
{
	Base_Core* base_core	 = new_Base_Core();
	Da_Core* real_core	 =    (Da_Core*)malloc(sizeof(Da_Core));
	m_da_interface       =    new_da_interface();
	printf("da_Core create\n");
	
	real_core->core		 = base_core;
	real_core->speaker	 = da_speaker;
	real_core->process   = da_process;

	base_core->core_type	 = CORE_DA;
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	base_core->up_out_data_list =  fifo_create(3, DA_CMD_SIZE);
	return real_core;
}

void delete_Da_Core(struct Da_Core* core)
{
	free(core->core);
	core->core = NULL;
	free(core);
	printf("da_Core delete\n");
}




