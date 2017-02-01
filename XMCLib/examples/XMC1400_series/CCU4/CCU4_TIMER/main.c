/* =========================================================================== *
 * Copyright (c) 2015, Infineon Technologies AG                                *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 * Redistributions of source code must retain the above copyright notice, this *
 * list of conditions and the following disclaimer. Redistributions in binary  *
 * form must reproduce the above copyright notice, this list of conditions and *
 * the following disclaimer in the documentation and/or other materials        *
 * provided with the distribution. Neither the name of the copyright holders   *
 * nor the names of its contributors may be used to endorse or promote         *
 * products derived from this software without specific prior written          *
 * permission.                                                                 *
 *                                                                                                                                                                                                                                                                                                                   *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       *
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      *
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR           *
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; *
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    *
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     *
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF      *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                  *
 * To improve the quality of the software, users are encouraged to share       *
 * modifications, enhancements or bug fixes with                               *
 * Infineon Technologies AG (dave@infineon.com).                               *
 *                                                                             *
 * ========================================================================== */

/**
 * @file
 * @date 08 October, 2015
 * @version 1.0.0
 *
 * @brief CCU4 demo example
 *
 * Synchronous start of CC4 slices using SCU and CCU4 drivers.
 * In this example, a CCU4 Slice is operated in a Single-shot Timer mode.
 * The start of the timer is triggered by an external event mapped to EVENT-1 of the slice.
 * The external event is generated by the SCU.
 * The timer generates 2 interrupts, one each for Compare match and Period match. The
 * interrupt counters for the respective interrupts are incremented in the ISRs.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_ccu4.h>
#include <xmc_scu.h>

/*********************************************************************************************************************
  * MACROS
********************************************************************************************************************/
#define SLICE_PTR         CCU40_CC41
#define MODULE_PTR        CCU40
#define MODULE_NUMBER     (0U)
#define SLICE_NUMBER      (1U)
#define CAPCOM_MASK       (1U) /**< Only CCU40 */

/*********************************************************************************************************************
  * GLOBAL DATA
********************************************************************************************************************/

XMC_CCU4_SLICE_COMPARE_CONFIG_t g_timer_object =
{
  .timer_mode 		   = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot   		   = true,
  .shadow_xfer_clear   = 0U,
  .dither_timer_period = 0U,
  .dither_duty_cycle   = 0U,
  .prescaler_mode	   = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable		   = 0U,
  .prescaler_initval   = 0U,
  .float_limit		   = 0U,
  .dither_limit		   = 0U,
  .passive_level 	   = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = 0U
};

/* CCU Slice Capture Initialization Data */
XMC_CCU4_SLICE_CAPTURE_CONFIG_t g_capture_object =
{
  .fifo_enable 		   = (uint32_t) false,
  .timer_clear_mode    = (uint32_t) XMC_CCU4_SLICE_TIMER_CLEAR_MODE_NEVER,
  .same_event          = (uint32_t) false,
  .ignore_full_flag    = (uint32_t) false,
  .prescaler_mode	   = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .prescaler_initval   = (uint32_t) 0,
  .float_limit		   = (uint32_t) 0,
  .timer_concatenation = (uint32_t) false
};

/* Interrupt counters */
volatile uint32_t g_num_period_interrupts;
volatile uint32_t g_num_compare_interrupts;
volatile bool period_match;

/*********************************************************************************************************************
  * MAIN APPLICATION
********************************************************************************************************************/

/* Interrupt handlers */
void IRQ0_Handler(void)
{
  g_num_period_interrupts++;
  XMC_CCU4_SLICE_ClearEvent(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  period_match = true;
}

void IRQ7_Handler(void)
{
  g_num_compare_interrupts++;
  XMC_SCU_SetCcuTriggerLow(CAPCOM_MASK);
  XMC_CCU4_SLICE_ClearEvent(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
}


int main(void)
{
  /* Local variable which holds configuration of Event-1 */
  XMC_CCU4_SLICE_EVENT_CONFIG_t config;

  config.duration = XMC_CCU4_SLICE_EVENT_FILTER_5_CYCLES;
  config.edge     = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE;
  config.level    = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH; /* Not needed */
  config.mapped_input = 8;

  /* Ensure fCCU reaches CCU42 */
  XMC_CCU4_SetModuleClock(MODULE_PTR, XMC_CCU4_CLOCK_SCU);

  XMC_CCU4_Init(MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  /* Get the slice out of idle mode */
  XMC_CCU4_EnableClock(MODULE_PTR, SLICE_NUMBER);

  /* Start the prescaler and restore clocks to slices */
  XMC_CCU4_StartPrescaler(MODULE_PTR);

  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(SLICE_PTR, &g_timer_object);

  /* Enable compare match and period match events */
  XMC_CCU4_SLICE_EnableEvent(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  XMC_CCU4_SLICE_EnableEvent(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);

  /* Connect period match event to SR0 */
  XMC_CCU4_SLICE_SetInterruptNode(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);

  /* Connect compare match event to SR1 */
  XMC_CCU4_SLICE_SetInterruptNode(SLICE_PTR, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP, XMC_CCU4_SLICE_SR_ID_1);


  /* Configure NVIC */
  /* Interrupt Multiplexer configuration */
  XMC_SCU_SetInterruptControl(0, XMC_SCU_IRQCTRL_CCU40_SR0_IRQ0);
  XMC_SCU_SetInterruptControl(7, XMC_SCU_IRQCTRL_CCU40_SR1_IRQ7);

  /* Set priority */
  NVIC_SetPriority(IRQ0_IRQn, 3U);
  NVIC_SetPriority(IRQ7_IRQn, 3U);

  /* Enable IRQ */
  NVIC_EnableIRQ(IRQ0_IRQn);
  NVIC_EnableIRQ(IRQ7_IRQn);

  /* Program a very large value into PR and CR */
  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE_PTR, 65500U);
  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE_PTR, 32000U);


  /* Enable shadow transfer */
  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, XMC_CCU4_SHADOW_TRANSFER_SLICE_1);

  /* Configure Event-1 and map it to Input-I */
  XMC_CCU4_SLICE_ConfigureEvent(SLICE_PTR, XMC_CCU4_SLICE_EVENT_1, &config);

  /* Map Event-1 to Start function */
  XMC_CCU4_SLICE_StartConfig(SLICE_PTR, XMC_CCU4_SLICE_EVENT_1, XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR);

  /* Generate an external start trigger */
  XMC_SCU_SetCcuTriggerHigh(CAPCOM_MASK);

  period_match = false;

  while(1U)
  {
    while(false == period_match);

    period_match = false;

    /* Generate an external start trigger */
    XMC_SCU_SetCcuTriggerHigh(CAPCOM_MASK);
  }

}