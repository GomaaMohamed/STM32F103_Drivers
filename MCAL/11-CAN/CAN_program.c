/*****************************************************************************
* @file:    CAN_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 10 Oct 2023 11:21:12 +0200
* @brief:   Controller Area Network(CAN) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include     "STD_TYPES.h"
#include     "BIT_MATH.h"

#include     "CAN_interface.h"
#include     "CAN_private.h"
#include     "CAN_config.h"
#include     "RCC_interface.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initiakize uart module
void CAN_init(void)
{
    // Enable Clock of CAN Controller 
	RCC_enableClock(RCC_APB1,RCC_CAN);

    // Initialize Bit Timing 
	// You should Be In Initialization Mode Firstly 
	CAN_setOperatingMode(CAN_INITIALIZATION_MODE);
	CAN_BTR |= CAN_BTR_FOR_BIT_TIMING;

   // Select BUS-OFF MANAGEMENT 
    #if BUS_OFF_MANAGEMENT == BUS_OFF_AUTOMATIC_MANAGEMENT
	    SET_BIT(CAN_MCR,6);
	#elif BUS_OFF_MANAGEMENT == BUS_OFF_NONAUTOMATIC_MANAGEMENT
		CLR_BIT(CAN_MCR,6);
	#endif

    // Set Interrupt Configurations 
	// FIFO0 
    #if CAN_NEW_MESSAGE_INTERRUPT_FIFO0 == CAN_NEW_MESSAGE_INTERRUPT_ENABLED
	    SET_BIT(CAN_IER,1);
	#elif CAN_NEW_MESSAGE_INTERRUPT_FIFO0 == CAN_NEW_MESSAGE_INTERRUPT_DISABLED
	    CLR_BIT(CAN_IER,1);
	#endif
	// FIFO1 
    #if CAN_NEW_MESSAGE_INTERRUPT_FIFO1 == CAN_NEW_MESSAGE_INTERRUPT_ENABLED
	    SET_BIT(CAN_IER,4);
	#elif CAN_NEW_MESSAGE_INTERRUPT_FIFO1 == CAN_NEW_MESSAGE_INTERRUPT_DISABLED
	    CLR_BIT(CAN_IER,4);
	#endif

    // Select WakeUp Mode 
	#if CAN_WAKEUP_MODE == CAN_AUTOMATIC_WAKEUP_MODE
	    SET_BIT(CAN_MCR,5);
	#elif CAN_WAKEUP_MODE == CAN_MANUAL_WAKEUP_MODE
	    CLR_BIT(CAN_MCR,5);
	#endif
	
    // Select Time Triggered Mode 
	#if CAN_TIMETRIGGERED_MODE == CAN_TIMETRIGGERED_MODE_DISABLED
	    CLR_BIT(CAN_MCR,7);
	#elif CAN_TIMETRIGGERED_MODE == CAN_TIMETRIGGERED_MODE_ENABLED
	    SET_BIT(CAN_MCR,7);
	#endif

    // Select Retransmission Option 
	#if CAN_RETRANSMISSION == CAN_AUTOMATIC_RETRANSMISSION
	    CLR_BIT(CAN_MCR,4);
	#elif CAN_RETRANSMISSION == CAN_NONAUTOMATIC_RETRANSMISSION
	    SET_BIT(CAN_MCR,4);
	#endif
   // Select RECIEVE FIFO Locked Mode 
	#if CAN_RECEIVE_FIFO == CAN_RECEIVE_FIFO_UNLOCKED
	    CLR_BIT(CAN_MCR,3);
	#elif CAN_RECEIVE_FIFO == CAN_RECEIVE_FIFO_LOCKED
	    SET_BIT(CAN_MCR,3);
	#endif

    // Select Priority Type Of Transmission 
	#if CAN_TRANSMIT_PRIORITY == CAN_TRANSMIT_PRIORITY_ID_BASED
		CLR_BIT(CAN_MCR,2);
	#elif CAN_TRANSMIT_PRIORITY == CAN_TRANSMIT_PRIORITY_REQUEST_BASED
	    SET_BIT(CAN_MCR,2);
	#endif
    // Enable Or Disable CAN During Debug 
	#if CAN_DURING_DEBUG  ==  CAN_DURING_DEBUG_ENABLED
		CLR_BIT(CAN_MCR,16);
	#elif CAN_DURING_DEBUG  ==  CAN_DURING_DEBUG_DISABLED
		SET_BIT(CAN_MCR,16);
	#endif

    // Initialize CAN Filtrs
	CAN_configFilters();
}

// Function to set operating mode
void CAN_setOperatingMode(OperatingMode_type OperatingMode)
{
	// Validate input parameters
	ASSERT(OperatingMode >= 0 && OperatingMode < CAN_OPERATING_MODE_ERR);

	// Set operating mode based on the previous mode
	if (OperatingMode == CAN_SLEEP_MODE)
	{   
    	// From Initialization Mode to Sleep Mode 
		if (CurrentModeFlag == 1)
		{
	    	// Disable Initialization Mode 
			CLR_BIT(CAN_MCR,0);

			// Enable Sleep mode 
			SET_BIT(CAN_MCR,1);

			// Wait Untile The Initialization Mode to Setup 
			while(GET_BIT(CAN_MSR,1) == 0);
		}
		// From Normal Mode to Sleep Mode 
		else if (CurrentModeFlag == 2)
		{
			// Enable Sleep mode 
		 	SET_BIT(CAN_MCR,1);
		    // Wait Untile The Initialization Mode to Setup 
			while(GET_BIT(CAN_MSR,1) == 0);
		}
		// Set current mode to be sleep
	  	CurrentModeFlag = 0;
	}
	else if (OperatingMode == CAN_INITIALIZATION_MODE)
	{
		// from Sleep Mode to Initialization Mode 
        if (CurrentModeFlag == 0)
		{
	    	// Disable Sleep Mode 
			CLR_BIT(CAN_MCR,1);

		    // Enable Initialization mode 
		 	SET_BIT(CAN_MCR,0);

			// Wait Untile The Initialization Mode to Setup 
			while(GET_BIT(CAN_MSR,0) == 0);
		}
		// From Normal Mode to Initialization Mode 
		else if (CurrentModeFlag == 2)
		{
			// Enable Initialization mode 
		 	SET_BIT(CAN_MCR,0);
			// Wait Untile The Initialization Mode to Setup 
			while(GET_BIT(CAN_MSR,0) == 0);
			
		}
		// Set current mode to be initialization
		CurrentModeFlag = 1;
	}
	else if (OperatingMode == CAN_NORMAL_MODE)
	{
		// From Sleep Mode to Normal Mode 
		if (CurrentModeFlag == 0)
		{
			// Disable Sleep Mode and init mode 
			CLR_BIT(CAN_MCR,1);
			CLR_BIT(CAN_MCR,0);

			// Wait Untile The Initialization Mode to Setup 
			while((GET_BIT(CAN_MSR,0) == 1)|(GET_BIT(CAN_MSR,1) == 1));  
		}
		// From Initialization Mode to Normal Mode 
		else if (CurrentModeFlag == 1)
		{
			// Disable Sleep Mode and init mode 
			CLR_BIT(CAN_MCR,1);
			CLR_BIT(CAN_MCR,0);
			// Wait Untile The Normal Mode to Setup 
			while((GET_BIT(CAN_MSR,0) == 1)&&(GET_BIT(CAN_MSR,1) == 1));
		}
		// Set current mode to be normal
		CurrentModeFlag = 2;
	}
		
}

// Function to reset operating mode
void CAN_resetOperatingMode(void)
{
    SET_BIT(CAN_MCR,15);	
}	
	
// Function to set test mode
void CAN_setTestMode(TestMode_type TestMode)
{
	// Validate input parameters
	ASSERT(TestMode >= 0 && TestMode < CAN_TEST_MODE_ERR);

	// You should Be In Initialization Mode Firstly 
	CAN_setOperatingMode(CAN_INITIALIZATION_MODE);

	// Select test mode type
    if (TestMode == CAN_SILENT_MODE)
	{
		SET_BIT(CAN_BTR,31);
	}
	else if (TestMode == CAN_LOOPBACK_MODE)
	{
		SET_BIT(CAN_BTR,30);
	}
	else if (TestMode == CAN_COMBINED_MODE)
	{
		SET_BIT(CAN_BTR,31);
		SET_BIT(CAN_BTR,30);
	}
}

// Function to reset test mode
void CAN_reSetTestMode(void)
{
	CLR_BIT(CAN_BTR,31);
	CLR_BIT(CAN_BTR,30);
}

// Function to send a data frame
void CAN_transmitDataFrame(u32 MessageId,u8 DataLength,u32 DataHigh,u32 DataLow)
{    
	// Validate input parameters

	// Check What is The Empty MailBox 
	if (GET_BIT(CAN_TSR,26)==1)
	{
    	// Set Message Identifier & Standrization & Type Of Data Frame 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI0R,2);

			// Set id 
		    CAN_TI0R &= ~(0b11111111111 << 21);
		    CAN_TI0R |= (MessageId << 21);

			// Set data frame 
		    CLR_BIT(CAN_TI0R,1);
		#elif  CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// Set extended
		    SET_BIT(CAN_TI0R,2);

		    // Set id
		    CAN_TI0R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI0R |= (MessageId << 3);

			// Set data frame */
		    CLR_BIT(CAN_TI0R,1);
		#endif
	
	    // Set The Length Of Data*/
	    if (DataLength <= 8)
		{
	        CAN_TDT0R &= ~(0b1111 << 0);
		    CAN_TDT0R |= DataLength;
		}
			   
	    // Write The Data That Will be Transmitted 
        CAN_TDL0R = DataLow;
		CAN_TDH0R = DataHigh;

	    // Make a Transmission Request
		SET_BIT(CAN_TI0R,0);
	        
		//wait until Transmission become Ok
		while(GET_BIT(CAN_TSR,1)==0);
	}
	/* Check MailBox1 */
	else if (GET_BIT(CAN_TSR,27)==1)
	{
        // SET Message Identifier & Standrization & Type Of Data Frame 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI1R,2);

			// Set id 
		    CAN_TI1R &= ~(0b11111111111 << 21);
		    CAN_TI1R |= (MessageId << 21);

			// Set data frame 
		    CLR_BIT(CAN_TI1R,1);
		#elif  CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// Set extended
		    SET_BIT(CAN_TI1R,2);

		    // Set id
		    CAN_TI1R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI1R |= (MessageId << 3);

			// Set data frame */
		    CLR_BIT(CAN_TI1R,1);
		#endif
	
	    // Set The Length Of Data*/
	    if (DataLength <= 8)
		{
	        CAN_TDT1R &= ~(0b1111 << 0);
		    CAN_TDT1R |= DataLength;
		}
			   
	    // Write The Data That Will be Transmitted 
        CAN_TDL1R = DataLow;
		CAN_TDH1R = DataHigh;

	    // Make a Transmission Request
		SET_BIT(CAN_TI1R,0);

	    //wait until Transmission become Ok
	    while(GET_BIT(CAN_TSR,9)==0);
	}
	/* Check MailBox2 */
	else if (GET_BIT(CAN_TSR,28)==1)
	{
        // SET Message Identifier & Standrization & Type Of Data Frame 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI2R,2);

			// Set id 
		    CAN_TI2R &= ~(0b11111111111 << 21);
		    CAN_TI2R |= (MessageId << 21);

			// Set data frame 
		    CLR_BIT(CAN_TI2R,1);
		#elif  CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// Set extended
		    SET_BIT(CAN_TI2R,2);

		    // Set id
		    CAN_TI2R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI2R |= (MessageId << 3);

			// Set data frame */
		    CLR_BIT(CAN_TI2R,1);
		#endif
	
	    // Set The Length Of Data*/
	    if (DataLength <= 8)
		{
	        CAN_TDT2R &= ~(0b1111 << 0);
		    CAN_TDT2R |= DataLength;
		}
			   
	    // Write The Data That Will be Transmitted 
        CAN_TDL2R = DataLow;
		CAN_TDH2R = DataHigh;

	    // Make a Transmission Request
		SET_BIT(CAN_TI2R,0);

	    //wait until Transmission become Ok
	    while(GET_BIT(CAN_TSR,17)==0);
    }
}

