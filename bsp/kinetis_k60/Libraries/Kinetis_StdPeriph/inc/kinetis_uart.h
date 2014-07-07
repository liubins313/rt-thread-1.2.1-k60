#ifndef __KINETIS_UART_H__
#define __KINIETIS_UART_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include "kinetis_k60.h"

    
typedef struct
{
    uint32_t UART_BaudRate;
    uint16_t UART_CharBits;
    uint16_t UART_StopBits;
    uint16_t UART_Parity;
    uint16_t UART_Mode;
    uint16_t UART_HardwareFlowControl;
}UART_InitType_t;
    


#define UART_PARITY_NONE      0x00
#define UART_PARITY_EVEN      0x02
#define UART_PARITY_ODD       0x03
#define IS_UART_PARITY(PARITY)  (   ((PARITY) == UART_PARITY_NONE)  \
                                  ||((PARITY) == UART_PARITY_EVEN)  \
                                  ||((PARITY) == UART_PARITY_ODD))




#define IS_UART_PERIPH(UART)        ( ((UART) == UART0_BASE_PTR)    \
                                      ((UART) == UART1_BASE_PTR)    \
                                      ((UART) == UART2_BASE_PTR)    \
                                      ((UART) == UART3_BASE_PTR)    \
                                      ((UART) == UART4_BASE_PTR)    \
                                      ((UART) == UART5_BASE_PTR)  )
                                      





#ifdef __cplusplus
}
#endif

#endif

