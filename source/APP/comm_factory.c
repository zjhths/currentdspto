#include "comm_factory.h"
#include "comm_core_hdlc.h"
#include "comm_core_uart.h"
#include "comm_core_ad.h"
#include "comm_core_da.h"

static void Core_speaker(struct Base_Core* core)
{
	printf("this is a base core\n");
}

Base_Core* new_Base_Core()
{
	Base_Core* base_core = (Base_Core*)malloc(sizeof(Base_Core));
	printf("BaseCore create\n");
	base_core->core_type = CORE_NONE;
	base_core->parent_core = NULL;
	base_core->speaker = Core_speaker;
	return base_core;
}

Base_Core* create_new_Core(CoreType core_type)
{
	Base_Core* base_core = NULL;
	switch (core_type)
	{
	case CORE_HDLC:
	{
		Hdlc_Core* real_core = new_Hdlc_Core();
		base_core = real_core->core;
		break;
	}
	case CORE_UART:
	{
		Uart_Core* real_core = new_Uart_Core();
		base_core = real_core->core;
		break;
	}
	case CORE_AD:
	{
		Ad_Core* real_core = new_Ad_Core();
		base_core = real_core->core;
		break;
	}
	case CORE_DA:
	{
		Da_Core* real_core = new_Da_Core();
		base_core = real_core->core;
		break;
	}
	default:
		break;
	}
	return base_core;
}

void delete_Base_Core(struct Base_Core* core)
{
	if (NULL != core->parent_core)
	{
		switch (core->core_type)
		{
		case CORE_HDLC:
		{
			delete_Hdlc_Core((Hdlc_Core*)core->parent_core);
			core = NULL;
			break;
		}
		case CORE_UART:
		{
			delete_Uart_Core((Uart_Core*)core->parent_core);
			core = NULL;
			break;
		}
		case CORE_AD:
		{
			delete_Ad_Core((Ad_Core*)core->parent_core);
			core = NULL;
			break;
		}
		case CORE_DA:
		{
			delete_Da_Core((Da_Core*)core->parent_core);
			core = NULL;
			break;
		}

		default:
			break;
		}
	}

	if (NULL != core)
	{
		free(core);
		core = NULL;
	}
	printf("Base_Core delete\n");
}

Core_Factory* new_core_factory()
{
	Core_Factory* core_factory = (Core_Factory*)malloc(sizeof(Core_Factory));
	core_factory->create_new_core = create_new_Core;
	return core_factory;
}

void delete_core_factory(Core_Factory* core_factory)
{
	free(core_factory);
	core_factory = NULL;
}
