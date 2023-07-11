/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                    */
/*********************************************************************************/ 

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ATIM_interface.h"
#include"ATIM_private.h"
#include"ATIM_config.h"

#include"RCC_interface.h"
#include"GPIO_interface.h"



/***********************TIM1****************************/
/* Clock of TIM1 is APB2_clk(8 MHZ)
   Disable TIM1 interrupt
   Disable TIM1
   F(TIM1)=8M/(1+PSC)
   If PSC=7
   Tick=>1us                       */
void TIM1_voidInit(void)
{
	//Enable Clock Of Timer 1
	RCC_voidEnableClock(RCC_APB2,RCC_TIM1);
	//Set Pin Mode Of PWM Channel 1 GPIOA GPIO_PIN8
	GPIO_voidSetPinDirection(GPIOA,GPIO_PIN8,GPIO_OUTPUT_2MHZ_AFPP);
	
	#if     ATIM1_COUNT_DIRECTION==ATIM_COUNTS_DOWN
	    /*Down Counter Mode*/
	    TIM1->CR1 &=~(0b111<<4);
	    TIM1->CR1 |= (0b001<<4);
	#elif   ATIM1_COUNT_DIRECTION==ATIM_COUNTS_UP
	    /*Down Counter Mode*/
	    TIM1->CR1&=~(0b111<<4);
	    TIM1->CR1|= (0b000<<4);	
	#else
		#error("You chosed Wrong count Direction")
	#endif
	
	
	/*ARR is Buffered can't changed Execpt at Update Event*/
	SET_BIT(TIM1->CR1,ATIM_ARPE);

	/*Only Counter OverFlow UnderFlow Generate update Interrupt */
	SET_BIT(TIM1->CR1,ATIM_URS);

	/*Enable Update Event */
	CLR_BIT(TIM1->CR1,ATIM_UDIS);

	/*Disable Update Interrupt */
	CLR_BIT(TIM1->DIER,ATIM_UIE);

	/*F(TIM2)=8M/(1+PSC)=1MHz
	*Ticks equal 1us*/
	TIM1->PSC=7;
}
/* Synchronous API  Lock Processor For Certain Ticks
   *Disable SysTick interrupt
   *enable Systick
   *polling flag (underflow)
   *Tick=>1us*/
void TIM1_voidSetBusyWait( u32 Copy_u32Ticks )
{
	/* repetition counter register.
	 * This means that data are transferred from
	   the preload registers to the shadow registers
	   every N+1 counter overflows or underflows,
       where N is the value in the TIMx_RCR repetition counter register
     */
	TIM1->RCR=(Copy_u32Ticks/65535)-1;
	TIM1->ARR=65535;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM1->EGR,ATIM_UG);
	/*Enable counter*/
	SET_BIT(TIM1->CR1,ATIM_CEN);	
	while(GET_BIT(TIM1->SR,ATIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM1->SR,ATIM_UIF);	
	
	TIM1->RCR=0;
	TIM1->ARR=Copy_u32Ticks%65535;
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM1->EGR,ATIM_UG);
	
	while(GET_BIT(TIM1->SR,ATIM_UIF)==0);
	/*Clear Uderflow Flag*/
	CLR_BIT(TIM1->SR,ATIM_UIF);
	/*Stop Timer*/
	CLR_BIT(TIM1->CR1,ATIM_CEN);
	
	

}


/*********************************************************/
void TIM1_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM1_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM1_u8ModeOfInterval=SINGLE_INTERVAL;

	Global1_u32Routine =(Copy_u32Ticks/65535);
	Global1_u32Fraction=(Copy_u32Ticks%65535);

	if(Global1_u32Routine)
	{
		/*  repetition counter register */
		TIM1->RCR=Global1_u32Routine-1;
		TIM1->ARR=65535;
		Global4_u8Flag=1;
	}
	else
	{
		TIM1->ARR=Global1_u32Fraction;
	}
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM1->EGR,ATIM_UG);
	/*Enable counter*/
	SET_BIT(TIM1->CR1,ATIM_CEN);
	/*Enable Update Interrupt */
	SET_BIT(TIM1->DIER,ATIM_UIE);
}

