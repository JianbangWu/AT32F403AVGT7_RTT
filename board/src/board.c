/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-08     shelton      first version
 */

#include "board.h"

void system_clock_config(void)
{
  /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

  /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_60, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* config hext division */
  crm_hext_clock_div_set(CRM_HEXT_DIV_2);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}

void clock_information(void)
{
  system_core_clock_update();
  crm_clocks_freq_type crm_clocks;
  crm_clocks_freq_get(&crm_clocks);
  rt_kprintf("System Clock information\r\n");
  rt_kprintf("SYSCLK_Frequency = %d\r\n", (int)crm_clocks.sclk_freq);
  rt_kprintf("HCLK_Frequency   = %d\r\n", (int)crm_clocks.ahb_freq);
  rt_kprintf("PCLK1_Frequency  = %d\r\n", (int)crm_clocks.apb1_freq);
  rt_kprintf("PCLK2_Frequency  = %d\r\n", (int)crm_clocks.apb2_freq);
}
MSH_CMD_EXPORT(clock_information, clock info);

static rt_err_t i2c_search_device()
{
  struct rt_i2c_bus_device *bus = rt_device_find("i2c1");
  uint8_t reg = 0xA7;

  rt_pin_mode(rt_pin_get("PE.1"), PIN_MODE_OUTPUT);

  rt_pin_write(rt_pin_get("PE.1"), PIN_LOW);
  rt_thread_mdelay(10);
  rt_pin_write(rt_pin_get("PE.1"), PIN_HIGH);
  rt_thread_mdelay(30);

  for (uint16_t i = 0; i < 0x7F; i++)
  {
    struct rt_i2c_msg msgs;

    msgs.addr = i;
    msgs.flags = RT_I2C_WR;
    msgs.buf = &reg;
    msgs.len = 1;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
      rt_kprintf("Found I2C Device Addr = %X\r\n", i);
    }
  }
}
MSH_CMD_EXPORT(i2c_search_device, search device);