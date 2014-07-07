/**************************************************************************//**
 * @file     system_MK60D10.c
 * @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Source File
 *           for the Device Series ...
 * @version  V1.00
 * @date     2012-12-27
 *
 * @note
 * Copyright (C) 2012 Personal Limited. All rights reserved.
 *
 * @par
 * Personal is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include "kinetis_k60.h"

#define ENABLE_BIT(x)   (1<<(x))
#define DISABLE_BIT(x)  (~(1<<(x)))

#define ENABLE_BYTE(x)  (uint8_t)(x)
#define DISABLE_BYTE(x) (uint8_t)(~(x))



/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Define clocks:      (Units:HZ)

        CPU_XTAL_CLK:
        CPU_XTAL32k_CLK_HZ:
        CPU_INT_SLOW_CLK_HZ:
        CPU_INT_FAST_CLK_HZ:
        DEFAULT_SYSTEM_CLOCK:

           0 ... Internal Crystal Oscillator(32KHZ)
                Core/System Clock: 96M
				 Bus        Clock: 48M
				 FlexBus    Clock: 48M
				 Flash      Clock: 24M

           1 ... External 8M Oscillator
                 Core/System Clock: 96M
				 Bus         Clock: 48M
				 FlexBus     Clock: 48M
				 Flash       Clock: 24M

           2 ... External 8M Oscillator OverClock
                 Core/System Clock: 200M
				 Bus         Clock: 100M
				 FlexBus     Clock: 100M
				 Flash       Clock: 25M

           3 ... External 50M Active Crystal
                 Core/System Clock: 100M
				 Bus         Clock: 50M
				 FlexBus     Clock: 50M
				 Flash       Clock: 25M
           4.... External 50M Active Crystal
                 Core/System Clock: 96M
                 Bus         Clock: 48M
                 FlexBus     Clock: 48M
                 Flash       Clock: 24M

 -----------------------------------------------------------------------------*/


#define HSE_VALUE       8000000UL


 
 #ifndef CLOCK_SETUP
    #define CLOCK_SETUP    0
 #endif


#if (CLOCK_SETUP == 0)
    #define CPU_XTAL_CLK_HZ                 4000000u
    #define CPU_XTAL32k_CLK_HZ              32768u
    #define CPU_INT_SLOW_CLK_HZ             32768u
    #define CPU_INT_FAST_CLK_HZ             4000000u
    
    #define DEFAULT_SYSTEM_CLOCK            96000000u
    #define DEFAULT_BUS_CLOCK               48000000u
    #define DEFAULT_FLEXBUS_CLOCK           48000000u
    #define DEFAULT_FLASH_CLOCK             24000000u
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL_CLK_HZ                 8000000u
    #define CPU_XTAL32k_CLK_HZ              32768u
    #define CPU_INT_SLOW_CLK_HZ             32768u
    #define CPU_INT_FAST_CLK_HZ             4000000u
    
    #define DEFAULT_SYSTEM_CLOCK            96000000u
    #define DEFAULT_BUS_CLOCK               48000000u
    #define DEFAULT_FLEXBUS_CLOCK           48000000u
    #define DEFAULT_FLASH_CLOCK             24000000u
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL_CLK_HZ                 8000000u
    #define CPU_XTAL32k_CLK_HZ              32768u
    #define CPU_INT_SLOW_CLK_HZ             32768u
    #define CPU_INT_FAST_CLK_HZ             4000000u
    
    #define DEFAULT_SYSTEM_CLOCK            100000000u
    #define DEFAULT_BUS_CLOCK               50000000u
    #define DEFAULT_FLEXBUS_CLOCK           50000000u
    #define DEFAULT_FLASH_CLOCK             25000000u
    
