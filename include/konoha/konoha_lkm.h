#ifndef KONOHA_LKM_H_
#define KONOHA_LKM_H_

#ifdef KONOHA_ON_LKM
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
#define PRIdPTR "d"
#define PRIuPTR "u"


typedef long jmp_buf ;
typedef intptr_t FILE;

#define TODO_LKM
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
#define assert(x) BUG_ON(!(x))
#define abort() BUG_ON(1)


#define DBG2_(stmt)  stmt

#define DBG2_P(fmt, ...) \
    printk(KERN_DEBUG "DBG2[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
    printk(KERN_DEBUG fmt, ## __VA_ARGS__); \
    printk(KERN_DEBUG "\n"); \

#define DBG2_DUMP(ctx, o, opt, msg) \
    printk(KERN_DEBUG "DBG2[%s]: %s\n", __FUNCTION__, msg); \
    knh_format(ctx, KNH_STDOUT, METHODN__dump, UP(o), UP(opt)); \
    printk(KERN_DEBUG "\n"); \

#define TODO2(msg) \
    printk(KERN_DEBUG "TODO2[%s:%d/%s]: %s\n", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__, msg); \
    printk(KERN_DEBUG "\n"); \

#define DBG2_RESIZE(o, p, os, ns) \
    DBG2_P("RESIZE %s(%p) %d => %d\n\tOLD_BLOCK(%p-%p)", STRUCTN((o->h.bcid)), o, (int)os, (int)ns, p, (p + os)); \
    printk(KERN_DEBUG "\n"); \

#define DBG2_ASSERT(c) KNH_ASSERT(c);

#define DBG2_ABORT() abort()
#define 	KNH_MALLOC(ctx, size)    knh_fastmalloc(ctx, size)
#define 	KNH_FREE(ctx, p, size)   knh_fastfree(ctx, p, size)


/* ../../src/ext/qsort.c */
void qsort(void* base,size_t total,size_t size, int (*comp)(const void*,const void*));

/* ../../src/ext/strerror.c */
char* strerror(int errno);
#endif

/* ------------------------------------------------------------------------ */

#endif
