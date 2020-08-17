/*
 * mnic_test.c
 *
 *  Created on: 2015-12-7
 *      Author: SUN
 */
#include "hw_types.h"
#include "stdio.h"
#include "stdint.h"
#include "mnic_nor.h"
#include "mnic_test.h"

int timer_test_flag=0;
int get_init_count = 0;
int set_init_count = 0;

void EmifFpgaTest(void)
{
	uint16_t TestRbVal = 0;
	uint16_t TestVal = 0;
	uint16_t LedVal = 0x01;
	uint32_t i = 0;
	//HWREGH(0x62000008) = LedVal;
	HWREGH(0x62000004) = 0x55;
	TestRbVal= HWREGH(0x62000004);
	TestVal = HWREGH(0x62000000);
	printf("\nEMIF fpga test is running....\n");
	while(TestVal < 16)
	{
		//HWREGH(LEDADDR) = LedVal;

		HWREGH(RWADDR) = TestVal;

		TestRbVal = HWREGH(RWADDR);

		if(TestVal != TestRbVal)
		{
			printf("EMIF fpga test error. Write value is %d but read back value is %d\n",TestVal,TestRbVal);
			return;
		}
		for (i = 0; i <= 15000000; i++)
			asm("	NOP");

		TestVal++;
		//LedVal = ~LedVal;
	}
	printf("EMIF fpga test has passed.\n");
}