// Function to cancel a transmission request
void CAN_abortTransmissionRequest(CanMailbox_type CanMailbox)
{
	// Validate input parameters
	ASSERT(CanMailbox >= 0 && CanMailbox < CAN_MAILBOX_ERR);

	// Select a mailbox to abort its transmission
	if (CanMailbox == CAN_MAILBOX0)
	{
		SET_BIT(CAN_TSR,7);
	}
	else if (CanMailbox == CAN_MAILBOX1)
	{
		SET_BIT(CAN_TSR,15);
	}
	else if(CanMailbox == CAN_MAILBOX2)
	{
		SET_BIT(CAN_TSR,23);
	}
}

// Function to send remote frame
void CAN_transmitRemoteFrame(u32 MessageId)
{
	// Validate input parameters

    // Check What is The Empty MailBox 
	// Check MailBox0 
	if (GET_BIT(CAN_TSR,26)==1)
	{
        // Set Message Identifier & Standrization & Type Of Data Frame */ 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI0R,2);
		    
			// Set id 
		    CAN_TI0R |= (MessageId << 21);
		    
			// Remote Frame 
		    SET_BIT(CAN_TI0R,1);
		#elif CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// set extended 
		    SET_BIT(CAN_TI0R,2);
		    
			// Set id 
		    CAN_TI0R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI0R |= (MessageId << 3);
		     
			// Set Remote Frame 
		    SET_BIT(CAN_TI0R,1);
		#endif
		
		// Make a Transmission Request                                                  */
		SET_BIT(CAN_TI0R,0);
		
		// wait until Transmission become Ok
		while(GET_BIT(CAN_TSR,1)==0);
	}
	        /* Check MailBox1 */
	else if (GET_BIT(CAN_TSR,27)==1)
	{
        // Set Message Identifier & Standrization & Type Of Data Frame */ 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI1R,2);
		    
			// Set id 
		    CAN_TI1R |= (MessageId << 21);
		    
			// Remote Frame 
		    SET_BIT(CAN_TI1R,1);
		#elif CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// set extended 
		    SET_BIT(CAN_TI1R,2);
		    
			// Set id 
		    CAN_TI1R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI1R |= (MessageId << 3);
		     
			// Set Remote Frame 
		    SET_BIT(CAN_TI1R,1);
		#endif
		
		// Make a Transmission Request                                                  */
		SET_BIT(CAN_TI1R,0);

		//wait until Transmission become Ok
		while(GET_BIT(CAN_TSR,9)==0);

	}
	/* Check MailBox2 */
	else if (GET_BIT(CAN_TSR,28)==1)
	{
        // Set Message Identifier & Standrization & Type Of Data Frame */ 
		#if CAN_STANDARDIZATION == CAN_STANDARD

		    // Set standard 
		    CLR_BIT(CAN_TI2R,2);
		    
			// Set id 
		    CAN_TI2R |= (MessageId << 21);
		    
			// Remote Frame 
		    SET_BIT(CAN_TI2R,1);
		#elif CAN_STANDARDIZATION == CAN_EXTENDED
		    
			// set extended 
		    SET_BIT(CAN_TI2R,2);
		    
			// Set id 
		    CAN_TI2R &= ~(0b11111111111111111111111111111 << 21);
		    CAN_TI2R |= (MessageId << 3);
		     
			// Set Remote Frame 
		    SET_BIT(CAN_TI2R,1);
		#endif
		
		// Make a Transmission Request                                                  */
		SET_BIT(CAN_TI2R,0);
		
	    //wait until Transmission become Ok
	    while(GET_BIT(CAN_TSR,17)==0);
    }
}

