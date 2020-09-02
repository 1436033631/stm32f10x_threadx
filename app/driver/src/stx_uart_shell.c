#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#include "tx_api.h"

#include "shell_cmd.h"
#include "stx_log.h"
//#include "stx_uart2.h"

#define SHELL_TASK_STK_SIZE     8192u
#define SHELL_TASK_PRIO         31u
#define SHELL_MSG_MAX_SIZE      32u

struct STX_SHELL_INFO_s {
	TX_THREAD  shell_task_tcb;
	char       shell_task_stk[SHELL_TASK_STK_SIZE];
	TX_QUEUE   shell_msg_quene;
	uint8_t shell_msg_buf[SHELL_MSG_MAX_SIZE];
};
static struct STX_SHELL_INFO_s shell_info;

// UART2 interrupt
void USART2_IRQHandler(void)
{
    uint8_t msg = 0;
	int ret = 0;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
    	msg = USART_ReceiveData(USART2);

		ret = tx_queue_send(&shell_info.shell_msg_quene, &msg, TX_NO_WAIT);
		if (ret != TX_SUCCESS) {
			Stx_Msg_Err("tx_queue_send fail ret %d cmd %c", ret, msg);
		}

//        USART_ClearFlag(USART2, USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
static void shell_cmd_help(void)
{
	stx_printf("\r\nUsage: \r\n");
	stx_printf("	ps\r\n");
	stx_printf("	sleep\r\n");
	stx_printf("	reboot\r\n");
	stx_printf("	time\r\n");
}
static void shell_cmd_handle(char *cmd)
{
	char child_cmd[8] = {0};
	char name[8] = {0};

	if (strlen(cmd) == 0) {
		return;
	}
	shell_cmd_cut(cmd, child_cmd, name);
	if (strstr(child_cmd, "ps")) {
		shell_cmd_ps(name);
	} else if (strstr(child_cmd, "sleep")) {
		shell_cmd_sleep(name);
	} else if (strstr(child_cmd, "reboot")) {
		shell_cmd_reboot(name);
	} else if (strstr(child_cmd, "time")) {
		shell_cmd_time(name);
	} else {
		shell_cmd_help();
	}
}

static void shell_task_entry(void)
{
	uint8_t msg = {0};
	static char cmd[32] = {0};
	uint8_t index = 0;
	while (1) {
		tx_queue_receive(&shell_info.shell_msg_quene, (void *)&msg, TX_WAIT_FOREVER);
		if ((msg == '\r') || (msg == '\n')) {
			//NOTICE:end flag for string
			cmd[index] = '\0';
			shell_cmd_handle(cmd);
			stx_printf("\r\n# ");
			index = 0;
		} else {
			cmd[index++] = msg;
			stx_printf("%c", msg);
		}
	}
}
void stx_shell_init(void)
{
	int ret = 0;

	ret = tx_queue_create(&shell_info.shell_msg_quene,
   						"shell_queue",
   						TX_4_ULONG,
   						shell_info.shell_msg_buf,
   						SHELL_MSG_MAX_SIZE * sizeof(uint8_t));
	if (ret != TX_SUCCESS) {
		Stx_Msg_Err("shell_queue create fail ret %d", ret);
	}

    ret = tx_thread_create(&shell_info.shell_task_tcb,
	                       "shell_task",
	                       shell_task_entry,
	                       0,
	                       &shell_info.shell_task_stk[0],
	                       SHELL_TASK_STK_SIZE,
	                       SHELL_TASK_PRIO,
	                       SHELL_TASK_PRIO,
	                       TX_NO_TIME_SLICE,
	                       TX_AUTO_START);
	if (ret != TX_SUCCESS) {
		Stx_Msg_Err("shell_task create fail ret %d", ret);
	}
}
