#ifndef STX_SHELL_MEM_H
#define STX_SHELL_MEM_H

int stx_shell_mem_init(void);

int stx_shell_mem_alloc(void **pBuf, int size);

int stx_shell_mem_free(void *pMemBase);

#endif
