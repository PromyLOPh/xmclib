XMCLIB_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
XMCLIB_CMSIS := $(XMCLIB_DIR)/CMSIS
XMCLIB_SRC := $(wildcard $(XMCLIB_DIR)/XMCLib/src/*.c) \
	$(wildcard $(XMCLIB_DIR)/Newlib/*.c) \
	$(wildcard $(XMCLIB_CMSIS)/Infineon/$(UC)_series/Source/*.c) \
	$(XMCLIB_CMSIS)/Infineon/$(UC)_series/Source/GCC/startup_$(UC).S
XMCLIB_INC := \
	-D$(UC)_$(UC_TYPE)x$(UC_MEM) \
	-I$(XMCLIB_DIR)/XMCLib/inc \
	-I$(XMCLIB_CMSIS)/Include \
	-I$(XMCLIB_CMSIS)/Infineon/Include \
	-I$(XMCLIB_CMSIS)/Infineon/$(UC)_series/Include
CMSIS_SRC := $(CMSIS)/Infineon/$(UC)_series/Source/
XMCLIB_LINKERSCRIPT := $(CMSIS_SRC)/GCC/$(UC)x$(UC_MEM).ld
XMCLIB_VERSION := 2.1.8
$(info Using xmclib version $(XMCLIB_VERSION) $(XMCLIB_DIR))
