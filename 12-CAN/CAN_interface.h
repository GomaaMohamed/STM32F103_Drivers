/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 21 Dec 2020                                                       */
/*********************************************************************************/
#ifndef    _CAN_INTERFACE_H_
#define    _CAN_INTERFACE_H_
/*********************************************User Types Of CAN Driver*********************************************************/
/* CAN Recieved Data Type */
typedef struct{
	u8  Copy_u8FifoState;   //State Of Fifo equal 1 if FIFO isn't empty & 0 if FIFO is empty
	u32 Copy_u32DataId;
	u8  Copy_u32FrameType;  //Frame Type equal 0 in case Of Data Frame and 1 in case of Remote Frame
	u8  Copy_u8DataLength;
	u8  Copy_u8FilterIndex;
	u32 Copy_u32DataLow;
	u32 Copy_u32DataHigh;	
}CAN_recievedata_t;
/*********************************************User Functions Of CAN Driver*********************************************************/
/* CAN initialization */
void CAN_voidInit(void);

/***********************************************************************
*  Operating Modes Function                                            *
*  Copy_u8Mode Options:                                                *
*  CAN_SLEEP_MODE                                                      *
*  CAN_INITIALIZATION_MODE                                             *
*  CAN_NORMAL_MODE                                                     *
***********************************************************************/
void CAN_voidSetOperatingMode(u8 Copy_u8Mode);
void CAN_voidReSetOperatingMode(void);

/* 
  Testing Modes Function
  Copy_u8Mode Options:
  CAN_SILENT_MODE
  CAN_LOOPBACK_MODE
  CAN_COMBINED_MODE
 */ 
void CAN_voidSetTestMode(u8 Copy_u8Mode);
void CAN_voidReSetTestMode(void);

/* Transmit Data Function......Note: Copy_u8DataLength  Value From 0(0byte) to 8(8byte)*/
void CAN_voidTransmitDataFrame(u32 Copy_u32MessageId,u8 Copy_u8DataLength,u32 Copy_u32DataHigh,u32 Copy_u32DataLow);

/* Abort Abort Transmission Request */
void CAN_voidAbortTransmissionRequest(u8 Copy_u8TransmissionRequest);

/* Requist Data Function */
void CAN_voidTransmitRemoteFrame(u32 Copy_u32MessageId);
/* Recived Data */
void CAN_voidRecieveData(u8 Copy_u8FifoNumber,CAN_recievedata_t* Copy_RecievedData);

void CAN_voidSetCallBack(void(*CallBack)(void));

/*
Remaining:
Time Triggered Mode
*/
/*********************************************User MACRO Definitions Of CAN Driver*********************************************************/
/* CAN Operating Modes */
#define  CAN_SLEEP_MODE              0
#define  CAN_INITIALIZATION_MODE     1
#define  CAN_NORMAL_MODE             2
/* CAN Testing Modes */
#define  CAN_SILENT_MODE             0
#define  CAN_LOOPBACK_MODE           1
#define  CAN_COMBINED_MODE           2
/* Transmission Request Options to abort */
#define  CAN_MAILBOX0   0
#define  CAN_MAILBOX1   1
#define  CAN_MAILBOX2   2
/* Recieved FIFO ID */
#define  CAN_FIFO0    0
#define  CAN_FIFO1    1




#endif
