/*****************************************************************************
* @file:    USART_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2S   
* @date:    Sat, 7 Oct 2023 12:21:12 +0200
* @brief:   USART Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "GPIO_interface.h"
#include  "RCC_interface.h"

#include  "USART_interface.h"
#include  "USART_private.h"
#include  "USART_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize USART
void USART_init(void)
{
	// Enable Clocks of GPIO  and USART 
	RCC_enableClock(RCC_APB2,RCC_IOPA);
	RCC_enableClock(RCC_APB2,RCC_USART);

	// Set Pin Directions of USART 
	GPIO_setPinDirection(USART_TX_PORT,USART_TX_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	GPIO_setPinDirection(USART_RX_PORT,USART_RX_PIN,GPIO_INPUT_FLOATING);

	// Set Baud Rate 
	#if USART_BAUD_RATE == BR_9600
		USART->BRR = 0x341;
	#elif USART_BAUD_RATE == BR_4800
		USART->BRR = 0x683;
	#elif USART_BAUD_RATE == BR_115200
		USART->BRR = 0x45;
	#endif

	// Set Data Size 
	#if     USART_DATA_SIZE  ==    USART_8BIT_DATA_SIZE
	    CLR_BIT(USART->CR1,12);
	#elif   USART_DATA_SIZE  ==    USART_9BIT_DATA_SIZE
	    SET_BIT(USART->CR1,12);
	#endif

	// PARITY Enabled Or Disabled 
	#if    USART_PARITY ==  USART_PARITY_ENABLED
	    // Enable Parity 
	    SET_BIT(USART->CR1,10);
        // Set Parity Check Type 
	    #if     USART_PARITY_CHECK  ==    USART_EVEN_PARITY
	    	CLR_BIT(USART->CR1,9);
	    #elif   USART_PARITY_CHECK  ==    USART_ODD_PARITY
	       SET_BIT(USART->CR1,9);
	    #endif
	#elif   USART_PARITY ==  USART_PARITY_DISABLED
	    // Disable Parity 
		CLR_BIT(USART->CR1,10);
	#endif

	// Enable USART
	SET_BIT(USART->CR1,2);  // Enable RX 
	SET_BIT(USART->CR1,3);  // Enable TX 
	SET_BIT(USART->CR1,13); // Enable  USART 
	USART->SR = 0;			// Clear Status Register 
}

// Function to send a character
void USART_transmitCharacter(u8 Character)
{  
	// Wait until data register to be empty
	while(GET_BIT(USART->SR,7) == 0);
	// Put data in uart data register
	USART->DR = Character;
	// Wait until data to be transmitted 
	while(GET_BIT(USART->SR,6) == 0);
	// Clear Tx flag
	CLR_BIT(USART->SR,6);
}

// Function to send a string
void USART_transmitString(u8 *String)
{  
	// Variable used as a counter
	u8 i = 0;
	// Loop on all string and send character by character
	while(String[i] != '\0')
	{
		USART_transmitCharacter(String[i]);
		i++;
	}
	// Send \0 end of string
	USART_transmitCharacter('\0');
}

// Function to receive an character
UartRecievedState_type USART_receiveCharacter(u8 *ReceivedData)
{ 
	// Flag used as a return
	volatile UartRecievedState_type State = RECEIVED_NOT_OK;

	// Check if there is a recieved data over uart or not 
    if(GET_BIT(USART->SR,5) == 1 )
	{
		// Recieve data
		*ReceivedData = USART->DR;
		// Clear Rx flag
		CLR_BIT(USART->SR,5);
		// Indicate recieved data
		State = RECEIVED_OK;
	}
	else
	{
		// Do Nothing
	}	
	return State;
}

// Function to enable transmission complete interrupt
void USART_enableCompleteTxInterrupt(void)
{
	SET_BIT(USART->CR1, 6);
}

// Function to disable transmission complete interrupt
void USART_disableCompleteTxInterrupt(void)
{
	CLR_BIT(USART->CR1, 6);
}

// Function to set transmission complete callback
void USART_setCompleteTxCallack(void (*Callback) (void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);
	// Set call back
	UASRT_TxCompleteCallback = Callback;
}

// Function to enable receiption complete interrupt
void USART_enableCompleteRxInterrupt(void)
{
	SET_BIT(USART->CR1, 5);
}

// Function to disable receiption complete interrupt
void USART_disableCompleteRxInterrupt(void)
{
	CLR_BIT(USART->CR1, 5);
}

// Function to set receiption complete callback
void USART_setCompleteRxCallack(void (*Callback) (void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);
	// Set call back
	UASRT_RxCompleteCallback = Callback;
}

// Function to enable transmission empty interrupt
void USART_enableTxRegisterEmptyInterrupt(void)
{
	SET_BIT(USART->CR1, 7);
}

// Function to disable transmission empty interrupt
void USART_disableTxRegisterEmptyInterrupt(void)
{
	CLR_BIT(USART->CR1, 7);
}

// Function to set transmission empty callback
void USART_setTxEmptyCallack(void (*Callback) (void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);
	// Set call back
	UASRT_TxEmptyCallback = Callback;
}


/* ==================================================================== */
/* ================= Private Functions Implementation ================= */
/* ==================================================================== */

void USART_IRQHandler(void)
{
	// Callbacks
	if (GET_BIT(USART->SR,6)==1)
	{
		UASRT_TxCompleteCallback();
		CLR_BIT(USART->SR, 6);
	}

	if (GET_BIT(USART->SR,5)==1)
	{
		UASRT_RxCompleteCallback();
		CLR_BIT(USART->SR, 5);
	}

	if (GET_BIT(USART->SR,7)==1)
	{
		UASRT_TxEmptyCallback();
		USART->DR = 0;
	}

}

