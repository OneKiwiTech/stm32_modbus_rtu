/*
 * FreeModbus Libary: RT-Thread Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portevent.c,v 1.60 2013/08/13 15:07:05 Armink $
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "FreeRTOS.h"
#include "event_groups.h"

#if MB_SLAVE_RTU_ENABLED > 0
/* ----------------------- Variables ----------------------------------------*/
static EventGroupHandle_t xSlaveOsEvent_h;
static StaticEventGroup_t xSlaveOsEventGroup;

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortEventInit( void )
{
    xSlaveOsEvent_h = xEventGroupCreateStatic( &xSlaveOsEventGroup );

    return TRUE;
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
    xEventGroupSetBits(xSlaveOsEvent_h, eEvent);
    return TRUE;
}

BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 0xFFFFFFFF;

    /* waiting forever OS event */
    uxBits  = xEventGroupWaitBits(xSlaveOsEvent_h,
            EV_READY | EV_FRAME_RECEIVED | EV_EXECUTE | EV_FRAME_SENT,
            pdTRUE,
            pdFALSE,
            xTicksToWait );

    if (uxBits & EV_READY) {
        *eEvent = EV_READY;
    }else if (uxBits &EV_FRAME_RECEIVED) {
        *eEvent = EV_FRAME_RECEIVED;
    }else if (uxBits & EV_EXECUTE){
        *eEvent = EV_EXECUTE;
    }else if (uxBits & EV_FRAME_SENT) {
        *eEvent = EV_FRAME_SENT;
    }else {

    }
    
    return TRUE;
}

#endif /* MB_SLAVE_RTU_ENABLED */
