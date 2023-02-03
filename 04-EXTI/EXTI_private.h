/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#ifndef _EXTI_PRIVATE_H_
#define _EXTI_PRIVATE_H_

static void (* RXTI0_Callback) (void) = NULL;
static void (* RXTI1_Callback) (void) = NULL;
static void (* RXTI2_Callback) (void) = NULL;
static void (* RXTI3_Callback) (void) = NULL;
static void (* RXTI4_Callback) (void) = NULL;

typedef struct{
	volatile  u32  IMR;
	volatile  u32  EMR;
	volatile  u32  RTSR;
	volatile  u32  FTSR;
	volatile  u32  SWIER;
	volatile  u32  PR;
	
}exti_t;

#define EXTI  ((volatile exti_t *)0x40010400)

#endif