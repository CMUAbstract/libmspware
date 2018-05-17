LIB = libmspware

ifeq ($(TOOLCHAIN),gcc)
DEPS += libmspbuiltins
else # TOOLCHAIN == gcc 
CFLAGS += -I$(LIB_ROOT)/libmspbuiltins/src/include
LFLAGS += -L$(LIB_ROOT)/libmspbuiltins/bld/gcc
LIBS += -lmspbuiltins
endif # TOOLCHAIN != gcc


OBJECTS = \
	adc12_b.o \
	aes256.o \
	comp_e.o \
	crc32.o \
	crc.o \
	cs.o \
	dma.o \
	esi.o \
	eusci_a_spi.o \
	eusci_a_uart.o \
	eusci_b_i2c.o \
	eusci_b_spi.o \
	framctl.o \
	gpio.o \
	lcd_c.o \
	mpu.o \
	mpy32.o \
	pmm.o \
	ram.o \
	ref_a.o \
	rtc_b.o \
	rtc_c.o \
	sfr.o \
	sysctl.o \
	timer_a.o \
	timer_b.o \
	tlv.o \
	wdt_a.o \

# FAMILYDEF is defined by Maker
# This switch is not exhaustive, we has branches only for families we use so far
ifeq ($(FAMILYDEF),__MSP430FR__)
FAMILY_DIR = MSP430FR5xx_6xx
else ifeq ($(FAMILYDEF),__MSP430F__)
FAMILY_DIR = MSP430F5xx_6xx
else # FAMILYDEF
$(error Unsupported or unimplemented MCU family)
endif # FAMILYDEF

override SRC_ROOT = ../../src/$(FAMILY_DIR)

override CFLAGS += \
	-I$(SRC_ROOT) \
