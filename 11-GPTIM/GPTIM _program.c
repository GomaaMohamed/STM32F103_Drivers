/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 10 Sep 2020                                                    */
/*********************************************************************************/
#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include     "GPTIM_interface.h"
#include    "GPTIM_private.h"
#include    "GPTIM_config.h"

/***********************TIM2****************************/
/*  Clock of TIM2 is APB1_clk(8 MHZ)
   Disable TIM7 interrupt
   Disable TIM6
   F(TIM2)=8M/(1+PSC)
   If PSC=7
	Tick=>1us                 */
void TIM2_voidInit(void)
{
	/*Up Counter Mode*/
	TIM2->CR1&=~(0b111<<4);
	TIM2->CR1|=(DOWNCOUNTER<<4);

	/*ARR is Buffered can't changed Execpt at Update Event*/
	SET_BIT(TIM2->CR1,GPTIM_ARPE);

	/*Only Counter OverFlow UnderFlow Generate update Interrupt */
	SET_BIT(TIM2->CR1,GPTIM_URS);

	/*Enable Update Event */
	CLR_BIT(TIM2->CR1,GPTIM_UDIS);

	/*Disable Update Interrupt */
	CLR_BIT(TIM2->DIER,GPTIM_UIE);

	/*F(TIM2)=8M/(1+PSC)=1MHz
	*Ticks equal 1us*/
	TIM2->PSC=7;
}
/* Synchronous API  Lock Processor For Certain Ticks
   *Disable SysTick interrupt
   *enable Systick
   *polling flag (underflow)
   *Tick=>1us*/
void TIM2_voidSetBusyWait( u32 Copy_u32Ticks )
{
	u32 Local_u32Routine=Copy_u32Ticks/65535;
	u32 Local_u32Fraction=Copy_u32Ticks%65535;
	while(Local_u32Routine--)
	{
		TIM2->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM2->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM2->CR1,GPTIM_CEN);
		while(GET_BIT(TIM2->SR,GPTIM_UIF)==0);
		/*Clear Uderflow Flag*/
		CLR_BIT(TIM2->SR,GPTIM_UIF);
	}

	TIM2->ARR=Local_u32Fraction;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM2->EGR,GPTIM_UG);
	/*Enable counter*/
	SET_BIT(TIM2->CR1,GPTIM_CEN);
	while(GET_BIT(TIM2->SR,GPTIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM2->SR,GPTIM_UIF);
	/*Stop Timer*/
	CLR_BIT(TIM2->CR1,GPTIM_CEN);



}
void TIM2_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM2_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM2_u8ModeOfInterval=SINGLE_INTERVAL;

	Global2_u32Routine =(Copy_u32Ticks/65535);
	Global2_u32Fraction=Copy_u32Ticks%65535;
	/*    to be initialize before enter the interrupt */
	Global2_u32CopyRoutine=Global2_u32Routine;
	/*stop timer */
	CLR_BIT(TIM2->CR1,GPTIM_CEN);

	if(Global2_u32Routine)
	{
		TIM2->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM2->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM2->CR1,GPTIM_CEN);
	}
	else
	{
		TIM2->ARR=Global2_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM2->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM2->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM2->DIER,GPTIM_UIE);
}
void TIM2_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM2_CallBack=Copy_ptr;
	/*Set Mode to Periodic*/
	TIM2_u8ModeOfInterval=PERIODIC_INTERVAL;

	Global2_u32Routine =(Copy_u32Ticks/65535) ;
	Global2_u32Fraction=Copy_u32Ticks%65535;

	if(Global2_u32Routine)
	{
		TIM2->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM2->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM2->CR1,GPTIM_CEN);
	}
	else
	{
		TIM2->ARR=Global2_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM2->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM2->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM2->DIER,GPTIM_UIE);
}

