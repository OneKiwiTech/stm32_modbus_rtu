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
#include "semphr.h"
#include "cmsis_os.h"

#include "mbconfig.h"
#include "mb_m.h"

#if MB_MASTER_RTU_ENABLED > 0
/* ----------------------- Variables ----------------------------------------*/
static EventGroupHandle_t xMasterOsEvent_h;
static StaticEventGroup_t xMasterOsEventGroup;

static EventGroupHandle_t xWaitReqEvent_h;
static StaticEventGroup_t xMasterWaitReqEventGroup;

static osSemaphoreDef_t   mbEvtSemp_m;
static SemaphoreHandle_t  mbEvtSempId_m;
/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBMasterPortEventInit( void )
{
    xMasterOsEvent_h = xEventGroupCreateStatic( &xMasterOsEventGroup );
    xWaitReqEvent_h = xEventGroupCreateStatic( &xMasterWaitReqEventGroup );

    return TRUE;
}

BOOL
xMBMasterPortEventPost( eMBMasterEventType eEvent )
{
	BaseType_t pxTaskWoken = pdFALSE;

    xEventGroupSetBitsFromISR(xMasterOsEvent_h, eEvent, &pxTaskWoken);

    if ( pxTaskWoken ){
    	taskYIELD();
    }

    return TRUE;
}

BOOL
xMBMasterPortEventGet( eMBMasterEventType * eEvent )
{
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 0xFFFFFFFF;

    /* waiting forever OS event */
    uxBits  = xEventGroupWaitBits(xMasterOsEvent_h,
            EV_MASTER_READY | EV_MASTER_FRAME_RECEIVED | EV_MASTER_EXECUTE |
            EV_MASTER_FRAME_SENT | EV_MASTER_ERROR_PROCESS,
            pdTRUE,
            pdFALSE,
            xTicksToWait );

    if (uxBits & EV_MASTER_READY) {
        *eEvent = EV_MASTER_READY;
    }else if (uxBits & EV_MASTER_FRAME_RECEIVED) {
        *eEvent = EV_MASTER_FRAME_RECEIVED;
    }else if (uxBits & EV_MASTER_EXECUTE){
        *eEvent = EV_MASTER_EXECUTE;
    }else if (uxBits & EV_MASTER_FRAME_SENT) {
        *eEvent = EV_MASTER_FRAME_SENT;
    }else if (uxBits & EV_MASTER_FRAME_SENT) {
        *eEvent = EV_MASTER_FRAME_SENT;
    }else {

    }

    return TRUE;
}



/**
 * This function is initialize the OS resource for modbus master.
 * Note:The resource is define by OS.If you not use OS this function can be empty.
 *
 */
void vMBMasterOsResInit( void )
{
	mbEvtSempId_m = osSemaphoreCreate(&mbEvtSemp_m, 1);
}



/**
 * This function is take Mobus Master running resource.
 * Note:The resource is define by Operating System.If you not use OS this function can be just return TRUE.
 *
 * @param lTimeOut the waiting time.
 *
 * @return resource taked result
 */
BOOL xMBMasterRunResTake( LONG lTimeOut )
{
	const TickType_t xTicksToWait = lTimeOut / portTICK_PERIOD_MS;
    /*If waiting time is -1 .It will wait forever */
    return (osSemaphoreWait(mbEvtSempId_m, xTicksToWait) == 0);
}

/**
 * This function is release Mobus Master running resource.
 * Note:The resource is define by Operating System.If you not use OS this function can be empty.
 *
 */
void vMBMasterRunResRelease( void )
{
    /* release resource */
	osSemaphoreRelease(mbEvtSempId_m);
}


/**
 * This is modbus master request process success callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 */
void vMBMasterCBRequestScuuess( void ) {
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
	BaseType_t  xIsTaskWoken = pdFALSE;

    xEventGroupSetBitsFromISR(xWaitReqEvent_h, EV_MASTER_PROCESS_SUCESS, &xIsTaskWoken);

    if ( xIsTaskWoken )
    {
    	taskYIELD();
    }

    /* You can add your code under here. */

}

/**
 * This is modbus master respond timeout error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBRespondTimeout(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength) {
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
	BaseType_t  xIsTaskWoken = pdFALSE;

    xEventGroupSetBitsFromISR(xWaitReqEvent_h, EV_MASTER_ERROR_RESPOND_TIMEOUT, &xIsTaskWoken);

    if ( xIsTaskWoken )
    {
    	taskYIELD();
    }
    /* You can add your code under here. */

}

/**
 * This is modbus master receive data error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBReceiveData(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength) {
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
	BaseType_t  xIsTaskWoken = pdFALSE;

    xEventGroupSetBitsFromISR(xWaitReqEvent_h, EV_MASTER_ERROR_RECEIVE_DATA, &xIsTaskWoken);

    if ( xIsTaskWoken )
    {
    	taskYIELD();
    }
    /* You can add your code under here. */

}

/**
 * This is modbus master execute function error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBExecuteFunction(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength) {
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
	BaseType_t  xIsTaskWoken = pdFALSE;

    xEventGroupSetBitsFromISR(xWaitReqEvent_h, EV_MASTER_ERROR_EXECUTE_FUNCTION, &xIsTaskWoken);

    if ( xIsTaskWoken )
    {
    	taskYIELD();
    }
    /* You can add your code under here. */

}


/**
 * This function is wait for modbus master request finish and return result.
 * Waiting result include request process success, request respond timeout,
 * receive data error and execute function error.You can use the above callback function.
 * @note If you are use OS, you can use OS's event mechanism. Otherwise you have to run
 * much user custom delay for waiting.
 *
 * @return request error code
 */
eMBMasterReqErrCode eMBMasterWaitRequestFinish( void ) {
    eMBMasterReqErrCode    eErrStatus = MB_MRE_NO_ERR;
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 0xFFFFFFFF;

    /* waiting forever OS event */
    uxBits  = xEventGroupWaitBits(xWaitReqEvent_h,
    		 EV_MASTER_PROCESS_SUCESS
			| EV_MASTER_ERROR_RESPOND_TIMEOUT
			| EV_MASTER_ERROR_RECEIVE_DATA
			| EV_MASTER_ERROR_EXECUTE_FUNCTION,
            pdTRUE,
            pdFALSE,
            xTicksToWait );

    /* waiting for OS event */
    if (uxBits & EV_MASTER_ERROR_RESPOND_TIMEOUT) {
    	eErrStatus = MB_MRE_TIMEDOUT;
    } else  if (uxBits & EV_MASTER_ERROR_RECEIVE_DATA) {
    	eErrStatus = MB_MRE_REV_DATA;
    } else  if (uxBits & EV_MASTER_ERROR_EXECUTE_FUNCTION) {
    	eErrStatus = MB_MRE_EXE_FUN;
    } else {

    }

    return eErrStatus;
}

#endif
