
#include "hw_types.h"
#include "hw_syscfg0_C6748.h"
#include "soc_C6748.h"
#include "hw_psc_C6748.h"
#include "mnic_C6748.h"
#include "uart.h"
#include "spi.h"
#include "psc.h"
#include "interrupt.h"
#include "mini_spi.h"
#include "spi.h"
//#include "wizchip_conf.h"
#include "string.h"
#include "fpga.h"
#include "gpio.h"

/* value to configure SMIO,SOMI,CLK and CS pin as functional pin */

volatile unsigned int flag_rx = 1;
volatile unsigned int flag_tx = 1;
unsigned int eth_tx_len;
unsigned int eth_rx_len=1;

unsigned char recv_buf[RECV_BUF_SIZE];
unsigned char send_buf[SEND_BUF_SIZE];

unsigned char *p_rx = recv_buf;
unsigned char *p_tx = send_buf;


void SPIInit()
{/* Waking up the SPI0 instance. */
	PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_SPI0, PSC_POWERDOMAIN_ALWAYS_ON,
					 PSC_MDCTL_NEXT_ENABLE);

    /* Performing the Pin Multiplexing for SPI0. */
    SPIPinMuxSetup(0);

    /* Using the Chip Select(CS) 0 pin of SPI0.  */
    SPI1CSPinMuxSetup(0);

    /* Enable use of SPI0 interrupts. */
//   SPIIntInit();

    /* Configuring and enabling the SPI0 instance. */
    SetUpSPI();

    CS_Enable();
}

 void SPIIntInit()
{
	 // Disable DSP CPU interrupts globally
	 	IntGlobalDisable();

	 	// Register the ISR in the vector table
	 	IntRegister(C674X_MASK_INT5, SPIIsr);

	 	// Map system interrupt to the DSP maskable interrupt
	 	IntEventMap(C674X_MASK_INT5, SYS_INT_SPI0_INT);

	 	// Enable the DSP maskable interrupt
	 	IntEnable(C674X_MASK_INT5);

	 	// Enable DSP interrupts globally
	 	IntGlobalEnable();
}

/*
** Configures SPI Controller
**
*/
 void SetUpSPI(void)
{
	 unsigned char dcs = 0x01;
	    unsigned int  val = SIMO_SOMI_CLK_CS;

	    SPIReset(SOC_SPI_0_REGS);

	    SPIOutOfReset(SOC_SPI_0_REGS);

	    SPIModeConfigure(SOC_SPI_0_REGS, SPI_MASTER_MODE);

	    /* moduleClk = coreClk/2 = 456MHz/2 = 228MHz spiClk = 1MHz */
	    SPIClkConfigure(SOC_SPI_0_REGS, 228000000, 1000000, SPI_DATA_FORMAT0);

	    SPIPinControl(SOC_SPI_0_REGS, 0, 0, &val);

	    /* Sets the default value for CS pin(line) */
	    SPIDefaultCSSet(SOC_SPI_0_REGS, dcs);

	    /* Configures SPI Data Format Register */
	    SPIConfigDataFmtReg(SPI_DATA_FORMAT0);

	     /* Selects the SPI Data format register to used and Sets CSHOLD
	      * to assert CS pin(line)
	      */
	    SPIDat1Config(SOC_SPI_0_REGS, SPI_CSHOLD | SPI_DATA_FORMAT0, 0x01);

	     /* map interrupts to interrupt line INT1 */
	    SPIIntLevelSet(SOC_SPI_0_REGS, SPI_RECV_INTLVL | SPI_TRANSMIT_INTLVL);

	    /* Enable SPI communication */
	    SPIEnable(SOC_SPI_0_REGS);
}

/*
** Configures Data Format register of SPI
**
*/
 void SPIConfigDataFmtReg(unsigned int dataFormat)
{
	 /* Configures the polarity and phase of SPI clock */
	     SPIConfigClkFormat(SOC_SPI_0_REGS,
	                        (SPI_CLK_POL_HIGH | SPI_CLK_INPHASE),
	                        dataFormat);

	     /* Configures SPI to transmit MSB bit First during data transfer */
	     SPIShiftMsbFirst(SOC_SPI_0_REGS, dataFormat);

	     /* Sets the Charcter length */
	     SPICharLengthSet(SOC_SPI_0_REGS, CHAR_LENGTH, dataFormat);
}

