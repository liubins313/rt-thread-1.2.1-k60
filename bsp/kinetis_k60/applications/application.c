/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup Kinetis_k60
 */
/*@{*/

#include <stdio.h>
#include <board.h>
#include <rtthread.h>
#include "thread_sleep.h"
#include "components.h"
#include "rtt_ksz8041.h"

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_LWIP
    eth_system_device_init();
    rt_hw_ksz8041_init();
    lwip_system_init();
    rt_kprintf("TCP/IP initialized!\n");
#endif
}



int rt_application_init()
{
    rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

//    thread_sleep_init();

    return 0;
}

/*@}*/
