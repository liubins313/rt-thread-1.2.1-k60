/**
  ******************************************************************************
  * @file    kinetis_mcg.h
  * @author  FLY
  * @version V0.5.0
  * @date    2012-12-28
  * @brief   This file contains all the functions prototypes for the MCG module 
  *          firmware library. 
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KINETIS_MCG_H__
#define __KINETIS_MCG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MK60D10.h"

/** @addtogroup KINETIS_StdPeriph Driver
  * @{
  */

/** @addtogroup MCG
  * @{
  */  

/** @defgroup MCG_Exported_Types
  * @{
  */
  
  typedef struct
  {
    uint32_t Freq_Core_Clock;     /*!< returns Core Clock frequency expressed in Hz */
    uint32_t Freq_System_Clock;   /*!< returns System Clock frequency expressed in Hz */
    uint32_t Freq_Bus_Clock;      /*!< returns Bus Clock frequency expressed in Hz */
    uint32_t Freq_FlexBus_Clock;  /*!< returns FlexBus Clock frequency expressed in Hz */
    uint32_t Freq_Flash_Clock;    /*!< returns Flash Clock frequency expressed in Hz */
  }MCG_ClocksTypeDef;

/** 
  * @}
  */


/**
* @defgroup MCGOUTCLK_clock_source
* @{
*/
  #define MCGCLK_SRC_FLL_OR_PLL          ((uint8_t)0)
  #define MCGCLK_SRC_IRC                 ((uint8_t)1)
  #define MCGCLK_SRC_ERC                 ((uint8_t)2)
  #define IS_MCGCLK_SRC(SOURCE)          ( ((SOURCE) == MCGCLK_SRC_FLL_OR_PLL)  \
                                           ((SOURCE) == MCGCLK_SRC_IRC)         \
                                           ((SOURCE) == MCGCLK_SRC_ERC) )
  
/** 
  * @}
  */ 

/**
* @defgroup FLL_External_Reference_Divider
* @{
*/
  #define FLL_ERC_DIV_1_32                      ((uint8_t)0x00u)
  #define FLL_ERC_DIV_2_64                      ((uint8_t)0x01u)
  #define FLL_ERC_DIV_4_128                     ((uint8_t)0x02u)
  #define FLL_ERC_DIV_8_256                     ((uint8_t)0x03u)
  #define FLL_ERC_DIV_16_512                    ((uint8_t)0x04u)
  #define FLL_ERC_DIV_32_1024                   ((uint8_t)0x05u)
  #define FLL_ERC_DIV_64_RESERVED               ((uint8_t)0x06u)
  #define FLL_ERC_DIV_128_RESERVED              ((uint8_t)0x07u)
  #define IS_FLL_ERC_DIVIDER(DIVID)             ((uint8_t)(DIVID)<= FLL_ERC_DIV_128_RESERVED)
/** 
  * @}
  */ 


/**
* @defgroup OSC_FREQUENCY_RANGE_SELECT
* @{
*/
  #define OSC_LOW_FREQ_RANGE                       ((uint8_t)0x00u)
  #define OSC_HIGH_FREQ_RANGE                      ((uint8_t)0x01u)
  #define OSC_VERY_HIGH_FREQ_RANGE                 ((uint8_t)0x02u)
  #define IS_OSC_FREQUENCY_RANGE(RANGE)             ((uint8_t)(RANGE) <= OSC_VERY_HIGH_FREQ_RANGE)
/** 
  * @}
  */ 

/**
* @defgroup PLL_EXTERNAL_REFERENCE_CLOCK_DIVIDER
* @{
*/
  #define PLL_DIVIDER_FACTOR(FACTOR)              ((uint8_t)((FACTOR)-1))
  #define IS_PLL_DIVIDER_FACTOR(FACTOR)           (((uint8_t)(FACTOR)>0) && ((uint8_t)(FACTOR)<26))

/** 
  * @}
  */ 
  
  
/**
* @defgroup PLL_EXTERNAL_REFERENCE_CLOCK_DIVIDER
* @{
*/
  #define PLL_MULTIPLY_FACTOR(FACTOR)           ((uint8_t)(FACTOR)-24)
  #define IS_PLL_MULTIPLY_FACTOR(FACTOR)        (((uint8_t)(FACTOR)>=24) && ((uint8_t)(FACTOR)<=55))

/** 
  * @}
  */ 


/**
* @defgroup DCO_RANGE_SELECT
* @{
*/
    #define   IS_DCO_RANGE(RANGE)               ((uint8_t)(RANGE)<=3)
/** 
  * @}
  */   
  
  
  


  
/**
  * @defgroup MCG_Exported_Functions
  * @{
  */
  
  
/** 
  * @}
  */  
  void MCG_Config_C1(uint8_t pos, uint8_t val);
  void MCG_Config_C2(uint8_t pos, uint8_t val);
  void MCG_Config_C3(uint8_t pos, uint8_t val);
  void MCG_Config_C4(uint8_t pos, uint8_t val);
  void MCG_Config_C5(uint8_t pos, uint8_t val);
  void MCG_Config_C6(uint8_t pos, uint8_t val);
/** 
  * @}
  */
  
#ifdef __cplusplus
}
#endof

#endif
