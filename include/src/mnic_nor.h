/*
 * mnic_nor.h
 *
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#ifndef MNIC_NOR_H_
#define MNIC_NOR_H_

//**FLASH变量和函数**

#define NOR_FLASH_BASE              (0x60000000)

//FLASH指令操作请查找数据手册
#define	FLASH_ADDR_555		0x6000AAAA              //也可以为0x6000AAAB,因为BA0地址线没有用
#define	FLASH_ADDR_AAA		0x60005555              //也可以为0x60005554
#define	FLASH_CMD_AA		0x8241
#define	FLASH_CMD_55		0x0816
#define	FLASH_CMD_A0		0x0201
#define FLASH_CMD_80		0x0001
#define	FLASH_CMD_10		0x0800
#define	FLASH_CMD_30		0x0A00
#define	FLASH_CMD_50		0x0810
//#define	FLASH_CMD_AA		0x0A41
//#define	FLASH_CMD_55		0x8118
//#define	FLASH_CMD_A0		0x0201
//#define FLASH_CMD_80		0x0001
//#define	FLASH_CMD_10		0x8000
//#define	FLASH_CMD_30		0x8200
//#define	FLASH_CMD_50		0x8010
extern void NOR_read(uint32_t,uint16_t *,uint32_t);	//读FLASH相应地址
extern void NOR_write(uint32_t,uint16_t *,uint32_t);//写FLASH相应地址
extern uint16_t readFlash(uint32_t addr);			//从32位地址上读16位数据
extern void writeFlash(uint32_t, uint16_t);			//写16位数据到32位地址
extern void NOR_sector_erase(uint32_t sector_addr);	//擦除FLASH区域
extern void NOR_block_erase(uint32_t block_addr);
extern void NOR_chip_erase();						//擦除整片FLASH
//**FLASH变量和函数**


#endif /* MNIC_NOR_H_ */
