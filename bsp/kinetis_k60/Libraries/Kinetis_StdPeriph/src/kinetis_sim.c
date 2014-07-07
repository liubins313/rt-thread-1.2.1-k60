#include "kinetis_sim.h"




/**
 * @fn:         SIM_SCGC_GPIO_Cmd
 * @bref:       Enable or Disable the clock gate of GPIOx
 * @params:     SCGC_GPIOx     
 *              State:          ENABLE/DISABLE
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-1 
 * 
 */
void SIM_SCGC_GPIO_Cmd(uint32_t SCGC_GPIOx, FunctionalState State)
{

    assert_expression(IS_SCGC_GPIO(SCGC_GPIOx));

    if(State != DISABLE)
    {
        if(SCGC_GPIOx & SCGC_GPIOA)
        {
            SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOB)
        {
            SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOC)
        {
            SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOD)
        {
            SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOE)
        {
            SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
        }
    }
    else
    {
        if(SCGC_GPIOx & SCGC_GPIOA)
        {
            SIM->SCGC5 &= ~SIM_SCGC5_PORTA_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOB)
        {
            SIM->SCGC5 &= ~SIM_SCGC5_PORTB_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOC)
        {
            SIM->SCGC5 &= ~SIM_SCGC5_PORTC_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOD)
        {
            SIM->SCGC5 &= ~SIM_SCGC5_PORTD_MASK;
        }
        if(SCGC_GPIOx & SCGC_GPIOE)
        {
            SIM->SCGC5 &= ~SIM_SCGC5_PORTE_MASK;
        }
    }
}


/**
 * @fn:         SIM_SCGC_UART_Cmd
 * @bref:       Enable or Disable the clock gate of GPIOx
 * @params:     SCGC_UARTx     
 *              State:          ENABLE/DISABLE
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-1 
 * 
 */
void SIM_SCGC_UART_Cmd(uint32_t SCGC_UARTx, FunctionalState State)
{
    assert_expression(IS_SCGC_UART(SCGC_UARTx));
    if(State != DISABLE)
    {
        if(SCGC_UARTx & SCGC_UART0)
        {
            SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
        }
        if(SCGC_UARTx & SCGC_UART1)
        {
            SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
        }
        if(SCGC_UARTx & SCGC_UART2)
        {
            SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
        }
        if(SCGC_UARTx & SCGC_UART3)
        {
            SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
        }
        if(SCGC_UARTx & SCGC_UART4)
        {
            SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
        }
    }
    else
    {
        if(SCGC_UARTx & SCGC_UART0)
        {
            SIM->SCGC4 &= ~SIM_SCGC4_UART0_MASK;
        }
        if(SCGC_UARTx & SCGC_UART1)
        {
            SIM->SCGC4 &= ~SIM_SCGC4_UART1_MASK;
        }
        if(SCGC_UARTx & SCGC_UART2)
        {
            SIM->SCGC4 &= ~SIM_SCGC4_UART2_MASK;
        }
        if(SCGC_UARTx & SCGC_UART3)
        {
            SIM->SCGC4 &= ~SIM_SCGC4_UART3_MASK;
        }
        if(SCGC_UARTx & SCGC_UART4)
        {
            SIM->SCGC1 &= ~SIM_SCGC1_UART4_MASK;
        }
    }
}



/**
 * @fn:         SIM_SCGC_RTC_Cmd
 * @bref:       Enable or Disable the clock gate of RTC
 * @params:     SCGC_UARTx     
 *              State:          ENABLE/DISABLE
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-1 
 * 
 */
void SIM_SCGC_RTC_Cmd (uint32_t SCGC_RTCx, FunctionalState State)
{
    assert_expression(IS_SCGC_RTC(SCGC_RTCx));
    
    if(State != DISABLE)
    {
        SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    }
    else
    {
        SIM->SCGC6 &= ~SIM_SCGC6_RTC_MASK;
    }
}




