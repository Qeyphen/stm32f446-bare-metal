CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

ART ?= 1

TARGET = firmware

LAB ?= Core/src/main.c
OPT_LVL ?= -O0


SRCS  = $(LAB)
SRCS += Core/src/system_clock.c
SRCS += Startup/startup_stm32f446xx.s

INCLUDES  = -ICore/include
INCLUDES += -ICore/src
INCLUDES += -IDrivers/CMSIS

DEFINES = -DSTM32F446xx

ifeq ($(ART),0)
DEFINES += -DDISABLE_ART
endif

CPU   = -mcpu=cortex-m4
FPU   = -mfpu=fpv4-sp-d16
FLOAT = -mfloat-abi=hard
THUMB = -mthumb

CFLAGS  = $(CPU) $(FPU) $(FLOAT) $(THUMB)
CFLAGS += -std=c11
CFLAGS += $(OPT_LVL)
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

OBJS   = $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS)))
SRCS_C = $(filter %.c,$(SRCS))

# --- Formatting files (C + headers) ---
FORMAT_FILES = $(shell find Core Drivers -type f \( -name "*.c" -o -name "*.h" \))

# --- Build targets ---
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
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).map $(TARGET).asm

disasm: $(TARGET).elf
	arm-none-eabi-objdump -d $(TARGET).elf > $(TARGET).asm

flash: $(TARGET).bin
	@echo "Flashing with ART=$(ART) and OPT_LVL=$(OPT_LVL)"
	st-flash write $(TARGET).bin 0x8000000

format:
	clang-format -i $(FORMAT_FILES)

format-check:
	clang-format --dry-run --Werror $(FORMAT_FILES)

raw-toggle-on:
	$(MAKE) clean
	$(MAKE) LAB=Labs/raw_toggle/main.c ART=1 OPT_LVL=$(OPT_LVL) flash

raw-toggle-off:
	$(MAKE) clean
	$(MAKE) LAB=Labs/raw_toggle/main.c ART=0 OPT_LVL=$(OPT_LVL) flash

.PHONY: all clean flash format format-check raw-toggle-on raw-toggle-off