/*
** Read a byte from SPI
** Implement the callback functions
*/
unsigned char Spi_Read_Byte()
{
    p_tx = &send_buf[0];
    p_rx = &recv_buf[0];
    eth_rx_len=  4;
    eth_tx_len = 4;
  //  GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_LOW);
        SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), 0x1);
      SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));
       // SPIIntEnable(SOC_SPI_0_REGS, SPI_RECV_INT);
        while(flag_tx);
        flag_rx = 1;
        flag_tx = 1;
        SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);
   //     GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_HIGH);
    return recv_buf[2];
}
/*
** Write a byte from SPI
** Implement the callback functions
*/
void Spi_Write_Byte(unsigned char wb)
{
    p_tx = &send_buf[0];
    p_rx = &recv_buf[0];
	eth_tx_len = 1;
	eth_rx_len = 0;
    send_buf[0] = wb;
  //  GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_LOW);

        SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), 0x1);
        SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));
       // SPIIntEnable(SOC_SPI_0_REGS, SPI_TRANSMIT_INT);
        while(flag_tx);
        flag_tx = 1;
        flag_rx = 1;
        SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);
      //  asm("	NOP");
     //   GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_HIGH);
}

/**
 * \brief   Read bytes from SPI, Implement the callback functions
 *
 * \param   *rbuf	:	Points of the bytes prepare read from SPI
 *
 * 			index	:	length of the bytes
 *
 * \return  None.
 */
 void Spi_Read_Buff(unsigned char *rbuf, unsigned int index)
{
	int i = 0;

//	for(i = 0; i < RECV_BUF_SIZE; i++) recv_buf[i] = 0;
    p_tx = &send_buf[0];
    p_rx = &recv_buf[0];
    eth_rx_len=index;
    SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), 0x1);
    //SPIIntEnable(SOC_SPI_0_REGS, SPI_RECV_INT); //接收中断使能
    SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));
    while(flag_tx||flag_rx);
    flag_rx = 1;
    flag_tx = 1;
    SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);
	for(i = 0; i < index; i++) rbuf[i] = recv_buf[i];
}

/**
 * \brief   Write bytes from SPI, Implement the callback functions
 *
 * \param   *wbuf	:	Points of the bytes prepare write to SPI
 *
 * 			index	:	length of the bytes
 *
 * \return  None.
 */
void Spi_Write_Buff(unsigned char *wbuf, unsigned int index)
{

	unsigned int i;

	p_tx = &send_buf[0];
	p_rx = &recv_buf[0];

	eth_tx_len = index;
	eth_rx_len = 0;
	for(i = 0; i < index; i++) send_buf[i] = wbuf[i];
//	GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_LOW);

	SPIDat1Config(SOC_SPI_0_REGS, (SPI_CSHOLD | SPI_DATA_FORMAT0), 0x1);
	SPIIntEnable(SOC_SPI_0_REGS, (SPI_RECV_INT | SPI_TRANSMIT_INT));//发送中断使能
	//SPIIntEnable(SOC_SPI_0_REGS, SPI_TRANSMIT_INT);
    while(flag_tx);
	flag_tx = 1;
	flag_rx = 1;
	SPIDat1Config(SOC_SPI_0_REGS, SPI_DATA_FORMAT0, 0x1);
	asm("	NOP");
	//GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_HIGH);

}


