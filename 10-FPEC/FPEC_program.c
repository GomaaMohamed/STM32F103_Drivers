#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag to check if there are a current flash Operation or not */
	while (GET_BIT(FPEC->SR,0) == 1);
	
	/* Check if FPEC is locked or not: in case of the Flash Memory is locked perform the  unlock sequence */
	if (GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	/* Select Page Erase Operation */
	SET_BIT(FPEC->CR,1);

	/* Write Page address to be erased */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000;

	/* Start erase operation */
	SET_BIT(FPEC->CR,6);

	/* Wait Busy Flag to check if the operation was finished or not */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* EOP Clear with writing one because this bit is setted when operation succeded */
	SET_BIT(FPEC->SR,5);
	
	/* Unselect Erase Operation */
	CLR_BIT(FPEC->CR,1);
}

void FPEC_voidEraseNumberOfPages(u8 Copy_u8StartPage,u8 Copy_u8PagesCount)
{
	u8 i;	
	for (i=Copy_u8StartPage;i<Copy_u8PagesCount;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}


void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 i;
	volatile u16 Temp;
        
    /* Wait Busy Flag to check if there are a current flash Operation or not */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not: in case of the Flash Memory is locked perform the  unlock sequence */
	if (GET_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	/* Write the nedded data */
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Select Write Flash Programming */
		SET_BIT(FPEC->CR,0);

		/* Half word operation */
		Temp = Copy_u16Data[i];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,0) == 1);
	
		/* EOP Clear with writing one because this bit is setted when operation succeded */
		SET_BIT(FPEC->SR,5);
		
		/* Unselect Writing Operation */
		CLR_BIT(FPEC->CR,0);
	}

}

