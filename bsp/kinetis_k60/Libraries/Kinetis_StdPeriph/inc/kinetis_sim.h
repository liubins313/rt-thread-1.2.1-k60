/**
  ******************************************************************************
  * @file    kinetis_sim.h
  * @author  FLY
  * @version V0.5.0
  * @date    2012-12-28
  * @brief   This file contains all the functions prototypes for the SIM module 
  *          firmware library. 
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KINETIS_SIM_H__
#define __KINETIS_SIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "kinetis_k60.h"

/** @addtogroup KINETIS_StdPeriph Driver
  * @{
  */

/** @addtogroup SIM
  * @{
  */  

    
/** 
  * @}
  */ 

/** 
  * @}
  */


/*
    GPIO Gate Control
*/
  #define SCGC_GPIOA         ((uint32_t)0x0100000)
  #define SCGC_GPIOB         ((uint32_t)0x0200000)
  #define SCGC_GPIOC         ((uint32_t)0x0400000)
  #define SCGC_GPIOD         ((uint32_t)0x0800000) 
  #define SCGC_GPIOE         ((uint32_t)0x1000000)
  #define SCGC_ALL_GPIO      ((uint32_t)0x1F00000)

#define IS_SCGC_GPIO(GPIOx)  ( (!((GPIOx)&(uint32_t)0x0000FFFF))       \
                               && ((GPIOx)>0)                          \
                               && ((GPIOx)<=SCGC_ALL_GPIO) )
                               
                               
/*
        UART Gate Control
*/
#define SCGC_UART0            (0x000001)
#define SCGC_UART1            (0x000002)
#define SCGC_UART2            (0x000004)
#define SCGC_UART3            (0x000008)
#define SCGC_UART4            (0x000010)
#define SCGC_ALL_UART         (0x00001F)

#define IS_SCGC_UART(UARTx)   (  ((UARTx) == SCGC_UART0)        \
                               ||((UARTx) == SCGC_UART1)        \
                               ||((UARTx) == SCGC_UART2)        \
                               ||((UARTx) == SCGC_UART3)        \
                               ||((UARTx) == SCGC_UART4) )


/*

        DAC Gate Control
*/
#define SCGC_DAC0             ((uint32_t)0x000001)
#define SCGC_DAC1             ((uint32_t)0x000002)
#define SCGC_ALL_DAC          ((uint32_t)0x000003)
#define IS_SCGC_DAC(DACx)     (((DACx)>0) &&((DACx)<=SCGC_ALL_DAC))


/*
        ENET Gate Control
*/
#define SCGC_ENET             ((uint32_t)0x0000001)
#define IS_SCGC_ENET(ENET)    ((ENET) == SCGC_ENET)


/*
        FTM Gate Control
*/
#define SCGC_FTM0             ((uint32_t)0x0000001)
#define SCGC_FTM1             ((uint32_t)0x0000002)
#define SCGC_FTM2             ((uint32_t)0x0000004)


/*
        SDHC Gate Control
*/
#define SCGC_SDHC             ((uint32_t)0x0010000)


/*
        SPI Gate Control
*/
#define SCGC_SPI0
#define SCGC_SPI1
#define SCGC_SPI2


/*
        FLEXCAN Gate Control
*/
#define SCGC_FLEXCAN0
#define SCGC_FLEXCAN1

/*
        RNGB Gate Control
*/
#define SCGC_RNGB            ((uint32_t)0x00000001)



/*
    LLWU Gate Control
*/
#define SCGC_LLWU           ((uint32_t)0x10000000)

/*
    VREF Gate Control
*/
#define SCGC_VREF           ((uint32_t)0x00100000)

/*
    CMP Gate Control
*/
#define SCGC_CMP            ((uint32_t)0x00080000)

/*
    USBOTG Gate Control
*/
#define SCGC_USBOTG         ((uint32_t)0x00040000)

/*
    I2C Gate Control
*/
#define SCGC_I2C0           ((uint32_t)0x00000040)
#define SCGC_I2C1           ((uint32_t)0x00000080)


/*
    CMT Gate Control
*/
#define SCGC_CMT            ((uint32_t)0x00000004)

/*
    EWN Gate Control
*/
#define SCGC_EWM            ((uint32_t)0x00000002)

/*
    TSI Gate Control
*/
#define SCGC_TSI            ((uint32_t)0x00000020)

/*
    REGFILE Gate Control
*/
#define SCGC_REGFILE        ((uint32_t)0x00000002)

/*
    LPTIMER Gate Control
*/
#define SCGC_LPTIMER        ((uint32_t)0x00000001)


/*
    RTC Gate Control
*/
#define SCGC_RTC            ((uint32_t)0x20000000)
#define IS_SCGC_RTC(RTC)    ((RTC) == SCGC_RTC)
/*
    ADC Gate Control
*/
#define SCGC_ADC0
#define SCGC_ADC1

/*
    PIT Gate Control
*/
#define SCGC_PIT            ((uint32_t)0x00800000)

/*
    PDB Gate Control
*/
#define SCGC_PDB            ((uint32_t)0x00400000)

/*
    USBDCD Gate Control
*/
#define SCGC_USBDCD         ((uint32_t)0x00200000)

/*
    CRC Gate Control
*/
#define SCGC_CRC            ((uint32_t)0x00040000)

/*
    I2S Gate Control
*/
#define SCGC_I2S            ((uint32_t)0x00008000)

/*
    DMAMUX  Gate Control
*/
#define SCGC_DMAMUX         ((uint32_t)0x00000002)

/*
    FTFL Gate Control
*/
#define SCGC_FTFL           ((uint32_t)0x00000001)

/*
    MPU Gate Control
*/
#define SCGC_MPU            ((uint32_t)0x00000004)

/*
    DMA Gate Control
*/
#define SCGC_DMA            ((uint32_t)0x00000002)

/*
    FLEXBUS Gate Control
*/
#define SCGC_FLEXBUS        ((uint32_t)0x00000001)






/* Disable or Enable the clock gate of GPIOx */
void SIM_SCGC_GPIO_Cmd(uint32_t SCGC_GPIOx, FunctionalState State);
/* Disable or Enable the clock gate of UARTx */
void SIM_SCGC_UART_Cmd(uint32_t SCGC_UARTx, FunctionalState State);  

/* Disable or Enable the clock gate of RTC */
void SIM_SCGC_RTC_Cmd(uint32_t SCGC_RTCx, FunctionalState State);

  
  
  
#ifdef __cplusplus
}
#endif

#endif
