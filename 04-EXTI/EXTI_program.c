/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include      "EXTI_interface.h"
#include      "EXTI_private.h"
#include      "EXTI_config.h"

void EXTI_voidInt()
{
	
}
void EXTI_voidEnableExti(u8 Copy_u8Line,u8 Copy_u8Mode)
{
	if(Copy_u8Mode == EXTI_RISING){
		SET_BIT(EXTI->IMR,Copy_u8Line);
		SET_BIT(EXTI->RTSR,Copy_u8Line);
	}
	else if(Copy_u8Mode == EXTI_FALLING){
		SET_BIT(EXTI->IMR,Copy_u8Line);
		SET_BIT(EXTI->FTSR,Copy_u8Line);
		
	}
	else if(Copy_u8Mode == EXTI_ON_CHANGE){
		SET_BIT(EXTI->IMR,Copy_u8Line);
		SET_BIT(EXTI->RTSR,Copy_u8Line);
		SET_BIT(EXTI->FTSR,Copy_u8Line);
		
	}
}
void EXTI_voidDisableExti(u8 Copy_u8Line)
{  
        CLR_BIT(EXTI->IMR,Copy_u8Line);
}
void EXTI_voidSwTrigger(u8 Copy_u8Line)
{
	
		SET_BIT(EXTI->SWIER,Copy_u8Line);
		SET_BIT(EXTI->PR,Copy_u8Line);
		
	
}
void EXTI_voidSetCallback(void (*ptr) (void),u8 Copy_u8Line)
{
	switch(Copy_u8Line)
	{
		case EXTI_LINE0: RXTI0_Callback = ptr; break;
		case EXTI_LINE1: RXTI1_Callback = ptr; break;
		case EXTI_LINE2: RXTI2_Callback = ptr; break;
		case EXTI_LINE3: RXTI3_Callback = ptr; break;
		case EXTI_LINE4: RXTI4_Callback = ptr; break;
	}
	
	
}
void EXTI0_IRQHandler(void)
{
	RXTI0_Callback();
	SET_BIT(EXTI->PR,0);
}
void EXTI1_IRQHandler(void)
{
	RXTI1_Callback();
	SET_BIT(EXTI->PR,1);
}
void EXTI2_IRQHandler(void)
{
	RXTI2_Callback();
	SET_BIT(EXTI->PR,2);
}
void EXTI3_IRQHandler(void)
{
	RXTI3_Callback();
	SET_BIT(EXTI->PR,3);
}
void EXTI4_IRQHandler(void)
{
	RXTI4_Callback();
	SET_BIT(EXTI->PR,4);
}
