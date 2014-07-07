#include "kinetis_rtc.h"


void RTC_OSC_Config(uint32_t RTC_Cap, FunctionalState ClockOutState, FunctionalState OSC_Enable_State)
{
    assert_expression(IS_RTC_LOAD_CAP(RTC_Cap));
    assert_expression(IS_FUNCTIONAL_STATE(ClockOutState));
    assert_expression(IS_FUNCTIONAL_STATE(ClockOutState));
    
//    if(IS_RTC_LOAD_CAP(RTC_Cap) && IS_FUNCTIONAL_STATE(ClockOutState)&& IS_FUNCTIONAL_STATE(ClockOutState))
    {
        RTC->CR &= (uint32_t)~(RTC_CR_SC2P_MASK|RTC_CR_SC4P_MASK|RTC_CR_SC8P_MASK|RTC_CR_SC16P_MASK);
        RTC->CR |= RTC_Cap;
        
        if(ClockOutState != DISABLE)
        {
            RTC->CR &= (uint32_t)~RTC_CR_CLKO_MASK;
        }
        else
        {
            RTC->CR |= RTC_CR_CLKO_MASK;
        }
        
        if(OSC_Enable_State != DISABLE)
        {
            RTC->CR |= RTC_CR_OSCE_MASK;
        }
        else
        {
            RTC->CR &= (uint32_t)~RTC_CR_OSCE_MASK;
        }
    }
}


void RTC_IT_Config(uint16_t RTC_IT, FunctionalState stateVal)
{
    
    assert_expression(IS_RTC_INT(RTC_IT));
    assert_expression(IS_FUNCTIONAL_STATE(stateVal));
    
//    if(IS_RTC_INT(RTC_IT) && IS_FUNCTIONAL_STATE(stateVal))
    if(stateVal != DISABLE)
    {
        RTC->IER |= RTC_IT;
    }
    else
    {
        RTC->IER &= (uint32_t)RTC_IT;
    }
}
void RTC_Flag_Clear(uint16_t RTC_IT)
{

}

void RTC_ConfigMode_Enter(void)
{
    RTC->SR&=~RTC_SR_TCE_MASK;
}
void RTC_ConfigMode_Exit(void)
{
    RTC->SR |= RTC_SR_TCE_MASK;
}

uint32_t RTC_Counter_Get(void)
{
    return RTC->TSR;
}
void RTC_Counter_Set(uint32_t counterVal)
{
    RTC_ConfigMode_Enter();
    RTC->TSR = counterVal;
    RTC_ConfigMode_Exit();
    
}

void RTC_Prescaler_Set(uint32_t prescalerVal)
{
    RTC_ConfigMode_Enter();
    RTC->TPR = prescalerVal;
    RTC_ConfigMode_Exit();
}
void RTC_Alarm_Set(uint32_t alarmVal)
{
    RTC->TAR = alarmVal;
}

void RTC_SoftReset(void)
{
    RTC->CR |= RTC_CR_SWR_MASK;
}

