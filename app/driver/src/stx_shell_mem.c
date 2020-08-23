#include "stx_shell_mem.h"
#include "stx_log.h"
#include "tx_api.h"

TX_BYTE_POOL shell_pool;

#define SHELL_POOL_SIZE    8192u

char shell_pool_buf[SHELL_POOL_SIZE];

int stx_shell_mem_init(void)
{
	int ret = STX_NG;
    if (ret = tx_byte_pool_create(&shell_pool, "shell_pool", shell_pool_buf, SHELL_POOL_SIZE)) != TX_SUCCESS) {
		Stx_Msg_Err("pool create fail");
	}
	return ret;
}

int stx_shell_mem_alloc(void **pBuf, int size)
{
	int ret = STX_NG;
	if ((pBuf == NULL) || (size == 0)) {
		Stx_Msg_Err("buf null || size 0");
		return STX_NG;
	}
	if ((ret = tx_byte_allocate(shell_pool, pBuf, size, TX_NO_WAIT)) != TX_SUCCESS) {
		Stx_Msg_Err("alloc fail");
	}
	return ret;
}

int stx_shell_mem_free(void *pMemBase)
{
	if (pMemBase == NULL) {
		Stx_Msg_Err("buf null");
	}
	return tx_byte_release(pMemBase);
}
