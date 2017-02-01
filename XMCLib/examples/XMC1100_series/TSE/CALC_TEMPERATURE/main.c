/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 9 November,2015
 * @version 1.0.0
 *
 * @brief TSE example, ROM function to calculate internal temperature
 *
 *
 * History
 *
 * Version 1.0.0 Initial
 */

#include <stdio.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>

#define TICKS_PER_SECOND 10000
#define LED1 P4_0

void SysTick_Handler(void)
{
  static uint32_t ticks = 0U;
  static uint32_t chip_temperature;

  ++ticks;
  if (ticks == TICKS_PER_SECOND)
  {
    ticks = 0U;
    XMC_GPIO_ToggleOutput(LED1);

    XMC_SCU_StartTempMeasurement();
    while (XMC_SCU_IsTempMeasurementDone() == false);
    chip_temperature = XMC_SCU_CalcTemperature();

    printf("Chip temperature: %d\n", chip_temperature);
  }
}

extern void initialise_monitor_handles(void);

int main(void)
{
  initialise_monitor_handles();

  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U);
}
