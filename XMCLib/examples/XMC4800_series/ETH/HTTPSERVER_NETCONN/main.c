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

#include "xmc_gpio.h"
#include "cmsis_os.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "ethernetif.h"
#include "httpserver_netconn/httpserver-netconn.h"

#if LWIP_DHCP == 1
#include <lwip/dhcp.h>
#endif

#define LED1 P5_9

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

extern struct netif xnetif;

void LWIP_Init(void)
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

  /* Create tcp_ip stack thread */
  tcpip_init( NULL, NULL );

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
  netif_add(&xnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

  /*  Registers the default network interface.*/
  netif_set_default(&xnetif);

#if LWIP_NETIF_STATUS_CALLBACK == 1
  /* Initialize interface status change callback */
  netif_set_status_callback(&xnetif, ETH_NETIF_STATUS_CB_FUNCTION);
#endif
}

void led1_task(void const *args)
{
  while(1)
  {
    XMC_GPIO_ToggleOutput(LED1);
    osDelay(500);
  }
}
osThreadDef(led1_task, osPriorityNormal, 1, 0);


void main_task(void const *args)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  LWIP_Init();
  http_server_netconn_init();

  osThreadCreate(osThread(led1_task), NULL);
}
osThreadDef(main_task, osPriorityNormal, 1, 0);

int main(void)
{
  osKernelInitialize();

  osThreadCreate(osThread(main_task), NULL);

  osKernelStart();
}