#elif (CLOCK_SETUP == 3)
    #define CPU_XTAL_CLK_HZ                 50000000u
    #define CPU_XTAL32k_CLK_HZ              32768u
    #define CPU_INT_SLOW_CLK_HZ             32768u
    #define CPU_INT_FAST_CLK_HZ             4000000u
    
    #define DEFAULT_SYSTEM_CLOCK            100000000u
    #define DEFAULT_BUS_CLOCK               50000000u
    #define DEFAULT_FLEXBUS_CLOCK           50000000u
    #define DEFAULT_FLASH_CLOCK             25000000u
#elif (CLOCK_SETUP == 4)
    #define CPU_XTAL_CLK_HZ                 50000000u
    #define CPU_XTAL32k_CLK_HZ              32768u
    #define CPU_INT_SLOW_CLK_HZ             32768u
    #define CPU_INT_FAST_CLK_HZ             4000000u
    
    #define DEFAULT_SYSTEM_CLOCK            96000000u
    #define DEFAULT_BUS_CLOCK               48000000u
    #define DEFAULT_FLEXBUS_CLOCK           48000000u
    #define DEFAULT_FLASH_CLOCK             24000000u
#endif


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()    */
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/

__IO Kinetis_ClocksType g_Clocks_Freq = {DEFAULT_SYSTEM_CLOCK, DEFAULT_BUS_CLOCK, DEFAULT_FLEXBUS_CLOCK, DEFAULT_FLASH_CLOCK};





/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    uint32_t MCGOUTClock;     
    uint8_t Divider;
  
    /* FLL or PLL is seleted as MCGOUTCLK source */
    if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u)
    {
        /* FLL is selected as MCGOUTCLK source */
        if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)
        {
            /* External reference clock is selected */
            if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)
            {
                /* System oscillator is selected */
                if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u)
                {
                    MCGOUTClock = CPU_XTAL_CLK_HZ;   //系统晶振驱动 MCG 时钟
                }
                /* 32KHz RTC oscillator is selected */
                else
                {
                    MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz 晶振驱动 MCG 时钟
                }
                
                /* Read out FRDIV  */
                Divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
                
                /* Calculate External Reference Clock Frequncy  */
                MCGOUTClock = (MCGOUTClock / Divider);  //计算FLL参考时钟分频
                /* If range is high frequency or Very high frequency */
                if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0u)
                {
                    /* addtional 32-divider */
                    MCGOUTClock /= 32u;  /* See Figure 24-1 */
                }
            }
            /*  The slow internal reference clock is selected */
            else
            {
                MCGOUTClock = CPU_INT_SLOW_CLK_HZ; 
            }
            
            /* 
             * Select an appropriate multiply factor to calculate MCGOUTCLK 
             */
            
            /* Params is invalid */
            if(MCGOUTClock <31250 || MCGOUTClock>39063)
            {
              return;
            }
            
            switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK))
            {
            case 0x0u:
                MCGOUTClock *= 640u;
                break;
            case 0x20u:
                MCGOUTClock *= 1280u;
                break;
            case 0x40u:
                MCGOUTClock *= 1920u;
                break;
            case 0x60u:
                MCGOUTClock *= 2560u;
                break;
            case 0x80u:
                MCGOUTClock *= 732u;
                break;
            case 0xA0u:
                MCGOUTClock *= 1464u;
                break;
            case 0xC0u:
                MCGOUTClock *= 2197u;
                break;
            case 0xE0u:
                MCGOUTClock *= 2929u;
                break;
            default:
                break;
            }
        }
        /* PLL is selected as MCGOUTCLK source */
        else
        {
            /* PLL */
            Divider = (1u + (MCG->C5 & MCG_C5_PRDIV_MASK));
            MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);  /* Calculate PLL Reference Clock */
            
            /* Calculate MCGOUTCLK */
            Divider = ((MCG->C6 & MCG_C6_VDIV_MASK) + 24u);
            MCGOUTClock *= Divider;       
        }
    }
    /* Internal Reference Clock is selected */
    else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u)
    {
        /* Slow IRC is Selected */
        if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)
        {
            MCGOUTClock = CPU_INT_SLOW_CLK_HZ;   
        }
        /* Fast IRC is selected */
        else
        {
            MCGOUTClock = CPU_INT_FAST_CLK_HZ;
        }
    }
    /* External Reference Clock is Selected */
    else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)
    {
        /* System oscillator is selected */
        if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u)
        {
            MCGOUTClock = CPU_XTAL_CLK_HZ;     //系统晶振驱动 MCG 时钟
        }
        /* 32KHz RTC oscillator is selected */
        else
        {
            MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz 晶振驱动 MCG 时钟
        }
    }
    /* We cannot find the source of MCGOUTCLK */
    else
    {
        /* do something here to handle exceptions */
        return;
    }
    
    /* Calculate System/Core Clock Frequency */
    SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
    g_Clocks_Freq.SystemCoreClock   = SystemCoreClock;
    g_Clocks_Freq.BusClock          = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT)));
    g_Clocks_Freq.FlexBusClock      = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV3_MASK) >> SIM_CLKDIV1_OUTDIV3_SHIFT)));
    g_Clocks_Freq.FlashClock        = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT)));
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */

 /**
 *      Register Description:
 *          SIM->CLKDIV1:
                OUTDIV1: System/Core CLK
                OUTDIV2: BUS CLK
                OUTDIV3: FLEXBUS CLK
                OUTDIV4: Flash CLK
 *
 */
