/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#ifndef _AFIO_INTERFACE_H_
#define _AFIO_INTERFACE_H_



void  AFIO_voidInit(void);
void  AFIO_voidSetExtiConfig(u8 Copy_u8Line, u8 Copy_u8PortMap);
void  AFIO_voidSelectOutputEventPin(u8 Copy_u8Port,u8 Copy_u8Pin);
void  AFIO_voidEnableOutputEvent(void);
void  AFIO_voidDisableOutputEvent(void);
void  AFIO_voidRemapPeriphralPins(u8 Copy_u8RemapingOptions);





/* definition of all Copy_u8Line Options from 0 to 15 */
#define      AFIO_EXTI_LINE0       0
#define      AFIO_EXTI_LINE1       1
#define      AFIO_EXTI_LINE2       2
#define      AFIO_EXTI_LINE3       3
#define      AFIO_EXTI_LINE4       4
#define      AFIO_EXTI_LINE5       5
#define      AFIO_EXTI_LINE6       6
#define      AFIO_EXTI_LINE7       7
#define      AFIO_EXTI_LINE8       8
#define      AFIO_EXTI_LINE9       9
#define      AFIO_EXTI_LINE10      10
#define      AFIO_EXTI_LINE11      11
#define      AFIO_EXTI_LINE12      12
#define      AFIO_EXTI_LINE13      13
#define      AFIO_EXTI_LINE14      14
#define      AFIO_EXTI_LINE15      15
/* Copy_u8PortMap Options :*/
#define      AFIO_EXTI_PORTA       0b0000
#define      AFIO_EXTI_PORTB       0b0001
#define      AFIO_EXTI_PORTC       0b0010

