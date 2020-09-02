#include "shell_cmd.h"
#include "stx_log.h"
#include"stm32f10x.h"
#include "core_cm3.h"

static void system_reboot(void)
{
	__disable_fault_irq();
	NVIC_SystemReset();
}
void shell_cmd_reboot(char *name)
{
	stx_printf("\r\nreboot ...\r\n");
	tx_thread_sleep(100);
	system_reboot();
}