void SystemInit (void)
{
    
    
  /*
   *    first step: DISABLE WDT
   */
   WDOG->UNLOCK     =   0xC520u;
   WDOG->UNLOCK     =   0xD928u;
   WDOG->STCTRLH    &=  ~0x0001u;
    
    
    
/* second step: Initialize Clock */
#if (CLOCK_SETUP == 0)
    
   /* Clock Div */
    SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
    
    /* C1[CLKS] = 0, C1[FRDIV] = 0, C1[IREFS] = 1 */
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;    
    /* C2[RANGE] = 0, C2[HGO] = 0, C2[EREFS]=0, C2[LP] = 0, C2[IRCS] = 0 */
    MCG->C2 = (uint8_t)0x00u;    
    /* C4[DMX32] = 0, C4[DRST_DRS] = 3 */
    MCG->C4 |= (uint8_t)0xE0;   /*DMX32 = 1, DRST_DRS = 3 */
    
    while((MCG->S & MCG_S_IREFST_MASK) == 0u); 
    while((MCG->S & MCG_S_CLKST_MASK) != 0x00u); 
    
    /* Clock Div */
 //   SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));

#elif (CLOCK_SETUP == 1)
    SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)       \
        | SIM_CLKDIV1_OUTDIV2(1)                \
        | SIM_CLKDIV1_OUTDIV3(1)                \
        | SIM_CLKDIV1_OUTDIV4(2));
    /*
        OSC_CR:
           [7]      ERCLKEN     = 0
           [5]      EREFSTEN    = 0
           [3]      SC2P        = 0
           [2]      SC4P        = 0
           [1]      SC8P        = 0
           [0]      SC16P       = 0
    */
    OSC->CR = (uint8_t)0x00u;
    
    /* System oscillator(OSCCLK) is seletecd as external reference clock */
    SIM->SOPT2 &= DISABLE_BYTE(SIM_SOPT1_MCGCLKSEL_MASK);

     /* switch to FBE */
     /*
        [5..4] RANGE    = 11, 
        [3]    HGO    = 0, 
        [2]    EREFS  = 1, 
        [1]    LP = 0,     
        [0]   IRCS = 0, 
    */
    MCG->C2 =  (uint8_t)0x24u;
     /*
        [7..6] CLKS   = 10, 
        [5..3] FRDIV  = 011,
        [2]    IREFS  = 0,  
        [1]    IRCLKEN = 1, 
        [0]    IREFSTEN = 0,   
     */
    MCG->C1 = (uint8_t)0x9Au;
    MCG->C4 &= (uint8_t)~0xE0u; /* FLL = 20MHZ */
    MCG->C6 = (uint8_t)0x00u;
  
    while((MCG->S & MCG_S_IREFST_MASK) != 0u); /* Wait until source of FLL reference clock is the internal reference clock */
    while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);/* Wait until the initialization cycles of the crystal oscillator clock have completed */
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2));  /* Wait until external refrence clock is selected */
    

    /*
    * PBE
    */
    MCG->C5 = (uint8_t)0x03u;   /* PRDIV = 3, Divider Factor = 4 */
    /* PLL MULTIPLY Factor = 48 */
    MCG->C6 = ENABLE_BYTE(MCG_C6_PLLS_MASK) | MCG_C6_VDIV0(48-0x18);		   

    while((MCG->S & MCG_S_PLLST_MASK) == 0u);   /* Wait until PLL is selected as the source of MCGOUTCLK */
    while((MCG->S & MCG_S_LOCK_MASK) == 0u);    /* Wait until PLL frequency is locked */

    /* Tranfer from PBE to PEE */
    MCG->C1 = (uint8_t)0x1Au;   /* C1[CLKS] = 0, C1[IREFS] = 0, C6[PLLS] = 1 */
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3));
    while((MCG->S & MCG_S_LOCK_MASK) == 0u);  
    


    
    
