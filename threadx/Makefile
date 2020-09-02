# source director
THREADX_SRC_DIR      = $(THREADX_DIR)
THREADX_SRC_PORT_DIR = $(THREADX_DIR)/ports/cortex_m3/gnu
THREADX_INC_PORT_DIR = $(THREADX_DIR)/ports/cortex_m3/gnu/inc
THREADX_SRC_COMM_DIR = $(THREADX_DIR)/common
THREADX_INC_COMM_DIR = $(THREADX_DIR)/common/inc

# include directories
INCLUDE_DIRS += $(THREADX_INC_COMM_DIR)
INCLUDE_DIRS += $(THREADX_INC_PORT_DIR)

ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_context_restore.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_context_save.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_interrupt_control.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_schedule.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_stack_build.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_thread_system_return.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_timer_interrupt.S
ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_initialize_low_level_sample.S
#ASM_SRC  += $(THREADX_SRC_PORT_DIR)/src/tx_vector_table_sample.S

# add freertos source
SRC  += $(wildcard ${THREADX_SRC_COMM_DIR}/src/*.c)
# SRC  += ${THREADX_SRC_COMM_DIR}/src/tx_block_allocate.c

