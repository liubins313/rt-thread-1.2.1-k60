#include "kinetis_gpio.h"



/**
 * @fn:         GPIO_Init
 * @bref:       Init a GPIO Pin according to GPIO_InitParams
 * @params:     GPIOx     
 *              GPIO_InitParams:      MUX/Mode/Pin
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType_t GPIO_InitParams)
{
    PORT_Type* Portx;
    uint32_t optionBits = 0;
    uint32_t tmpRegVal;
    uint8_t PinDir = 0;
    uint32_t index;
    
   assert_expression(IS_GPIO(GPIOx));
   assert_expression(IS_GPIO_PIN(GPIO_InitParams.GPIO_Pin));
   assert_expression(IS_GPIO_MODE(GPIO_InitParams.GPIO_Mode));
    

    switch((uint32_t)GPIOx)
    {
        case (uint32_t)GPIOA:
            Portx = PORTA;
            break;
        case (uint32_t)GPIOB:
            Portx = PORTB;
            break;
        case (uint32_t)GPIOC:
            Portx = PORTC;
            break;
        case (uint32_t)GPIOD:
            Portx = PORTD;
            break;
        case (uint32_t)GPIOE:
            Portx = PORTE;
            break;
        default:
            return;
    }
    
    for(index = 0; index <= 31; ++index)
    {
        if(GPIO_InitParams.GPIO_Pin == (1<<index))
        {   
            break;
        }
    }
    
    tmpRegVal = Portx->PCR[index];
    tmpRegVal &= ~PORT_PCR_MUX_MASK;
    
    /* GPIO Mode */
    if((GPIO_InitParams.GPIO_Mode & PORT_PCR_MUX_MASK) == PORT_PCR_MUX(1))
    {
        optionBits |= PORT_PCR_MUX(1);
        optionBits &= (uint32_t)0xFFFFFFF50;
        
        PinDir = (GPIO_InitParams.GPIO_Mode>>4)&0x0F;
        
        switch(GPIO_InitParams.GPIO_Mode)
        {
            case GPIO_Out_OD:
                optionBits |= 0x20;
                PinDir = 1;
                break;
            case GPIO_Out_PP:
                optionBits |= 0x03;
                PinDir = 1;
                break;
            case GPIO_Out_PD:
                optionBits |= 0x02;
                break;
            case GPIO_IN_UP:
                optionBits |= 0x03;
                break;
            case GPIO_IN_DN:
                optionBits |= 0x02;
                break;
            case GPIO_IN_FLOATING:
                optionBits |= 0x00;
                break;
            default:
                return;
        }
        
        /* InputMode */
        if(PinDir == 2)
        {
            GPIOx->PDDR &= (uint32_t)~GPIO_InitParams.GPIO_Pin;
        }
        /* Output Mode */
        else if(PinDir == 1)
        {
            GPIOx->PDDR |= GPIO_InitParams.GPIO_Pin;
        }
        
        tmpRegVal &= ~0xFFFF8050u;
        tmpRegVal  |= optionBits;
    }
    else
    {
        tmpRegVal |= GPIO_InitParams.GPIO_Mode;
    }
    
    
    Portx->PCR[index] = tmpRegVal;
}

uint8_t  GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint32_t Pin)
{
    uint8_t bitVal = 0;
    
    assert_expression(IS_GPIO(GPIOx));
    assert_expression(IS_GPIO_PIN(Pin));

    if (GPIOx->PDOR & Pin)
    {
        bitVal = 1;
    }

    return bitVal;
}

uint32_t GPIO_ReadOutputData(GPIO_Type* GPIOx)
{
    assert_expression(IS_GPIO(GPIOx));
    
    return (GPIOx->PDOR); 
}

uint8_t  GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint32_t Pin)
{
    uint8_t bitVal = 0;
    
    assert_expression(IS_GPIO(GPIOx));
    assert_expression(IS_GPIO_PIN(Pin));
    
    if (GPIOx->PDIR & Pin)
    {
        bitVal = 1;
    }
    return bitVal;
}



uint32_t GPIO_ReadInputData(GPIO_Type* GPIOx)
{
    assert_expression(IS_GPIO(GPIOx));
    
    return (GPIOx->PDIR);   
}


/**
 * @fn:         GPIO_SetBits
 * @bref:       Set  Many Pin's value on GPIOx
 * @params:     GPIOx     
 *              Pins:     GPIO_Pin_0 ~ ALL_PINS
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void  GPIO_SetBits(GPIO_Type* GPIOx, uint32_t Pins)
{
    assert_expression(IS_GPIO(GPIOx));
    
    GPIOx->PSOR |= Pins;
}


/**
 * @fn:         GPIO_ClearBits
 * @bref:       Clear  Many Pin's value on GPIOx
 * @params:     GPIOx     
 *              Pins:     GPIO_Pin_0 ~ ALL_PINS
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void  GPIO_ClearBits(GPIO_Type* GPIOx, uint32_t Pins)
{
    assert_expression(IS_GPIO(GPIOx));

    GPIOx->PCOR |= Pins;
}


/**
 * @fn:         GPIO_Write
 * @bref:       Write a uint32_t-type value to GPIOx
 * @params:     GPIOx     
 *              portVal:      0 ~ 0xFFFFFFFF
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void  GPIO_Write(GPIO_Type* GPIOx, uint32_t portVal)
{
    uint32_t setBits = 0;
    uint32_t clearBits = 0;
    uint32_t bitShift;
    uint32_t i;
    
    assert_expression(IS_GPIO(GPIOx));
    
    for(i=0; i<=31; i++)
    {
        bitShift = (uint32_t)1<<i;
        if(portVal & bitShift)
        {
            setBits |= bitShift;
        }
        else
        {
            clearBits |= bitShift;
        }
    }
    
    GPIOx->PSOR |= setBits;
    GPIOx->PCOR |= clearBits;
}


/**
 * @fn:         GPIO_WriteBit
 * @bref:       Set or Clear  Pin on GPIOx
 * @params:     GPIOx     
 *              Pin:      GPIO_Pin_0 ~ GPIO_Pin_31
 *              action:   SET / CLEAR
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void GPIO_WriteBit(GPIO_Type* GPIOx, uint32_t Pin, BitAction_t action)
{
    assert_expression(IS_GPIO(GPIOx));
    assert_expression(IS_GPIO_PIN(Pin));
    assert_expression(IS_BIT_ACTION(action));
 
    if(action == CLEAR)
    {
     GPIOx->PCOR |= Pin;
    }
    else 
    {
     GPIOx->PSOR |= Pin;
    }
   
}

/**
 * @fn:         GPIO_Toggle
 * @bref:       Revert the GPIO Pin based on the last value.
 * @params:     GPIOx     
 *              Pin:      GPIO_Pin_0 ~ GPIO_Pin_31
 * @return:     none
 * @version:    0.1
 * @date:       2013-1-2 
 * 
 */
void  GPIO_Toggle(GPIO_Type* GPIOx, uint32_t Pin)
{

    assert_expression(IS_GPIO(GPIOx));
    assert_expression(IS_GPIO_PIN(Pin));    
    
    
    GPIOx->PTOR |= Pin;
    
}

