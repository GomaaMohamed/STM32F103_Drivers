/***************************************/
/* Author  :Gomaa                      */
/* Date    :19 Seb 2020                */
/* Version :V01                        */
/***************************************/

#ifndef    _USART_CONFIG_H_
#define    _USART_CONFIG_H_ 

/* Baud Rate Configuration at Clock 8 MHZ
       USART_BAUD_RATE:
	   BR_9600
	   BR_4800
	   BR_115200
 */
 
#define   USART_BAUD_RATE   BR_9600

/* Parity Check Enabled Or Disabled */
#define   USART_PARITY  USART_PARITY_DISABLED
#if   USART_PARITY ==   USART_PARITY_ENABLED
/* Parity Check Configuration
          Options:
		  USART_EVEN_PARITY
		  USART_ODD_PARITY
 */
#define   USART_PARITY_CHECK   USART_EVEN_PARITY
#endif

/* Frame Size Configuration
         Options:
		 USART_8BIT_DATA_SIZE
		 USART_9BIT_DATA_SIZE
 */
#define   USART_DATA_SIZE   USART_8BIT_DATA_SIZE

#endif







