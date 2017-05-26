Description of example project
==============================

HTTPSERVER

This is a demonstration of how to make the most basic kind 
of server using lWIP.

* httpserver-netconn.c - uses netconn and netbuf API

Hardware Setup
===============
XMC4500 Relaxkit 

How to test the application
============================
a. Copy the files to a new project
   The following directories need to be added to the compiler include paths:
   "${workspace_loc:/${ProjName}/cmsis_rtos_rtx/INC}"
   "${workspace_loc:/${ProjName}/cmsis_rtos_rtx/SRC}"
   "${workspace_loc:/${ProjName}/lwip/include}"
   "${workspace_loc:/${ProjName}/lwip/include/ipv4}"
   "${workspace_loc:/${ProjName}/lwip/port/cmsis-rtos/include}"
   "${workspace_loc:/${ProjName}/lwip/port/cmsis-rtos/netif}"
   "${workspace_loc:/${ProjName}/httpserver_netconn}"
     
   The following macors need to be defined in the compiler settings:
     __CORTEX_M4F
     __FPU_PRESENT
     __CMSIS_RTOS
     XMC_ETH_PHY_KSZ8081RNB

b. In the folder cmsis_rtos_rtx keep only the targer compiler folder, i.e. GCC  
c. Compile and flash the application onto the device
d. Run the application. 

The IP address of the board is manual configured using 192.168.0.10.
Reconfigure PC network address to something like 192.168.0.11. 
Direct your web browser at 192.168.0.10, a welcome message should be displayed.

NOTE: New batch of Relaxkit boards are using ksz8081 instead of ksz8031. 
      If the application hangs in the ethernetif_error function, please use the ksz8031 by replacing the C macro XMC_ETH_PHY_KSZ8081RNB by XMC_ETH_PHY_KSZ8031RNL in compiler settings.