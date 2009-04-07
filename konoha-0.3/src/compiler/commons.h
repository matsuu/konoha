#ifndef COMMONS_H_
#define COMMONS_H_

#include<konoha/konoha_dev.h>
#include<konoha/gen/konohac_klr_.h>

#ifdef __cplusplus
extern "C" {
#endif

#undef IS_Token
#define IS_Token(o)      (((Token*)o)->h.cid == CLASS_Token)
#define TOKENNo(o)        knh_token_tochar(SP(o)->tt)

#undef IS_Stmt
#define IS_Stmt(o)       (((Stmt*)o)->h.cid == CLASS_Stmt)
#define STMTNo(o)         knh_stmt_tochar(SP(o)->stt)

/* ------------------------------------------------------------------------ */

#define FL(o)            ((Object*)o)
#define TM(o)            ((Term*)o)

/* ------------------------------------------------------------------------ */

#define TWARN_  0
#define TCHECK_ 1
#define TCONV_  2
#define TITERCONV_ 3

/* ------------------------------------------------------------------------ */

#define TS_MN(mn)  knh_tfieldn_name(METHODN_TOFIELDN(mn))
#define TS_FN(fn)  knh_tfieldn_name(fm)

/* ------------------------------------------------------------------------ */

#ifdef KNH_DBGMODE2
#define KNH_DEBUG3
#endif

#ifdef KNH_DBGMODE3
#define SAFE_ASSERT(ctx, abr, c)  KNH_ASSERT(c)
#else
#define SAFE_ASSERT(ctx, abr, c)  if(!(c)) knh_Asm_assert(ctx, abr, c)
#endif

/* ------------------------------------------------------------------------ */

#ifdef KNH_DEBUG3

#define DEBUG3(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "\nDEBUG3[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define TODO3(fmt, ...) \
	fflush(stdout); \
	fprintf(stderr, "\nTODO3[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define DEBUG3_ASSERT(c)    KNH_ASSERT(c)

#define DEBUG3_PTC(name, tc) \
	fflush(stdout); \
	fprintf(stderr, "\nDEBUG3[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, "%s: c=%d, e=%d\n", name, (tc)->c, (tc)->e); \

#define DEBUG3_STC(name, tc) \
	fflush(stdout); \
	fprintf(stderr, "\nDEBUG3[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	fprintf(stderr, "%s: c=%d, e=%d\n", name, (tc).c, (tc).e); \

#else

#define DEBUG3(fmt, ...)
#define TODO3(fmt, ...)
#define DEBUG3_ASSERT(c) KNH_ASSERT(c)
#define DEBUG3_PTC(name, tc)
#define DEBUG3_STC(name, tc)

#endif

/* ------------------------------------------------------------------------ */
/* @see(knh_Stmt_add_index) */

#ifndef TT_SUBSETE
#define TT_SUBSETE TT_ITR
#endif

/* ------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------ */

#define LABEL_BUFSIZ         40

//#ifndef KONOHAC_ERROR_BUFSIZ
//#define KONOHAC_ERROR_BUFSIZ 512
//#endif

/* ------------------------------------------------------------------------ */
/* [TE] */


#ifdef __cplusplus
}
#endif

#endif /*COMMONS_H_*/
