/*
 * mnic_nor.c
 * ģ�鹦�ܣ�Nor Flash��д��������
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#include "stdint.h"
#include "mnic_nor.h"

/*
 * ��������	  void NOR_read()
 * �������ܣ�   ��FLASH��Ӧ��ַ
 * ������ڣ�   uint32_t addr   ��FLASH�׵�ַ
 *            uint16_t *data  �������׵�ַ
 *            uint32_t length ������
 * �������ڣ�
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
 * ��������	  void NOR_write()
 * �������ܣ�   дFLASH��Ӧ��ַ
 * ������ڣ�   uint32_t addr    дFLASH�׵�ַ
 *            uint16_t *data   д�����׵�ַ
 *            uint32_t length  д����
 * �������ڣ�
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
 * ��������	  void writeFlash()
 * �������ܣ�   д16λ���ݵ�32λ��ַ
 * ������ڣ�   uint16_t data 16λ����
 *            uint32_t addr 32λ��ַ
 * �������ڣ�
 */
void writeFlash(uint32_t addr, uint16_t data)
{
   *(volatile unsigned short *)addr = data;
}

/*
 * ��������	  void readFlash()
 * �������ܣ�   ��32λ��ַ�϶�16λ����
 * ������ڣ�   uint32_t addr 32λ��ַ
 * �������ڣ�   uint16_t data 16λ����
 */
uint16_t readFlash(uint32_t addr)
{
	return *(volatile unsigned short *)addr;
}

/*
 * ��������	  void NOR_sector_erase()
 * �������ܣ�   ����FLASH����
 * ������ڣ�   uint32_t addr �����ַ
 * �������ڣ�
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
 * ��������	  void NOR_block_erase()
 * �������ܣ�   ����FLASH��
 * ������ڣ�   uint32_t addr ���ַ
 * �������ڣ�
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
 * ��������	  void NOR_chip_erase()
 * �������ܣ�   ������ƬFLASH
 * ������ڣ�
 * �������ڣ�
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
