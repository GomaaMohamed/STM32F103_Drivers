/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                    */
/*********************************************************************************/ 
#ifndef   ATIM_PRIVATE_H
#define	  ATIM_PRIVATE_H
typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RCR;
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 BDTR;
	volatile u32 DCR;
	volatile u32 DMAR;

}TIM_t;

#define     TIM1        ((volatile TIM_t *)0x40012C00)
#define     TIM8        ((volatile TIM_t *)0x40013400)

/****************************ATIM Options******************************/
#define           ATIM_COUNTS_UP                      0
#define           ATIM_COUNTS_DOWN                    1
#define           ATIM_CENTER_ALIGNED_MODE1           2
#define           ATIM_CENTER_ALIGNED_MODE2           3
#define           ATIM_CENTER_ALIGNED_MODE3           4

/***********************TIM_CR1****************************************/
#define          ATIM_ARPE                              7
#define          ATIM_URS                               2
#define          ATIM_UDIS                              1
#define          ATIM_CEN                               0    
                   
/********************TIM1->DIER***************************************/
#define          ATIM_UIE                               0

/********************TIM1->SR*****************************************/
#define          ATIM_UIF                               0

/********************TIM1->EGR****************************************/
#define          ATIM_UG                                0
/*******************TIM1_CCMR1**************************************/
#define          ATIM_OC1PE                             3
#define          ATIM_OC2PE                             11
/*******************TIM1_CCMR2**************************************/
#define          ATIM_OC3PE                             3
#define          ATIM_OC4PE                             11

/*Interval Mode*/
#define    SINGLE_INTERVAL     0
#define    PERIODIC_INTERVAL   1


/* Define Callback Global Variable */
static void (*TIM1_CallBack)(void);
/* Define Variable for interval mode */
static u8  TIM1_u8ModeOfInterval;
static u32 Global1_u32Fraction;
static u32 Global1_u32Routine ;
static volatile  u8  Global4_u8Flag=1;
#endif


