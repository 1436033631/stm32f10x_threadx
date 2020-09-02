#include "shell_cmd.h"
#include "stx_log.h"
#include "tx_api.h"
#include "tx_thread.h"
#include "tx_mutex.h"

struct stx_mtx_info{
	char *name;
	long count;
	TX_THREAD *owner;
	TX_THREAD *first_suspend;
	TX_MUTEX *next_mtx;
	long suspend_count;
};

void show_mutex_info(void)
{
	int ret = 0;
	struct stx_mtx_info mtx_info;
	TX_MUTEX *p_mtx = _tx_mutex_created_ptr;
	stx_printf("---------------------------------\r\n");
    stx_printf("*******  Total %3d Mutex  *******\r\n", _tx_mutex_created_count);
    stx_printf("---------------------------------\r\n");
    stx_printf(" ID      Name         Count  SuspendCount  Owner                FirstSuspended\r\n");
	for (int i=0; i<_tx_mutex_created_count; i++) {
		ret = tx_mutex_info_get(p_mtx,
                           &mtx_info.name,
                           &mtx_info.count,
                           &mtx_info.owner,
                           &mtx_info.first_suspend,
                           &mtx_info.suspend_count,
                           &mtx_info.next_mtx);
        if (ret) {
            Stx_Msg_Err("Error get %d Mutex\r\n", i);
            return;
        }

        stx_printf("%3d  %12s  %5d  %12d", i, mtx_info.name, mtx_info.count, mtx_info.suspend_count);

        /* if the Mutex owner is available */
        if (mtx_info.owner != NULL) {
            stx_printf("  %s", (mtx_info.owner->tx_thread_name == NULL ? " " : mtx_info.owner->tx_thread_name));
        }

        if (mtx_info.first_suspend != NULL) {
            stx_printf("  %s", (mtx_info.first_suspend->tx_thread_name == NULL ? " " : mtx_info.first_suspend->tx_thread_name));
        }
        stx_printf("\r\n");

        p_mtx = p_mtx->tx_mutex_created_next;
	}
}

