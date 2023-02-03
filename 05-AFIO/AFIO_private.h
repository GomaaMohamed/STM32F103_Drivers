/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#ifndef _AFIO_PRIVATE_H_
#define _AFIO_PRIVATE_H_



typedef struct{
	volatile  u32  EVCR;
	volatile  u32  MAPR;
	volatile  u32  EXTICR[4];
	volatile  u32  MAPR2;
	
	
}afio_t;

#define AFIO  ((volatile afio_t *)0x40010000)

#endif