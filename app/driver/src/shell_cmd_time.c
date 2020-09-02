#include "shell_cmd.h"
#include "stx_log.h"

void shell_cmd_time(char *name)
{
	int total_task_run_time = STX_SHELL_GTE_TIME / 1000;
	stx_printf("\r\nsystem run %dh_%dm_%ds\r\n", total_task_run_time/3600, total_task_run_time/60%60, total_task_run_time%60);
}