void TIM2_voidStopInterval(void)
{
	//*Disable Update Interrupt
    CLR_BIT(TIM2->DIER,GPTIM_UIE);
	//*Stop Timer
	CLR_BIT(TIM2->CR1,GPTIM_CEN);
}
u32  TIM2_u16GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	u16 Local_u16Cycle=Global2_u32Routine - Global2_u32CopyRoutine;

	Local_u32ElapsedTime=((TIM2->ARR)-(TIM2->CNT))+(Local_u16Cycle*65535);
	return Local_u32ElapsedTime;
}
u32  TIM2_u16GetRemainingTime(void)
{
	u32 local_u32RemainingTime=0;
	if(Global2_u32CopyRoutine>=1)
	{
		local_u32RemainingTime=(TIM2->CNT)+(Global2_u32CopyRoutine-1)*65535+Global2_u32Fraction;
	}
	else if(Global2_u32CopyRoutine==0)
	{
		local_u32RemainingTime=TIM2->CNT;
	}
	return local_u32RemainingTime;
}
/***********************TIM3******************************/

/*  Clock of TIM2 is APB1_clk(8 MHZ)
   Disable TIM7 interrupt
   Disable TIM6
   F(TIM2)=8M/(1+PSC)
   If PSC=7
	Tick=>1us                 */

void TIM3_voidInit(void)
{
	/*Up Counter Mode*/
	TIM3->CR1&=~(0b111<<4);
	TIM3->CR1|=(DOWNCOUNTER<<4);

	/*ARR is Buffered can't changed Execpt at Update Event*/
	SET_BIT(TIM3->CR1,GPTIM_ARPE);

	/*Only Counter OverFlow UnderFlow Generate update Interrupt */
	SET_BIT(TIM3->CR1,GPTIM_URS);

	/*Enable Update Event */
	CLR_BIT(TIM3->CR1,GPTIM_UDIS);

	/*Disable Update Interrupt */
	CLR_BIT(TIM3->DIER,GPTIM_UIE);

	/*F(TIM2)=8M/(1+PSC)=1MHz
	*Ticks equal 1us*/
	TIM3->PSC=7;
}
/* Synchronous API  Lock Processor For Certain Ticks
   *Disable SysTick interrupt
   *enable Systick
   *polling flag (underflow)
   *Tick=>1us*/
void TIM3_voidSetBusyWait( u32 Copy_u32Ticks )
{
	u32 Local_u32Routine=Copy_u32Ticks/65535;
	u32 Local_u32Fraction=Copy_u32Ticks%65535;
	while(Local_u32Routine--)
	{
		TIM3->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM3->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM3->CR1,GPTIM_CEN);
		while(GET_BIT(TIM3->SR,GPTIM_UIF)==0);
		/*Clear Underflow Flag*/
		CLR_BIT(TIM3->SR,GPTIM_UIF);
	}

	TIM3->ARR=Local_u32Fraction;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM3->EGR,GPTIM_UG);
	/*Enable counter*/
	SET_BIT(TIM3->CR1,GPTIM_CEN);
	while(GET_BIT(TIM3->SR,GPTIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM3->SR,GPTIM_UIF);
	/*Stop Timer*/
	CLR_BIT(TIM3->CR1,GPTIM_CEN);



}
void TIM3_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM3_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM3_u8ModeOfInterval=SINGLE_INTERVAL;

	Global3_u32Routine =(Copy_u32Ticks/65535);
	Global3_u32Fraction=Copy_u32Ticks%65535;
	/*    to be initialize before enter the interrupt */
	Global3_u32CopyRoutine=Global3_u32Routine;
	/*stop timer */
	CLR_BIT(TIM3->CR1,GPTIM_CEN);

	if(Global3_u32Routine)
	{
		TIM3->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM3->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM3->CR1,GPTIM_CEN);
	}
	else
	{
		TIM3->ARR=Global3_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM3->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM3->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM3->DIER,GPTIM_UIE);
}
void TIM3_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM3_CallBack=Copy_ptr;
	/*Set Mode to Periodic*/
	TIM3_u8ModeOfInterval=PERIODIC_INTERVAL;

	Global3_u32Routine =(Copy_u32Ticks/65535) ;
	Global3_u32Fraction=Copy_u32Ticks%65535;

	if(Global3_u32Routine)
	{
		TIM3->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM3->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM3->CR1,GPTIM_CEN);
	}
	else
	{
		TIM3->ARR=Global3_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM3->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM3->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM3->DIER,GPTIM_UIE);
}

