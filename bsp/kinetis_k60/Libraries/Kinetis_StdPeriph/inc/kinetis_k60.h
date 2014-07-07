#ifndef __KINETIS_K60_H__
#define __KINETIS_K60_H__


#ifdef __cplusplus
extern "C" {
#endif
    
#include "MK60DZ10.h"

    

#include "core_cm4.h"
#include "system_MK60D10.h"
    
  

typedef enum
{
    DISABLE = 0,
    ENABLE = 1
}FunctionalState;

#define IS_FUNCTIONAL_STATE(State)      ( ((State)== DISABLE) || ((State) == ENABLE) )

#ifndef NULL
#define NULL    ((void*)0)
#endif

#ifndef __IO
#define  __IO volatile
#endif

#ifndef __O
#define  _O volatile
#endif

#ifndef __I
#define  __I volatile
#endif


typedef struct
{
    uint32_t SystemCoreClock;
    uint32_t BusClock;
    uint32_t FlexBusClock;
    uint32_t FlashClock;
}Kinetis_ClocksType;

extern __IO Kinetis_ClocksType g_Clocks_Freq; 



#ifdef USING_STD_PERIPH
#include "kinetis_config.h"
#endif


#ifdef __cplusplus
}
#endif

#endif

