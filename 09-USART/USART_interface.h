/***************************************/
/* Author  :Gomaa                      */
/* Date    :16 Seb 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _USART_INTERFACE_H_
#define _USART_INTERFACE_H_

void USART_voidInit(void);
void USART_voidTransmit(u8 Copy_u8DataToTransmit[]);
u8   USART_u8Receive(u8 *ReceivedData);



#endif