void DDR2Test(void)
{
	unsigned int i,errorCnt = 0;
    unsigned int Length = 0x8000000 / 4;   //Test as DWORD, total 128MB(1Gb)

    printf("\nDDR2 test is running....\n");
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = 0;

		if(HWREG(DDR2STARTADDR + i) != 0x00000000)
		{
			errorCnt++;
			printf("When writing 0x00000000, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}

	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != 0x00000000)
		{
			errorCnt++;
			printf("When writing 0x00000000, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}

	if(errorCnt > 0)
		printf("Writing 0x00000000 is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing 0x00000000 is ok.\n");

	errorCnt = 0;
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = 0xFFFFFFFF;

		if(HWREG(DDR2STARTADDR + i) != 0xFFFFFFFF)
		{
			errorCnt++;
			printf("When writing 0xFFFFFFFF, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != 0xFFFFFFFF)
		{
			errorCnt++;
			printf("When writing 0xFFFFFFFF, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	if(errorCnt > 0)
		printf("Writing 0xFFFFFFFF is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing 0xFFFFFFFF is ok.\n");

	errorCnt = 0;
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = 0xAAAAAAAA;

		if(HWREG(DDR2STARTADDR + i) != 0xAAAAAAAA)
		{
			errorCnt++;
			printf("When writing 0xAAAAAAAA, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != 0xAAAAAAAA)
		{
			errorCnt++;
			printf("When writing 0xAAAAAAAA, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	if(errorCnt > 0)
		printf("Writing 0xAAAAAAAA is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing 0xAAAAAAAA is ok.\n");

	errorCnt = 0;
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = 0x55555555;
		if(HWREG(DDR2STARTADDR + i) != 0x55555555)
		{
			errorCnt++;
			printf("When writing 0x55555555, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != 0x55555555)
		{
			errorCnt++;
			printf("When writing 0x55555555, Address 0x%x is error, Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	if(errorCnt > 0)
		printf("Writing 0x55555555 is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing 0x55555555 is ok.\n");

	errorCnt = 0;
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = i*4;
		if(HWREG(DDR2STARTADDR + i) != i*4)
		{
			errorCnt++;
			printf("When writing sequence data, Address 0x%x is error Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}
	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != i*4)
		{
			errorCnt++;
			printf("When writing sequence data, Address 0x%x is error Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}

	if(errorCnt > 0)
		printf("Writing sequence data is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing sequence data is ok.\n");

	errorCnt = 0;
	for(i = 0; i < Length; i++)
	{
		HWREG(DDR2STARTADDR + i) = (Length-i) * 4;

		if(HWREG(DDR2STARTADDR + i) != (Length-i) * 4)
		{
			errorCnt++;
			printf("When writing reverse sequence data, Address 0x%x is error Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}

	for(i = 0; i < Length; i++)
	{
		if(HWREG(DDR2STARTADDR + i) != (Length-i) * 4)
		{
			errorCnt++;
			printf("When writing reverse sequence data, Address 0x%x is error Value is 0x%x!\n", i, HWREG(DDR2STARTADDR + i));
		}
	}

	if(errorCnt > 0)
		printf("Writing reverse sequence data is fail, %d error(s) occurred!\n", errorCnt);
	else
		printf("Writing reverse sequence data is ok.\n");

	printf("DDR2 Test has finished.\n");

}

/*
 * 函数功能:测试FLASH擦除,读写
 * 说明: FLASH 6401B的大小为4M*16bit,块尺寸为32K*16bit,该测试程序对两个块进行了测试
 */
void NorFlashTest(void)
{
	int32_t i, j, errorCnt = 0;
    unsigned int Length = 0x10000;  //Full test: 0x400000 (FLASH 6401B : 4M*16bit  block size: 32K*16bit  length=0x10000:test two block)
    uint32_t Flash_StartAdd;
    uint16_t read_data=0;
    uint16_t write_data=0;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;

    printf("\nFlash test is running....\n");

    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);

	for(i = 0; i < Length; i++)
	{
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != 0)
		{
			errorCnt++;
			printf("When writing 0x0000, Address 0x%x is error, Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing 0x0000 is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing 0x0000 is ok.\n");

	errorCnt = 0;
	write_data=0xFFFF;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;
    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);
	for(i = 0; i < Length; i++)
	{
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != 0xFFFF)
		{
			errorCnt++;
			printf("When writing 0xFFFF, Address 0x%x is error, Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing 0xFFFF is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing 0xFFFF is ok.\n");

	errorCnt = 0;
	write_data=0xAAAA;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;
    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);
	for(i = 0; i < Length; i++)
	{
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != 0xAAAA)
		{
			errorCnt++;
			printf("When writing 0xAAAA, Address 0x%x is error, Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing 0xAAAA is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing 0xAAAA is ok.\n");

	errorCnt = 0;
	write_data=0x5555;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;
    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);
	for(i = 0; i < Length; i++)
	{
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != 0x5555)
		{
			errorCnt++;
			printf("When writing 0x5555, Address 0x%x is error, Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing 0x5555 is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing 0x5555 is ok.\n");

	errorCnt = 0;
	i=0;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;
    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);
	for(i = 0; i < Length; i++)
	{
		if(j*2>65535)
			j=0;

		write_data=j*2;
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != j*2)
		{
			errorCnt++;
			printf("When writing sequence data, Address 0x%x is error Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		j++;
		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing sequence data is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing sequence data is ok.\n");

	errorCnt = 0;
    Flash_StartAdd=(uint32_t)NOR_FLASH_BASE;
    j=32767;
    NOR_block_erase(Flash_StartAdd);
    NOR_block_erase(Flash_StartAdd+2*0x8000);
	for(i = 0; i < Length; i++)
	{
		if(j<0)
			j=32767;

		write_data = j*2;
		NOR_write(Flash_StartAdd, &write_data, 1);
		NOR_read(Flash_StartAdd, &read_data, 1);

		if(read_data != j*2)
		{
			errorCnt++;
			printf("When writing reverse sequence data, Address 0x%x is error Value is 0x%x!\n", Flash_StartAdd, read_data);
		}

		j--;
		Flash_StartAdd = Flash_StartAdd + 2;
	}

	if(errorCnt > 0)
		printf("Writing reverse sequence data is fail, %d error(s) occurred!\n",errorCnt);
	else
		printf("Writing reverse sequence data is ok.\n");

	printf("Flash Test has finished.\n");

}
/*****************************END OF FILE************************************/
