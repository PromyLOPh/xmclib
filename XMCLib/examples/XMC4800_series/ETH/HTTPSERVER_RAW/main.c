/*
 * Copyright (C) 2015-2016 Infineon Technologies AG. All rights reserved.
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
 * @date 07 August,2017
 * @version 1.2.0
 *
 * @brief ETH HTTP server demo example using the netconn interface
 *
 * History <br>
 *
 * Version 1.0.0 
 * - Initial
 *
 * Version 1.0.2
 * - Stability and speed improvements
 *
 * Version 1.1.0
 * - lwIP 2.0.2
 *
 * Version 1.2.0
 * - Changed the way the interface features are assigned
 * 
 */

#include <xmc_gpio.h>

#include <lwip/netif.h>
#include <lwip/init.h>
#include <lwip/timeouts.h>
#include <netif/etharp.h>
#include <ethernetif.h>
#include "httpserver_raw/httpd.h"

#if LWIP_DHCP == 1
#include <lwip/dhcp.h>
#endif

#define LED1 P5_9
#define LED2 P5_8

#define BUTTON1 P15_13
#define BUTTON2 P15_12

/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

#define BUTTONS_TMR_INTERVAL 100

int8_t bx = 0;

extern struct netif xnetif;

static void buttons_timer(void *arg)
{
  XMC_UNUSED_ARG(arg);

  if (XMC_GPIO_GetInput(BUTTON1) != 0)
  {
    bx++;
  }

  if (XMC_GPIO_GetInput(BUTTON2) != 0)
  {
    bx--;
  }

  sys_timeout(BUTTONS_TMR_INTERVAL, buttons_timer, NULL);
}

static void LWIP_Init(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#if LWIP_DHCP == 0
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#else
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#endif

  lwip_init();

  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))

  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.

  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  netif_add(&xnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /*  Registers the default network interface.*/
  netif_set_default(&xnetif);

  /* If callback enabled */
#if LWIP_NETIF_STATUS_CALLBACK == 1
  /* Initialize interface status change callback */
  netif_set_status_callback(&xnetif, ETH_NETIF_STATUS_CB_FUNCTION);
#endif
}

/* Initialisation of functions to be used with CGi*/
//  CGI handler to switch LED status
const char *ledcontrol_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  if(strcmp(pcValue[0], "led1") == 0)
  {
    XMC_GPIO_ToggleOutput(LED1);
  }
  else {
    XMC_GPIO_ToggleOutput(LED2);
  }
  return "/cgi.htm";
}

const char *data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  return "/data.ssi";
}

tCGI led_handler_struct[] =
{
  {
    .pcCGIName = "/ledcontrol.cgi",
    .pfnCGIHandler = ledcontrol_handler
  },
  {
   .pcCGIName = "/data.cgi",
   .pfnCGIHandler = data_handler
  }
};

int cgi_init(void)
{
  http_set_cgi_handlers(led_handler_struct, 2);

  return 0;
}

/**
 * Initialize SSI handlers
 */
const char *TAGS[]={"bx"};

static uint16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
  return (sprintf(pcInsert, "%d", bx));
}

void ssi_init(void)
{
  http_set_ssi_handler(ssi_handler, (char const **)TAGS, 1);
}

int main(void)
{
  XMC_GPIO_CONFIG_t config;
  
  config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

  XMC_GPIO_Init(BUTTON1, &config);
  XMC_GPIO_Init(BUTTON2, &config);
  
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  
  XMC_GPIO_Init(LED1, &config);
  XMC_GPIO_Init(LED2, &config);

  SysTick_Config(SystemCoreClock / 1000);

  LWIP_Init();
  httpd_init();
  cgi_init();
  ssi_init();

  sys_timeout(BUTTONS_TMR_INTERVAL, buttons_timer, NULL);

  while(1)
  {
    sys_check_timeouts();
  }
}
