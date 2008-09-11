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

/* ======================================================================== */
/* [DBGMODE2] */

#ifdef KNH_DBGMODE2
#define KNH_DBGMODE     1

#define DBG2_(stmt)  stmt

#define DBG2_P(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "\nDBG2[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define DBG2_DUMP(ctx, o, opt, msg) \
	fprintf(stdout, "DBG2[%s]: %s\n", __FUNCTION__, msg); \
	knh_format(ctx, KNH_STDOUT, METHODN__dump, UP(o), UP(opt)); \
	fprintf(stdout, "\n"); \

#define TODO2(msg) \
	fprintf(stdout, "TODO2[%s:%d/%s]: %s\n", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__, msg); \

#define DBG2_RESIZE(o, p, os, ns) \
	DBG2_P("RESIZE %s(%p) %d => %d\n\tOLD_BLOCK(%p-%p)", STRUCTN((o->h.bcid)), o, (int)os, (int)ns, p, (p + os)); \

#define DBG2_ASSERT(c, fmt, ...) \
	if(!(c)) { \
		fflush(stdout); \
		fprintf(stderr, "\nDBG2!![%s:%d/%s]:\n\t", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		KNH_ASSERT(c); \
	} \

#define KNH_MALLOC(ctx, size) DBG2_malloc(ctx, size)
#define KNH_FREE(p, size)   DBG2_free(p, size)

#else/*KNH_DBGMODE2*/

#define DBG2_(stmt)
#define DBG2_P(fmt, ...)
#define DBG2_DUMP(ctx, o, opt, msg)
#define TODO2(msg)
#define DBG2_RESIZE(o, p, os, ns)
#define DBG2_ASSERT(c, fmt, ...)   KNH_ASSERT(c)

#define KNH_MALLOC(ctx, size) knh_malloc(ctx, size)
#define KNH_FREE(p, size)   knh_free(p, size)

#endif/*KNH_DBGMODE2*/

/* ======================================================================== */
/* KONOHA_DEBUGMODE */

#ifdef KNH_DBGMODE

#define DBG_(stmt)  stmt

#define DBG_P(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "\nDBG[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
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
		fprintf(stderr, "\nDBG!![%s:%d/%s]:\n\t", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		KNH_ASSERT(c); \
	} \

#else/*KNH_DBGMODE2*/

#define DBG_(stmt)
#define DBG_P(fmt, ...)
#define DBG_DUMP(ctx, o, opt, msg)
#define TODO()
#define DBG_ASSERT(c, fmt, ...)   KNH_ASSERT(c)

#endif/*KNH_DBGMODE2*/

/* ======================================================================== */

#endif /*KONOHA_DEBUG_H_*/