void TIM1_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/*save CallBack*/
	TIM1_CallBack=Copy_ptr;
	/*Set Mode to Single*/
	TIM1_u8ModeOfInterval=PERIODIC_INTERVAL;

	Global1_u32Routine =(Copy_u32Ticks/65535);
	Global1_u32Fraction=Copy_u32Ticks%65535;

	if(Global1_u32Routine)
	{
		/*  repetition counter register */
		TIM1->RCR=Global1_u32Routine-1;
		TIM1->ARR=65535;
		Global4_u8Flag=1;
	}
	else
	{
		TIM1->ARR=Global1_u32Fraction;
		Global4_u8Flag=0;
	}
	/*Re-Initialize the the counter & prescaller*/
	SET_BIT(TIM1->EGR,ATIM_UG);
	/*Enable counter*/
	SET_BIT(TIM1->CR1,ATIM_CEN);
	/*Enable Update Interrupt */
	SET_BIT(TIM1->DIER,ATIM_UIE);
}
void TIM1_voidStopInterval(void)
{
	//*Disable Update Interrupt
    CLR_BIT(TIM1->DIER,ATIM_UIE);
	//*Stop Timer
	CLR_BIT(TIM1->CR1,ATIM_CEN);
}
u32  TIM1_u16GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	u16 Local_u16Cycle=Global1_u32Routine - TIM1->RCR+1;

	Local_u32ElapsedTime=((TIM1->ARR)-(TIM1->CNT))+(Local_u16Cycle*65535);
	return Local_u32ElapsedTime;
}
u32  TIM1_u16GetRemainingTime(void)
{
	u32 local_u32RemainingTime=0;
	u32 local_u32Routine=TIM1->RCR+1;
	if((local_u32Routine)>=1)
	{
		local_u32RemainingTime=(TIM1->CNT)+(local_u32Routine-1)*65535+Global1_u32Fraction;
	}
	else if(local_u32Routine==0)
	{
		local_u32RemainingTime=TIM1->CNT;
	}
	return local_u32RemainingTime;
}
void TIM1_voidGenPWMChannelNo1(u8 Copy_u8DutyCycle)
{
	/* Attention
	  PWM freq & PWM Duty
	  calculated at edge aligned mode
	  future plan to configure to work in both edge and center aligned mode	
	 */
	if ((Copy_u8DutyCycle>=0)&&(Copy_u8DutyCycle<=100))
	{
		/*  Enable Channel Nomber 1               */
		TIM1->CCER |=(1<<0); 
		/*  CC1 channel is configured as output */
		TIM1->CCMR1 &=~(0b11<<0);
	
		/*Preload register on TIMx_CCR1 enabled
		(it means that the CCR1 cannot be modified except at each update event)*/
		SET_BIT(TIM1->CCMR1,ATIM_OC1PE);
		/*set channel1 to PWM mode 1?(110)*/
		TIM1->CCMR1 &=~(0b111<<4); /* Clear     */
		TIM1->CCMR1 |= (0b110<<4); /* PWM mode 1*/
	
		/*************************************************************/
		/* PWM Duty = CCR1/( ARR+1)=CCR1/(1+999)
		CCR1 =(1000*DutyCycle)/100=10*DutyCycle
		*/
		TIM1->CCR1=10*Copy_u8DutyCycle;
	
	
		//PWM freq = fclk/((psc+1)(ARR+1) )= 8Mhz/((7+1)*(999+1)) =1Khz
		TIM1->PSC=7;        //the prescaler =15+1=16
		TIM1->ARR=999;      // the auto reload register
		/*Re-Initialize the the counter & prescaller*/
		SET_BIT(TIM1->EGR,ATIM_UG);
		/* OC and OCN outputs are enabled */
		SET_BIT(TIM1->BDTR,15);
		/*Enable counter*/
		SET_BIT(TIM1->CR1,ATIM_CEN);
	}
	else
	{
		/* #error "Error DutyCycle Out of range";  */
	}
	
}
void TIM1_voidStopPWMChannel1(void)
{

	//*Stop Timer
	CLR_BIT(TIM1->CR1,ATIM_CEN);
	TIM1->CCR1=0;
	/* OC and OCN outputs are Disabled */
	CLR_BIT(TIM1->BDTR,15);
}
void TIM1_voidGenPWMChannelNo2(u8 Copy_u8DutyCycle)
{
	/* Attention
	  PWM freq & PWM Duty
	  calculated at edge aligned mode
	  future plan to configure to work in both edge and center aligned mode	
	 */
	if ((Copy_u8DutyCycle>=0)&&(Copy_u8DutyCycle<=100))
	{
		/*  Enable Channel Nomber 2               */
		TIM1->CCER |=(1<<4); 
		/*  CC2 channel is configured as output */
		TIM1->CCMR1 &=~(0b11<<8);
	
		/*Preload register on TIMx_CCR2 enabled
		(it means that the CCR2 cannot be modified except at each update event)*/
		TIM1->CCMR1 |=(1<<ATIM_OC2PE);
		/*set channel2 to PWM mode 1?(110)*/
		TIM1->CCMR1 &=~(0b111<<12); /* Clear     */
		TIM1->CCMR1 |= (0b110<<12); /* PWM mode 1*/
	
		/*************************************************************/
		/* PWM Duty = CCR2/( ARR+1)=CCR2/(1+999)
		CCR1 =(1000*DutyCycle)/100=10*DutyCycle
		*/
		TIM1->CCR2=10*Copy_u8DutyCycle;
	
	
		//PWM freq = fclk/((psc+1)(ARR+1) )= 8Mhz/((7+1)*(999+1)) =1Khz
		TIM1->PSC=7;        //the prescaler =15+1=16
		TIM1->ARR=999;      // the auto reload register
		/*Re-Initialize the the counter & prescaller*/
		SET_BIT(TIM1->EGR,ATIM_UG);
		/* OC and OCN outputs are enabled */
		SET_BIT(TIM1->BDTR,15);
		/*Enable counter*/
		SET_BIT(TIM1->CR1,ATIM_CEN);
	}
	else
	{
		/* #error "Error DutyCycle Out of range" */
	}
	
}
void TIM1_voidGenPWMChannelNo3(u8 Copy_u8DutyCycle)
{
	/* Attention
	  PWM freq & PWM Duty
	  calculated at edge aligned mode
	  future plan to configure to work in both edge and center aligned mode	
	 */
	if ((Copy_u8DutyCycle>=0)&&(Copy_u8DutyCycle<=100))
	{
		/*  Enable Channel Nomber 3               */
		TIM1->CCER |=(1<<8); 
		/*  CC3 channel is configured as output */
		TIM1->CCMR2 &=~(0b11<<0);
	
		/*Preload register on TIMx_CCR3 enabled
		(it means that the CCR3 cannot be modified except at each update event)*/
		SET_BIT(TIM1->CCMR2,ATIM_OC3PE);
		/*set channel3 to PWM mode 1?(110)*/
		TIM1->CCMR2 &=~(0b111<<4); /* Clear     */
		TIM1->CCMR2 |= (0b110<<4); /* PWM mode 1*/
	
		/*************************************************************/
		/* PWM Duty = CCR2/( ARR+1)=CCR2/(1+999)
		CCR1 =(1000*DutyCycle)/100=10*DutyCycle
		*/
		TIM1->CCR3=10*Copy_u8DutyCycle;
	
	
		//PWM freq = fclk/((psc+1)(ARR+1) )= 8Mhz/((7+1)*(999+1)) =1Khz
		TIM1->PSC=7;        //the prescaler =15+1=16
		TIM1->ARR=999;      // the auto reload register
		/*Re-Initialize the the counter & prescaller*/
		SET_BIT(TIM1->EGR,ATIM_UG);
		/* OC and OCN outputs are enabled */
		SET_BIT(TIM1->BDTR,15);
		/*Enable counter*/
		SET_BIT(TIM1->CR1,ATIM_CEN);
	}
	else
	{
		/* #error "Error DutyCycle Out of range" */
	}
	
}
void TIM1_voidGenPWMChannelNo4(u8 Copy_u8DutyCycle)
{
	/* Attention
	  PWM freq & PWM Duty
	  calculated at edge aligned mode
	  future plan to configure to work in both edge and center aligned mode	
	 */
	if ((Copy_u8DutyCycle>=0)&&(Copy_u8DutyCycle<=100))
	{
		/*  Enable Channel Nomber 4               */
		TIM1->CCER |=(1<<12); 
		/*  CC4 channel is configured as output */
		TIM1->CCMR2 &=~(0b11<<8);
	
		/*Preload register on TIMx_CCR2 enabled
		(it means that the CCR2 cannot be modified except at each update event)*/
		TIM1->CCMR2 |=(1<<ATIM_OC4PE);
		/*set channel2 to PWM mode 1?(110)*/
		TIM1->CCMR2 &=~(0b111<<12); /* Clear     */
		TIM1->CCMR2 |= (0b110<<12); /* PWM mode 1*/
	
		/*************************************************************/
		/* PWM Duty = CCR2/( ARR+1)=CCR2/(1+999)
		CCR1 =(1000*DutyCycle)/100=10*DutyCycle
		*/
		TIM1->CCR4=10*Copy_u8DutyCycle;
	
	
		//PWM freq = fclk/((psc+1)(ARR+1) )= 8Mhz/((7+1)*(999+1)) =1Khz
		TIM1->PSC=7;        //the prescaler =15+1=16
		TIM1->ARR=999;      // the auto reload register
		/*Re-Initialize the the counter & prescaller*/
		SET_BIT(TIM1->EGR,ATIM_UG);
		/* OC and OCN outputs are enabled */
		SET_BIT(TIM1->BDTR,15);
		/*Enable counter*/
		SET_BIT(TIM1->CR1,ATIM_CEN);
	}
	else
	{
		/* #error "Error DutyCycle Out of range" */
	}
	
}
//**********************TIM1****************************
void TIM1_UP_IRQHandler(void)
{


	if(Global4_u8Flag==1)
	{
		//Clear Update Interrupt Flag
		CLR_BIT(TIM1->SR,ATIM_UIF);
		TIM1->ARR=Global1_u32Fraction;
		/*  repetition counter register */
		TIM1->RCR=0;
	    /* Re-Initialize the the counter & prescaller*/
	    SET_BIT(TIM1->EGR,ATIM_UG);
	    Global4_u8Flag=0;
	}
	
	else
	{
		if(TIM1_u8ModeOfInterval==SINGLE_INTERVAL)
		{
			//*Disable Update Interrupt
	        CLR_BIT(TIM1->DIER,ATIM_UIE);
			//*Stop Timer
			CLR_BIT(TIM1->CR1,ATIM_CEN);
		}
		//*Callback Notification
		TIM1_CallBack();
		//Clear Uderflow Flag/
		CLR_BIT(TIM1->SR,ATIM_UIF);

		if(Global1_u32Routine)
		{
			TIM1->RCR=Global1_u32Routine-1;
			TIM1->ARR=65535;
			Global4_u8Flag=1;
		}
		else
		{
			TIM1->ARR=Global1_u32Fraction;
			TIM1->RCR=0;
		}
	    //*Re-Initialize the the counter & prescaller
	    SET_BIT(TIM1->EGR,ATIM_UG);

	}

}

