#include "shell_cmd_ps.h"
#include "stx_log.h"
#include "tx_api.h"

static void show_tsk_info(void)
{
	Stx_Msg_Info(">>>");
}

int shell_cmd_ps(char *cmd_name)
{
	int ret = STX_NG;
	char cmd[8] = {0};
	char name[8] = {0};
	shell_cmd_parser(cmd_name, cmd, name);
	switch(cmd) {
		case "tsk":
			show_tsk_info();
			break;
		default:
			break;
	}
	return ret;
}
