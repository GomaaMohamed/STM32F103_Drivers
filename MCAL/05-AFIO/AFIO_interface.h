/*****************************************************************************
* @file:    AFIO_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Tue, 3 Oct 2023 16:21:12 +0200
* @brief:   Alternative Function Input Output(AFIO) Driver for STM32F103
******************************************************************************/
#ifndef _AFIO_INTERFACE_H
#define _AFIO_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/******************** Exti Lines data types *************************/

typedef enum
{
    AFIO_EXTI_LINE0=0,
    AFIO_EXTI_LINE1,  
    AFIO_EXTI_LINE2,  
    AFIO_EXTI_LINE3,  
    AFIO_EXTI_LINE4,  
    AFIO_EXTI_LINE5,  
    AFIO_EXTI_LINE6,  
    AFIO_EXTI_LINE7,  
    AFIO_EXTI_LINE8,  
    AFIO_EXTI_LINE9,  
    AFIO_EXTI_LINE10,
    AFIO_EXTI_LINE11,
    AFIO_EXTI_LINE12,
    AFIO_EXTI_LINE13,
    AFIO_EXTI_LINE14,
    AFIO_EXTI_LINE15,
    EXTI_LINE_ERR
} AfioExtiLine_type;

typedef enum
{
    AFIO_EXTI_PORTA=0,
    AFIO_EXTI_PORTB,
    AFIO_EXTI_PORTC,
    EXTI_PORT_ERR
} AfioExtiPort_type;

/******************** Output Events data types *************************/

typedef enum
{
    AFIO_OUTUT_EVENT_PIN0=0,
    AFIO_OUTUT_EVENT_PIN1,       
    AFIO_OUTUT_EVENT_PIN2,      
    AFIO_OUTUT_EVENT_PIN3,      
    AFIO_OUTUT_EVENT_PIN4,      
    AFIO_OUTUT_EVENT_PIN5,      
    AFIO_OUTUT_EVENT_PIN6,      
    AFIO_OUTUT_EVENT_PIN7,      
    AFIO_OUTUT_EVENT_PIN8,      
    AFIO_OUTUT_EVENT_PIN9,      
    AFIO_OUTUT_EVENT_PIN10,     
    AFIO_OUTUT_EVENT_PIN11,     
    AFIO_OUTUT_EVENT_PIN12,     
    AFIO_OUTUT_EVENT_PIN13,     
    AFIO_OUTUT_EVENT_PIN14,     
    AFIO_OUTUT_EVENT_PIN15,     
    OUTPUT_PIN_ERR
} AfioOutputEventPin_type;

typedef enum
{
    AFIO_OUTPUT_EVENT_PORTA=0,
    AFIO_OUTPUT_EVENT_PORTB,
    AFIO_OUTPUT_EVENT_PORTC,
    OUTPUT_PORT_ERR
} AfioOutputEventPort_type;