/*
** Data transmission and reception SPIIsr
**
*/
 void SPIIsr(void)
{
    unsigned int intCode = 0;

    IntEventClear(SYS_INT_SPI0_INT);

    intCode = SPIInterruptVectorGet(SOC_SPI_0_REGS);

    while (intCode)
    {
        if(intCode == SPI_TX_BUF_EMPTY) //发送中断
        {

            if (!eth_tx_len)
            {
            	flag_tx = 0;  //接收清零
                SPIIntDisable(SOC_SPI_0_REGS, SPI_TRANSMIT_INT);
            }
            else
            {

            	eth_tx_len--;
            	SPITransmitData1(SOC_SPI_0_REGS, *p_tx);
            	p_tx++;
            }
        }

        if(intCode == SPI_RECV_FULL) //接收中断
        {
        	 eth_rx_len--;
        	  *p_rx = (char)SPIDataReceive(SOC_SPI_0_REGS);
        	   p_rx++;
            if (!eth_rx_len)
            {

                SPIIntDisable(SOC_SPI_0_REGS, SPI_RECV_INT);
                flag_rx = 0;  //接收清零
            }



        }
        intCode = SPIInterruptVectorGet(SOC_SPI_0_REGS);//查看是否还有数据发送或接收
    }
   // flag = 0;   //发送清零
}

 /**
  * \brief   This function selects the SPI0 pins for use. The SPI0 pins
  *          are multiplexed with pins of other peripherals in the
  *          System on Chip(SoC).
  *
  * \param   None.
  *
  * \return  None.
  */

 /* Pin multiplexing bit masks for SPI0 pins. */
 #define PINMUX3_SPI0_CLK_ENABLE   (SYSCFG_PINMUX3_PINMUX3_3_0_SPI0_CLK << \
                                     SYSCFG_PINMUX3_PINMUX3_3_0_SHIFT)

 #define PINMUX3_SPI0_SIMO_ENABLE  (SYSCFG_PINMUX3_PINMUX3_15_12_SPI0_SIMO0 << \
                                     SYSCFG_PINMUX3_PINMUX3_15_12_SHIFT)

 #define PINMUX3_SPI0_SOMI_ENABLE  (SYSCFG_PINMUX3_PINMUX3_11_8_SPI0_SOMI0 << \
                                     SYSCFG_PINMUX3_PINMUX3_11_8_SHIFT)

 #define PINMUX3_SPI0_ENA_ENABLE   (SYSCFG_PINMUX3_PINMUX3_7_4_NSPI0_ENA << \
                                     SYSCFG_PINMUX3_PINMUX3_7_4_SHIFT)

 /* Pin multiplexing bit masks for SPI1 pins. */

 #define PINMUX5_SPI1_CLK_ENABLE   (SYSCFG_PINMUX5_PINMUX5_11_8_SPI1_CLK << \
                                    SYSCFG_PINMUX5_PINMUX5_11_8_SHIFT)

 #define PINMUX5_SPI1_SIMO_ENABLE  (SYSCFG_PINMUX5_PINMUX5_23_20_SPI1_SIMO0 << \
                                    SYSCFG_PINMUX5_PINMUX5_23_20_SHIFT)

 #define PINMUX5_SPI1_SOMI_ENABLE  (SYSCFG_PINMUX5_PINMUX5_19_16_SPI1_SOMI0 << \
                                    SYSCFG_PINMUX5_PINMUX5_19_16_SHIFT)

 #define PINMUX5_SPI1_ENA_ENABLE   (SYSCFG_PINMUX5_PINMUX5_15_12_NSPI1_ENA << \
                                    SYSCFG_PINMUX5_PINMUX5_15_12_SHIFT)


 void SPIPinMuxSetup(unsigned int instanceNum)
 {
     unsigned int savePinMux = 0;

     if(0 == instanceNum)
     {
         /*
         ** Clearing the bits in context and retaining the other bit values
         ** of PINMUX3 register.
         */
         savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                             ~(SYSCFG_PINMUX3_PINMUX3_3_0 | \
                               SYSCFG_PINMUX3_PINMUX3_15_12 | \
                               SYSCFG_PINMUX3_PINMUX3_11_8 | \
                               SYSCFG_PINMUX3_PINMUX3_7_4);

         /* Actual selection of SPI0 peripheral's pins for use. */
         HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
              (PINMUX3_SPI0_CLK_ENABLE | PINMUX3_SPI0_SIMO_ENABLE | \
               PINMUX3_SPI0_SOMI_ENABLE | PINMUX3_SPI0_ENA_ENABLE | \
               savePinMux);

     }
     else if(1 == instanceNum)
     {
         /*
         ** Clearing the bits in context and retaining the other bit values
         ** of PINMUX5 register.
         */
         savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                             ~(SYSCFG_PINMUX5_PINMUX5_11_8 | \
                               SYSCFG_PINMUX5_PINMUX5_23_20 | \
                               SYSCFG_PINMUX5_PINMUX5_19_16 | \
                               SYSCFG_PINMUX5_PINMUX5_15_12);

         /* Actual selection of SPI1 peripheral's pins for use. */
         HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
              (PINMUX5_SPI1_CLK_ENABLE | PINMUX5_SPI1_SIMO_ENABLE | \
               PINMUX5_SPI1_SOMI_ENABLE | PINMUX5_SPI1_ENA_ENABLE | \
               savePinMux);



     }
     else
     {


     }

 }

 /**
  * \brief   This function selects the specified Chip Select(CS) pin of
  *          SPI0 for use.
  *
  * \param   csPinNum    the number of the Chip Select(CS) pin to be used.
  *
  * \return  None.
  */

 void SPI0CSPinMuxSetup(unsigned int csPinNum)
 {
      unsigned int spi0CSPinMux = 0;
      unsigned int savePinMux = 0;

      switch(csPinNum)
      {
           case 0:

               /* Obtaining the bit-mask to select SPI0_SCS[0] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX4_PINMUX4_7_4_NSPI0_SCS0 << \
                               SYSCFG_PINMUX4_PINMUX4_7_4_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_7_4);

               /* Actual selection of SPI0_SCS[0] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi0CSPinMux | savePinMux);
           break;

           case 1:

               /* Obtaining the bit-mask to select SPI0_SCS[1] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX4_PINMUX4_3_0_NSPI0_SCS1 << \
                               SYSCFG_PINMUX4_PINMUX4_3_0_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_3_0);

               /* Actual selection of SPI0_SCS[1] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi0CSPinMux | savePinMux);

           break;

           case 2:

               /* Obtaining the bit-mask to select SPI0_SCS[2] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_31_28_NSPI0_SCS2 << \
                               SYSCFG_PINMUX3_PINMUX3_31_28_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX3 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                  ~(SYSCFG_PINMUX3_PINMUX3_31_28);


               /* Actual selection of SPI0_SCS[2] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                    (spi0CSPinMux | savePinMux);

           break;

           case 3:

               /* Obtaining the bit-mask to select SPI0_SCS[3] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_27_24_NSPI0_SCS3 << \
                               SYSCFG_PINMUX3_PINMUX3_27_24_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX3 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                  ~(SYSCFG_PINMUX3_PINMUX3_27_24);

               /* Actual selection of SPI0_SCS[3] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                    (spi0CSPinMux | savePinMux);

           break;

           case 4:

               /* Obtaining the bit-mask to select SPI0_SCS[4] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_23_20_NSPI0_SCS4 << \
                               SYSCFG_PINMUX3_PINMUX3_23_20_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX3 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                  ~(SYSCFG_PINMUX3_PINMUX3_23_20);

               /* Actual selection of SPI0_SCS[4] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                    (spi0CSPinMux | savePinMux);

           break;

           case 5:

               /* Obtaining the bit-mask to select SPI0_SCS[5] for use. */
               spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_19_16_NSPI0_SCS5 << \
                               SYSCFG_PINMUX3_PINMUX3_19_16_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX3 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                  ~(SYSCFG_PINMUX3_PINMUX3_19_16);

               /* Actual selection of SPI0_SCS[5] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                    (spi0CSPinMux | savePinMux);

           break;

           default:
           break;
      }

 }

 /**
  * \brief   This function selects the specified Chip Select(CS) pin of
  *          SPI1 for use.
  *
  * \param   csPinNum    the number of the Chip Select(CS) pin to be used.
  *
  * \return  None.
  */

 void SPI1CSPinMuxSetup(unsigned int csPinNum)
 {
      unsigned int spi1CSPinMux = 0;
      unsigned int savePinMux = 0;

      switch(csPinNum)
      {
           case 0:

               /* Obtaining the bit-mask to select SPI1_SCS[0] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX5_PINMUX5_7_4_NSPI1_SCS0 << \
                               SYSCFG_PINMUX5_PINMUX5_7_4_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX5 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                                  ~(SYSCFG_PINMUX5_PINMUX5_7_4);

               /* Actual selection of SPI1_SCS[0] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 1:

               /* Obtaining the bit-mask to select SPI1_SCS[1] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX5_PINMUX5_3_0_NSPI1_SCS1 << \
                               SYSCFG_PINMUX5_PINMUX5_3_0_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX5 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                                  ~(SYSCFG_PINMUX5_PINMUX5_3_0);

               /* Actual selection of SPI1_SCS[1] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 2:

               /* Obtaining the bit-mask to select SPI1_SCS[2] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_31_28_NSPI1_SCS2 << \
                               SYSCFG_PINMUX4_PINMUX4_31_28_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
                                  ~(SYSCFG_PINMUX4_PINMUX4_31_28);

               /* Actual selection of SPI1_SCS[2] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 3:

               /* Obtaining the bit-mask to select SPI1_SCS[3] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_27_24_NSPI1_SCS3 << \
                               SYSCFG_PINMUX4_PINMUX4_27_24_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_27_24);

               /* Actual selection of SPI1_SCS[3] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 4:

               /* Obtaining the bit-mask to select SPI1_SCS[4] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_23_20_NSPI1_SCS4 << \
                               SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_23_20);

               /* Actual selection of SPI1_SCS[4] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 5:

               /* Obtaining the bit-mask to select SPI1_SCS[5] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_19_16_NSPI1_SCS5 << \
                               SYSCFG_PINMUX4_PINMUX4_19_16_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_19_16);

               /* Actual selection of SPI1_SCS[5] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 6:

               /* Obtaining the bit-mask to select SPI1_SCS[6] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_15_12_NSPI1_SCS6 << \
                               SYSCFG_PINMUX4_PINMUX4_15_12_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_15_12);

               /* Actual selection of SPI1_SCS[6] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           case 7:

               /* Obtaining the bit-mask to select SPI1_SCS[7] for use. */
               spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_11_8_NSPI1_SCS7 << \
                               SYSCFG_PINMUX4_PINMUX4_11_8_SHIFT);

               /*
               ** Clearing the bits in context and retaining the other bit
               ** values of PINMUX4 register.
               */
               savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                  ~(SYSCFG_PINMUX4_PINMUX4_11_8);

               /* Actual selection of SPI1_SCS[7] pin for use. */
               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                    (spi1CSPinMux | savePinMux);

           break;

           default:
           break;

      }

 }

 void CS_Enable()
 {
 #define PINMUX4_GPIO1_6_ENABLE (SYSCFG_PINMUX4_PINMUX4_7_4_GPIO1_6  << \
		SYSCFG_PINMUX4_PINMUX4_7_4_SHIFT)
 	unsigned int savePinmux = 0;
 	    /*将PINMUX4寄存器的24~27位清0*/
 	    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
 	                 ~(SYSCFG_PINMUX4_PINMUX4_7_4));

 	    /*在PINMUX0寄存器里将引脚配置成普通IO口GP1[6]*/
 	    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
 	         (PINMUX4_GPIO1_6_ENABLE | savePinmux);

 		/*配置GPIO pin 23(GPIO1[6])为输出*/
 		GPIODirModeSet(SOC_GPIO_0_REGS, 23,GPIO_DIR_OUTPUT);

// 		/*给GP1[6]写低电平*/
// 		GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_LOW);
//

// 		/*给GP1[6]写高电平*/
		GPIOPinWrite(SOC_GPIO_0_REGS,23,GPIO_PIN_HIGH);
 }
