#ifndef __KINETIS_RTC_H__
#define __KINETIS_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "kinetis_k60.h"
    

#ifndef RTC
#define RTC     (RTC_BASE_PTR)
#endif


    
/*
    RTC Interrupt Source
    
 */
 #define RTC_INT_ALR = 0x04 /* RTC Alarm Interrupt */
 #define RTC_INT_OW  = 0x02 /* RTC Overflow Interrupt */
 #define RTC_INT_IV  = 0x01 /* Time invalid flag Interrupt */
 #define RTC_ALL_INT   0x07
 #define IS_RTC_INT(IT)    ((IT) && ((IT)<=RTC_ALL_INT))
    


/*
    Load Capacitance  
*/
#define CAP_2P                  RTC_CR_SC2P_MASK
#define CAP_4P                  RTC_CR_SC4P_MASK
#define CAP_8P                  RTC_CR_SC8P_MASK
#define CAP_16P                 RTC_CR_SC16P_MASK
#define IS_RTC_LOAD_CAP(CAP)    (   ((CAP) == CAP_2P)       \
                                  ||((CAP) == CAP_4P)       \
                                  ||((CAP) == CAP_8P)       \
                                  ||((CAP) == CAP_16P)      )
    
    
    
void RTC_OSC_Config(uint32_t RTC_Cap, FunctionalState ClockOutState, FunctionalState OSC_Enable_State);    
void RTC_IT_Config(uint16_t RTC_IT, FunctionalState stateVal);
void RTC_Flag_Clear(uint16_t RTC_IT);

void RTC_ConfigMode_Enter(void);
void RTC_ConfigMode_Exit(void);

uint32_t RTC_Counter_Get(void);
void RTC_Counter_Set(uint32_t counterVal);

void RTC_Prescaler_Set(uint32_t prescalerVal);
void RTC_Alarm_Set(uint32_t alarmVal);

void RTC_SoftReset(void);


#ifdef __cplusplus
}
#endif








#endif

