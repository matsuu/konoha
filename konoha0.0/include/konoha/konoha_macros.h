#ifndef KONOHA_MACRO_H_
#define KONOHA_MACRO_H_

#include"konoha_t.h"

/* ------------------------------------------------------------------------ */

#define SP(o)               (o)
#define DP(o)               ((o)->b)

#ifdef KNH_DEBUGMODE
#define KNH_NOTICE(ctx, fmt, ...) \
	knh_printf(ctx, KNH_STDERR, "konoha [%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	knh_printf(ctx, KNH_STDERR, fmt, ## __VA_ARGS__); \
	knh_write_EOL(ctx, KNH_STDERR); \

#define KNH_WARNING(ctx, fmt, ...) \
	knh_printf(ctx, KNH_STDERR, "konoha [%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
	knh_printf(ctx, KNH_STDERR, fmt, ## __VA_ARGS__); \
	knh_write_EOL(ctx, KNH_STDERR); \

#else

#ifdef KNH_PACKAGE
#define KNH_TITLE  "konoha[" KNH_PACKAGE "]: "
#else
#define KNH_TITLE  "konoha: "
#endif

#define KNH_NOTICE(ctx, fmt, ...) \
	if(knh_Context_isVerbose(ctx)) { \
		knh_printf(ctx, KNH_STDERR, KNH_TITLE); \
		knh_printf(ctx, KNH_STDERR, fmt, ## __VA_ARGS__); \
		knh_write_EOL(ctx, KNH_STDERR); \
	} \

#define KNH_WARNING(ctx, fmt, ...) \
	knh_printf(ctx, KNH_STDERR, KNH_TITLE); \
	knh_printf(ctx, KNH_STDERR, fmt, ## __VA_ARGS__); \
	knh_write_EOL(ctx, KNH_STDERR); \

#endif

#define KNH_EXIT(fmt, ...) {\
		fprintf(stderr, "konoha[%s]: ", __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\nExiting.. done. \n"); \
		exit(0); \
	} \

/* ------------------------------------------------------------------------ */

#define KNH_MAX(a,b)     (((a) > (b)) ? (a) : (b))
#define KNH_MIN(a,b)     (((a) < (b)) ? (a) : (b))
#define KNH_MID(a,b)     (((a) + (b)) / 2)

/* ------------------------------------------------------------------------ */

#endif /*KONOHA_MACRO_H_*/
