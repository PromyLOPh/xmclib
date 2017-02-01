EXAMPLE NAME: USBH_VCOM_XMC45

EXAMPLE REVISION HISTORY:
V1.0.0 initial version 

OVERVIEW: 
XMC4500 USB virtual COM port demo (serial port emulation)
This example demonstrates the implementation of a USB host stack supporting a CDC-ACM
class and emulating a virtual COM port (serial port). The USB stack is based on a open
source stack LUFA and the low level driver is based on the CMSIS USBH API.  

DESCRIPTION:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
chapter "Implementing the application"

REQUIREMENTS:
1) Two XMC4500 General Purpose board CPU_45A-V3
2) USB Cable - Micro A plug to Micro B plug
3) USB cable - Micro B plug to Standard A plug
3) Windows PC/Laptop installed with DAVE v4 (Version 4.1.4 or higher)
4) Serial port terminal Tera Term or equivalent.

EXAMPLE PROJECT SETUP:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
chapter "Implementing the application"

HOW TO CREATE THE PROJECT: 
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
chapter "Implementing the application"

HOW TO TEST:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
chapter "How to test"

OBSERVATIONS:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
chapter "How to test"

HINTS HOW TO MIGRATE EXAMPLE TO OTHER DEVICES:
Create project for the selected XMC device that supports USB.
The clock setup function is device specific. Please modify
ClockSetup() in main.c according to the selected device.
For XMC4400 the UART pins used should be changed to Rx P1.5
and TX P1.7 Alternate output function for P1.7 and input for DX0 channel
for P1.5 have to be changed. File uart.c, uart_init() has to be adapted. 

EXAMPLE PROJECT LIMITATIONS/KNOWN ISSUES:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"

REFERENCES:
Please see "Getting Started - XMC4500_USBH_VCOM_Example_V1.0.pdf"
inside root folder of the example project










