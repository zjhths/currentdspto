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
#define FLASH_ADDR_555      0x60000AAA    //0x6000AAAA
#define FLASH_ADDR_AAA      0x60000554    //0x60005555
#define FLASH_CMD_AA       0x00AA
#define FLASH_CMD_55        0x0055
#define FLASH_CMD_A0        0x00A0
#define FLASH_CMD_80        0x0080
#define FLASH_CMD_10        0x0010
#define FLASH_CMD_30        0x0030
#define FLASH_CMD_50        0x0050
/*#define   FLASH_ADDR_555      0x6000AAAA              //也可以为0x6000AAAB,因为BA0地址线没有用
#define FLASH_ADDR_AAA      0x60005555              //也可以为0x60005554
#define FLASH_CMD_AA        0x8241
#define FLASH_CMD_55        0x0816
#define FLASH_CMD_A0        0x0201
#define FLASH_CMD_80        0x0001
#define FLASH_CMD_10        0x0800
#define FLASH_CMD_30        0x0A00
#define FLASH_CMD_50        0x0810*/
//#define   FLASH_CMD_AA        0x0A41
//#define   FLASH_CMD_55        0x8118
//#define   FLASH_CMD_A0        0x0201
//#define FLASH_CMD_80      0x0001
//#define   FLASH_CMD_10        0x8000
//#define   FLASH_CMD_30        0x8200
//#define   FLASH_CMD_50        0x8010
extern void NOR_read(unsigned int,unsigned char  *,unsigned int);   //读FLASH相应地址
extern void NOR_write(unsigned int,unsigned char  *,unsigned int);//写FLASH相应地址
extern unsigned short  readFlash(unsigned int addr);            //从32位地址上读16位数据
extern void writeFlash(unsigned int, unsigned short );          //写16位数据到32位地址
extern void NOR_sector_erase(unsigned int sector_addr); //擦除FLASH区域
extern void NOR_block_erase(unsigned int block_addr);
extern void NOR_chip_erase();                       //擦除整片FLASH
//**FLASH变量和函数**


#endif /* MNIC_NOR_H_ */
