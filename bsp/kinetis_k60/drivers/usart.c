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
        ���ڵĶ�Ӧ��ϵ
        UART_Index: 0 - 5
        Rx_GPIO_Index: 0 - 4 (����A-E)
        Rx_Pin_Index:  0 - 31
        Rx_Alt_Index:  0 - 7

        Tx_GPIO_Index: 0 - 4 (����A-E)
        Tx_Pin_Index:  0 - 31
        Tx_Alt_Index:  0 - 7

*/
typedef struct
{
    uint32_t UART_Index:4;//ռ4bit
    uint32_t Rx_GPIO_Index:4;//ռ4bit
    uint32_t Rx_Pin_Index:6;//ռ6bit
    uint32_t Rx_Alt_Index:4;//ռ4bit
    uint32_t Tx_GPIO_Index:4;//ռ4bit
    uint32_t Tx_Pin_Index:6;//ռ6bit
    uint32_t Tx_Alt_Index:4;//ռ4bit
} UART_Map_t;  //����32bit

/*
    �������ܿ��������Ӧ��ӳ���ϵ
*/
static const UART_Map_t cUART_Maps[13] =
{
    {0, 0, 1, 2, 0, 2, 2},  /* UART0, RxPORT PORTA, PIN1, MUX_2, TxPORT PORTA, PIN2, MUX_2, ������ */
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


/* ��������Ѱ�Һ��ʵ�PORT */
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

/* ��������Ѱ�Һ��ʵĴ��� */
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


/* ����������ʹ��PORT */
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

/* ��������ʹ�ܴ���ʱ��  */
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


//UART ��ʼ��
UART_Type* UART_Init(uint32_t UARTxMap, uint32_t baud)
{
    //���д������ʼ���
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

    //�����ڱ��в鵽��
    if(!isFound)
    {
        return NULL;
    }

    pUART = FindUARTFromIndex(map->UART_Index);

    if(((uint32_t)pUART == UART0_BASE) || ((uint32_t)pUART == UART1_BASE))
    {
        clock = g_Clocks_Freq.SystemCoreClock; //UART0 UART1ʹ��CoreClock
    }
    else
    {
        clock = g_Clocks_Freq.BusClock;
    }

    sbr = (uint16_t) ((clock)/(baud*16));
    brfa = ((clock*2)/baud-(sbr*32));


    RxPort = FindPortFromIndex(map->Rx_GPIO_Index);
    TxPort = FindPortFromIndex(map->Tx_GPIO_Index);
    /* ʹ��PORT */
    PortEnableFromIndex(map->Rx_GPIO_Index);
    PortEnableFromIndex(map->Tx_GPIO_Index);

    RxPort->PCR[map->Rx_Pin_Index] = PORT_PCR_MUX(map->Rx_Alt_Index);
    TxPort->PCR[map->Tx_Pin_Index] = PORT_PCR_MUX(map->Tx_Alt_Index);


    UARTEnableFromIndex(map->UART_Index);

    //����uart���ƼĴ�����ʵ�ֻ����İ�λ���书��
    pUART->C2 &= ~(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //��ֹ���ͽ���,�μ��ֲ�1221ҳ
    pUART->C1 = 0;


    pUART->S2 &= ~UART_S2_MSBF_MASK;//����Ϊ���λ���ȴ���

    //���ô���Ƶ��
    pUART->BDH |= ((sbr>>8)&UART_BDH_SBR_MASK);//���ø�5λ�����ݣ��μ��ֲ�1218ҳ
    pUART->BDL = (sbr&UART_BDL_SBR_MASK);//���õ�8λ����
    pUART->C4 |= brfa&(UART_BDL_SBR_MASK>>3);//����С��λ���μ��ֲ�1232ҳ

    //�����ж�ʹ��
    pUART->C2 |= UART_C2_RIE_MASK; //���������жϣ��μ��ֲ�1221ҳ

    if(((uint32_t)pUART == UART0_BASE) || ((uint32_t)pUART == UART1_BASE))
    {
        clock = g_Clocks_Freq.SystemCoreClock; //UART0 UART1ʹ��CoreClock
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

    //ʹ�ܽ������뷢����
    pUART->C2 |= (UART_C2_RE_MASK|UART_C2_TE_MASK);	 //�������ݷ��ͽ���,�μ��ֲ�1221ҳ
    return pUART;
}

/***********************************************************************************************
 ���ܣ����ڷ���1���ֽ�
 �βΣ�uartch: ���ں�
       ch    : ���͵�����
 ���أ�0
 ��⣺���ô��ڷ���1���ַ���
************************************************************************************************/
void UART_SendByte(UART_Type *UARTx, uint8_t ch)
{
    //�ȴ����ͻ������գ��μ��ֲ�1223ҳ
    while(!(UARTx->S1 & UART_S1_TDRE_MASK));
    //��������,�μ��ֲ�1230ҳ
    UARTx->D=(uint8_t)ch;
}
/***********************************************************************************************
 ���ܣ����ڷ���N���ֽ�
 �βΣ�uartch  : ���ں�
       buff    : ����ָ��
			 len     : ���ݳ���
 ���أ�0
 ��⣺��������������һ���ļ�
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
 ���ܣ����ڽ���1���ֽ�
 �βΣ�uartch: ���ں�
       ch:    ���յ����ֽ�
 ���أ�0ʧ��  1 �ɹ�
 ��⣺�˴����ò�ѯ�ķ�ʽ�������ݽ��գ��в������أ�����ʹ���жϽ��յķ�ʽ
************************************************************************************************/
uint8_t UART_Receive(UART_Type *UARTx, uint8_t *ch)
{
    if((UARTx->S1 & UART_S1_RDRF_MASK)!= 0)//�жϽ��ջ������Ƿ���,�μ��ֲ�1223ҳ
    {
        *ch =(uint8_t)(UARTx->D);	//��������,�μ��ֲ�1230ҳ
        return 1; 			//���ܳɹ�
    }
    return 0;			//�����ʱ������ʧ��
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
