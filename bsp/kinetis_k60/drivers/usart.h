/*
 * File      : usart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-28     FLY          the first version
 */

#ifndef __USART_H__
#define __USART_H__

#include "kinetis_k60.h"
#include <rthw.h>
#include <rtthread.h>






/*
    Kinetis K60 所有串口的映射表，请根据自己控制板的实际情况选择其中的一种
    
    注：命令规则
    UARTx - RxPort - RxPin - RxMux - TxPort - TxPin - TxMux
    请不要更改下面的各种预定义的值，否则会导致初始化串口失败
*/

#define UART0_PA1_M2_PA2_M2     (0x20808100U)
#define UART0_PA14_M3_PA15_M3   (0x33C0CE00U)
#define UART0_PB16_M3_PB17_M3   (0x3444D010U)
#define UART0_PD6_M3_PD7_M3     (0x31CCC630U)
#define UART1_PE0_M3_PE1_M3     (0x3050C041U)
#define UART1_PC3_M3_PC4_M3     (0x3108C321U)
#define UART2_PD2_M3_PD3_M3     (0x30CCC232U)
#define UART3_PB10_M3_PB11_M3   (0x32C4CA13U)
#define UART3_PC17_M3_PC18_M3   (0x3488D123U)
#define UART3_PE4_M3_PE5_M3     (0x3150C443U)
#define UART4_PE24_M3_PE25_M3   (0x3650D844U)
#define UART4_PC14_M3_PC15_M3   (0x33C8CE24U)
#define UART5_PD8_M3_PD9_M3			(0x324cc835U)





void rt_hw_usart_init(void);





extern UART_Type* UART_Init(uint32_t uartxMap, uint32_t baud);
extern void UART_SendByte(UART_Type *uartx, uint8_t ch);                                                                 
extern void UART_SendBytes(UART_Type *uartx,uint8_t *buf, uint32_t len);
extern void UART_SendString(UART_Type *uartx, uint8_t *str);
extern uint8_t UART_Receive(UART_Type *uartx, uint8_t *ch);
void UART1_RX_TX_IRQHandler(void);


#endif