/****************** Periphiral Maps data type *******************/
typedef enum
{
    AFIO_REMAP_SPI1=0, // Remap (SS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)
    AFIO_REMAP_I2C1,   // Remap (SCL/PB8, SDA/PB9)
    AFIO_REMAP_USART1, // Remap (TX/PB6, RX/PB7)
    AFIO_REMAP_USART2, // Remap (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
    AFIO_REMAP_USART3_MAP1, // Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14) 
    AFIO_REMAP_USART3_MAP2, // Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12) 
    AFIO_REMAP_TIM1_MAP1,   // Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6,CH1N/PA7, CH2N/PB0, CH3N/PB1) 
    AFIO_REMAP_TIM1_MAP2,   // Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15,CH1N/PE8, CH2N/PE10, CH3N/PE12) 
    AFIO_REMAP_TIM2_MAP1,   // Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
    AFIO_REMAP_TIM2_MAP2,   // Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11) 
    AFIO_REMAP_TIM2_MAP3,   // Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) 
    AFIO_REMAP_TIM3_MAP1,   // Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1) 
    AFIO_REMAP_TIM3_MAP2,   // Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) 
    AFIO_REMAP_TIM4_MAP1,   // Full remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)
    AFIO_REMAP_CAN_MAP1,               // CAN_RX mapped to PA11, CAN_TX mapped to PA12
    AFIO_REMAP_CAN_MAP2,               // CAN_RX mapped to PB8, CAN_TX mapped to PB9 (not available on 36-pin package)             
    AFIO_REMAP_CAN_MAP3,               // CAN_RX mapped to PD0, CAN_TX mapped to PD1
    AFIO_REMAP_PD0,                    // PD0 remapped on OSC_IN, PD1 remapped on OSC_OUT  
    AFIO_REMAP_TIM5CH4_MAP1,           // TIM5_CH4 is connected to PA3 
    AFIO_REMAP_TIM5CH4_MAP2,           // LSI internal clock is connected to TIM5_CH4 input for calibration purpose 
    AFIO_REMAP_ADC1_INJEC_MAP1,        // the ADC1 External trigger injected conversion is connected to EXTI15
    AFIO_REMAP_ADC1_INJEC_MAP2,        // ADC1 External Event injected conversion is connected to TIM8 Channel4 
    AFIO_REMAP_ADC1_REGULAR_MAP1,      // the ADC1 External trigger regular conversion is connected to EXTI11
    AFIO_REMAP_ADC1_REGULAR_MAP2,      // the ADC1 External Event regular conversion is connected to TIM8 TRGO
    AFIO_REMAP_ADC2_INJEC_MAP1,        // the ADC2 external trigger injected conversion is connected to EXTI15
    AFIO_REMAP_ADC2_INJEC_MAP2,        // the ADC2 external event injected conversion is connected to TIM8_Channel4
    AFIO_REMAP_ADC2_REGULAR_MAP1,      // ADC2 external trigger regular conversion is connected to EXTI11
    AFIO_REMAP_ADC2_REGULAR_MAP2,      // the ADC2 external event regular conversion is connected to TIM8_TRGO 
    AFIO_REMAP_JTAG_MAP1,              // Full SWJ (JTAG-DP + SW-DP): Reset State
    AFIO_REMAP_JTAG_MAP2,              // Full SWJ (JTAG-DP + SW-DP) but without NJTRST
    AFIO_REMAP_JTAG_MAP3,              // JTAG-DP Disabled and SW-DP Enabled
    AFIO_REMAP_JTAG_MAP4,              // JTAG-DP Disabled and SW-DP Disabled
    AFIO_REMAP_TIM9,                   // TIM9_CH1 on PE5 and TIM9_CH2 on PE6
    AFIO_REMAP_TIM10,                  // It controls the mapping of the TIM10_CH1 alternate function onto the GPIO ports.Remap (PF6) 
    AFIO_REMAP_TIM11,                  // It controls the mapping of the TIM11_CH1 alternate function onto the GPIO ports.Remap (PF7) 
    AFIO_REMAP_TIM13,                  // It controls the mapping of the TIM13_CH1 alternate function onto the GPIO ports.Remap (PF8)
    AFIO_REMAP_TIM114,                 // It controls the mapping of the TIM14_CH1 alternate function onto the GPIO ports.Remap (PF9)
    AFIO_REMAP_FSMC_NADV,              // The NADV signal is not connected. The I/O pin can be used by another peripheral
    PERIPHERAL_MAP_ERR
} AfioPeriphiralMap_type;



/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Remap external interrupts lines
 * @parameter1----------------> (ExtiLine) external interrupt line
 * @parameter2----------------> (PortMap) port to map any external interrupt line to
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant        
 */
void AFIO_remapExtiLine(AfioExtiLine_type ExtiLine, AfioExtiPort_type PortMap);

/**
 * @brief---------------------> Remap output event pins
 * @parameter1----------------> (OutputEventPort) output event port
 * @parameter2----------------> (OutputEventPin) output event pun
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant 
 */
void AFIO_remapOutputEventPin(AfioOutputEventPort_type OutputEventPort,AfioOutputEventPin_type OutputEventPin);

/**
 * @brief---------------------> enable output event 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void AFIO_enableOutputEvent(void);

/**
 * @brief---------------------> disable output event 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void AFIO_disableOutputEvent(void);

/**
 * @brief---------------------> Remap periphiral pins
 * @parameter1----------------> (PeriphiralMap) periphiral map
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant   
 */
void AFIO_remapPeriphiralPins(AfioPeriphiralMap_type PeriphiralMap);





#endif
