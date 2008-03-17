#ifndef KONOHA_MISC_H_
#define KONOHA_MISC_H_
#include"konoha_t.h"
#include<stdlib.h>
#include<string.h>

/* ======================================================================== */


/* ======================================================================== */
//
//#ifdef KONOHA_TERM_COLOR
//#define TERM_INIT          "\x1b[0m"
//#define TERM_BOLD          "\x1b[1m"
//#define TERM_COLOR_RED     "\x1b[0;31m"
//#define TERM_COLOR_GREEN   "\x1b[0;32m"
//#define TERM_COLOR_YELLOW  "\x1b[0;32m"
//#define TERM_COLOR_BLUE    "\x1b[0;34m"
//#define TERM_COLOR_DEBUG   "\x1b[0;37m"
//#define TERM_COLOR_DEMO    "\x1b[0;32m" 
//#else
#define TERM_INIT          ""
#define TERM_BOLD          ""
#define TERM_COLOR_RED     ""
#define TERM_COLOR_GREEN   ""
#define TERM_COLOR_YELLOW  ""
#define TERM_COLOR_BLUE    ""
#define TERM_COLOR_DEBUG   ""
#define TERM_COLOR_DEMO    ""
//#endif/*KONOHA_TERM_COLOR*/


#define TODO_KONOHA64()

#define MEMO(fmt, ...) \
	fprintf(stderr, "MEMO[%s:%d/%s]: ", __FILE__, __LINE__, __func__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \


#define DEBUG_DUMP(ctx, o) \
	fprintf(stdout, TERM_COLOR_DEBUG "DEBUG[%s:%d/%s]:\n", __FILE__, __LINE__, __func__); \
	knh_format(ctx, KNH_STDOUT, METHODN__dump, o, KNH_NULL); \
	fprintf(stdout, "\n" TERM_INIT); \



/* ======================================================================== */

/* null, bool */

//#define IST(text,t)    (knh_strcmp(text, (char*)t.buf) == 0)

/* stdin, stdout, stderr */

#define DEFVAL(v,a,b)  (IS_NOTNULL(v) ? a : b)

/* ======================================================================== */

#define knh_struct_cid(s)   knh_Object_cid(s)

#define MSG(s)             s

#endif /*KONOHA_MISC_H_*/