#elif (CLOCK_SETUP == 2)
      SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)       \
        | SIM_CLKDIV1_OUTDIV2(1)                \
        | SIM_CLKDIV1_OUTDIV3(1)                \
        | SIM_CLKDIV1_OUTDIV4(2));  
    /* FBE */
    OSC->CR = (uint8_t)0x00u;
    SIM->SOPT2 &= (uint8_t)~0x01u;
    
    MCG->C2 = (uint8_t)0x24u;
    MCG->C1 = (uint8_t)0x9Au;
    MCG->C4 &= (uint8_t)~0xE0u;
    MCG->C5 = (uint8_t)0x03u;    //4分频
    MCG->C6 = (uint8_t)0x00u;
    while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);
    while((MCG->S & MCG_S_IREFST_MASK) != 0u); 
    while((MCG->S & 0x0Cu) != 0x08u);          
    
    /* PBE */
    MCG->C5 = (uint8_t)0x03u; /*  */
    MCG->C6 = ENABLE_BYTE(MCG_C6_PLLS_MASK) \ | MCG_C6_VDIV0(50-0x18);	
    while((MCG->S & MCG_S_PLLST_MASK) == 0u);   
    while((MCG->S & MCG_S_LOCK_MASK) == 0u);  

    /* PEE */
    MCG->C1 = (uint8_t)0x1Au;
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3));   
    while((MCG->S & MCG_S_LOCK_MASK) == 0u); 
    
    



/*
        System/Core Clock : 100MHz
        Bus         Clock : 50MHz
        FlexBu      Clock : 50MHz
        Flash       Clock : 25MHz
 */
