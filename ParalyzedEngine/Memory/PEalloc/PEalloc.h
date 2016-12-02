#ifndef __PE_PEALLOC_H_
#define __PE_PEALLOC_H_
#include <stddef.h>
#include <stdlib.h>
#define LIKELY(x) __builtin_expect((x),1)
#define UNLIKELY(x) __builtin_expect((x),0)
#define pe_malloc malloc
#ifdef _cplusplus
extern "C"{
#endif 

extern void * PE_malloc(size_t size);
#ifdef _cplusplus
}
#endif 

#endif