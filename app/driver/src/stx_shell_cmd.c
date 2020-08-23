#include "stx_shell_cmd.h"
#include "stx_shell_mem.h"
#include "stx_log.h"
#include "tx_api.h"

struct shell_cmd_s cmd_default;
TX_MUTEX shell_cmd_list_mutex;

static void cmd_help(void)
{

}

void shell_cmd_init(void)
{
	char root_cmd_name[16] = "root_cmd";
	struct shell_cmd_s *p_cmd = &cmd_default;
	if (stx_shell_mem_alloc((void **)&p_cmd->name, sizeof(root_cmd_name)) != STX_OK) {
		Stx_Msg_Err("p_new_cmd->name alloc fail");
	}
	strcpy(p_cmd->name, root_cmd_name);
	p_cmd->name->proc = NULL;
	p_cmd->pNext = NULL;
	stx_shell_mem_init();
}

int shell_cmd_register(char *name, SHELL_CMD_PROC_f proc)
{
	int ret = STX_NG;
	struct shell_cmd_s *p_new_cmd;
	struct shell_cmd_s *p_last_cmd = &cmd_default;
	if ((name == NULL) || (proc == NULL)) {
		Stx_Msg_Err("pool create fail");
		return ret;
	}
	if (stx_shell_mem_alloc((void **)&p_new_cmd, sizeof(struct shell_cmd_s)) != STX_OK) {
		Stx_Msg_Err("p_new_cmd alloc fail");
	}
	if (stx_shell_mem_alloc((void **)&p_new_cmd->name, strlen(name) + 1) != STX_OK) {
		stx_shell_mem_free((void *)p_new_cmd);
		Stx_Msg_Err("p_new_cmd->name alloc fail");
	}
	strcpy((char *)p_new_cmd->name, name);
	p_new_cmd->proc = proc;
	p_new_cmd->pNext = NULL;
	tx_mutex_get(&shell_cmd_list_mutex, TX_WAIT_FOREVER);
	while(p_last_cmd != NULL) {
		p_last_cmd = p_last_cmd->pNext;
	}
	p_last_cmd->pNext = p_new_cmd;
	tx_mutex_put(&shell_cmd_list_mutex);
	return ret;
}

int shell_cmd_unregister(char *name, SHELL_CMD_PROC_f proc)
{
	int ret = STX_NG;
	struct shell_cmd_s *p_cmd = &cmd_default;
	struct shell_cmd_s *p_next_cmd;
	tx_mutex_get(&shell_cmd_list_mutex, TX_WAIT_FOREVER);
	while (p_cmd) {
		p_next_cmd = p_cmd->pNext;
		if (strcmp(p_next_cmd->name, name) == 0) && (p_next_cmd->proc == proc)) {
			p_cmd->pNext = p_next_cmd->pNext;
			stx_shell_mem_free((void *)p_next_cmd->name);
			stx_shell_mem_free((void *)p_next_cmd);
			break;
		}
		p_cmd = p_cmd->pNext;
	}
	tx_mutex_put(&shell_cmd_list_mutex);
	return ret;
}

int shell_cmd_parser(char *src_name, char *cmd, char *name)
{
	int ret = STX_NG;

	while (*src_name != ' ') {
		*cmd = *src_name;
		cmd++;
		src_name++;
	}
	*cmd = '\0';
	memcpy(name, src_name+1, strlen(src_name)-1);
	return ret;
}
