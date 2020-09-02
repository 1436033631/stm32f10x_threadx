#include "shell_cmd.h"
#include "stx_log.h"
#include "tx_api.h"
#include "tx_thread.h"

struct stx_tsk_info {
    char    *pName;
    int  CurState;
    long   RunCount;
    long   TimeSlice;
    int  Priority;
    int  PreemptionThreshold;
    TX_THREAD *pNextThread;
    TX_THREAD *pSuspendedThread;
};


/* Task Execution State */
static const char *tsk_state[] = {
    [TX_READY]          = "READY",
    [TX_COMPLETED]      = "COMPLETED",
    [TX_TERMINATED]     = "TERMINATED",
    [TX_SUSPENDED]      = "SUSPENDED",
    [TX_SLEEP]          = "SLEEP",
    [TX_QUEUE_SUSP]     = "QUEUE_SUSP",
    [TX_SEMAPHORE_SUSP] = "SEMAPHORE_SUSP",
    [TX_EVENT_FLAG]     = "EVENT_FLAG",
    [TX_BLOCK_MEMORY]   = "BLOCK_MEMORY",
    [TX_BYTE_MEMORY]    = "BYTE_MEMORY",
    [TX_IO_DRIVER]      = "IO_DRIVER",
    [TX_FILE]           = "FILE",
    [TX_TCP_IP]         = "TCP_IP",
    [TX_MUTEX_SUSP]     = "MUTEX_SUSP",
};

static int sys_get_task_id(TX_THREAD *pTargetTask)
{
    TX_THREAD *pTask = _tx_thread_created_ptr;
    int i;

    for (i = 0; i < _tx_thread_created_count; i++) {
        if (pTask == pTargetTask) {
            return i;
        }

        pTask = pTask->tx_thread_created_next;
    }

    return 0;
}

void show_tsk_info(void)
{
	int ret = 0, next_tsk_id = 0;
	TX_THREAD *p_task = _tx_thread_created_ptr;
	struct stx_tsk_info tsk_info;
	Stx_Msg_Info("thread count %d", _tx_thread_created_count);
	stx_printf(" ID  PRI  PREEMPT  SCHED            STAT  NEXT_ID  STKSIZE  STKUSED  STKBASE   STKEND    STKPTR    NAME\r\n");
    stx_printf("--------------------------------------------------------------------------------------------------------------------------\r\n");
	for (int i=0; i<_tx_thread_created_count; i++) {
		ret = tx_thread_info_get(p_task,
								&tsk_info.pName,				        /* Pointer to the thread's name */
								&tsk_info.CurState,			    /* Pointer to the thread's current execution state */
								&tsk_info.RunCount,			    /* Pointer to the threads run count */
								&tsk_info.Priority,			    /* Pointer to the threads priority */
								&tsk_info.PreemptionThreshold,  /* Pointer to the threads preemption-threshold */
								&tsk_info.TimeSlice,			/* Pointer to the threads time-slice */
								&tsk_info.pNextThread, 		    /* Pointer to the next created thread */
								&tsk_info.pSuspendedThread);	/* Pointer to the next thread in suspension list */
		if ((next_tsk_id = sys_get_task_id(tsk_info.pSuspendedThread)) < 0) {
			next_tsk_id = i;
		}
		stx_printf("%3d%5d%9d%7d%16s%9d%9d%9d  %8x  %8x  %8x  %s\r\n",
				  i,
                  tsk_info.Priority,
                  tsk_info.PreemptionThreshold,
                  tsk_info.RunCount,
                  tsk_state[tsk_info.CurState],
                  next_tsk_id,
                  p_task->tx_thread_stack_size,
                  (unsigned int)p_task ->tx_thread_stack_end - (unsigned int)p_task->tx_thread_stack_ptr + 1,
                  p_task->tx_thread_stack_start,
                  p_task->tx_thread_stack_end,
                  p_task->tx_thread_stack_ptr,
                  tsk_info.pName);
		p_task = p_task->tx_thread_created_next;
	}
}

