CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

TARGET = firmware

LAB ?= Core/src/main.c

SRCS  = $(LAB)
SRCS += Core/src/system_clock.c
SRCS += Startup/startup_stm32f446xx.s

INCLUDES  = -ICore/include
INCLUDES += -ICore/src
INCLUDES += -IDrivers/CMSIS

DEFINES = -DSTM32F446xx

CPU   = -mcpu=cortex-m4
FPU   = -mfpu=fpv4-sp-d16
FLOAT = -mfloat-abi=hard
THUMB = -mthumb

CFLAGS  = $(CPU) $(FPU) $(FLOAT) $(THUMB)
CFLAGS += -std=c11
CFLAGS += -O0
CFLAGS += -g3
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
CFLAGS += $(INCLUDES)
CFLAGS += $(DEFINES)

LDFLAGS  = $(CPU) $(FPU) $(FLOAT) $(THUMB)
LDFLAGS += -TLinker/STM32F446RETx_FLASH.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += --specs=nano.specs
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,--print-memory-usage

OBJS = $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS)))

all: $(TARGET).elf $(TARGET).bin
	@$(SIZE) $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).map

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x8000000

.PHONY: all clean flash