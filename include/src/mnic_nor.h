/*
 * mnic_nor.h
 *
 *  Created on: 2015-12-7
 *      Author: SUN
 */

#ifndef MNIC_NOR_H_
#define MNIC_NOR_H_

//**FLASH�����ͺ���**

#define NOR_FLASH_BASE              (0x60000000)

//FLASHָ���������������ֲ�
#define	FLASH_ADDR_555		0x6000AAAA              //Ҳ����Ϊ0x6000AAAB,��ΪBA0��ַ��û����
#define	FLASH_ADDR_AAA		0x60005555              //Ҳ����Ϊ0x60005554
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
extern void NOR_read(uint32_t,uint16_t *,uint32_t);	//��FLASH��Ӧ��ַ
extern void NOR_write(uint32_t,uint16_t *,uint32_t);//дFLASH��Ӧ��ַ
extern uint16_t readFlash(uint32_t addr);			//��32λ��ַ�϶�16λ����
extern void writeFlash(uint32_t, uint16_t);			//д16λ���ݵ�32λ��ַ
extern void NOR_sector_erase(uint32_t sector_addr);	//����FLASH����
extern void NOR_block_erase(uint32_t block_addr);
extern void NOR_chip_erase();						//������ƬFLASH
//**FLASH�����ͺ���**


#endif /* MNIC_NOR_H_ */