#elif (CLOCK_SETUP == 3)
   SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)          \
        | SIM_CLKDIV1_OUTDIV2(1)                  \
        | SIM_CLKDIV1_OUTDIV3(1)                  \
        | SIM_CLKDIV1_OUTDIV4(3));
    /* FBE */
    OSC->CR = (uint8_t)0x00u;    
    SIM->SOPT2 &= (uint8_t)~0x01u; /* System Oscillator is selected */
    
    MCG->C2 = (uint8_t)0x24u; 
    MCG->C1 = (uint8_t)0x9Au;
    MCG->C4 &= (uint8_t)~0xE0u;
    MCG->C5 = (uint8_t)0x03u;
    MCG->C6 = (uint8_t)0x00u;
    /* Check whether the initializeation cycles of the crystal oscillator clock have completed */
    while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);   
    /* Check wether Source of FLL reference clock is the external reference clock */
    while((MCG->S & MCG_S_IREFST_MASK) != 0u);
    /* Check wether External reference clock is selected. */
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2));
    
    /*
        PRDIV = 25      50MHz/25 = ...
    */
    /* PBE */
    MCG->C5 = (uint8_t)(25-1);
    
    /*
        [7]     LOLIE = 0
        [6]     PLLS  = 1
        [5]     CME   = 0
        [4-0]   VDIV  = 26 = 50 - 24(Note: the minimal multiply factor is 24)
        MCGPLLCLK = 50MHz/24*48 = 100MHz
    */
    MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(50-0x18));
    
    /* Check wether Source of PLLS clock is PLL clock. */
    while((MCG->S & MCG_S_PLLST_MASK) == 0u);
    /* Check wehter PLL is locked */
    while((MCG->S & MCG_S_LOCK_MASK) == 0u); 
    
    /*
        [7-6]   CLKS = 0;
        [5-3]   FRDIV = 3, if RANGE = 0, Divide Factor is 8; for other RANGE values, Divide Factor is 256
        [2]     IREFS = 0
        [1]     IRCLKEN = 1
        [0]     IREFSTEN = 0
    */
    /* PEE */
    MCG->C1 = (uint8_t)0x1Au;
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3));  
    while((MCG->S & MCG_S_LOCK_MASK) == 0u); 
    
/*
        System/Core Clock : 96MHz
        Bus         Clock : 48MHz
        FlexBu      Clock : 48MHz
        Flash       Clock : 24MHz
 */
#elif (CLOCK_SETUP == 4)
   SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)          \
        | SIM_CLKDIV1_OUTDIV2(1)                  \
        | SIM_CLKDIV1_OUTDIV3(1)                  \
        | SIM_CLKDIV1_OUTDIV4(3));
    /* FBE */
    OSC->CR = (uint8_t)0x00u;    
    SIM->SOPT2 &= (uint8_t)~0x01u; /* System Oscillator is selected */
    
    MCG->C2 = (uint8_t)0x24u; 
    MCG->C1 = (uint8_t)0x9Au;
    MCG->C4 &= (uint8_t)~0xE0u;
    MCG->C5 = (uint8_t)0x03u;
    MCG->C6 = (uint8_t)0x00u;
    /* Check whether the initializeation cycles of the crystal oscillator clock have completed */
    while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);   
    /* Check wether Source of FLL reference clock is the external reference clock */
    while((MCG->S & MCG_S_IREFST_MASK) != 0u);
    /* Check wether External reference clock is selected. */
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2));
    
    /*
        PRDIV = 25      50MHz/25 = ...
    */
    /* PBE */
    MCG->C5 = (uint8_t)(25-1);
    
    /*
        [7]     LOLIE = 0
        [6]     PLLS  = 1
        [5]     CME   = 0
        [4-0]   VDIV  = 26 = 50 - 24(Note: the minimal multiply factor is 24)
        MCGPLLCLK = 50MHz/25*48 = 96MHz
    */
    MCG->C6 = (uint8_t)(0x40u|MCG_C6_VDIV(48-0x18));
    
    /* Check wether Source of PLLS clock is PLL clock. */
    while((MCG->S & MCG_S_PLLST_MASK) == 0u);
    /* Check wehter PLL is locked */
    while((MCG->S & MCG_S_LOCK_MASK) == 0u); 
    
    /*
        [7-6]   CLKS = 0;
        [5-3]   FRDIV = 3, if RANGE = 0, Divide Factor is 8; for other RANGE values, Divide Factor is 256
        [2]     IREFS = 0
        [1]     IRCLKEN = 1
        [0]     IREFSTEN = 0
    */
    /* PEE */
    MCG->C1 = (uint8_t)0x1Au;
    while((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3));  
    while((MCG->S & MCG_S_LOCK_MASK) == 0u); 
    
#endif


//    SystemCoreClockUpdate();
}

