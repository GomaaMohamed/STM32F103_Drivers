/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_


/* 
  Copy_u8Line values form LINE0 to LINE15 
  Copy_u8Mode Options :
        RISING     
        FALLING    
        On_Change  
    
*/
void EXTI_voidInt();
void EXTI_voidEnableExti(u8 Copy_u8Line, u8 Copy_u8Mode);
void EXTI_voidDisableExti(u8 Copy_u8Line);
void EXTI_voidSwTrigger(u8 Copy_u8Line);
void EXTI_voidSetCallback(void (*ptr) (void),u8 Copy_u8Line);


/* definition of all exti lines from 0 to 15 */
#define       EXTI_LINE0   0
#define       EXTI_LINE1   1
#define       EXTI_LINE2   2
#define       EXTI_LINE3   3
#define       EXTI_LINE4   4
#define       EXTI_LINE5   5
#define       EXTI_LINE6   6
#define       EXTI_LINE7   7
#define       EXTI_LINE8   8
#define       EXTI_LINE9   9
#define       EXTI_LINE10  10
#define       EXTI_LINE11  11
#define       EXTI_LINE12  12
#define       EXTI_LINE13  13
#define       EXTI_LINE14  14
#define       EXTI_LINE15  15

/* Exti Mode */
#define       EXTI_RISING     0
#define       EXTI_FALLING    1
#define       EXTI_ON_CHANGE  2
       

#endif