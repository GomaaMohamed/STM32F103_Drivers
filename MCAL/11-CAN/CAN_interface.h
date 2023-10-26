/*****************************************************************************
* @file:    CAN_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 10 Oct 2023 11:21:12 +0200
* @brief:   Controller Area Network(CAN) Driver for STM32F103
******************************************************************************/
#ifndef    _CAN_INTERFACE_H
#define    _CAN_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* CAN Recieved Data Type */
typedef struct{
	u8  FifoState;   //State Of Fifo equal 1 if FIFO isn't empty & 0 if FIFO is empty
	u32 DataId;
	u8  FrameType;  //Frame Type equal 0 in case Of Data Frame and 1 in case of Remote Frame
	u8  DataLength;
	u8  FilterIndex;
	u32 DataLow;
	u32 DataHigh;	
}ReceivedData_type;

/* CAN operating mode data type */
typedef enum
{
	// CAN Operating Modes
	CAN_SLEEP_MODE=0,
	CAN_INITIALIZATION_MODE,
	CAN_NORMAL_MODE,
	CAN_OPERATING_MODE_ERR
} OperatingMode_type;

/* CAN testing mode data type */
typedef enum
{
	// CAN Testing Modes
	CAN_SILENT_MODE=0,
	CAN_LOOPBACK_MODE,
	CAN_COMBINED_MODE,
	CAN_TEST_MODE_ERR
} TestMode_type;

/* CAN mailbox data type */
typedef enum
{
	CAN_MAILBOX0=0,
	CAN_MAILBOX1,
	CAN_MAILBOX2,
	CAN_MAILBOX_ERR
} CanMailbox_type;

/* CAN fifo data type */
typedef enum
{
	CAN_FIFO0=0,
	CAN_FIFO1,
	CAN_FIFO_ERR
} CanFifo_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */


/**
 * @brief---------------------> Initialize can module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void CAN_init(void);

/**
 * @brief---------------------> Set can operating mode
 * @parameter1----------------> (OperatingMode) operating mode to be set
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 */
void CAN_setOperatingMode(OperatingMode_type OperatingMode);

/**
 * @brief---------------------> Reset operating mode
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void CAN_resetOperatingMode(void);

/**
 * @brief---------------------> Set can test mode
 * @parameter1----------------> (TestMode) test mode to be set
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_setTestMode(TestMode_type TestMode);

/**
 * @brief---------------------> Reset test mode
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void CAN_resetTestMode(void);

/**
 * @brief---------------------> Send data frame
 * @parameter1----------------> (MessageId) id of the data to be sent 
 * @parameter2----------------> (DataLength) length of the data to be sent 
 * @parameter3----------------> (DataHigh) high 4 bytes data to be sent 
 * @parameter4----------------> (DataLow) low 4 bytes data to be sent 
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_transmitDataFrame(u32 MessageId,u8 DataLength,u32 DataHigh,u32 DataLow);

/**
 * @brief---------------------> Cancel data transmission request
 * @parameter1----------------> (CanMailbox) mailbox to be canceled its transmission 
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_abortTransmissionRequest(CanMailbox_type CanMailbox);

/**
 * @brief---------------------> Send remote frame
 * @parameter1----------------> (MessageId) message id to be requested
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_transmitRemoteFrame(u32 MessageId);

/**
 * @brief---------------------> Receive data
 * @parameter1----------------> (CanFifo) can fifo to be read
 * @parameter2----------------> (RecievedData) varible to hold received data
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_recieveData(CanFifo_type CanFifo,ReceivedData_type* RecievedData);

/**
 * @brief---------------------> Set can callback
 * @parameter1----------------> (Callback) callback to be set
 * @return--------------------> None
 * @preconditions-------------> CAN is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void CAN_setCallBack(void(*Callback)(void));




#endif
