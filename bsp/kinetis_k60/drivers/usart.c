/*
 * File      : usart.c
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

#include "kinetis_k60.h"
#include "usart.h"
#include "board.h"
#include "serial.h"


/*
        串口的对应关系
        UART_Index: 0 - 5
        Rx_GPIO_Index: 0 - 4 (代表A-E)
        Rx_Pin_Index:  0 - 31
        Rx_Alt_Index:  0 - 7

        Tx_GPIO_Index: 0 - 4 (代表A-E)
        Tx_Pin_Index:  0 - 31
        Tx_Alt_Index:  0 - 7

*/
typedef struct
{
    uint32_t UART_Index:4;//占4bit
    uint32_t Rx_GPIO_Index:4;//占4bit
    uint32_t Rx_Pin_Index:6;//占6bit
    uint32_t Rx_Alt_Index:4;//占4bit
    uint32_t Tx_GPIO_Index:4;//占4bit
    uint32_t Tx_Pin_Index:6;//占6bit
    uint32_t Tx_Alt_Index:4;//占4bit
} UART_Map_t;  //共计32bit

/*
    串口所能可能情况对应的映射关系
*/
static const UART_Map_t cUART_Maps[13] =
{
    {0, 0, 1, 2, 0, 2, 2},  /* UART0, RxPORT PORTA, PIN1, MUX_2, TxPORT PORTA, PIN2, MUX_2, 下类似 */
    {0, 0,14, 3, 0,15, 3},
    {0, 1,16, 3, 1,17, 3},
    {0, 3, 6, 3, 3, 7, 3},
    {1, 4, 0, 3, 4, 1, 3},
    {1, 2, 3, 3, 2, 4, 3},
    {2, 3, 2, 3, 3, 3, 3},
    {3, 1,10, 3, 1,11, 3},
    {3, 2,17, 3, 2,18, 3},
    {3, 4, 4, 3, 4, 5, 3},
    {4, 4,24, 3, 4,25, 3},
    {4, 2,14, 3, 2,15, 3},
    {5, 3, 8, 3, 3, 9, 3}
};



#ifdef RT_USING_UART1
struct k60_serial_int_rx uart1_int_rx;
struct k60_serial_device uart1 =
{
    UART1_PE0_M3_PE1_M3,
    NULL,
    &uart1_int_rx
};
struct rt_device uart1_device;
#endif

#ifdef RT_USING_UART2
struct k60_serial_int_rx uart2_int_rx;

struct k60_serial_device uart2 =
{
    UART2_PD2_M3_PD3_M3,
    RT_NULL,
    &uart2_int_rx
};
struct rt_device uart2_device;
#endif


#ifdef RT_USING_UART3
struct k60_serial_int_rx uart3_int_rx;

struct k60_serial_device uart3 =
{
    UART3_PB10_M3_PB11_M3,
    RT_NULL,
    &uart3_int_rx
};
struct rt_device uart3_device;
#endif


#ifdef RT_USING_UART4
struct k60_serial_int_rx uart4_int_rx;

struct k60_serial_device uart4 =
{
    UART4_PC14_M3_PC15_M3,
    RT_NULL,
    &uart4_int_rx
};
struct rt_device uart4_device;
#endif


#ifdef RT_USING_UART5
struct k60_serial_int_rx uart5_int_rx;

struct k60_serial_device uart5 =
{
    UART5_PD8_M3_PD9_M3,
    RT_NULL,
    &uart5_int_rx
};
struct rt_device uart5_device;
#endif


/* 根据索引寻找合适的PORT */
static volatile PORT_Type* FindPortFromIndex(uint32_t index)
{
    volatile PORT_Type* port = NULL;

    switch(index)
    {
    case 0:
        port = PORTA;
        break;
    case 1:
        port = PORTB;
        break;
    case 2:
        port = PORTC;
        break;
    case 3:
        port = PORTD;
        break;
    case 4:
        port = PORTE;
        break;
    default:
        break;
    }
    return port;
}

/* 根据索引寻找合适的串口 */
static UART_Type* FindUARTFromIndex(uint32_t index)
{
    UART_Type* pUART = NULL;

    switch(index)
    {
    case 0:
        pUART = UART0;
        break;
    case 1:
        pUART = UART1;
        break;
    case 2:
        pUART = UART2;
        break;
    case 3:
        pUART = UART3;
        break;
    case 4:
        pUART = UART4;
        break;
    case 5:
        pUART = UART5;
        break;
    default:
        pUART = NULL;
        break;
    }

    return pUART;
}


/* 根据索引，使用PORT */
void PortEnableFromIndex(uint32_t index)
{
    switch(index)
    {
    case 0:
        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        break;
    case 1:
        SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
        break;
    case 2:
        SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
        break;
    case 3:
        SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
        break;
    case 4:
        SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
        break;
    default:
        break;
    }
}

/* 根据索引使能串口时钟  */
void UARTEnableFromIndex(uint32_t index)
{
    switch(index)
    {
    case 0:
        SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
        break;
    case 1:
        SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
        break;
    case 2:
        SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
        break;
    case 3:
        SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
        break;
    case 4:
        SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
        break;
    case 5:
        SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
        break;
    }
}


