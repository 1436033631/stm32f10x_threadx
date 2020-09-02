#include "shell_cmd.h"
#include "stx_log.h"
#include "tx_api.h"
#include "tx_thread.h"
#include "tx_mutex.h"

static void shell_ps_help(void)
{
	stx_printf("Usage: ps [tsk|mtx|sem|flg|msg|mem|all|irq|profile] ([option])\r\n");
	stx_printf("          tsk - Task info\r\n");
    stx_printf("          mtx - Mutex info\r\n");
    stx_printf("          sem - Semaphore info\r\n");
    stx_printf("          flg - Eventflag info\r\n");
    stx_printf("          msg - Message queue info\r\n");
    stx_printf("          mem - Memory pool info\r\n");
    stx_printf("          all - All the above info\r\n");
    stx_printf("          irq [reset|all|<id>] - IRQ info\r\n");
    stx_printf("          profile [reset] - profiler result\r\n");
}

int shell_cmd_ps(char *cmd_name)
{
	int ret = STX_NG;
	char cmd[8] = {0};
	char name[8] = {0};
	shell_cmd_cut(cmd_name, cmd, name);
	if(strstr(cmd, "tsk")) {
		show_tsk_info();
	} else if (strstr(cmd, "mtx")) {
		show_mutex_info();
	} else if (strstr(cmd, "sem")) {

	} else if (strstr(cmd, "mem")) {

	} else if (strstr(cmd, "flg")) {

	} else if (strstr(cmd, "msg")) {

	} else if (strstr(cmd, "all")) {

	} else if (strstr(cmd, "irq")) {

	} else if (strstr(cmd, "profile")) {
		show_profile();
	} else {
		shell_ps_help();
	}
	return ret;
}
