
						LUFA- Library

This package contains the device version of the open-source USB LUFA library for use with 
XMC microcontrollers.

LUFA is a simple to use, lightweight framework which allows for the
quick and easy creation of complex USB applications.


The LUFA Library has many advantages over implementing the code required to drive the XMC USB directly.
It is much more preferable to incorporate LUFA into your existing projects - or even make a new project 
using LUFA - than it is to start from scratch and use the XMC USB registers directly. 

Some of these reasons are:

Speed of Development: LUFA ships with a wide range of pre-made demos
and projects for you to try, learn and extend. 
In addition, there are inbuilt class drivers for several of the USB classes which you can make use of 
in your projects with minimal effort.

Maintainability: As LUFA takes care of much of the USB implementation, you can be left to focusing 
on your actual project's functionality, rather than being held back developing and debugging the USB stack code. 
Since LUFA uses clear APIs for USB development, your code will be more readable than if it had 
the low level USB stack code integrated into it directly. Updating the LUFA library is a simple folder-replacement 
and gives new features and bug fixes in seconds each time a new release is made.

Size: Not just requiring less code to make complex USB devices, LUFA is written to compile down as much as possible 
into optimal code, to occupy only a small space for its feature set.

Support: Since many people are now using LUFA in their own projects, 
you can take advantage of other's knowledge when you run into difficulties or need some advice. 


Please, include the USB folder in your project in order to create your application. 

======================
== REVISION HISTORY ==
======================

XMC USB Library v1.0.0
--------------------------------------------
  - Initial version

XMC USB Library v1.0.2   (06-05-2016)
--------------------------------------------
  - Optimizations for memcpy and bit reversal.
  - Updated examples.
  - Added DAVE project files.