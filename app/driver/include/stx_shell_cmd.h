#ifndef STX_SHELL_CMD_H
#define STX_SHELL_CMD_H

typedef int (*SHELL_CMD_PROC_f)(char *cmd_name);

struct shell_cmd_s {
	char *name;
	SHELL_CMD_PROC_f proc;
	struct shell_cmd_s *pNext;
};

void shell_cmd_init(void);

int shell_cmd_register(char *name, SHELL_CMD_PROC_f proc);

int shell_cmd_unregister(char *name, SHELL_CMD_PROC_f proc);

int shell_cmd_parser(char *src_name, char *cmd, char *name);

#endif

