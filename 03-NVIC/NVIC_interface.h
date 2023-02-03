/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                     */
/*********************************************************************************/

#ifndef _NVIC_INTERFACE_H_
#define _NVIC_INTERFACE_H_

void NVIC_voidEnableInterrupt(u8 Copy_u8IntNumber);
void NVIC_voidDisableInterrupt(u8 Copy_u8IntNumber);
void NVIC_voidSetPendingFlag(u8 Copy_u8IntNumber);
void NVIC_voidClearPendingFlag(u8 Copy_u8IntNumber);
u8 NVIC_voidGetActiveFlag(u8 Copy_u8IntNumber);
void NVIC_voidSetPriority(s8 Copy_s8IntId,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority,u32 Copy_u32Group);

/* Definition of Groups */
#define   NVIC_GROUP3   0x05FA0300   // 4 bits for group (IPR)  ->  group
#define   NVIC_GROUP4   0x05FA0400   // 3 bits for group & 1 bit for sub
#define   NVIC_GROUP5   0x05FA0500   // 2 bits for group & 2 bit for sub
#define   NVIC_GROUP6   0x05FA0600   // 1 bits for group & 3 bit for sub
#define   NVIC_GROUP7   0x05FA0700   // 0 bits for group & 4 bit for sub
   
#endif