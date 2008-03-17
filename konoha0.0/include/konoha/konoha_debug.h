#ifndef KONOHA_DEBUG_H_
#define KONOHA_DEBUG_H_

/* ======================================================================== */

//#define KONOHA_DEBUGMODE 1
//#define KONOHA_DEMOMODE  1
#define KONOHA_SAFEMODE  1

/* ======================================================================== */
/* KONOHA_TERM */

//#ifdef KONOHA_TERM_COLOR
//#define TERM_INIT          "\x1b[0m"
//#define TERM_COLOR_DEBUG   "\x1b[0;37m"
//#define TERM_COLOR_SAFE    "\x1b[0;33m"
//#define TERM_COLOR_DEMO    "\x1b[0;32m" 
//#else
#define TERM_INIT          ""
#define TERM_COLOR_NOTICE  ""
#define TERM_COLOR_DEBUG   ""
#define TERM_COLOR_SAFE    ""
#define TERM_COLOR_DEMO    ""
//#endif/*KONOHA_TERM_COLOR*/

/* ======================================================================== */
/* KONOHA_DEBUGMODE */

#define KNH_NOTICE(fmt, ...) \
	if(knh_verbose()) { \
		fprintf(stderr, "konoha[%s]: ", __func__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
	} \
	
/* ======================================================================== */
/* KONOHA_DEBUGMODE */

#ifdef KONOHA_DEBUGMODE

#ifndef KONOHA_SAFEMODE
	#define KONOHA_SAFEMODE
#endif

#define DEBUG(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, TERM_COLOR_DEBUG "\nDEBUG[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __func__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n" TERM_INIT); \

#define TODO() \
	fprintf(stdout, \
		TERM_COLOR_DEBUG "TODO[%s:%d/%s]:\n" TERM_INIT, \
		__FILE__, __LINE__, __func__); \

#define DEBUG_RESIZE(o, p, os, ns) \
	DEBUG("RESIZE %s(%p) %d => %d", STRUCTN(knh_Object_topsid(o)), o, (int)os, (int)ns); \
	DEBUG("RESIZE old region %p-%p", p , (p + os)); \

#else /*KONOHA_DEBUGMODE*/

#define DEBUG(fmt, ...)
#define DUMP(ctx, o)
#define TODO()

#define DEBUG_RESIZE(o, p, os, ns) 


#endif/*KONOHA_DEBUGMODE*/
	

/* ======================================================================== */
/* KONOHA_SAFEMODE */

#ifdef KONOHA_SAFEMODE

#define DEBUG_ASSERT(o)     assert(o)
#define KNH_ASSERT(o)       assert(o)
#define KNH_FAST_ASSERT(o)  assert(o)

#define SAFE_ASSERT(c, fmt, ...) \
	if(!(c)) { \
		fflush(stdout); \
		fprintf(stderr, TERM_COLOR_DEBUG "\nSAFE!![%s:%d/%s]:\n\t", KNH_SAFEFILE(__FILE__), __LINE__, __func__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n" TERM_INIT); \
		assert(c); \
	} \

#else /*KONOHA_SAFEMODE*/

#define DEBUG_ASSERT(o)
#define KNH_ASSERT(o)
#define KNH_FAST_ASSERT(o)
#define SAFE_ASSERT(o, fmt, ...) 

#endif/*KONOHA_SAFEMODE*/

/* ======================================================================== */
/* KONOHA_DEMOMODE */

#ifdef KONOHA_DEMOMODE

#define DEMO_DUMP(ctx, o, opt, msg) \
	fprintf(stdout, TERM_COLOR_DEMO "DEMO[%s]: %s\n", __func__, msg); \
	knh_format(ctx, KNH_STDOUT, METHODN__dump, o, opt); \
	fprintf(stdout, "\n" TERM_INIT); \

#else /*KONOHA_SAFEMODE*/

#define DEMO_DUMP(ctx,o, opt, msg)

#endif/*KONOHA_SAFEMODE*/

#endif /*KONOHA_DEBUG_H_*/
