#ifndef KONOHA_MACRO_H_
#define KONOHA_MACRO_H_

#include"konoha_t.h"

/* ------------------------------------------------------------------------ */

#define knh_struct_cid(s)   knh_Object_cid(s)

#define MSG(s)             s

/* ------------------------------------------------------------------------ */

#define KNH_MAX(a,b)     (((a) > (b)) ? (a) : (b))
#define KNH_MIN(a,b)     (((a) < (b)) ? (a) : (b))
#define KNH_MID(a,b)     (((a) + (b)) / 2)

/* ------------------------------------------------------------------------ */

#define knh_snprintf(b,n,fmt, ...)  snprintf(b,n,fmt, ## __VA_ARGS__)
#define knh_qsort qsort

/* ------------------------------------------------------------------------ */

#endif /*KONOHA_MACRO_H_*/