void TIM3_voidStopInterval(void)
{
	//*Disable Update Interrupt
    CLR_BIT(TIM3->DIER,GPTIM_UIE);
	//*Stop Timer
	CLR_BIT(TIM3->CR1,GPTIM_CEN);
}
u32  TIM3_u16GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	u16 Local_u16Cycle=Global3_u32Routine - Global3_u32CopyRoutine;

	Local_u32ElapsedTime=((TIM3->ARR)-(TIM3->CNT))+(Local_u16Cycle*65535);
	return Local_u32ElapsedTime;
}
u32  TIM3_u16GetRemainingTime(void)
{
	u32 local_u32RemainingTime=0;
	if(Global3_u32CopyRoutine>=1)
	{
		local_u32RemainingTime=(TIM3->CNT)+(Global3_u32CopyRoutine-1)*65535+Global3_u32Fraction;
	}
	else if(Global3_u32CopyRoutine==0)
	{
		local_u32RemainingTime=TIM3->CNT;
	}
	return local_u32RemainingTime;
}
/**********************TIM4*********************************/

/*  Clock of TIM2 is APB1_clk(8 MHZ)
   Disable TIM7 interrupt
   Disable TIM6
   F(TIM2)=8M/(1+PSC)
   If PSC=7
	Tick=>1us                 */
void TIM4_voidInit(void)
{
	/*Up Counter Mode*/
	TIM4->CR1&=~(0b111<<4);
	TIM4->CR1|=(DOWNCOUNTER<<4);

	/*ARR is Buffered can't changed Execpt at Update Event*/
	SET_BIT(TIM4->CR1,GPTIM_ARPE);

	/*Only Counter OverFlow UnderFlow Generate update Interrupt */
	SET_BIT(TIM4->CR1,GPTIM_URS);

	/*Enable Update Event */
	CLR_BIT(TIM4->CR1,GPTIM_UDIS);

	/*Disable Update Interrupt */
	CLR_BIT(TIM4->DIER,GPTIM_UIE);

	/*F(TIM2)=8M/(1+PSC)=1MHz
	*Ticks equal 1us*/
	TIM4->PSC=7;
}
/* Synchronous API  Lock Processor For Certain Ticks
   *Disable SysTick interrupt
   *enable Systick
   *polling flag (underflow)
   *Tick=>1us*/
