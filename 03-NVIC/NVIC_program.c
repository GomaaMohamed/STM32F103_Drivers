/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                    */
/*********************************************************************************/

#include      "STD_TYPES.h"
#include      "BIT_MATH.h"


#include      "NVIC_interface.h"
#include      "NVIC_private.h"
#include      "NVIC_config.h"

void NVIC_voidEnableInterrupt(u8 Copy_u8IntNumber)
{
	if(Copy_u8IntNumber <= 31)
	{
		NVIC_ISER0 = 1<<(Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISER1 = 1<<(Copy_u8IntNumber);
	}
}
void NVIC_voidDisableInterrupt(u8 Copy_u8IntNumber)
{
	if(Copy_u8IntNumber <= 31)
	{
		NVIC_ICER0 = 1<<(Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICER1 = 1<<(Copy_u8IntNumber);
	}
}
void NVIC_voidSetPendingFlag(u8 Copy_u8IntNumber)
{
	if(Copy_u8IntNumber <= 31)
	{
		NVIC_ISPR0 = 1<<(Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISPR1 = 1<<(Copy_u8IntNumber);
	}
}
void NVIC_voidClearPendingFlag(u8 Copy_u8IntNumber)
{
	if(Copy_u8IntNumber <= 31)
	{
		NVIC_ICPR0 = 1<<(Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICPR1 = 1<<(Copy_u8IntNumber);
	}
}
u8 NVIC_voidGetActiveFlag(u8 Copy_u8IntNumber)
{
	u8 LocalResult;
	if(Copy_u8IntNumber <= 31)
	{
		LocalResult = GET_BIT(NVIC_IAPR0,Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		LocalResult = GET_BIT(NVIC_IAPR1,Copy_u8IntNumber);
	}
	return LocalResult;
}
void NVIC_voidSetPriority(s8 Copy_s8IntId,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority,u32 Copy_u32Group)
{   u8 Local_u8Priority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((Copy_u32Group - 0x05FA0300)/256));
	/* Core Periphiral */	
	
	/* Core Periphiral */
    if(Copy_s8IntId >= 0)
	{   SCB_AIRCR = Copy_u32Group;
		NVIC_IPR[Copy_s8IntId] = Local_u8Priority << 4;
	}	
}