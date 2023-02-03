/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 10 Sep 2020                                                    */
/*********************************************************************************/
#ifndef    _GPTIM_PRIVATE_H_
#define    _GPTIM_PRIVATE_H_
/****************TIM2*******************/

static volatile  u32 Global2_u32Routine=0;
static volatile  u32 Global2_u32Fraction;
static volatile  u32 Global2_u32CopyRoutine;
static volatile  u8  Global2_u8Flag=1;
/* Define Callback Global Variable */
static volatile void (*TIM2_CallBack)(void);
/* Define Variable for interval mode */
static volatile u8 TIM2_u8ModeOfInterval;

/****************TIM3*******************/

static volatile  u32 Global3_u32Routine=0;
static volatile  u32 Global3_u32Fraction;
static volatile  u32 Global3_u32CopyRoutine;
static volatile  u8  Global3_u8Flag=1;
static volatile  void (*TIM3_CallBack)(void);
static volatile  u8     TIM3_u8ModeOfInterval;

/****************TIM4*******************/

static volatile  u32 Global4_u32Routine=0;
static volatile  u32 Global4_u32Fraction;
static volatile  u32 Global4_u32CopyRoutine;
static volatile  u8  Global4_u8Flag=1;
static volatile  void (*TIM4_CallBack)(void);
static volatile  u8     TIM4_u8ModeOfInterval;


/****************TIM5*******************/

static volatile  u32 Global5_u32Routine=0;
static volatile  u32 Global5_u32Fraction;
static volatile  u32 Global5_u32CopyRoutine;
static volatile  u8  Global5_u8Flag=1;
static volatile  void (*TIM5_CallBack)(void);
static volatile  u8     TIM5_u8ModeOfInterval;




/*Interval Mode*/
#define    SINGLE_INTERVAL     0
#define    PERIODIC_INTERVAL   1

typedef struct
{
	volatile u32 CR1;           /*00*/
	volatile u32 CR2;           /*04*/
	volatile u32 SMCR;          /*08*/
	volatile u32 DIER;          /*0C*/
	volatile u32 SR;            /*10*/
	volatile u32 EGR;           /*14*/
	volatile u32 CCMR1;         /*18*/
	volatile u32 CCMR2;         /*1C*/
	volatile u32 CCER;          /*20*/
	volatile u32 CNT;           /*24*/
	volatile u32 PSC;           /*28*/
	volatile u32 ARR;           /*2C*/
	volatile u32 Reserved1;     /*30*/
	volatile u32 CCR1;          /*34*/
	volatile u32 CCR2;          /*38*/
	volatile u32 CCR3;          /*3C*/
	volatile u32 CCR4;          /*40*/
	volatile u32 Reserved2;     /*44*/
	volatile u32 DCR;           /*48*/
	volatile u32 DMAR;          /*4C*/
}TIM_t;
#define  TIM2    ((volatile TIM_t*)0x40000000)
#define  TIM3    ((volatile TIM_t*)0x40000400)
#define  TIM4    ((volatile TIM_t*)0x40000800)
#define  TIM5    ((volatile TIM_t*)0x40000C00)
#endif
