#include "shell_cmd.h"
#include "stx_log.h"
#include "tx_api.h"
#include "tx_thread.h"

void shell_cmd_sleep(char *name)
{
	int sec = 0;
	if ((sec = atoi(name)) > 0) {
		tx_thread_sleep(sec * 1000);
	} else {
		stx_printf("task sleep n second\r\n");
	}
}