void TIM4_voidSetBusyWait( u32 Copy_u32Ticks )
{
	u32 Local_u32Routine=Copy_u32Ticks/65535;
	u32 Local_u32Fraction=Copy_u32Ticks%65535;
	while(Local_u32Routine--)
	{
		TIM4->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM4->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM4->CR1,GPTIM_CEN);
		while(GET_BIT(TIM4->SR,GPTIM_UIF)==0);
		/*Clear Uderflow Flag*/
		CLR_BIT(TIM4->SR,GPTIM_UIF);
	}

	TIM4->ARR=Local_u32Fraction;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM4->EGR,GPTIM_UG);
	/*Enable counter*/
	SET_BIT(TIM4->CR1,GPTIM_CEN);
	while(GET_BIT(TIM4->SR,GPTIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM4->SR,GPTIM_UIF);
	/*Stop Timer*/
	CLR_BIT(TIM4->CR1,GPTIM_CEN);



}
void TIM4_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM4_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM4_u8ModeOfInterval=SINGLE_INTERVAL;

	Global4_u32Routine =(Copy_u32Ticks/65535);
	Global4_u32Fraction=Copy_u32Ticks%65535;
	/*    to be initialize before enter the interrupt */
	Global4_u32CopyRoutine=Global4_u32Routine;
	/*stop timer */
	CLR_BIT(TIM4->CR1,GPTIM_CEN);

	if(Global4_u32Routine)
	{
		TIM4->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM4->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM4->CR1,GPTIM_CEN);
	}
	else
	{
		TIM4->ARR=Global4_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM4->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM4->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM4->DIER,GPTIM_UIE);
}
void TIM4_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM4_CallBack=Copy_ptr;
	/*Set Mode to Periodic*/
	TIM4_u8ModeOfInterval=PERIODIC_INTERVAL;

	Global4_u32Routine =(Copy_u32Ticks/65535) ;
	Global4_u32Fraction=Copy_u32Ticks%65535;

	if(Global4_u32Routine)
	{
		TIM4->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM4->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM4->CR1,GPTIM_CEN);
	}
	else
	{
		TIM4->ARR=Global2_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM4->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM4->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM4->DIER,GPTIM_UIE);
}

void TIM4_voidStopInterval(void)
{
	//*Disable Update Interrupt
    CLR_BIT(TIM4->DIER,GPTIM_UIE);
	//*Stop Timer
	CLR_BIT(TIM4->CR1,GPTIM_CEN);
}
u32  TIM4_u16GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	u16 Local_u16Cycle=Global4_u32Routine - Global4_u32CopyRoutine;

	Local_u32ElapsedTime=((TIM4->ARR)-(TIM4->CNT))+(Local_u16Cycle*65535);
	return Local_u32ElapsedTime;
}
 u32  TIM4_u16GetRemainingTime(void)
{
	u32 local_u32RemainingTime=0;

	if(Global4_u32CopyRoutine>=1)
	{
		local_u32RemainingTime=(TIM4->CNT)+(Global4_u32CopyRoutine-1)*65535+Global4_u32Fraction;
	}
	else if(Global4_u32CopyRoutine==0)
	{
		local_u32RemainingTime=TIM4->CNT;
	}
	return local_u32RemainingTime;
}
/**************************TIM5**********************/

/*  Clock of TIM2 is APB1_clk(8 MHZ)
   Disable TIM7 interrupt
   Disable TIM6                        
   F(TIM2)=8M/(1+PSC)
   If PSC=7
	Tick=>1us                 */
void TIM5_voidInit(void)
{
	/*Up Counter Mode*/
	TIM5->CR1&=~(0b111<<4);
	TIM5->CR1|=(DOWNCOUNTER<<4);

	/*ARR is Buffered can't changed Execpt at Update Event*/
	SET_BIT(TIM5->CR1,GPTIM_ARPE);

	/*Only Counter OverFlow UnderFlow Generate update Interrupt */
	SET_BIT(TIM5->CR1,GPTIM_URS);

	/*Enable Update Event */
	CLR_BIT(TIM5->CR1,GPTIM_UDIS);

	/*Disable Update Interrupt */
	CLR_BIT(TIM5->DIER,GPTIM_UIE);
	
	/*F(TIM2)=8M/(1+PSC)=1MHz
	*Ticks equal 1us*/
	TIM5->PSC=7;
}
/* Synchronous API  Lock Processor For Certain Ticks
   *Disable SysTick interrupt
   *enable Systick
   *polling flag (underflow)
   *Tick=>1us*/
