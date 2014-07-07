#ifndef __KINETIS_GPIO_H__
#define __KINETIS_GPIO_H__

#include "kinetis_k60.h"



typedef enum
{
  GPIO_ANALOG       = 0x000u,
  GPIO_Out_OD       = 0x101u,          /* open-drain */
  GPIO_Out_PP       = 0x102u,          /* pull-up */
  GPIO_Out_PD       = 0x103u,          /* pull-down */
  GPIO_IN_UP        = 0x104u,                 
  GPIO_IN_DN        = 0x105u,
  GPIO_IN_FLOATING  = 0x106u,
  GPIO_ALIT2        = 0x200u,
  GPIO_ALIT3        = 0x300u,   
  GPIO_ALIT4        = 0x400u,
  GPIO_ALIT5        = 0x500u,
  GPIO_ALIT6        = 0x600u,
  GPIO_ALIT7        = 0x700u,
    
}GPIO_ModeType_t;


typedef enum
{
    CLEAR = 0,
    SET = 1
}BitAction_t;


typedef struct
{
    uint32_t GPIO_Pin;
    GPIO_ModeType_t GPIO_Mode;
}GPIO_InitType_t;




#ifndef GPIOA
  #define GPIOA   PTA
#endif

#ifndef GPIOB
  #define GPIOB   PTB
#endif

#ifndef GPIOC
  #define GPIOC   PTC
#endif

#ifndef GPIOD
  #define GPIOD   PTD
#endif

#ifndef GPIOE
  #define GPIOE   PTE
#endif


#ifndef PORTA
#define PORTA   (PORTA_BASE)
#endif

#ifndef PORTB
#define PORTB   (PORTB_BASE)
#endif

#ifndef PORTC
#define PORTC   (PORTC_BASE)
#endif

#ifndef PORTD
#define PORTD   (PORTD_BASE)
#endif

#ifndef PORTE
#define PORTE   (PORTE_BASE)
#endif

                                     
#define GPIO_Pin_0                 (0x00000001UL)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 (0x00000002UL)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 (0x00000004UL)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 (0x00000008UL)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 (0x00000010UL)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 (0x00000020UL)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 (0x00000040UL)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 (0x00000080UL)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 (0x00000100UL)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 (0x00000200UL)  /*!< Pin 9 selected */
#define GPIO_Pin_10                (0x00000400UL)  /*!< Pin 10 selected */
#define GPIO_Pin_11                (0x00000800UL)  /*!< Pin 11 selected */
#define GPIO_Pin_12                (0x00001000UL)  /*!< Pin 12 selected */
#define GPIO_Pin_13                (0x00002000UL)  /*!< Pin 13 selected */
#define GPIO_Pin_14                (0x00004000UL)  /*!< Pin 14 selected */
#define GPIO_Pin_15                (0x00008000UL)  /*!< Pin 15 selected */
#define GPIO_Pin_16                (0x00010000UL)  /*!< Pin 16 selected */
#define GPIO_Pin_17                (0x00020000UL)  /*!< Pin 17 selected */
#define GPIO_Pin_18                (0x00040000UL)  /*!< Pin 18 selected */
#define GPIO_Pin_19                (0x00080000UL)  /*!< Pin 19 selected */
#define GPIO_Pin_20                (0x00100000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_21                (0x00200000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_22                (0x00400000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_23                (0x00800000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_24                (0x01000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_25                (0x02000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_26                (0x04000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_27                (0x08000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_28                (0x10000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_29                (0x20000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_30                (0x40000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_31                (0x80000000UL)  /*!< Pin 20 selected */
#define GPIO_Pin_All               (0xFFFFFFFFUL)  /*!< All pins selected */

                                     
#define IS_GPIO_PIN(Pin)           (   ((Pin) == GPIO_Pin_0)              \
                                     ||((Pin) == GPIO_Pin_1)              \
                                     ||((Pin) == GPIO_Pin_2)              \
                                     ||((Pin) == GPIO_Pin_3)              \
                                     ||((Pin) == GPIO_Pin_4)              \
                                     ||((Pin) == GPIO_Pin_5)              \
                                     ||((Pin) == GPIO_Pin_6)              \
                                     ||((Pin) == GPIO_Pin_7)              \
                                     ||((Pin) == GPIO_Pin_8)              \
                                     ||((Pin) == GPIO_Pin_9)               \
                                     ||((Pin) == GPIO_Pin_10)              \
                                     ||((Pin) == GPIO_Pin_11)              \
                                     ||((Pin) == GPIO_Pin_12)              \
                                     ||((Pin) == GPIO_Pin_13)              \
                                     ||((Pin) == GPIO_Pin_14)              \
                                     ||((Pin) == GPIO_Pin_15)              \
                                     ||((Pin) == GPIO_Pin_16)              \
                                     ||((Pin) == GPIO_Pin_17)              \
                                     ||((Pin) == GPIO_Pin_18)              \
                                     ||((Pin) == GPIO_Pin_19)              \
                                     ||((Pin) == GPIO_Pin_20)              \
                                    )

#define IS_GPIO(GPIOx)             (  ((GPIOx) == GPIOA)    \
                                    ||((GPIOx) == GPIOB)    \
                                    ||((GPIOx) == GPIOC)    \
                                    ||((GPIOx) == GPIOD)    \
                                    ||((GPIOx) == GPIOE) ) 
                                    
#define IS_GPIO_MODE(MODE)         (  ((MODE)== GPIO_ANALOG)        \
                                    ||((MODE)== GPIO_Out_PP)        \
                                    ||((MODE)== GPIO_Out_PD)        \
                                    ||((MODE)== GPIO_Out_OD)        \
                                    ||((MODE)== GPIO_IN_UP)         \
                                    ||((MODE)== GPIO_IN_DN)         \
                                    ||((MODE)== GPIO_IN_FLOATING)   \
                                    ||((MODE) == GPIO_ALT2   )      \
                                    ||((MODE) == GPIO_ALT3   )      \
                                    ||((MODE) == GPIO_ALT4   )      \
                                    ||((MODE) == GPIO_ALT5   )      \
                                    ||((MODE) == GPIO_ALT6   )      \
                                    ||((MODE) == GPIO_ALT7 ) )


#define IS_BIT_ACTION(ACTION)       (((ACTION)==CLEAR) || ((ACTION) == SET))                                    

void  GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType_t GPIO_InitParams);
uint8_t  GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint32_t Pin);
uint32_t GPIO_ReadOutputData(GPIO_Type* GPIOx);
uint8_t  GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint32_t Pin);
uint32_t GPIO_ReadInputData(GPIO_Type* GPIOx);
void  GPIO_SetBits(GPIO_Type* GPIOx, uint32_t Pins);
void  GPIO_ClearBits(GPIO_Type* GPIOx, uint32_t Pins);  
void  GPIO_Write(GPIO_Type* GPIOx, uint32_t portVal);
void  GPIO_WriteBit(GPIO_Type* GPIOx, uint32_t Pin, BitAction_t action);
void  GPIO_Toggle(GPIO_Type* GPIOx, uint32_t Pin);

#endif
