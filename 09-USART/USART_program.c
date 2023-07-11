/***************************************/
/* Author  :Gomaa                      */
/* Date    :19 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "GPIO_interface.h"
#include  "RCC_interface.h"


#include  "USART_interface.h"
#include  "USART_private.h"
#include  "USART_config.h"

void USART_voidInit(void)
{
	/* Enable Clocks of GPIO  and USART */
	RCC_voidEnableClock(RCC_APB2,RCC_IOPA);
	RCC_voidEnableClock(RCC_APB2,RCC_USART);
	/* Set Pin Directions of USART */
	GPIO_voidSetPinDirection(GPIOA,GPIO_PIN9,GPIO_OUTPUT_2MHZ_AFPP);
	GPIO_voidSetPinDirection(GPIOA,GPIO_PIN10,GPIO_INPUT_FLOATING);


	/* Set Baud Rate */
	#if USART_BAUD_RATE == BR_9600
	USART->BRR = 0x341;
	#elif USART_BAUD_RATE == BR_4800
	USART->BRR = 0x683;
	#elif USART_BAUD_RATE == BR_115200
	USART->BRR = 0x45;
	#endif

	/* Set Data Size */
	#if     USART_DATA_SIZE  ==    USART_8BIT_DATA_SIZE
	      CLR_BIT(USART->CR1,12);
	#elif   USART_DATA_SIZE  ==    USART_9BIT_DATA_SIZE
	      SET_BIT(USART->CR1,12);
	#endif

	/* PARITY Enabled Or Disabled */
	#if    USART_PARITY ==  USART_PARITY_ENABLED
	     /* Enable Parity */
	      SET_BIT(USART->CR1,10);
        /* Set Parity Check Type */
	    #if     USART_PARITY_CHECK  ==    USART_EVEN_PARITY
	       CLR_BIT(USART->CR1,9);
	    #elif   USART_PARITY_CHECK  ==    USART_ODD_PARITY
	       SET_BIT(USART->CR1,9);
	    #endif
	#elif   USART_PARITY ==  USART_PARITY_DISABLED
	    /* Disable Parity */
		CLR_BIT(USART->CR1,10);
	#endif


	/*    Enable RX     */
	/*    Enable TX     */
	/*    Enable  USART */
	SET_BIT(USART->CR1,2);
	SET_BIT(USART->CR1,3);
	SET_BIT(USART->CR1,13);
	/* Clear Status Register */
	USART->SR = 0;
	
	
}
void USART_voidTransmit(u8 *Copy_u8DataToTransmit)
{  u8 i = 0;
	while(Copy_u8DataToTransmit[i] != '\0')
	{
		USART->DR = Copy_u8DataToTransmit[i];
		while(GET_BIT(USART->SR,6) == 0);
		i++;
		CLR_BIT(USART->SR,6);
	}
}
u8   USART_u8Receive(u8 *ReceivedData)
{ 
	     volatile u8 Loc_u8 = 0;
         //while(GET_BIT(USART->SR,5) == 0);
         if(GET_BIT(USART->SR,5) == 1 ){
			 *ReceivedData = USART->DR;
			 CLR_BIT(USART->SR,5);
			 Loc_u8 = 1;
		 }
		 else{
			 // Do Nothing
		 }
	
	return Loc_u8;
}


