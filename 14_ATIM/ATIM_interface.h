/****************************************************************/
/* Author :Hussin Ebrahim                                       */
/* Date   :5/4/2021                                             */
/* Version:V01                                                  */
/****************************************************************/
#ifndef   ATIM_INTERFACE_H
#define	  ATIM_INTERFACE_H
void TIM1_voidSetBusyWait( u32 Copy_u32Ticks );
void TIM1_voidInit(void);
void TIM1_voidSetIntervalPeriodic( u32 Copy_u32Ticks,void (*Copy_ptr)(void));
void TIM1_voidSetIntervalSingle( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
u32  TIM1_u16GetRemainingTime(void);
u32  TIM1_u16GetElapsedTime(void);
void TIM1_voidStopInterval(void);
void TIM1_voidGenPWMChannelNo1(u8 Copy_u8DutyCycle);
void TIM1_voidGenPWMChannelNo2(u8 Copy_u8DutyCycle);
void TIM1_voidGenPWMChannelNo3(u8 Copy_u8DutyCycle);
void TIM1_voidGenPWMChannelNo4(u8 Copy_u8DutyCycle);
#endif