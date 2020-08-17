/*
 * mnic_interrupt.h
 *
 *  Created on: 2019-11-15
 *      Author: Administrator
 */

#ifndef MNIC_INTERRUPT_H_
#define MNIC_INTERRUPT_H_


void Init2_bus_data_receive(void);
void Init3_bus_msg_receive(void);
void Init0_485_receive(void);
void Init1_uart_receive(void);
void TimerIsr(void);
void SPI_isr();
void ADS_Isr();
void I2CIsr();
void VM_SPI_and_uart_isr();
void HDLC_int();
void InterCommunication();
void ExterCommunication(unsigned char target);
void VM_spi_int_and_IM_spi_int();
void HDLC_and_uart_isr();




#endif /* MNIC_INTERRUPT_H_ */
