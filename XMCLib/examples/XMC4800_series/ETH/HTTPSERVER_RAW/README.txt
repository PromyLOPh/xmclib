Description of example project
==============================

HTTPSERVER

This is a demonstration of how to make the most basic kind of server using lWIP.

* httpd.c - uses,
  - the raw API
  - the system timer to  to have certain functions called at regular intervals to 
    perform house-keeping tasks, such as handling TCP timeouts, retransmissions and so forth.
  - Uses CGI and SSI

* fsdata.c is the flash file system, generated from the makefsdata folder using the makefsdata utility
  - to generate new content for the server, 
    1. place your web content in the folder fs of makefsdata folder
    2. run makefsdata without arguments
    3. copy fsdata.c to the folder httpserver_raw using name fsdata.dat

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
   "${workspace_loc:/${ProjName}/httpserver_raw}"

   The following macors need to be defined in the compiler settings:
     XMC_ETH_PHY_KSZ8081RNB
     
b. Compile and flash the application onto the device
c. Run the application. 

The IP address of the board is manual configured using 192.168.0.10.
Reconfigure PC network address to something like 192.168.0.11. 
Direct your web browser at 192.168.0.10, a welcome message should be displayed.
Pressing the buttons toggles the LED1 and LED2 of the Relaxkit.