void TIM5_voidSetBusyWait( u32 Copy_u32Ticks )
{
	u32 Local_u32Routine=Copy_u32Ticks/65535;
	u32 Local_u32Fraction=Copy_u32Ticks%65535;
	while(Local_u32Routine--)
	{
		TIM5->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM5->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM5->CR1,GPTIM_CEN);
		while(GET_BIT(TIM5->SR,GPTIM_UIF)==0);
		/*Clear Uderflow Flag*/
		CLR_BIT(TIM5->SR,GPTIM_UIF);
	}

	TIM5->ARR=Local_u32Fraction;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM5->EGR,GPTIM_UG);
	/*Enable counter*/
	SET_BIT(TIM5->CR1,GPTIM_CEN);
	while(GET_BIT(TIM5->SR,GPTIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM5->SR,GPTIM_UIF);
	/*Stop Timer*/
	CLR_BIT(TIM5->CR1,GPTIM_CEN);
	
	
	
}
void TIM5_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM5_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM5_u8ModeOfInterval=SINGLE_INTERVAL;

	Global5_u32Routine =(Copy_u32Ticks/65535);
	Global5_u32Fraction=Copy_u32Ticks%65535;
	/*    to be initialize before enter the interrupt */
	Global5_u32CopyRoutine=Global5_u32Routine;
	/*stop timer */
	CLR_BIT(TIM5->CR1,GPTIM_CEN);

	if(Global5_u32Routine)
	{
		TIM5->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM5->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM5->CR1,GPTIM_CEN);
	}
	else
	{
		TIM5->ARR=Global5_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM5->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM5->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM5->DIER,GPTIM_UIE);
}
void TIM5_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM5_CallBack=Copy_ptr;
	/*Set Mode to Periodic*/
	TIM5_u8ModeOfInterval=PERIODIC_INTERVAL;

	Global5_u32Routine =(Copy_u32Ticks/65535) ;
	Global5_u32Fraction=Copy_u32Ticks%65535;

	if(Global5_u32Routine)
	{
		TIM5->ARR=65535;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM5->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM5->CR1,GPTIM_CEN);
	}
	else
	{
		TIM5->ARR=Global5_u32Fraction;
	    /*Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM5->EGR,GPTIM_UG);
		/*Enable counter*/
		SET_BIT(TIM5->CR1,GPTIM_CEN);
	}

	/*Enable Update Interrupt */
	SET_BIT(TIM5->DIER,GPTIM_UIE);
}

void TIM5_voidStopInterval(void)
{
	//*Disable Update Interrupt
    CLR_BIT(TIM5->DIER,GPTIM_UIE);
	//*Stop Timer
	CLR_BIT(TIM5->CR1,GPTIM_CEN);
}
u32  TIM5_u16GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	u16 Local_u16Cycle=Global5_u32Routine - Global5_u32CopyRoutine;

	Local_u32ElapsedTime=((TIM5->ARR)-(TIM5->CNT))+(Local_u16Cycle*65535);
	return Local_u32ElapsedTime;
}
u32  TIM5_u16GetRemainingTime(void)
{
	u32 local_u32RemainingTime=0;
	if(Global5_u32CopyRoutine>=1)
	{
		local_u32RemainingTime=(TIM5->CNT)+(Global5_u32CopyRoutine-1)*65535+Global5_u32Fraction;
	}
	else if(Global5_u32CopyRoutine==0)
	{
		local_u32RemainingTime=TIM5->CNT;
	}
	return local_u32RemainingTime;
}


