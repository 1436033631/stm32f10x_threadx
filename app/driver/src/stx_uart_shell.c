#include "stx_log.h"
#include "tx_api.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define SHELL_TASK_STK_SIZE     512u
#define SHELL_TASK_PRIO         250u

struct STX_SHELL_MSG_S {
	int cnt;
	uint8_t buf[128];
};
struct STX_SHELL_INFO_s {
	TX_THREAD  shell_task_tcb;
	char       shell_task_stk[SHELL_TASK_STK_SIZE];
	TX_MUTEX   shell_msg_mutex;
	TX_QUEUE   shell_msg_quene;
	struct STX_SHELL_MSG_S shell_msg_buf[32];
};
static struct STX_SHELL_INFO_s shell_info;

// UART2 interrupt
void USART2_IRQHandler(void)
{
    uint8_t data;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART2);
        // add usart receive here
		(void)data;
//		tx_queue_send(&shell_info.shell_msg_quene, &msg, ULONG wait_option)
        USART_ClearFlag(USART2, USART_FLAG_RXNE);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

static void shell_task_entry(void)
{
	int ret = 0;
	struct STX_SHELL_MSG_S msg;
	while (1) {
		ret = tx_queue_receive(&shell_info.shell_msg_quene, (void *)&msg, TX_WAIT_FOREVER);

	}
}
void stx_shell_init(void)
{
	int ret = 0;

	ret = tx_queue_create(&shell_info.shell_msg_quene,
   						"shell_queue",
   						TX_1_ULONG,
   						shell_info.shell_msg_buf,
   						sizeof(shell_info.shell_msg_buf));
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

	ret = tx_mutex_create(&shell_info.shell_msg_mutex,
						 "shell_mutex",
						 TX_INHERIT);
	if (ret != TX_SUCCESS) {
		Stx_Msg_Err("shell_mutex create fail ret %d", ret);
	}

}
