/***************************************/
/* Author  :Gomaa                      */
/* Date    :19 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _USART_PRIVATE_H_
#define _USART_PRIVATE_H_

typedef struct {
	
	  volatile u32 SR;
	  volatile u32 DR;
	  volatile u32 BRR;
	  volatile u32 CR1;
	  volatile u32 CR2;
	  volatile u32 CR3;
	  volatile u32 GTPR;
	  
	
}usart_t;
#define  USART  ((volatile usart_t *)(0x40013800))


/*Parity On Or Off */
#define   USART_PARITY_ENABLED    0
#define   USART_PARITY_DISABLED   1
/* Parity Check Options */
#define       USART_EVEN_PARITY  0
#define		  USART_ODD_PARITY   1
/* Data Size Options */
#define    USART_8BIT_DATA_SIZE  0
#define    USART_9BIT_DATA_SIZE  1

/* Baud Rate Configuration */
#define   BR_9600    0
#define   BR_4800    1
#define   BR_115200  2



#endif