//**********************TIM2****************************
void TIM2_IRQHandler(void)
{
	if(Global2_u8Flag){
		Global2_u32CopyRoutine=Global2_u32Routine;
		Global2_u8Flag=0;
	}

	//Local_u32Routine=Global_u32Routine;
	if((Global2_u32CopyRoutine)>1)
	{
		Global2_u32CopyRoutine--;
		//Clear Uderflow Flag
		CLR_BIT(TIM2->SR,GPTIM_UIF);
		TIM2->ARR=65535;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM2->EGR,GPTIM_UG);

	}
	else if((Global2_u32CopyRoutine)==1)
	{
		Global2_u32CopyRoutine--;
		//*Clear Uderflow Flag
		CLR_BIT(TIM2->SR,GPTIM_UIF);
		TIM2->ARR=Global2_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM2->EGR,GPTIM_UG);

	}
	else
	{
		if(TIM2_u8ModeOfInterval==SINGLE_INTERVAL)
		{
			//*Disable Update Interrupt
	        CLR_BIT(TIM2->DIER,GPTIM_UIE);
			//*Stop Timer
			CLR_BIT(TIM2->CR1,GPTIM_CEN);
		}
		//*Callback Notification
		TIM2_CallBack();
		//Clear Uderflow Flag/
		CLR_BIT(TIM2->SR,GPTIM_UIF);

		if(Global2_u32Routine)TIM2->ARR=65535;
		else TIM2->ARR=Global2_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM2->EGR,GPTIM_UG);

		Global2_u8Flag=1;
	}

}

/**************TIM3***********************/
void TIM3_IRQHandler(void)
{
	if(Global3_u8Flag){
		Global3_u32CopyRoutine=Global3_u32Routine;
		Global3_u8Flag=0;
	}
	if((Global3_u32CopyRoutine)>1)
	{
		Global3_u32CopyRoutine--;
		//Clear Uderflow Flag
		CLR_BIT(TIM3->SR,GPTIM_UIF);
		TIM3->ARR=65535;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM3->EGR,GPTIM_UG);

	}
	else if((Global3_u32CopyRoutine)==1)
	{
		Global3_u32CopyRoutine--;
		//*Clear Uderflow Flag
		CLR_BIT(TIM3->SR,GPTIM_UIF);
		TIM3->ARR=Global3_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM3->EGR,GPTIM_UG);

	}
	else
	{
		if(TIM3_u8ModeOfInterval==SINGLE_INTERVAL)
		{
			//*Disable Update Interrupt
	        CLR_BIT(TIM3->DIER,GPTIM_UIE);
			//*Stop Timer
			CLR_BIT(TIM3->CR1,GPTIM_CEN);
		}
		//*Callback Notification
		TIM3_CallBack();
		//Clear Uderflow Flag/
		CLR_BIT(TIM3->SR,GPTIM_UIF);

		if(Global3_u32Routine)TIM3->ARR=65535;
		else TIM3->ARR=Global3_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM3->EGR,GPTIM_UG);

		Global3_u8Flag=1;
	}

}

//**************TIM4***********************
void TIM4_IRQHandler(void)
{
	if(Global4_u8Flag){
		Global4_u32CopyRoutine=Global4_u32Routine;
		Global4_u8Flag=0;
	}
	if((Global4_u32CopyRoutine)>1)
	{
		Global4_u32CopyRoutine--;
		//Clear Uderflow Flag
		CLR_BIT(TIM4->SR,GPTIM_UIF);
		TIM4->ARR=65535;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM4->EGR,GPTIM_UG);

	}
	else if((Global4_u32CopyRoutine)==1)
	{
		Global4_u32CopyRoutine--;
		//*Clear Uderflow Flag
		CLR_BIT(TIM4->SR,GPTIM_UIF);
		TIM4->ARR=Global4_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM4->EGR,GPTIM_UG);

	}
	else
	{
		if(TIM4_u8ModeOfInterval==SINGLE_INTERVAL)
		{
			//*Disable Update Interrupt
	        CLR_BIT(TIM4->DIER,GPTIM_UIE);
			//*Stop Timer
			CLR_BIT(TIM4->CR1,GPTIM_CEN);
		}
		//*Callback Notification
		TIM4_CallBack();
		//Clear Uderflow Flag/
		CLR_BIT(TIM4->SR,GPTIM_UIF);

		if(Global4_u32Routine)TIM4->ARR=65535;
		else TIM4->ARR=Global4_u32Fraction;
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM4->EGR,GPTIM_UG);

		Global4_u8Flag=1;
	}

}




