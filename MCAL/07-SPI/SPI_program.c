/*****************************************************************************
* @file:    SPI_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law. 
* @version: V0.2   
* @date:    Sun, 8 Oct 2023 16:55:32 +0200
* @brief:   SPI Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "GPIO_interface.h"

#include  "SPI_interface.h"
#include  "SPI_private.h"
#include  "SPI_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize spi module
void SPI_init(void)
{
	// Disable SPI 
	CLR_BIT(SPI->CR1,6);
	
	// Select mode
	#if SPI_MODE == SPI_MASTER_MODE
	    // Initialize Master Pins 
	    // Set MOSI1 Pin 
	    GPIO_setPinDirection(SPI_MOSI_PORT,SPI_MOSI_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	    // Set MISO1 Pin 
	    GPIO_setPinDirection(SPI_MISO_PORT,SPI_MISO_PIN,GPIO_INPUT_FLOATING);
	    // Set SCK Pin 
	    GPIO_setPinDirection(SPI_SCK_PORT,SPI_SCK_PIN,GPIO_OUTPUT_2MHZ_AFPP);
		// Set SS pin
	    GPIO_setPinDirection(SPI_SS_PORT,SPI_SS_PIN,GPIO_OUTPUT_2MHZ_AFPP); 
	    
	    // Select Master Mode 
	    SET_BIT(SPI->CR1,2);
		SET_BIT(SPI->CR1,8);
		SET_BIT(SPI->CR1,9);
	#elif   SPI_MODE == SPI_SLAVE_MODE
	    // Initialize Slave Pins 
	    // Set MOSI1 Pin 
	    GPIO_setPinDirection(SPI_MOSI_PORT,SPI_MOSI_PIN,GPIO_INPUT_FLOATING);
	    // Set MISO1 Pin 
	    GPIO_setPinDirection(SPI_MISO_PORT,SPI_MISO_PIN,GPIO_OUTPUT_2MHZ_AFPP);
	    // Set SCK Pin 
	    GPIO_setPinDirection(SPI_SCK_PORT,SPI_SCK_PIN,GPIO_INPUT_FLOATING);
	    // Set NSS Pin 
	    GPIO_setPinDirection(SPI_SS_PORT,SPI_SS_PIN,GPIO_INPUT_FLOATING);
	    
	    // Select Slave Mode 
	    CLR_BIT(SPI->CR1,2);
	#endif 
	
	// Set The First Bit to send 
	#if      SPI_FIRST_BIT_TO_SEND == SPI_MSB_FIRST
	    CLR_BIT(SPI->CR1,7);
	#elif   SPI_FIRST_BIT_TO_SEND == SPI_LSB_FIRST
	    SET_BIT(SPI->CR1,7);
	#endif

	// Set Data Frame Format to send 
	#if      SPI_DATA_FRAME_FORMAT == SPI_8BIT_FORMAT
	    CLR_BIT(SPI->CR1,11);
	#elif   SPI_DATA_FRAME_FORMAT == SPI_16BIT_FORMAT
	    SET_BIT(SPI->CR1,11);
	#endif

	// Set Clock Polarity 
	#if      SPI_CLOCK_POLARITY  == SPI_0_POLARITY
	     // Clock Polarity 0 
		 CLR_BIT(SPI->CR1,1);
	#elif   SPI_CLOCK_POLARITY  == SPI_1_POLARITY
	     // Clock Polarity 1 
		 SET_BIT(SPI->CR1,1);
	#endif

	// Set Clock Phase 
	#if      SPI_CLOCK_PHASE  == SPI_SAMPLE_SETUP
	     /* Clock Phase First */
		 CLR_BIT(SPI->CR1,0);
	#elif   SPI_CLOCK_PHASE  == SPI_SETUP_SAMPLE
	     /* Clock Phase Second transition */
		 SET_BIT(SPI->CR1,0);
	#endif

	// Set Baud Rate Control 
	SPI->CR1 |= ( SPI_BAUD_RATE << 3);
	
	// Enable SPI 
	SET_BIT(SPI->CR1,6);
}

// Function to send and receive synchronous
void SPI_sendReceiveSynch(u8 DataToSend,u8 *DataToReceive)
{
	// Clear For Slave select Pin
	GPIO_setPinValue(SPI_SS_PORT,SPI_SS_PIN,GPIO_LOW);
	
	// Check Busy Flag
	while(GET_BIT(SPI->SR,7) == 1);

	// Send Data 
	SPI->DR = DataToSend;
	
	// Check RX Flag 
	while(GET_BIT(SPI->SR,0) == 1);

	// Return Received Data 
	*DataToReceive = SPI->DR;
	
	// Clear For Slave select Pin
	GPIO_setPinValue(SPI_SS_PORT,SPI_SS_PIN,GPIO_HIGH);
	
	
}

// Function to send and receive asynchronous
void SPI_sendReceiveAsynch(u8 DataToSend,void  (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Clear For Slave select Pin
	GPIO_setPinValue(SPI_SS_PORT,SPI_SS_PIN,GPIO_LOW);
	
	// Send Data 
	SPI->DR = DataToSend;
	
	// Set Call Back 
	SPI1_Callback = Callback;
	
	// Enable RX Interrupt 
	SET_BIT(SPI->CR2,6);
}

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */
void SPI1_IRQHandler(void)
{
	SPI1_Callback();
	// Disable RX Interrupt 
	CLR_BIT(SPI->CR2,6);
}
