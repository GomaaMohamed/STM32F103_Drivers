/*****************************************************************************
* @file:    USART_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sat, 7 Oct 2023 12:21:12 +0200
* @brief:   USART Driver for STM32F103
******************************************************************************/
#ifndef _USART_INTERFACE_H
#define _USART_INTERFACE_H


/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Recieved State Data Type */
typedef enum
{
    RECEIVED_NOT_OK=0,
    RECEIVED_OK,
} UartRecievedState_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize uart module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void USART_init(void);

/**
 * @brief---------------------> Send charchter
 * @parameter1----------------> (Character) charcter to be sent
 * @return--------------------> None
 * @preconditions-------------> USART is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant
 */
void USART_transmitCharacter(u8 Character);

/**
 * @brief---------------------> Send String
 * @parameter1----------------> (String) string to be sent
 * @return--------------------> None
 * @preconditions-------------> USART is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant
 */
void USART_transmitString(u8 String[]);

/**
 * @brief---------------------> Receive character
 * @parameter1----------------> (ReceivedData) pointer to hold received data
 * @return--------------------> Received state
 * @preconditions-------------> USART is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
UartRecievedState_type USART_receiveCharacter(u8 *ReceivedData);

/**
 * @brief---------------------> Enable UART Complete Tx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_enableCompleteTxInterrupt(void);

/**
 * @brief---------------------> Disable UART Complete Tx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_disableCompleteTxInterrupt(void);

/**
 * @brief---------------------> Set UART Complete Tx callback
 * @parameter1----------------> (Callback) pointer to function to be called at UART interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_setCompleteTxCallack(void (*Callback) (void));

/**
 * @brief---------------------> Enable UART Complete Rx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_enableCompleteRxInterrupt(void);

/**
 * @brief---------------------> Disable UART Complete Rx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_disableCompleteRxInterrupt(void);

/**
 * @brief---------------------> Set UART Rx callback
 * @parameter1----------------> (Callback) pointer to function to be called at UART interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_setCompleteRxCallack(void (*Callback) (void));

/**
 * @brief---------------------> Enable UART Empty Tx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_enableTxRegisterEmptyInterrupt(void);

/**
 * @brief---------------------> Disable UART Empty Tx interrupt
 * @param---------------------> None 
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_disableTxRegisterEmptyInterrupt(void);

/**
 * @brief---------------------> Set UART Empty Tx callback
 * @parameter1----------------> (Callback) pointer to function to be called at UART interrupt
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void USART_setTxEmptyCallack(void (*Callback) (void));

#endif
