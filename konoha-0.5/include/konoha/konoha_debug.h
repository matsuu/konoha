#ifndef KONOHA_DEBUG_H_
#define KONOHA_DEBUG_H_

/* ======================================================================== */
/* [FASTMODE] */

#ifdef KNH_FASTMODE
#define KNH_ASSERT(c)
#define DEBUG_ASSERT(c)
#define SAFE_(s)

#else/*KNH_FASTMODE*/
#define KNH_ASSERT(c)    assert(c)
#define DEBUG_ASSERT(c)  assert(c)
#define SAFE_(s)         s
#endif/*KNH_FASTMODE*/

#define KNH_ABORT()      abort()

/* ======================================================================== */
/* [DBGMODE2] */

#define KNH_USING_FASTMALLOC 1

#ifdef KNH_DBGMODE2
#define KNH_DBGMODE     1

#define DBG2_(stmt)  stmt

#define DBG2_P(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "DBG2[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define DBG2_DUMP(ctx, o, opt, msg) \
	fprintf(stdout, "DBG2[%s]: %s\n", __FUNCTION__, msg); \
	knh_format(ctx, KNH_STDOUT, METHODN__dump, UP(o), UP(opt)); \
	knh_flush(ctx, KNH_STDOUT);\
	fprintf(stdout, "\n"); \

#define TODO2(msg) \
	fprintf(stdout, "TODO2[%s:%d/%s]: %s\n", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__, msg); \

#define DBG2_RESIZE(o, p, os, ns) \
	DBG2_P("RESIZE %s(%p) %d => %d\n\tOLD_BLOCK(%p-%p)", STRUCTN((o->h.bcid)), o, (int)os, (int)ns, p, (p + os)); \

#define DBG2_ASSERT(c) KNH_ASSERT(c);

#ifdef KNH_USING_FASTMALLOC2
#define KNH_MALLOC(ctx, size)    knh_fastmalloc(ctx, size)
#define KNH_FREE(ctx, p, size)   knh_fastfree(ctx, p, size)
#else
#define KNH_MALLOC(ctx, size)    DBG2_malloc(ctx, size, (char*)__FUNCTION__)
#define KNH_FREE(ctx, p, size)   DBG2_free(ctx, p, size, (char*)__FUNCTION__)
#endif

#define DBG2_ABORT()    abort()

#else/*KNH_DBGMODE2*/

#define DBG2_(stmt)
#define DBG2_P(fmt, ...)
#define DBG2_DUMP(ctx, o, opt, msg)
#define TODO2(msg)
#define DBG2_RESIZE(o, p, os, ns)
#define DBG2_ASSERT(c)
#define DBG2_ABORT()

#ifdef KNH_USING_FASTMALLOC
#define 	KNH_MALLOC(ctx, size)    knh_fastmalloc(ctx, size)
#define 	KNH_FREE(ctx, p, size)   knh_fastfree(ctx, p, size)
#else/*KNH_USING_FASTMALLOC*/
#define 	KNH_MALLOC(ctx, size) knh_malloc(ctx, size)
#define 	KNH_FREE(ctx, p, size)   knh_free(ctx, p, size)
#endif/*KNH_USING_FASTMALLOC*/

#endif/*KNH_DBGMODE2*/

/* ======================================================================== */
/* KONOHA_DEBUGMODE */

#ifdef KNH_DBGMODE

#define DBG_(stmt)  stmt

#define DBG_P(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "DBG[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define DBG_DUMP(ctx, o, opt, msg) \
	fprintf(stdout, "DBG[%s]: %s\n", __FUNCTION__, msg); \
	knh_format(ctx, KNH_STDOUT, METHODN__dump, o, opt); \
	fprintf(stdout, "\n"); \

#define TODO() \
	fprintf(stderr, "TODO[%s:%d/%s]:\n", KNH_SAFEFILE(__FILE__) , __LINE__, __FUNCTION__); \

#define DBG_ASSERT(c, fmt, ...) \
	if(!(c)) { \
		fflush(stdout); \
		fprintf(stderr, "DBG!![%s:%d/%s]:\n\t", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		KNH_ASSERT(c); \
	} \

#define KNH_CTXASSERT(ctx, c, fmt, ...) \
	if(!(c)) { \
		fprintf(stderr, "DEBUG[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		KNH_ASSERT(c); \
	} \

#else/*KNH_DBGMODE*/

#define DBG_(stmt)
#define DBG_P(fmt, ...) \
	if(konoha_isDebugMode2()) {\
		fflush(stdout); \
		fprintf(stderr, "DBG[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
	}\

#define DBG_DUMP(ctx, o, opt, msg)
#define TODO()
#define DBG_ASSERT(c, fmt, ...)   KNH_ASSERT(c)

#define KNH_CTXASSERT(ctx, c, fmt, ...) \
	if(!(c)) { \
		char ebuf_[256];\
		knh_snprintf(ebuf_, sizeof(ebuf_), "Konoha!!: " fmt, ## __VA_ARGS__);\
		KNH_THROWs(ctx, ebuf_);\
	} \


#endif/*KNH_DBGMODE2*/

/* ======================================================================== */
/* [STUPID] */

#define KNH_FUTURE(msg) {\
		fprintf(stderr, "FUTURE[%s:%d] %s will be supported in the near future.\n", KNH_SAFEFILE(__FILE__), __LINE__, msg); \
	}\

/* ======================================================================== */
/* [STUPID] */

#define STUPID_NOTFOUND   0
#define STUPID_OUTOFINDEX 1
#define STUPID_TYPEERROR  2

#define KNH_STUPID(ctx, o, a)

/* ======================================================================== */

#ifdef KNH_USING_THREAD

#define TODO_LOCK() \
	fprintf(stderr, "TODO[%s:%d/%s]: LOCK\n", KNH_SAFEFILE(__FILE__) , __LINE__, __FUNCTION__); \

#define TODO_UNLOCK() \
	fprintf(stderr, "TODO[%s:%d/%s]: UNLOCK\n", KNH_SAFEFILE(__FILE__) , __LINE__, __FUNCTION__); \

#else

#define TODO_LOCK()
#define TODO_UNLOCK()

#endif

/* ======================================================================== */

#endif /*KONOHA_DEBUG_H_*/