/* Copy_u8Port Options :*/
#define      AFIO_OUTUT_EVENT_PORTA     0
#define      AFIO_OUTUT_EVENT_PORTB     1
#define      AFIO_OUTUT_EVENT_PORTC     2
/* Copy_u8Pin Options :*/
#define      AFIO_OUTUT_EVENT_PIN0      0
#define      AFIO_OUTUT_EVENT_PIN1      1
#define      AFIO_OUTUT_EVENT_PIN2      2
#define      AFIO_OUTUT_EVENT_PIN3      3
#define      AFIO_OUTUT_EVENT_PIN4      4
#define      AFIO_OUTUT_EVENT_PIN5      5
#define      AFIO_OUTUT_EVENT_PIN6      6
#define      AFIO_OUTUT_EVENT_PIN7      7
#define      AFIO_OUTUT_EVENT_PIN8      8
#define      AFIO_OUTUT_EVENT_PIN9      9
#define      AFIO_OUTUT_EVENT_PIN10     10
#define      AFIO_OUTUT_EVENT_PIN11     11
#define      AFIO_OUTUT_EVENT_PIN12     12
#define      AFIO_OUTUT_EVENT_PIN13     13
#define      AFIO_OUTUT_EVENT_PIN14     14
#define      AFIO_OUTUT_EVENT_PIN15     15
/* Copy_u8Peripheral,Copy_u8RemapingOptions Options :*/
#define      AFIO_REMAP_SPI1                     0    /* Remap (NSS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)*/
#define      AFIO_REMAP_I2C1                     1    /* Remap (SCL/PB8, SDA/PB9)*/
#define      AFIO_REMAP_USART1                   2    /* Remap (TX/PB6, RX/PB7)*/
#define      AFIO_REMAP_USART2                   3    /* Remap (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)*/
#define      AFIO_REMAP_USART3_MAP1              4    /* Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14) */
#define      AFIO_REMAP_USART3_MAP2              5    /*  Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12) */
#define      AFIO_REMAP_TIM1_MAP1                6    /* Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6,CH1N/PA7, CH2N/PB0, CH3N/PB1) */
#define      AFIO_REMAP_TIM1_MAP2                7    /* Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15,CH1N/PE8, CH2N/PE10, CH3N/PE12) */
#define      AFIO_REMAP_TIM2_MAP1                8    /*  Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)*/
#define      AFIO_REMAP_TIM2_MAP2                9    /* Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)*/ 
#define      AFIO_REMAP_TIM2_MAP3                10   /* Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) */
#define      AFIO_REMAP_TIM3_MAP1                11   /*  Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1) */ 
#define      AFIO_REMAP_TIM3_MAP2                12   /*  Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) */
#define      AFIO_REMAP_TIM4_MAP1                13   /*  Full remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)*/ 
#define      AFIO_REMAP_CAN_MAP1                 14   /*  CAN_RX mapped to PA11, CAN_TX mapped to PA12*/
#define      AFIO_REMAP_CAN_MAP2                 15   /*  CAN_RX mapped to PB8, CAN_TX mapped to PB9 (not available on 36-pin package)*/              
#define      AFIO_REMAP_CAN_MAP3                 16   /* : CAN_RX mapped to PD0, CAN_TX mapped to PD1*/ 
#define      AFIO_REMAP_PD0                      17   /* : PD0 remapped on OSC_IN, PD1 remapped on OSC_OUT */ 
#define      AFIO_REMAP_TIM5CH4_MAP1             18   /*  TIM5_CH4 is connected to PA3 */
#define      AFIO_REMAP_TIM5CH4_MAP2             19   /*  LSI internal clock is connected to TIM5_CH4 input for calibration purpose */
#define      AFIO_REMAP_ADC1_INJEC_MAP1          20   /*  the ADC1 External trigger injected conversion is connected to EXTI15*/
#define      AFIO_REMAP_ADC1_INJEC_MAP2          21   /*  ADC1 External Event injected conversion is connected to TIM8 Channel4. */
#define      AFIO_REMAP_ADC1_REGULAR_MAP1        22   /*  the ADC1 External trigger regular conversion is connected to EXTI11*/
#define      AFIO_REMAP_ADC1_REGULAR_MAP2        23   /* the ADC1 External Event regular conversion is connected to TIM8 TRGO. */
#define      AFIO_REMAP_ADC2_INJEC_MAP1          24    /*  the ADC2 external trigger injected conversion is connected to EXTI15*/
#define      AFIO_REMAP_ADC2_INJEC_MAP2          25   /* the ADC2 external event injected conversion is connected to TIM8_Channel4. */
#define      AFIO_REMAP_ADC2_REGULAR_MAP1        26   /*  ADC2 external trigger regular conversion is connected to EXTI11*/
#define      AFIO_REMAP_ADC2_REGULAR_MAP2        27   /* the ADC2 external event regular conversion is connected to TIM8_TRGO */
#define      AFIO_REMAP_JTAG_MAP1                28   /*  Full SWJ (JTAG-DP + SW-DP): Reset State*/
#define      AFIO_REMAP_JTAG_MAP2                29   /*  Full SWJ (JTAG-DP + SW-DP) but without NJTRST*/
#define      AFIO_REMAP_JTAG_MAP3                30   /*  JTAG-DP Disabled and SW-DP Enabled*/
#define      AFIO_REMAP_JTAG_MAP4                31   /*  JTAG-DP Disabled and SW-DP Disabled*/



#define      AFIO_REMAP_TIM9                     32    /* TIM9_CH1 on PE5 and TIM9_CH2 on PE6 */
#define      AFIO_REMAP_TIM10                    33    /* It controls the mapping of the TIM10_CH1 alternate function onto the GPIO ports.Remap (PF6) */
#define      AFIO_REMAP_TIM11                    34    /* It controls the mapping of the TIM11_CH1 alternate function onto the GPIO ports.Remap (PF7) */
#define      AFIO_REMAP_TIM13                    35    /* It controls the mapping of the TIM13_CH1 alternate function onto the GPIO ports.Remap (PF8)*/
#define      AFIO_REMAP_TIM114                   36    /* It controls the mapping of the TIM14_CH1 alternate function onto the GPIO ports.Remap (PF9)*/
#define      AFIO_REMAP_FSMC_NADV                37    /* The NADV signal is not connected. The I/O pin can be used by another peripheral. */




 






















#endif