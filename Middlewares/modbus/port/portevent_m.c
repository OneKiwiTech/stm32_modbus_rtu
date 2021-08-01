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

#include "mbconfig.h"

#if MB_MASTER_RTU_ENABLED > 0
/* ----------------------- Variables ----------------------------------------*/
static EventGroupHandle_t xMasterOsEvent_h;
static StaticEventGroup_t xMasterOsEventGroup;

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBMasterPortEventInit( void )
{
    xMasterOsEvent_h = xEventGroupCreateStatic( &xMasterOsEventGroup );

    return TRUE;
}

BOOL
xMBMasterPortEventPost( eMBMasterEventType eEvent )
{
    xEventGroupSetBits(xMasterOsEvent_h, eEvent);
    return TRUE;
}

BOOL
xMBMasterPortEventGet( eMBMasterEventType * eEvent )
{
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

    /* waiting forever OS event */
    uxBits  = xEventGroupWaitBits(xMasterOsEvent_h,
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

#endif