// Function to receive data through can
void CAN_recieveData(CanFifo_type CanFifo,ReceivedData_type* RecievedData)
{	
	// Validate input parameters
	ASSERT(CanFifo >= 0 && CanFifo < CAN_FIFO_ERR);

	// Set received state initialization
	RecievedData->FifoState = 0;

	// Check Which FIFO That You want Recive from 
	if (CanFifo == CAN_FIFO0)
	{
		// Check the FIFO0 If it Not Empty 
		if (((CAN_RF0R) & (0b11)) > 0)
		{
			// Set received state to be 1 (there is a received data)
			RecievedData->FifoState = 1;

			// Fill ID of The Recieved Data 
			// Check Id Type 
			if (GET_BIT(CAN_RI0R, 2) == 0)
			{
				RecievedData->DataId = (CAN_RI0R >> 21);
			}
			else if (GET_BIT(CAN_RI0R, 2) == 1)
			{
				RecievedData->DataId = (CAN_RI0R >> 3);
			}

			// Fill Frame Type of The Recived Data 
			RecievedData->FrameType = GET_BIT(CAN_RI0R, 1);

			// Fill Length of The Recived Data 
			RecievedData->DataLength = (CAN_RDT0R & 0x01);

			// Fill Index of The Recived Data Filter 
			RecievedData->FilterIndex = (CAN_RDT0R >> 8);

			// Fill  Recived Data LOW 
			RecievedData->DataLow = CAN_RDL0R;

			// Fill Fill  Recived Data HIGH 
			RecievedData->DataHigh = CAN_RDH0R;

			// Release FIFO0 output mailbox
			SET_BIT(CAN_RF0R, 5);
		}
	}
	else if(CanFifo == CAN_FIFO1)
	{
		// Check the FIFO1 If it Not Empty 
		if (((CAN_RF1R)&(0b11)) > 0)
	    {
		    // Set received state to be 1 (there is a received data)
			RecievedData->FifoState=1;

			// Fill ID of The Recived Data 
			// Check Id Type 
			if(GET_BIT(CAN_RI1R,2) == 0)
			{
				RecievedData->DataId = (CAN_RI1R>>21);
			}
			else if(GET_BIT(CAN_RI1R,2) == 1)
			{
				RecievedData->DataId = (CAN_RI1R>>3);
			}
				
			// Fill Frame Type of The Recived Data 
			RecievedData->FrameType = GET_BIT(CAN_RI1R,1);
					
			// Fill Length of The Recived Data 
			RecievedData->DataLength = (CAN_RDT1R & 0x01);
					
			// Fill Index of The Recived Data Flilter 
			RecievedData->FilterIndex = (CAN_RDT1R >> 8);
				
			// Fill  Recived Data LOW 
			RecievedData->DataLow = CAN_RDL1R;
					
			// Fill Fill  Recived Data HIGH 
			RecievedData->DataHigh = CAN_RDH1R;
				 
			// Release FIFO0 output mailbox
			SET_BIT(CAN_RF1R,5);
		}
	}
}

