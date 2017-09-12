Description of example project
==============================

SYSTEM_TIME

This is a demonstration of how to use the ETH System Time.

Hardware Setup
===============
XMC4700/XMC4800 Relaxkit 

How to test the application
============================
a. Copy the files to a new project
   The following directories need to be added to the compiler include paths:
   "${workspace_loc:/${ProjName}/lwip/include}"
   "${workspace_loc:/${ProjName}/lwip/port/nosys/include}"
   "${workspace_loc:/${ProjName}/lwip/port/nosys/netif}"

   The following macors need to be defined in the compiler settings:
     XMC_ETH_PHY_KSZ8081RNB
     
b. Compile and flash the application onto the device
c. Run the application. 

The IP address of the board is manual configured using 192.168.0.10.
Reconfigure PC network address to something like 192.168.0.11. 
Direct your web browser at 192.168.0.10, a welcome message should be displayed.
Pressing the buttons toggles the LED1 and LED2 of the Relaxkit.