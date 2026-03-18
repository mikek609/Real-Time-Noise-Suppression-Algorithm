TARGET = noise_suppression

CPP_SOURCES = src/main.cpp

# Library Locations
LIBDAISY_DR = ~/daisy_prog/libDaisy
DAISYSP_DIR = ~/daisy_prog/DaisySP

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
