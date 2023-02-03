/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 10 Sep 2020                                                    */
/*********************************************************************************/
#ifndef    _GPTIM_INTERFACE_H_
#define    _GPTIM_INTERFACE_H_

/********************TIM2********************/
void TIM2_voidInit(void);
void TIM2_voidSetBusyWait( u32 Copy_u32Ticks );
void TIM2_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM2_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM2_voidStopInterval(void);
u32  TIM2_u16GetElapsedTime(void);
u32  TIM2_u16GetRemainingTime(void);

/********************TIM3********************/

void TIM3_voidInit(void);
void TIM3_voidSetBusyWait( u32 Copy_u32Ticks );
void TIM3_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM3_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM3_voidStopInterval(void);
u32  TIM3_u16GetElapsedTime(void);
u32  TIM3_u16GetRemainingTime(void);

/********************TIM4********************/

void TIM4_voidInit(void);
void TIM4_voidSetBusyWait( u32 Copy_u32Ticks );
void TIM4_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM4_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void TIM4_voidStopInterval(void);
u32  TIM4_u16GetElapsedTime(void);
u32  TIM4_u16GetRemainingTime(void);


/********************CR1**********************/
#define   GPTIM_CEN           0
#define   GPTIM_UDIS          1
#define   GPTIM_URS           2
#define   GPTIM_OPM           3
#define   GPTIM_ARPE          7
/******************DIER***********************/
#define   GPTIM_UIE           0
/*******************EGR**************************/
#define   GPTIM_UG            0
/*******************SR***************************/
#define   GPTIM_UIF           0



#endif
