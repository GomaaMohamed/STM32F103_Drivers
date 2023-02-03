/***************************************/
/* Author  :Gomaa                      */
/* Date    :16 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "GPIO_interface.h"


#include  "SPI_interface.h"
#include  "SPI_private.h"
#include  "SPI_config.h"



void SPI_voidInit(void)
{
	
	
	/* Disable SPI */
	CLR_BIT(SPI->CR1,6);
	
	#if   SPI_MODE == SPI_MASTER_MODE
	
	    /* Initialize Master Pins */
	    /* Set MOSI1 Pin */
	    GPIO_voidSetPinDirection(SPI_MOSI_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	    /* Set MISO1 Pin */
	    GPIO_voidSetPinDirection(SPI_MISO_PIN,GPIO_INPUT_FLOATING);
	    /* Set SCK Pin */
	    GPIO_voidSetPinDirection(SPI_SCK_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	    //GPIO_voidSetPinDirection(GPIOA,PIN4); Not Used in case of master
	    
	    /*Select Master Mode */
	    SET_BIT(SPI->CR1,2);
		SET_BIT(SPI->CR1,8);
		SET_BIT(SPI->CR1,9);
	 
	#elif   SPI_MODE == SPI_SLAVE_MODE
	
	    /* Initialize Slave Pins */
	    /* Set MOSI1 Pin */
	    GPIO_voidSetPinDirection(SPI_MOSI_PIN,GPIO_INPUT_FLOATING);
	    /* Set MISO1 Pin */
	    GPIO_voidSetPinDirection(SPI_MISO_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	    /* Set SCK Pin */
	    GPIO_voidSetPinDirection(SPI_SCK_PIN,GPIO_INPUT_FLOATING);
	    /* Set NSS Pin */
	    GPIO_voidSetPinDirection(SPI_SLAVE_SELECT_PIN,GPIO_INPUT_FLOATING);
	    
	    /* Select Slave Mode */
	    CLR_BIT(SPI->CR1,2);
	#endif 
	
	/* Set The First Bit to send */
	#if      SPI_FIRST_BIT_TO_SEND == SPI_MSB_FIRST
	     CLR_BIT(SPI->CR1,7);
	#elif   SPI_FIRST_BIT_TO_SEND == SPI_LSB_FIRST
	     SET_BIT(SPI->CR1,7);
	#endif
	/* Set Data Frame Format to send */
	#if      SPI_DATA_FRAME_FORMAT == SPI_8BIT_FORMAT
	    CLR_BIT(SPI->CR1,11);
	#elif   SPI_DATA_FRAME_FORMAT == SPI_16BIT_FORMAT
	    SET_BIT(SPI->CR1,11);
	#endif
	/* Set Clock Polarity */
	#if      SPI_CLOCK_POLARITY  == SPI_0_POLARITY
	     /* Clock Polarity 0 */
		 CLR_BIT(SPI->CR1,1);
	#elif   SPI_CLOCK_POLARITY  == SPI_1_POLARITY
	     /* Clock Polarity 1 */
		 SET_BIT(SPI->CR1,1);
	
	#endif
	/* Set Clock Phase */
	#if      SPI_CLOCK_PHASE  == SPI_SAMPLE_SETUP
	     /* Clock Phase First */
		 CLR_BIT(SPI->CR1,0);
	#elif   SPI_CLOCK_PHASE  == SPI_SETUP_SAMPLE
	     /* Clock Phase Second transition */
		 SET_BIT(SPI->CR1,0);
	
	#endif
	/* Set Baud Rate Control */
	SPI->CR1 |= ( SPI_BAUD_RATE << 3);
	
	/* Enable SPI */
	SET_BIT(SPI->CR1,6);
	
}
void SPI_voidSendReceiveSynch(u8 Copy_u8DataToSend,u8 *Copy_u8DataToReceive)
{
	
	
	/* Clear For Slave select Pin*/
	GPIO_voidSetPinValue(SPI_SLAVE_SELECT_PIN,GPIO_LOW);
	
	/*Check Busy Flag*/
	while(GET_BIT(SPI->SR,7) == 1);
	/* Send Data */
	SPI->DR = Copy_u8DataToSend;
	
	/* Check RX Flag */
	while(GET_BIT(SPI->SR,0) == 1);
	/* Return To The Received Data */ 
	*Copy_u8DataToReceive = SPI->DR;
	
	/* Clear For Slave select Pin*/
	GPIO_voidSetPinValue(SPI_SLAVE_SELECT_PIN,GPIO_HIGH);
	
	
}
void SPI_voidSendReceiveAsynch(u8 Copy_u8DataToSend,void  (*CallBack)(u8))
{
	
	/* Clear For Slave select Pin*/
	GPIO_voidSetPinValue(SPI_SLAVE_SELECT_PIN,GPIO_LOW);
	
	
	/* Send Data */
	SPI->DR = Copy_u8DataToSend;
	
	/* Set Call Back */
	SPI1_CallBack = CallBack;
	
	/* Enable RX Interrupt */
	SET_BIT(SPI->CR2,6);
}
void SPI1_IRQHandler(void)
{
	SPI1_CallBack(SPI->DR);
	/* Disable RX Interrupt */
	CLR_BIT(SPI->CR2,6);
}
