#ifndef KONOHA_MACRO_H_
#define KONOHA_MACRO_H_

#include"konoha_t.h"

/* ------------------------------------------------------------------------ */

#define SP(o)               (o)
#define DP(o)               ((o)->b)

#define KONOHA_FATAL   0
#define KONOHA_ERROR   1
#define KONOHA_WARNING 2
#define KONOHA_NOTICE  3

#define _(s)          s

#define KNH_NOTICE(ctx, fmt, ...) \
	konoha_says(ctx, KONOHA_NOTICE, fmt, ## __VA_ARGS__) \

#define KNH_WARNING(ctx, fmt, ...) \
	konoha_says(ctx, KONOHA_WARNING, fmt, ## __VA_ARGS__) \

#define KNH_EXIT(fmt, ...) {\
		fprintf(stderr, "konoha: Emergency Exit at %s\n\t", __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		exit(1); \
	} \

/* ------------------------------------------------------------------------ */

#define KNH_MAX(a,b)     (((a) > (b)) ? (a) : (b))
#define KNH_MIN(a,b)     (((a) < (b)) ? (a) : (b))
#define KNH_MID(a,b)     (((a) + (b)) / 2)

/* ------------------------------------------------------------------------ */

#endif /*KONOHA_MACRO_H_*/
