#include "tx_api.h"
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stx_uart2.h"
#include "stx_log.h"
RCC_ClocksTypeDef RCC_Clocks;

#define  APP_CFG_TASK_START_STK_SIZE                    4096u
#define  APP_CFG_TASK_START_PRIO                        100u

static  TX_THREAD   app_root_task_tcb;
static  char        app_root_task_stk[APP_CFG_TASK_START_STK_SIZE];

/**
  *SystickInit
  */
/* Init SysTick Clock*/
void SystickInit(void)
{
    SysTick_Config(SystemCoreClock / 1000);
    NVIC_SetPriority (SysTick_IRQn, 1);
}
static void app_root_task_entry (ULONG thread_input)
{
	stx_shell_init();
    while (1)
	{
        Stx_Msg_Info("########");
        tx_thread_sleep(1000);
    }
}

int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_stm32f10x_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_stm32f10x.c file
       */
    __enable_irq();

    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(0x1000000);
    //SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
    /* Add your application code here
     */
    SystickInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	stx_uart2_init();
	Stx_Msg_Info("welcome to threadx, jump to kernel...");

    tx_kernel_enter();

}

void  tx_application_define(void *first_unused_memory)
{
	int ret = 0;
    ret = tx_thread_create(&app_root_task_tcb,
                       "app_root_task",
                       app_root_task_entry,
                       0,
                       &app_root_task_stk[0],
                       APP_CFG_TASK_START_STK_SIZE,
                       APP_CFG_TASK_START_PRIO,
                       APP_CFG_TASK_START_PRIO,
                       TX_NO_TIME_SLICE,
                       TX_AUTO_START);
	if (ret != TX_SUCCESS) {
		Stx_Msg_Err("app_task_start create fail ret %d", ret);
	}
}
