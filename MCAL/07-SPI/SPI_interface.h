/*****************************************************************************
* @file:    SPI_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 8 Oct 2023 16:55:32 +0200
* @brief:   SPI Driver for STM32F103
******************************************************************************/
#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H


/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize spi module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void SPI_init(void);

/**
 * @brief---------------------> Send and receive data synchronous
 * @parameter1----------------> (DataToSend) data to be sent
 * @parameter2----------------> (DataToReceive) pointer to hold received data
 * @return--------------------> None
 * @preconditions-------------> Spi is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-Reentrant      
 */
void SPI_sendReceiveSynch(u8 DataToSend,u8 *DataToReceive);

/**
 * @brief---------------------> Send and receive data asynchronous
 * @parameter1----------------> (DataToSend) data to be sent
 * @parameter2----------------> (Callback) Callback function to be called at receive
 * @return--------------------> None
 * @preconditions-------------> Spi is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant    
 */
void SPI_sendReceiveAsynch(u8 DataToSend,void  (*Callback)(void));



#endif
