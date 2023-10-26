/*****************************************************************************
* @file:    FPEC_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 11 Oct 2023 14:21:12 +0200
* @brief:   FPEC Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to erase a page
void FPEC_eraseFlashPage(u8 PageNumber)
{
	// Validate input parameters
	ASSERT(PageNumber >=0 && PageNumber < 64)

	// Wait Busy Flag to check if there are a current flash Operation or not 
	while (GET_BIT(FPEC->SR,0) == 1);
	
	// Check if FPEC is locked or not: in case of the Flash Memory is locked perform the  unlock sequence 
	if (GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	// Select Page Erase Operation 
	SET_BIT(FPEC->CR,1);

	// Write Page address to be erased 
	FPEC->AR = (u32)(PageNumber * 1024) + 0x08000000;

	// Start erase operation 
	SET_BIT(FPEC->CR,6);

	// Wait Busy Flag to check if the operation was finished or not 
	while (GET_BIT(FPEC->SR,0) == 1);

	// EOP Clear with writing one because this bit is setted when operation succeded 
	SET_BIT(FPEC->SR,5);
	
	// Unselect Erase Operation 
	CLR_BIT(FPEC->CR,1);
}

// Function to erase number of pages
void FPEC_eraseNumberOfPages(u8 StartPage, u8 PagesCount)
{
	// Validate input parameters
	ASSERT(StartPage >= 0 && StartPage < 64);
	ASSERT(PagesCount >= 0 && PagesCount < 64);

	// Loop on all nedded pages and erase it
	u8 i;	
	for (i=StartPage;i<PagesCount;i++)
	{
		FPEC_eraseFlashPage(i);
	}
}

// Function to write number of half words
void FPEC_writeFlash(u32 Address, u16* Data, u8 Length)
{
	u8 i;
	volatile u16 Temp;
        
    // Wait Busy Flag to check if there are a current flash Operation or not 
	while (GET_BIT(FPEC->SR,0) == 1);

	// Check if FPEC is locked or not: in case of the Flash Memory is locked perform the  unlock sequence 
	if (GET_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	// Write the nedded data 
	for (i = 0; i< Length; i++)
	{
		// Select Write Flash Programming 
		SET_BIT(FPEC->CR,0);

		// Half word operation 
		Temp = Data[i];
		*((volatile u16*)Address) = Data[i];
		Address += 2 ;

		// Wait Busy Flag 
		while (GET_BIT(FPEC->SR,0) == 1);
	
		// EOP Clear with writing one because this bit is setted when operation succeded 
		SET_BIT(FPEC->SR,5);
		
		// Unselect Writing Operation 
		CLR_BIT(FPEC->CR,0);
	}

}

