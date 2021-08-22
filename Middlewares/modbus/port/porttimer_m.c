/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
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
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
 
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "mb_m.h"
#include "mbconfig.h"

#if MB_MASTER_RTU_ENABLED > 0
/* ----------------------- static functions ---------------------------------*/
//static void prvvTIMERExpiredISR( void );

/* -----------------------    variables     ---------------------------------*/
extern TIM_HandleTypeDef htim7;
volatile USHORT usT35TimeOut50us = 0;
/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBMasterPortTimersInit( USHORT usTim1Timerout50us )
{
  TIM_MasterConfigTypeDef sMasterConfig;
  
  usT35TimeOut50us = usTim1Timerout50us;

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000) - 1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = (50 - 1) * usTim1Timerout50us;
  
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    return FALSE;
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    return FALSE;
  }
  
  return TRUE;
}
 
void vMBMasterPortTimersT35Enable()
{
  LONG timer_tick = (50 - 1) * usT35TimeOut50us;
    /* Set current timer mode, don't change it.*/
  vMBMasterSetCurTimerMode(MB_TMODE_T35);
   __HAL_TIM_SET_AUTORELOAD(&htim7, timer_tick);
   HAL_TIM_Base_Start_IT(&htim7);
}

void vMBMasterPortTimersConvertDelayEnable()
{
    LONG timer_tick = MB_MASTER_DELAY_MS_CONVERT;

    /* Set current timer mode, don't change it.*/
    vMBMasterSetCurTimerMode(MB_TMODE_CONVERT_DELAY);

     __HAL_TIM_SET_AUTORELOAD(&htim7, timer_tick);
    HAL_TIM_Base_Start_IT(&htim7);
}

void vMBMasterPortTimersRespondTimeoutEnable()
{
    LONG timer_tick = MB_MASTER_TIMEOUT_MS_RESPOND ;
  
    /* Set current timer mode, don't change it.*/
    vMBMasterSetCurTimerMode(MB_TMODE_RESPOND_TIMEOUT);
     __HAL_TIM_SET_AUTORELOAD(&htim7, timer_tick);
    HAL_TIM_Base_Start_IT(&htim7);
}

void
vMBMasterPortTimersDisable(  )
{
  /* Disable any pending timers. */
  HAL_TIM_Base_Stop_IT(&htim7);
}
 
/* Create an ISR which is called whenever the timer has expired. This function
* must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
* the timer has expired.
 */

//static void prvvTIMERExpiredISR( void )
//{
//( void )pxMBMasterPortCBTimerExpired(  );
//}


#endif /* MB_MASTER_RTU_ENABLED */
