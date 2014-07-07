
/* Includes ------------------------------------------------------------------*/
#include "kinetis_k60.h"
#include <rtthread.h>
#include "board.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
//void HardFault_Handler(void)
//{
//    // definition in libcpu/arm/cortex-m4/context_*.S
//}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//    // definition in libcpu/arm/cortex-m4/context_*.S
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//    // definition in boarc.c
//}

/******************************************************************************/
/*               Kientis K60 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_MK60D10.s).                                                 */
/******************************************************************************/

void UART0_RX_TX_IRQHandler(void) 
{
    
    
    
}


void UART1_RX_TX_IRQHandler(void) 
{
#ifdef RT_USING_UART1
    extern struct rt_device uart1_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart1_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif    
}

void UART2_RX_TX_IRQHandler(void) 
{
#ifdef RT_USING_UART2
    extern struct rt_device uart2_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart2_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}


void UART3_RX_TX_IRQHandler(void) 
{
#ifdef RT_USING_UART3
    extern struct rt_device uart3_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart3_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}



void UART4_RX_TX_IRQHandler(void) 
{
#ifdef RT_USING_UART4
    extern struct rt_device uart4_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart4_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

void UART5_RX_TX_IRQHandler(void) 
{
#ifdef RT_USING_UART5
    extern struct rt_device uart5_device;
	extern void rt_hw_serial_isr(struct rt_device *device);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart5_device);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
