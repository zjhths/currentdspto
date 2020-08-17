/*
 * mnic_nor.c
 * 模块功能：Nor Flash读写擦除操作
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#include "stdint.h"
#include "mnic_nor.h"

/*
 * 函数名：	  void NOR_read()
 * 函数功能：   读FLASH相应地址
 * 函数入口：   uint32_t addr   读FLASH首地址
 *            uint16_t *data  读数据首地址
 *            uint32_t length 读长度
 * 函数出口：
 */
void NOR_read(uint32_t addr, uint16_t *data, uint32_t length)
{
   uint32_t i;
   uint16_t *src= (uint16_t *)addr;

   for (i = 0; i < length; i++)
   {
     *data++ = *src++;
   }
}

/*
 * 函数名：	  void NOR_write()
 * 函数功能：   写FLASH相应地址
 * 函数入口：   uint32_t addr    写FLASH首地址
 *            uint16_t *data   写数据首地址
 *            uint32_t length  写长度
 * 函数出口：
 */
void NOR_write(uint32_t addr, uint16_t *data, uint32_t length)
{
   uint32_t i,j;
   uint16_t *des= (uint16_t *)addr;

   for (i = 0; i < length; i++)
   {
		writeFlash(FLASH_ADDR_555, FLASH_CMD_AA);/*0xAA*/
	  	writeFlash(FLASH_ADDR_AAA, FLASH_CMD_55);/*0x55*/
	  	writeFlash(FLASH_ADDR_555, FLASH_CMD_A0);/*0xa0*/

		*des++ = *data++;
	  	for (j=0;j<1000;j++)
			asm("	NOP");
   }
}

/*
 * 函数名：	  void writeFlash()
 * 函数功能：   写16位数据到32位地址
 * 函数入口：   uint16_t data 16位数据
 *            uint32_t addr 32位地址
 * 函数出口：
 */
void writeFlash(uint32_t addr, uint16_t data)
{
   *(volatile unsigned short *)addr = data;
}

/*
 * 函数名：	  void readFlash()
 * 函数功能：   从32位地址上读16位数据
 * 函数入口：   uint32_t addr 32位地址
 * 函数出口：   uint16_t data 16位数据
 */
uint16_t readFlash(uint32_t addr)
{
	return *(volatile unsigned short *)addr;
}

/*
 * 函数名：	  void NOR_sector_erase()
 * 函数功能：   擦除FLASH区域
 * 函数入口：   uint32_t addr 区域地址
 * 函数出口：
 */
void NOR_sector_erase(uint32_t sector_addr)
{
	int i;

  	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_80);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	/*50 for 6401B 30 for 6401*/
	writeFlash(sector_addr,FLASH_CMD_50);

	/*Sector-Erase MAX:25 ms*/
	for (i=0;i<6900000;i++)
		asm("	NOP");
}

/*
 * 函数名：	  void NOR_block_erase()
 * 函数功能：   擦除FLASH块
 * 函数入口：   uint32_t addr 块地址
 * 函数出口：
 */
void NOR_block_erase(uint32_t block_addr)
{
	int i;

  	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_80);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	/*30 for 6401B 50 for 6401*/
	writeFlash(block_addr,FLASH_CMD_30);

	/*Block-Erase MAX:25 ms*/
	for (i=0;i<6900000;i++)
		asm("	NOP");
}

/*
 * 函数名：	  void NOR_chip_erase()
 * 函数功能：   擦除整片FLASH
 * 函数入口：
 * 函数出口：
 */
void NOR_chip_erase()
{
	int i;

  	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_80);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_AA);
	writeFlash(FLASH_ADDR_AAA,FLASH_CMD_55);
	writeFlash(FLASH_ADDR_555,FLASH_CMD_10);

	/*Chip-Erase MAX:50 ms*/
	for (i=0;i<13800000;i++)
		asm("	NOP");
}
/*****************************END OF FILE************************************/
