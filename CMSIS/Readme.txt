==================
== INTRODUCTION ==
==================

This folder contains the Cortex Microcontroller Software Interface Standard (CMSIS) v4.5.0.  
http://www.keil.com/pack/doc/CMSIS/General/html/index.html

==============
== CONTENTS ==
==============
In addition to the standard CMSIS components:
 - CMSIS-CORE
 - CMSIS-DSP
 - CMSIS-RTOS

Infineon provides the following content:
XMC Device CMSIS compliant header files
XMC Device CMSIS compliant startup files
XMC Device CMSIS compliant system initialization files
XMC linker files
XMC Device SVD files

======================
== REVISION HISTORY ==
======================

CMSIS v4.5.0p1 (06-04-2016)
--------------------------------------------
- Linker files: 
  1. Add assertion to prevent that region SRAM_combined overflows no_init section.
  2. Fix size of sections copied during initialization from FLASH to RAM to be multiple of 4. 
     It corrects wrong initialization of first variable in section.
- system_XMC4100.c: 
  1. Use correct macro name XMC4108_Q48x64.
     It corrects compilation problems.
  2. Initialization of g_hrpwm_char_data not done for XMC4108_Q48x64 and XMC4108_F64x64.
- startup_XMC410x.s, startup_XMC4200.s, startup_XMC440x.s, startup_XMC450x.s:
  1. Fix weak definition of Veneers when using ENABLE_CPU_CM_001_WORKAROUND.
     It corrects compilation problems.

CMSIS v4.5.0p2 (29-04-2016)
--------------------------------------------
- Changed:
  - system_XMC1100.c, system_XMC1200.c, system_XMC1300.c: 
    - Set flash wait states to 1 cycle
- Updated
  - XMC1300.svd, XMC1400.svd, XMC4300.svd/.h, XMC4700.svd/.h, XMC4800.svd/.h

CMSIS v4.5.0p3 (14-07-2016)
--------------------------------------------
- Changed:
  - Update of copyright notice (BSD like) for device header files and system files. 
- Fixed:
  - Masking of OSCHPCTRL value in system_*.c files for XMC4

CMSIS v4.5.0p4 (30-08-2016)
--------------------------------------------
- Changed:
  - Added support for new XMC1400 packages
  - Fixed waning linker messages when compiling for TLE devices