// Function to set can callback
void CAN_setCallback(void(*CallBack)(void))
{
	CAN1_Callback = CallBack;
}

/* ==================================================================== */
/* ================= Private Functions Implementation ================= */
/* ==================================================================== */

// Function to configure 
static void CAN_configFilters(void)
{
	// put Filters In Initialization Mode 
	SET_BIT(CAN_FMR,0);

	/****** Filters activation *********/ 
	// Filter0 ACTIVATION
 	#if CAN_FILTER_BANK0_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
        SET_BIT(CAN_FA1R,0);
 	#elif CAN_FILTER_BANK0_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,0);
 	#endif

 	// Filter1 ACTIVATION
 	#if CAN_FILTER_BANK1_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,1);
 	#elif CAN_FILTER_BANK1_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,1);
 	#endif

	// Filter2 ACTIVATION
 	#if CAN_FILTER_BANK2_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,2);
 	#elif CAN_FILTER_BANK2_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,2);
 	#endif

 	// Filter3 ACTIVATION
 	#if CAN_FILTER_BANK3_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,3);
 	#elif CAN_FILTER_BANK3_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,3);
 	#endif

	// Filter4 ACTIVATION
 	#if CAN_FILTER_BANK4_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,4);
 	#elif CAN_FILTER_BANK4_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,4);
 	#endif

 	// Filter5 ACTIVATION
 	#if CAN_FILTER_BANK5_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,5);
 	#elif CAN_FILTER_BANK5_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,5);
 	#endif

    // Filter6 ACTIVATION
 	#if CAN_FILTER_BANK6_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,6);
 	#elif CAN_FILTER_BANK6_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,6);
 	#endif

    // Filter7 ACTIVATION
 	#if CAN_FILTER_BANK7_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,7);
 	#elif CAN_FILTER_BANK7_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,7);
 	#endif

 	// Filter8 ACTIVATION
 	#if CAN_FILTER_BANK8_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,8);
 	#elif CAN_FILTER_BANK8_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,8);
 	#endif

 	// Filter9 ACTIVATION
 	#if CAN_FILTER_BANK9_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,9);
 	#elif CAN_FILTER_BANK9_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,9);
 	#endif

 	// Filter10 ACTIVATION
 	#if CAN_FILTER_BANK10_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,10);
 	#elif CAN_FILTER_BANK10_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,10);
 	#endif

 	// Filter11 ACTIVATION
 	#if CAN_FILTER_BANK11_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,11);
 	#elif CAN_FILTER_BANK11_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,11);
 	#endif

 	// Filter12 ACTIVATION
 	#if CAN_FILTER_BANK12_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,12);
 	#elif CAN_FILTER_BANK12_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,12);
 	#endif

    // Filter13 ACTIVATION
 	#if CAN_FILTER_BANK13_ACTIVATION == CAN_FILTER_BANK_ACTIVATED
 	    SET_BIT(CAN_FA1R,13);
 	#elif CAN_FILTER_BANK13_ACTIVATION == CAN_FILTER_BANK_NONACTIVATED
 	    CLR_BIT(CAN_FA1R,13);
 	#endif


	/******* Assign Filters To a One FIFO *******/
	// Filter0 Assignment 
	#if CAN_FILTER_BANK0_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,0);
	#elif CAN_FILTER_BANK0_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,0);
	#endif  
	
	// Filter1 Assignment 
	#if CAN_FILTER_BANK1_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,1);
	#elif CAN_FILTER_BANK1_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,1);
	#endif  
	
	// Filter2 Assignment
	#if CAN_FILTER_BANK2_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,2);
	#elif CAN_FILTER_BANK2_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,2);
	#endif  
	
	// Filter3 Assignment
	#if CAN_FILTER_BANK3_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,3);
	#elif CAN_FILTER_BANK3_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,3);
	#endif  
	
	// Filter4 Assignment
	#if CAN_FILTER_BANK4_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,4);
	#elif CAN_FILTER_BANK4_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,4);
	#endif  
	
	// Filter5 Assignment
	#if CAN_FILTER_BANK5_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,5);
	#elif CAN_FILTER_BANK5_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,5);
	#endif  
	
	// Filter6 Assignment
	#if CAN_FILTER_BANK6_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,6);
	#elif CAN_FILTER_BANK6_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,6);
	#endif  
	
	// Filter7 Assignment
	#if CAN_FILTER_BANK7_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,7);
	#elif CAN_FILTER_BANK7_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,7);
	#endif  
	
	// Filter8 Assignment
	#if CAN_FILTER_BANK8_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,8);
	#elif CAN_FILTER_BANK8_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,8);
	#endif  
	
	// Filter9 Assignment
	#if CAN_FILTER_BANK9_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,9);
	#elif CAN_FILTER_BANK9_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,9);
	#endif  
	
	    // Filter10 Assignment
	#if CAN_FILTER_BANK10_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,10);
	#elif CAN_FILTER_BANK10_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,10);
	#endif  
	
	// Filter11 Assignment
	#if CAN_FILTER_BANK11_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,11);
	#elif CAN_FILTER_BANK11_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,11);
	#endif  
	
	// Filter12 Assignment
	#if CAN_FILTER_BANK12_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,12);
	#elif CAN_FILTER_BANK12_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,12);
	#endif  
	
	// Filter13 Assignment
	#if CAN_FILTER_BANK13_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO0 
	    CLR_BIT(CAN_FFA1R,13);
	#elif CAN_FILTER_BANK13_ASSIGNMENT == CAN_FILTER_BANK_ASSIGNED_TO_FIFO1
	    SET_BIT(CAN_FFA1R,13);
	#endif  

/*** make The Configuration Type Of All Filter Banks then Fill Prameters Of All Filter Banks (ID & Mask) ***/
	// Configurations Of Filter BANK0  
	#if   CAN_FILTER_BANK0_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
		SET_BIT(CAN_FS1R,0);
	    CLR_BIT(CAN_FM1R,0);
	    // Fill ID & Mask 
	 	CAN_F0R1 = CAN_FILTER_BANK0_ID0;
	 	CAN_F0R2 = CAN_FILTER_BANK0_MASK0;
    #elif  CAN_FILTER_BANK0_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,0);
	    SET_BIT(CAN_FM1R,0);
	 	// Fill ID  
	 	CAN_F0R1 |= (CAN_FILTER_BANK0_ID0 << 21);
	 	CAN_F0R2 |= (CAN_FILTER_BANK0_ID1 << 21);
    #elif  CAN_FILTER_BANK0_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,0);
	    CLR_BIT(CAN_FM1R,0);
	 	// Fill ID & Mask */
	    CAN_F0R1 = CAN_FILTER_BANK0_ID0;
	    CAN_F0R1 |= (CAN_FILTER_BANK0_MASK0<<16);
	    CAN_F0R2 = CAN_FILTER_BANK0_ID1;
	    CAN_F0R2 |= (CAN_FILTER_BANK0_MASK1<<16);
    #elif  CAN_FILTER_BANK0_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST */
	    CLR_BIT(CAN_FS1R,0);
		SET_BIT(CAN_FM1R,0);
	    // Fill ID & Mask */
	 	CAN_F0R1 = CAN_FILTER_BANK0_ID0;
	 	CAN_F0R1 |= (CAN_FILTER_BANK0_ID1<<16);
	 	CAN_F0R2 = CAN_FILTER_BANK0_ID2;
	 	CAN_F0R2 |= (CAN_FILTER_BANK0_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK1  
	#if   CAN_FILTER_BANK1_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
        // Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,1);
	    CLR_BIT(CAN_FM1R,1);
	    // Fill ID & Mask 
	 	CAN_F1R1 = CAN_FILTER_BANK1_ID0;
		CAN_F1R2 = CAN_FILTER_BANK1_MASK0;
    #elif  CAN_FILTER_BANK1_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,1);
	    SET_BIT(CAN_FM1R,1);
	 	// Fill ID  
	 	CAN_F1R1 |= (CAN_FILTER_BANK1_ID0 << 21);
	 	CAN_F1R2 |= (CAN_FILTER_BANK1_ID1 << 21);
    #elif  CAN_FILTER_BANK1_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,1);
	    CLR_BIT(CAN_FM1R,1);
	    // Fill ID & Mask 
	 	CAN_F1R1 = CAN_FILTER_BANK1_ID0;
	 	CAN_F1R1 |= (CAN_FILTER_BANK1_MASK0<<16);
	 	CAN_F1R2 = CAN_FILTER_BANK1_ID1;
	 	CAN_F1R2 |= (CAN_FILTER_BANK1_MASK1<<16);
    #elif  CAN_FILTER_BANK1_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,1);
		SET_BIT(CAN_FM1R,1);
	 	// Fill ID & Mask 
	 	CAN_F1R1 = CAN_FILTER_BANK1_ID0;
	 	CAN_F1R1 |= (CAN_FILTER_BANK1_ID1<<16);
	 	CAN_F1R2 = CAN_FILTER_BANK1_ID2;
	 	CAN_F1R2 |= (CAN_FILTER_BANK1_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK2  
	#if CAN_FILTER_BANK2_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
        // Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,2);
	    CLR_BIT(CAN_FM1R,2);
	 	// Fill ID & Mask */
	 	CAN_F2R1 = CAN_FILTER_BANK2_ID0;
	 	CAN_F2R2 = CAN_FILTER_BANK2_MASK0;
    #elif  CAN_FILTER_BANK2_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,2);
	    SET_BIT(CAN_FM1R,2);
	 	// Fill ID  
	    CAN_F2R1 |= (CAN_FILTER_BANK2_ID0 << 21);
	    CAN_F2R2 |= (CAN_FILTER_BANK2_ID1 << 21);
    #elif  CAN_FILTER_BANK2_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,2);
	    CLR_BIT(CAN_FM1R,2);
	    // Fill ID & Mask 
	 	CAN_F2R1 = CAN_FILTER_BANK2_ID0;
	 	CAN_F2R1 |= (CAN_FILTER_BANK2_MASK0<<16);
	 	CAN_F2R2 = CAN_FILTER_BANK2_ID1;
	 	CAN_F2R2 |= (CAN_FILTER_BANK2_MASK1<<16);
    #elif  CAN_FILTER_BANK2_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,2);
		SET_BIT(CAN_FM1R,2);
	    // Fill ID & Mask 
	 	CAN_F2R1 = CAN_FILTER_BANK2_ID0;
	 	CAN_F2R1 |= (CAN_FILTER_BANK2_ID1<<16);
	 	CAN_F2R2 = CAN_FILTER_BANK2_ID2;
	 	CAN_F2R2 |= (CAN_FILTER_BANK2_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK3  
	#if   CAN_FILTER_BANK3_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,3);
	    CLR_BIT(CAN_FM1R,3);
	 	// Fill ID & Mask 
	 	CAN_F3R1 = CAN_FILTER_BANK3_ID0;
	 	CAN_F3R2 = CAN_FILTER_BANK3_MASK0;
    #elif  CAN_FILTER_BANK3_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,3);
	    SET_BIT(CAN_FM1R,3);
	 	// Fill ID 
	    CAN_F3R1 |= (CAN_FILTER_BANK3_ID0 << 21);
	    CAN_F3R2 |= (CAN_FILTER_BANK3_ID1 << 21);
    #elif  CAN_FILTER_BANK3_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
       	// Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,3);
	    CLR_BIT(CAN_FM1R,3);
	 	// Fill ID & Mask 
	 	CAN_F3R1 = CAN_FILTER_BANK3_ID0;
	 	CAN_F3R1 |= (CAN_FILTER_BANK3_MASK0<<16);
	 	CAN_F3R2 = CAN_FILTER_BANK3_ID1;
	 	CAN_F3R2 |= (CAN_FILTER_BANK3_MASK1<<16);
    #elif  CAN_FILTER_BANK3_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,3);
		SET_BIT(CAN_FM1R,3);
	 	// Fill ID & Mask 
	 	CAN_F3R1 = CAN_FILTER_BANK3_ID0;
	 	CAN_F3R1 |= (CAN_FILTER_BANK3_ID1<<16);
	 	CAN_F3R2 = CAN_FILTER_BANK3_ID2;
	 	CAN_F3R2 |= (CAN_FILTER_BANK3_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK4  
	#if CAN_FILTER_BANK4_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,4);
	    CLR_BIT(CAN_FM1R,4);
	 	// Fill ID & Mask 
	 	CAN_F4R1 = CAN_FILTER_BANK4_ID0;
	 	CAN_F4R2 = CAN_FILTER_BANK4_MASK0;
    #elif  CAN_FILTER_BANK4_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
    	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,4);
	    SET_BIT(CAN_FM1R,4);
		// Fill ID  
	    CAN_F4R1 |= (CAN_FILTER_BANK4_ID0 << 21);
	    CAN_F4R2 |= (CAN_FILTER_BANK4_ID1 << 21);
    #elif  CAN_FILTER_BANK4_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,4);
	    CLR_BIT(CAN_FM1R,4);
	 	// Fill ID & Mask 
	 	CAN_F4R1 = CAN_FILTER_BANK4_ID0;
	 	CAN_F4R1 |= (CAN_FILTER_BANK4_MASK0<<16);
	 	CAN_F4R2 = CAN_FILTER_BANK4_ID1;
	 	CAN_F4R2 |= (CAN_FILTER_BANK4_MASK1<<16);
    #elif  CAN_FILTER_BANK4_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,4);
		SET_BIT(CAN_FM1R,4);
	 	// Fill ID & Mask 
	 	CAN_F4R1 = CAN_FILTER_BANK4_ID0;
	 	CAN_F4R1 |= (CAN_FILTER_BANK4_ID1<<16);
	 	CAN_F4R2 = CAN_FILTER_BANK4_ID2;
	 	CAN_F4R2 |= (CAN_FILTER_BANK4_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK5  
	#if   CAN_FILTER_BANK5_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,5);
	    CLR_BIT(CAN_FM1R,5);
	 	// Fill ID & Mask 
	 	CAN_F5R1 = CAN_FILTER_BANK5_ID0;
	 	CAN_F5R2 = CAN_FILTER_BANK5_MASK0;
    #elif  CAN_FILTER_BANK5_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,5);
	    SET_BIT(CAN_FM1R,5);
	 	// Fill ID  
	    CAN_F5R1 |= (CAN_FILTER_BANK5_ID0 << 21);
	    CAN_F5R2 |= (CAN_FILTER_BANK5_ID1 << 21);
    #elif  CAN_FILTER_BANK5_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,5);
	    CLR_BIT(CAN_FM1R,5);
	 	// Fill ID & Mask 
	 	CAN_F5R1 = CAN_FILTER_BANK5_ID0;
	 	CAN_F5R1 |= (CAN_FILTER_BANK5_MASK0<<16);
	 	CAN_F5R2 = CAN_FILTER_BANK5_ID1;
	 	CAN_F5R2 |= (CAN_FILTER_BANK5_MASK1<<16);
    #elif  CAN_FILTER_BANK5_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,5);
		SET_BIT(CAN_FM1R,5);
	 	// Fill ID & Mask 
	 	CAN_F5R1 = CAN_FILTER_BANK5_ID0;
	 	CAN_F5R1 |= (CAN_FILTER_BANK5_ID1<<16);
	 	CAN_F5R2 = CAN_FILTER_BANK5_ID2;
	 	CAN_F5R2 |= (CAN_FILTER_BANK5_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK6  
	#if CAN_FILTER_BANK6_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,6);
	    CLR_BIT(CAN_FM1R,6);
	 	// Fill ID & Mask */
	 	CAN_F6R1 = CAN_FILTER_BANK6_ID0;
	 	CAN_F6R2 = CAN_FILTER_BANK6_MASK0;
    #elif  CAN_FILTER_BANK6_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,6);
	    SET_BIT(CAN_FM1R,6);
	 	// Fill ID  
	    CAN_F6R1 |= (CAN_FILTER_BANK6_ID0 << 21);
	    CAN_F6R2 |= (CAN_FILTER_BANK6_ID1 << 21);
    #elif  CAN_FILTER_BANK6_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
       	// Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,6);
	    CLR_BIT(CAN_FM1R,6);
	 	// Fill ID & Mask */
	 	CAN_F6R1 = CAN_FILTER_BANK6_ID0;
	 	CAN_F6R1 |= (CAN_FILTER_BANK6_MASK0<<16);
	 	CAN_F6R2 = CAN_FILTER_BANK6_ID1;
	 	CAN_F6R2 |= (CAN_FILTER_BANK6_MASK1<<16);
    #elif  CAN_FILTER_BANK6_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,6);
		SET_BIT(CAN_FM1R,6);
	 	// Fill ID & Mask 
	 	CAN_F6R1 = CAN_FILTER_BANK6_ID0;
	 	CAN_F6R1 |= (CAN_FILTER_BANK6_ID1<<16);
	 	CAN_F6R2 = CAN_FILTER_BANK6_ID2;
	 	CAN_F6R2 |= (CAN_FILTER_BANK6_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK7  
	#if CAN_FILTER_BANK7_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,7);
	    CLR_BIT(CAN_FM1R,7);
	 	// Fill ID & Mask */
	 	CAN_F7R1 = CAN_FILTER_BANK7_ID0;
	 	CAN_F7R2 = CAN_FILTER_BANK7_MASK0;
    #elif  CAN_FILTER_BANK7_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,7);
	    SET_BIT(CAN_FM1R,7);
	 	// Fill ID  
	     CAN_F7R1 |= (CAN_FILTER_BANK7_ID0 << 21);
	     CAN_F7R2 |= (CAN_FILTER_BANK7_ID1 << 21);
    #elif  CAN_FILTER_BANK7_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,7);
	    CLR_BIT(CAN_FM1R,7);
	 	// Fill ID & Mask 
	 	CAN_F7R1 = CAN_FILTER_BANK7_ID0;
	 	CAN_F7R1 |= (CAN_FILTER_BANK7_MASK0<<16);
	 	CAN_F7R2 = CAN_FILTER_BANK7_ID1;
	 	CAN_F7R2 |= (CAN_FILTER_BANK7_MASK1<<16);
    #elif  CAN_FILTER_BANK7_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,7);
		SET_BIT(CAN_FM1R,7);
	 	// Fill ID & Mask 
	 	CAN_F7R1 = CAN_FILTER_BANK7_ID0;
	 	CAN_F7R1 |= (CAN_FILTER_BANK7_ID1<<16);
	 	CAN_F7R2 = CAN_FILTER_BANK7_ID2;
	 	CAN_F7R2 |= (CAN_FILTER_BANK7_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK8  
	#if CAN_FILTER_BANK8_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,8);
	    CLR_BIT(CAN_FM1R,8);
	 	// Fill ID & Mask 
	 	CAN_F8R1 = CAN_FILTER_BANK8_ID0;
	 	CAN_F8R2 = CAN_FILTER_BANK8_MASK0;
    #elif  CAN_FILTER_BANK8_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,8);
	    SET_BIT(CAN_FM1R,8);
	 	// Fill ID  
	    CAN_F8R1 |= (CAN_FILTER_BANK8_ID0 << 21);
	    CAN_F8R2 |= (CAN_FILTER_BANK8_ID1 << 21);
    #elif  CAN_FILTER_BANK8_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,8);
	    CLR_BIT(CAN_FM1R,8);
	 	// Fill ID & Mask 
	 	CAN_F8R1 = CAN_FILTER_BANK8_ID0;
	 	CAN_F8R1 |= (CAN_FILTER_BANK8_MASK0<<16);
	 	CAN_F8R2 = CAN_FILTER_BANK8_ID1;
	 	CAN_F8R2 |= (CAN_FILTER_BANK8_MASK1<<16);
    #elif  CAN_FILTER_BANK8_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,8);
		SET_BIT(CAN_FM1R,8);
	 	// Fill ID & Mask 
	 	CAN_F8R1 = CAN_FILTER_BANK8_ID0;
	 	CAN_F8R1 |= (CAN_FILTER_BANK8_ID1<<16);
	 	CAN_F8R2 = CAN_FILTER_BANK8_ID2;
	 	CAN_F8R2 |= (CAN_FILTER_BANK8_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK9  
	#if   CAN_FILTER_BANK9_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,9);
	    CLR_BIT(CAN_FM1R,9);
	 	// Fill ID & Mask 
	 	CAN_F9R1 = CAN_FILTER_BANK9_ID0;
	 	CAN_F9R2 = CAN_FILTER_BANK9_MASK0;
    #elif  CAN_FILTER_BANK9_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,9);
	    SET_BIT(CAN_FM1R,9);
	 	// Fill ID  
	    CAN_F9R1 |= (CAN_FILTER_BANK9_ID0 << 21);
	    CAN_F9R2 |= (CAN_FILTER_BANK9_ID1 << 21);
    #elif CAN_FILTER_BANK9_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,9);
	    CLR_BIT(CAN_FM1R,9);
	 	// Fill ID & Mask 
		CAN_F9R1 = CAN_FILTER_BANK9_ID0;
		CAN_F9R1 |= (CAN_FILTER_BANK9_MASK0<<16);
		CAN_F9R2 = CAN_FILTER_BANK9_ID1;
		CAN_F9R2 |= (CAN_FILTER_BANK9_MASK1<<16);
    #elif  CAN_FILTER_BANK9_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,9);
		SET_BIT(CAN_FM1R,9);
	 	// Fill ID & Mask */
	 	CAN_F9R1 = CAN_FILTER_BANK9_ID0;
	 	CAN_F9R1 |= (CAN_FILTER_BANK9_ID1<<16);
	 	CAN_F9R2 = CAN_FILTER_BANK9_ID2;
	 	CAN_F9R2 |= (CAN_FILTER_BANK9_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK10  
	#if   CAN_FILTER_BANK10_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,10);
	    CLR_BIT(CAN_FM1R,10);
	 	// Fill ID & Mask 
	 	CAN_F10R1 = CAN_FILTER_BANK10_ID0;
	 	CAN_F10R2 = CAN_FILTER_BANK10_MASK0;
    #elif  CAN_FILTER_BANK10_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,10);
	    SET_BIT(CAN_FM1R,10);
	 	// Fill ID  
	     CAN_F10R1 |= (CAN_FILTER_BANK10_ID0 << 21);
	     CAN_F10R2 |= (CAN_FILTER_BANK10_ID1 << 21);
    #elif  CAN_FILTER_BANK10_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
       	// Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,10);
	    CLR_BIT(CAN_FM1R,10);
	 	// Fill ID & Mask 
	 	CAN_F10R1 = CAN_FILTER_BANK10_ID0;
	 	CAN_F10R1 |= (CAN_FILTER_BANK10_MASK0<<16);
	 	CAN_F10R2 = CAN_FILTER_BANK10_ID1;
	 	CAN_F10R2 |= (CAN_FILTER_BANK10_MASK1<<16);
    #elif  CAN_FILTER_BANK10_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,10);
		SET_BIT(CAN_FM1R,10);
	 	// Fill ID & Mask 
	 	CAN_F10R1 = CAN_FILTER_BANK10_ID0;
	 	CAN_F10R1 |= (CAN_FILTER_BANK10_ID1<<16);
	 	CAN_F10R2 = CAN_FILTER_BANK10_ID2;
	 	CAN_F10R2 |= (CAN_FILTER_BANK10_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK11  
	#if   CAN_FILTER_BANK11_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,11);
	    CLR_BIT(CAN_FM1R,11);
	 	// Fill ID & Mask 
	 	CAN_F11R1 = CAN_FILTER_BANK11_ID0;
	 	CAN_F11R2 = CAN_FILTER_BANK11_MASK0;
    #elif  CAN_FILTER_BANK11_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,11);
	    SET_BIT(CAN_FM1R,11);
	 	// Fill ID  
	    CAN_F11R1 |= (CAN_FILTER_BANK11_ID0 << 21);
	    CAN_F11R2 |= (CAN_FILTER_BANK11_ID1 << 21);
    #elif  CAN_FILTER_BANK11_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
        // Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,11);
	    CLR_BIT(CAN_FM1R,11);
	 	// Fill ID & Mask
	 	CAN_F11R1 = CAN_FILTER_BANK11_ID0;
	 	CAN_F11R1 |= (CAN_FILTER_BANK11_MASK0<<16);
	 	CAN_F11R2 = CAN_FILTER_BANK11_ID1;
	 	CAN_F11R2 |= (CAN_FILTER_BANK11_MASK1<<16);
    #elif  CAN_FILTER_BANK11_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,11);
		SET_BIT(CAN_FM1R,11);
	 	// Fill ID & Mask 
	 	CAN_F11R1 = CAN_FILTER_BANK11_ID0;
	 	CAN_F11R1 |= (CAN_FILTER_BANK11_ID1<<16);
	 	CAN_F11R2 = CAN_FILTER_BANK11_ID2;
	 	CAN_F11R2 |= (CAN_FILTER_BANK11_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK12  
	#if   CAN_FILTER_BANK12_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
    	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,12);
	    CLR_BIT(CAN_FM1R,12);
	 	// Fill ID & Mask 
	 	CAN_F12R1 = CAN_FILTER_BANK12_ID0;
	 	CAN_F12R2 = CAN_FILTER_BANK12_MASK0;
    #elif  CAN_FILTER_BANK12_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,12);
	    SET_BIT(CAN_FM1R,12);
	 	// Fill ID  
	    CAN_F12R1 |= (CAN_FILTER_BANK12_ID0 << 21);
		CAN_F12R2 |= (CAN_FILTER_BANK12_ID1 << 21);
    #elif  CAN_FILTER_BANK12_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
       	// Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,12);
	    CLR_BIT(CAN_FM1R,12);
	 	// Fill ID & Mask 
	 	CAN_F12R1 = CAN_FILTER_BANK12_ID0;
	 	CAN_F12R1 |= (CAN_FILTER_BANK12_MASK0<<16);
	 	CAN_F12R2 = CAN_FILTER_BANK12_ID1;
	 	CAN_F12R2 |= (CAN_FILTER_BANK12_MASK1<<16);
    #elif  CAN_FILTER_BANK12_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,12);
		SET_BIT(CAN_FM1R,12);
	 	// Fill ID & Mask 
	 	CAN_F12R1 = CAN_FILTER_BANK12_ID0;
	 	CAN_F12R1 |= (CAN_FILTER_BANK12_ID1<<16);
	 	CAN_F12R2 = CAN_FILTER_BANK12_ID2;
	 	CAN_F12R2 |= (CAN_FILTER_BANK12_ID3<<16);
    #endif
	
	// Configurations Of Filter BANK13  
	#if   CAN_FILTER_BANK13_MODE == CAN_ONE_32BIT_FILTER_ID_MASK
     	// Set The Mode to be CAN_ONE_32BIT_FILTER_ID_MASK 
	    SET_BIT(CAN_FS1R,13);
	    CLR_BIT(CAN_FM1R,13);
	 	// Fill ID & Mask 
	 	CAN_F13R1 = CAN_FILTER_BANK13_ID0;
	 	CAN_F13R2 = CAN_FILTER_BANK13_MASK0;
    #elif  CAN_FILTER_BANK13_MODE == CAN_TWO_32BIT_FILTER_ID_LIST
      	// Set The Mode to be CAN_TWO_32BIT_FILTER_ID_LIST 
	    SET_BIT(CAN_FS1R,13);
	    SET_BIT(CAN_FM1R,13);
	 	// Fill ID  
	    CAN_F13R1 |= (CAN_FILTER_BANK13_ID0 << 21);
	    CAN_F13R2 |= (CAN_FILTER_BANK13_ID1 << 21);
    #elif  CAN_FILTER_BANK13_MODE == CAN_TWO_16BIT_FILTERS_ID_MASK
       	// Set The Mode to be CAN_TWO_16BIT_FILTERS_ID_MASK 
	    CLR_BIT(CAN_FS1R,13);
	    CLR_BIT(CAN_FM1R,13);
	 	// Fill ID & Mask 
	 	CAN_F13R1 = CAN_FILTER_BANK13_ID0;
	 	CAN_F13R1 |= (CAN_FILTER_BANK13_MASK0<<16);
	 	CAN_F13R2 = CAN_FILTER_BANK13_ID1;
	 	CAN_F13R2 |= (CAN_FILTER_BANK13_MASK1<<16);
    #elif  CAN_FILTER_BANK13_MODE == CAN_FOUR_16BIT_FILTER_ID_LIST
        // Set The Mode to be CAN_FOUR_16BIT_FILTER_ID_LIST 
	    CLR_BIT(CAN_FS1R,13);
		SET_BIT(CAN_FM1R,13);
	 	// Fill ID & Mask 
	 	CAN_F13R1 = CAN_FILTER_BANK13_ID0;
	 	CAN_F13R1 |= (CAN_FILTER_BANK13_ID1<<16);
	 	CAN_F13R2 = CAN_FILTER_BANK13_ID2;
	 	CAN_F13R2 |= (CAN_FILTER_BANK13_ID3<<16);
    #endif
	
	// Put filters in active mode
	CLR_BIT(CAN_FMR,0); 
}

void CAN1_RX1_IRQHandler(void)
{
	/* Set Call Back */
	CAN1_Callback();
	
}
void CAN1_RX0_IRQHandler(void)
{
	/* Set Call Back */
	CAN1_Callback();

}
void CAN1_TX_IRQHandler(void)
{
	/* Set Call Back */
	CAN1_Callback();

}

