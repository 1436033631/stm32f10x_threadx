# toolchain
TOOLCHAIN    = /usr/local/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-
CC           = $(TOOLCHAIN)gcc
CP           = $(TOOLCHAIN)objcopy
AS           = $(TOOLCHAIN)gcc
HEX          = $(CP) -O ihex
BIN          = $(CP) -O binary -S

# define mcu, specify the target processor
$(info build start stm32_threadx...)
MCU          = cortex-m3

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJECT_NAME=stm32f10x_rtos

# specify define
DDEFS       =

# define root dir
ROOT_DIR     = .

# define output dir
OUT_DIR     = output

# define include dir
INCLUDE_DIRS =

# define stm32f10x lib dir
STM32F10x_LIB_DIR      = $(ROOT_DIR)/stm32f10x_lib

# define threadx dir
THREADX_DIR  = $(ROOT_DIR)/threadx

# define guix dir
GUIX_DIR      = $(ROOT_DIR)/guix

# define user dir
APP_DIR      = $(ROOT_DIR)/app

# link file
LINK_SCRIPT  = $(ROOT_DIR)/stm32_flash.ld

# user specific
SRC       =
ASM_SRC   =

# user include
INCLUDE_DIRS  =

# include sub makefiles
include $(STM32F10x_LIB_DIR)/Makefile   # STM32 Standard Peripheral Library
include $(THREADX_DIR)/Makefile         # threadx source
#include $(GUIX_DIR)/Makefile            # guix source
include $(APP_DIR)/Makefile             # app source



INC_DIR  = $(patsubst %, -I%, $(INCLUDE_DIRS))

# run from Flash
DEFS	 = $(DDEFS) -DRUN_FROM_FLASH=1

OBJECTS  = $(ASM_SRC:.s=.o) $(SRC:.c=.o)

# Define optimisation level here
OPT = -Os

MC_FLAGS = -mcpu=$(MCU)

AS_FLAGS = $(MC_FLAGS) $(OPT) -g -gdwarf-2 -mthumb  #-Wa,-amhls=$(<:.s=.lst)
CP_FLAGS = $(MC_FLAGS) $(OPT) -g -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -fverbose-asm  $(DEFS) #-Wa,-ahlms=$(<:.c=.lst)
LD_FLAGS = $(MC_FLAGS) -g -gdwarf-2 -mthumb -nostartfiles -Xlinker --gc-sections -T$(LINK_SCRIPT) -Wl,-Map=$(PROJECT_NAME).map,--cref,--no-warn-mismatch
#
# makefile rules
#
all: $(OBJECTS) $(PROJECT_NAME).elf  $(PROJECT_NAME).hex $(PROJECT_NAME).bin
	$(TOOLCHAIN)size $(PROJECT_NAME).elf
	$(info build stm32_threadx success)

%.o: %.c
	$(CC) -c $(CP_FLAGS) -I . $(INC_DIR) $< -o $@

%.o: %.s
	$(AS) -c $(AS_FLAGS) $< -o $@

%.elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN)  $< $@

flash: $(PROJECT_NAME).bin
	st-flash write $(PROJECT_NAME).bin 0x8000000

erase:
	st-flash erase

clean:
	-rm -rf $(PROJECT_NAME).elf
	-rm -rf $(PROJECT_NAME).map
	-rm -rf $(PROJECT_NAME).hex
	-rm -rf $(PROJECT_NAME).bin
	-rm -rf $(SRC:.c=.o)
	-rm -rf $(STM32F10x_LIB_DIR)/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.o

