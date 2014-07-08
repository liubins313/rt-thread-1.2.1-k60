/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     bernard      first version
 * 2012-05-15     lgnq         modified according bernard's implementation.
 * 2012-05-28     bernard      code cleanup
 * 2012-11-23     bernard      fix compiler warning.
 * 2013-02-20     bernard      use RT_SERIAL_RB_BUFSZ to define
 *                             the size of ring buffer.
 */

#include <rthw.h>
#include <rtthread.h>
#include "uart.h"
#include "gpio.h"

#include "rtt_serial.h"
#include <rtdevice.h>

static struct rt_serial_device serial5;
static struct serial_ringbuffer uart5_int_rx;
static uint16_t *gRevCh = RT_NULL;

static void UART_ISR(uint16_t byteReceived)
{
//    static uint16_t ch;
    /* enter interrupt */
    rt_interrupt_enter();
//    ch = byteReceived;
    gRevCh = &byteReceived;
    rt_hw_serial_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t kinetis_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    uint32_t baudrate;
		UART_InitTypeDef UART_InitStruct1;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    UART_InitStruct1.instance = serial->config.reserved;
    
    switch(cfg->baud_rate)
    {
    case BAUD_RATE_9600:
        baudrate = 9600;
        break;
    case BAUD_RATE_115200:
        baudrate = 115200;
        break;
    }
    UART_QuickInit(UART0_RX_PD06_TX_PD07, baudrate);

    /* enable Tx hardware FIFO to enhance proformence */
    UART_EnableTxFIFO(UART_InitStruct1.instance, true);
    UART_SetTxFIFOWatermark(UART_InitStruct1.instance, UART_GetTxFIFOSize(HW_UART0));

    /* enable Rx IT */
    UART_CallbackRxInstall(UART_InitStruct1.instance, UART_ISR);
    UART_ITDMAConfig(UART_InitStruct1.instance, kUART_IT_Rx, true);
    return RT_EOK;
}

static rt_err_t kinetis_control(struct rt_serial_device *serial, int cmd, void *arg)
{

    RT_ASSERT(serial != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        UART_ITDMAConfig(serial->config.reserved, kUART_IT_Rx, false);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        UART_ITDMAConfig(serial->config.reserved, kUART_IT_Rx, true);
        break;
    }
    return RT_EOK;
}

static int kinetis_putc(struct rt_serial_device *serial, char c)
{
    UART_WriteByte(serial->config.reserved, c);
    return 1;
}

static int kinetis_getc(struct rt_serial_device *serial)
{
		int c;
     c = -1;
   
    if(gRevCh != RT_NULL)
    {
        c = *gRevCh;
        gRevCh = RT_NULL;
    }

    return c;
}

static const struct rt_uart_ops kinetis_uart_ops =
{
    kinetis_configure,
    kinetis_control,
    kinetis_putc,
    kinetis_getc,
};

int rt_hw_usart_init(void)
{
    struct serial_configure config;
    
    UART_QuickInit(UART5_RX_PD08_TX_PD09, 115200);

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.reserved  = HW_UART5;
    serial5.ops    = &kinetis_uart_ops;
    serial5.int_rx = &uart5_int_rx;
    serial5.config = config;

    return rt_hw_serial_register(&serial5, "uart5",
                                 RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                                 RT_NULL);
}
