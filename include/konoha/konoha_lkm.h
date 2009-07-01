#ifndef KONOHA_LKM_H_
#define KONOHA_LKM_H_

#ifdef KONOHA_OS__LKM
#include<linux/kernel.h>
#include<linux/string.h>
#include<linux/version.h>
#include<linux/slab.h>
#include<linux/types.h>
#include<linux/ctype.h>

#define KNH_USING_INT32      1
#define KNH_USING_NOFLOAT    1
#define KNH_USING_NOFILE     1

#define KNH_EXT_QSORT  1
#define KNH_EXT_SETJMP 1

#undef KNH_USING_SOCKET
#undef KNH_USING_ICONV
#undef KNH_USING_REGEX
#undef KNH_USING_SQLITE3
#undef KNH_USING_KONOHAGET
#undef KNH_USING_PTHREAD
#undef KNH_USING_THREAD
#undef KNH_USING_READLINE


/* stdint.h */
#ifndef _STDINT_H
#define _STDINT_H
typedef long                      intptr_t;
#endif

/* /usr/include/inttypes.h */
#define __PRI64_PREFIX	"ll"
#define __PRIPTR_PREFIX
#define PRIdPTR __PRIPTR_PREFIX "d"


typedef long jmp_buf ;
typedef intptr_t FILE;

#define TODO_LKM
/*
#undef  DBG_
#define DBG_(stmt)
#undef  DBG_P
#define DBG_P(fmt, ...) 
*/

#define getenv(a) NULL
#define stdin  ((FILE*)NULL)
#define stdout KERN_INFO
#define stderr KERN_ALERT

#define malloc(x) kmalloc(x,GFP_KERNEL)
#define free(x)   kfree(x)

#define fprintf(out,fmt, arg...) printk(out fmt , ##arg)
#define fputs(prompt, fp) 
#define fgetc(fp) (-1)
#define EOF -1
#define fflush(x)
#define exit(i)  printk(KERN_EMERG "KONOHA_exit!!!")
#define setjmp(j) 0
#define longjmp(a,b)
#define assert(x) WARN_ON(x)
#define abort() WARN_ON(1)

/* ../../src/ext/qsort.c */
void qsort(void* base,size_t total,size_t size, int (*comp)(const void*,const void*));

/* ../../src/ext/strerror.c */
char* strerror(int errno);
#endif

/* ------------------------------------------------------------------------ */

#endif
