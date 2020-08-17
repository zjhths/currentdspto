
#ifndef MINI_SPI_H_
#define MINI_SPI_H_

#define SIMO_SOMI_CLK_CS        0x00000E01
#define CHAR_LENGTH             0x8

#define SEND_BUF_SIZE			64
#define RECV_BUF_SIZE			64


 void SPIConfigDataFmtReg(unsigned int dataFormat);
 void SPIIsr(void);
 void SetUpSPI(void);
void SPIInit(void);
 void SPIIntInit();

unsigned char Spi_Read_Byte();
void Spi_Write_Byte(unsigned char wb);
void Spi_Read_Buff(unsigned char *rbuf, unsigned int index);
void Spi_Write_Buff(unsigned char *wbuf, unsigned int index);


void SPI0CSPinMuxSetup(unsigned int csPinNum);
void SPI1CSPinMuxSetup(unsigned int csPinNum);
void SPIPinMuxSetup(unsigned int instanceNum);
void CS_Enable();

extern unsigned char recv_buf[];
extern unsigned char send_buf[];

#endif /* MNIC_SPI_H_ */
