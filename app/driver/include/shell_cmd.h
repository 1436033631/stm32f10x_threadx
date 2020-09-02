#ifndef SHELL_CMD_H
#define SHELL_CMD_H

int shell_cmd_ps(char *cmd_name);

void show_tsk_info(void);

void show_mutex_info(void);

void show_profile(void);

void shell_cmd_sleep(char *name);

void shell_cmd_reboot(char *name);

void shell_cmd_time(char *name);

#endif
