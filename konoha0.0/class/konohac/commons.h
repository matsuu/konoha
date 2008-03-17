#ifndef COMMONS_H_
#define COMMONS_H_

#include<konoha/konoha_dev.h>
#include<konoha/konohac_asm_.h>

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* @see(knh_Stmt_add_index) */

#ifndef TT_SLICE
#define TT_SLICE  TT_SEMICOLON
#endif

#ifndef TT_SUBSET
#define TT_SUBSET TT_SEMICOLON
#endif

/* ------------------------------------------------------------------------ */

#ifndef KONOHA_LOCALVAR_SIZE
#define KONOHA_LOCALVAR_SIZE 127
#endif

/* ------------------------------------------------------------------------ */

#define LABEL_BUFSIZ         40

#ifndef KONOHAC_ERROR_BUFSIZ
#define KONOHAC_ERROR_BUFSIZ 512
#endif  

#ifndef KONOHAC_FILELINE_FMT
#define KONOHAC_FILELINE_FMT    "%s:[%s:%d+%d]"
#endif

/* ------------------------------------------------------------------------ */

#define MC_FIRST      1
#define MC_NOTFIRST   0

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*COMMONS_H_*/
