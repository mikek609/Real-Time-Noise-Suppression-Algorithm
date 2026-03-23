TARGET = blink_led

CPP_SOURCES = src/blink_led.cpp

# Library Locations
LIBDAISY_DIR = ./libDaisy
DAISYSP_DIR = ./DaisySP

# CMSIS-DSP
CMSIS_DSP = $(LIBDAISY_DIR)/Drivers/CMSIS-DSP

C_INCLUDES += -I$(CMSIS_DSP)/Include
C_INCLUDES += -I$(CMSIS_DSP)/Include/dsp
C_INCLUDES += -I$(CMSIS_DSP)/PrivateInclude

C_SOURCES += $(CMSIS_DSP)/Source/TransformFunctions/TransformFunctions.c
C_SOURCES += $(CMSIS_DSP)/Source/CommonTables/CommonTables.c
C_SOURCES += $(CMSIS_DSP)/Source/ComplexMathFunctions/ComplexMathFunctions.c
C_SOURCES += $(CMSIS_DSP)/Source/BasicMathFunctions/BasicMathFunctions.c
C_SOURCES += $(CMSIS_DSP)/Source/WindowFunctions/WindowFunctions.c

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile