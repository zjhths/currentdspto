#include "comm_core_hdlc.h"
#include "fifo.h"
#include "interface_hdlc.h"

Hdlc_interface* my_hdlc;




//#ifndef MAIN

//#endif
//��̬�ӿ�ʵ��
static void Hdlc_speaker(struct Base_Core* core)
{
	printf("this is Hdlc Core, core type is :%d\n",core->core_type);

}

static void Hdlc_process(struct Base_Core* core)
{   unsigned char temp[HDLC_CMD_SIZE];
    if(fifo_readable(core->up_out_data_list))
    {
        fifo_read(core->up_out_data_list, (void *)temp);
        my_hdlc->send(my_hdlc,temp,HDLC_CMD_SIZE);
    }
}

Hdlc_Core* new_Hdlc_Core()
{
	Base_Core* base_core	 = new_Base_Core();							//�ȹ������
	Hdlc_Core* real_core  = (Hdlc_Core*)malloc(sizeof(Hdlc_Core));	//�ڹ��������࣬Ӧ���������˳������ڴ�Ƚ���
	my_hdlc=new_hdlc_interface(0);
	printf("Hdlc_Core create\n");

	real_core->core		 = base_core;								
	real_core->speaker	 = Hdlc_speaker;
	real_core->process   = Hdlc_process;

	base_core->core_type	 = CORE_HDLC;								//����ʼ�������ڻ����麯����
	base_core->parent_core = (void*)real_core;
	base_core->speaker	 = real_core->speaker;
	base_core->process   = real_core->process;

	base_core->up_out_data_list =  fifo_create(3, HDLC_CMD_SIZE);
	base_core->up_in_data_list =  my_hdlc->recv_fifo;
	my_hdlc->send_fifo = base_core->up_in_data_list;
	return real_core;
}




void delete_Hdlc_Core(struct Hdlc_Core* core)
{
	free(core->core);			//�ͷ���������ڴ�
	core->core = NULL;
	free(core);
	printf("Hdlc_Core delete\n");
}