//UART 初始化
UART_Type* UART_Init(uint32_t UARTxMap, uint32_t baud)
{
    //进行传输速率计算
    uint16_t sbr;
    uint8_t brfa;
    uint32_t clock;
    UART_Map_t *map;
    int32_t i;
    uint8_t isFound = 0;
    volatile PORT_Type *RxPort;
    volatile PORT_Type *TxPort;
    UART_Type* pUART;

    map = (UART_Map_t*)&UARTxMap;

    for(i=sizeof(cUART_Maps)/sizeof(UART_Map_t); i; i--)
    {
        if( UARTxMap == *(uint32_t*)&cUART_Maps[i-1])
        {
            isFound = 1;
            break;
        }
    }

    //代表在表中查到了
    if(!isFound)
    {
        return NULL;
    }

    pUART = FindUARTFromIndex(map->UART_Index);

    if(((uint32_t)pUART == UART0_BASE) || ((uint32_t)pUART == UART1_BASE))
    {
        clock = g_Clocks_Freq.SystemCoreClock; //UART0 UART1使用CoreClock
    }
    else
    {
        clock = g_Clocks_Freq.BusClock;
    }

    sbr = (uint16_t) ((clock)/(baud*16));
    brfa = ((clock*2)/baud-(sbr*32));


    RxPort = FindPortFromIndex(map->Rx_GPIO_Index);
    TxPort = FindPortFromIndex(map->Tx_GPIO_Index);
    /* 使能PORT */
    PortEnableFromIndex(map->Rx_GPIO_Index);
    PortEnableFromIndex(map->Tx_GPIO_Index);

    RxPort->PCR[map->Rx_Pin_Index] = PORT_PCR_MUX(map->Rx_Alt_Index);
    TxPort->PCR[map->Tx_Pin_Index] = PORT_PCR_MUX(map->Tx_Alt_Index);


    UARTEnableFromIndex(map->UART_Index);

    //配置uart控制寄存器，实现基本的八位传输功能
    pUART->C2 &= ~(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //禁止发送接受,参见手册1221页
    pUART->C1 = 0;


    pUART->S2 &= ~UART_S2_MSBF_MASK;//配置为最低位优先传输

    //配置传输频率
    pUART->BDH |= ((sbr>>8)&UART_BDH_SBR_MASK);//设置高5位的数据，参加手册1218页
    pUART->BDL = (sbr&UART_BDL_SBR_MASK);//设置低8位数据
    pUART->C4 |= brfa&(UART_BDL_SBR_MASK>>3);//设置小数位，参见手册1232页

    //接受中断使能
    pUART->C2 |= UART_C2_RIE_MASK; //开启接收中断，参见手册1221页

    if(((uint32_t)pUART == UART0_BASE) || ((uint32_t)pUART == UART1_BASE))
    {
        clock = g_Clocks_Freq.SystemCoreClock; //UART0 UART1使用CoreClock
    }

    if(pUART == UART0)
        NVIC_EnableIRQ(UART0_RX_TX_IRQn);
    else if(pUART == UART1)
        NVIC_EnableIRQ(UART1_RX_TX_IRQn);
    else if(pUART == UART2)
        NVIC_EnableIRQ(UART2_RX_TX_IRQn);
    else if(pUART == UART3)
        NVIC_EnableIRQ(UART3_RX_TX_IRQn);
    else if(pUART == UART4)
        NVIC_EnableIRQ(UART4_RX_TX_IRQn);
    else if(pUART == UART5)
        NVIC_EnableIRQ(UART5_RX_TX_IRQn);

    //使能接收器与发送器
    pUART->C2 |= (UART_C2_RE_MASK|UART_C2_TE_MASK);	 //开启数据发送接受,参见手册1221页
    return pUART;
}

/***********************************************************************************************
 功能：串口发送1个字节
 形参：uartch: 串口号
       ch    : 发送的数据
 返回：0
 详解：利用串口发送1个字符串
************************************************************************************************/
void UART_SendByte(UART_Type *UARTx, uint8_t ch)
{
    //等待发送缓冲区空，参见手册1223页
    while(!(UARTx->S1 & UART_S1_TDRE_MASK));
    //发送数据,参见手册1230页
    UARTx->D=(uint8_t)ch;
}
/***********************************************************************************************
 功能：串口发送N个字节
 形参：uartch  : 串口号
       buff    : 数据指针
			 len     : 数据长度
 返回：0
 详解：它可以用来发送一个文件
************************************************************************************************/
void UART_SendBytes (UART_Type *UARTx,uint8_t *buf,uint32_t len)
{
    uint32_t i;
    for(i=0; i<len; i++)
    {
        UART_SendByte(UARTx,buf[i]);
    }
}

/***********************************************************************************************
 功能：串口接受1个字节
 形参：uartch: 串口号
       ch:    接收到的字节
 返回：0失败  1 成功
 详解：此处采用查询的方式进行数据接收，有不利因素，尽量使用中断接收的方式
************************************************************************************************/
uint8_t UART_Receive(UART_Type *UARTx, uint8_t *ch)
{
    if((UARTx->S1 & UART_S1_RDRF_MASK)!= 0)//判断接收缓冲区是否满,参见手册1223页
    {
        *ch =(uint8_t)(UARTx->D);	//接受数据,参见手册1230页
        return 1; 			//接受成功
    }
    return 0;			//如果超时，接受失败
}



/*
 * Init all related hardware in here
 * rt_hw_serial_init() will register all supported USART device
 */
void rt_hw_usart_init()
{

    /* uart init */
#ifdef RT_USING_UART1

    /* register uart1 */
    rt_hw_serial_register(&uart1_device, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart1);
#endif

#ifdef RT_USING_UART2

    /* register uart2 */
    rt_hw_serial_register(&uart2_device, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart2);
#endif

#ifdef RT_USING_UART3


    /* register uart3 */
    rt_hw_serial_register(&uart3_device, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart3);
#endif

#ifdef RT_USING_UART4

    /* register uart4 */
    rt_hw_serial_register(&uart4_device, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart4);
#endif

#ifdef RT_USING_UART5

    /* register uart5 */
    rt_hw_serial_register(&uart5_device, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart5);
#endif
}
