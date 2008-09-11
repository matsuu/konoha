/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation  
 * All rights reserved.
 * 
 * You may choose one of the following two licenses when you use konoha. 
 * See www.konohaware.org/license.html for further information.
 * 
 * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
 * (2) Konoha Software Foundation License 1.0
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 ****************************************************************************/

#ifndef CLASS_KONOHAC_H_
#define CLASS_KONOHAC_H_

#include<konoha/konoha_t.h>
#include"konoha.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

typedef knh_ushort_t   knh_token_t;
typedef knh_ushort_t   knh_stmt_t;
#define knh_perror_t   int

/* ------------------------------------------------------------------------ */
/* @class Token Object knh_Token_struct */
/* @flag Token.TailWildCard TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.TopDot TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Getter TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Setter TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Generated TKF SP(%s)->flag 'is:set:*:*' */

/* @flag Token.ExceptionType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.NotNullType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.IteratorType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.ArrayType TKF SP(%s)->flag 'is:set:*:*' */

/* @flag Token.Typed  TKF SP(%s)->flag 'is:set:*:*' */

typedef struct knh_Token {
//	knh_fileid_t fileid;
//	knh_line_t   line;
//	knh_flag_t   flag;
//	knh_token_t  tt;
	knh_type_t   type;
	union {
		knh_token_t   tt_next;
		knh_short_t   index;
		knh_methodn_t mn;
		knh_token_t   tt_op;
		knh_fieldn_t  fn;
		knh_class_t   cid;
	};
	union {
		Object* data;
		struct knh_Array_t*  list;
		struct knh_String_t* str;
		struct knh_Token_t* token;
		struct knh_Method_t* mtd;
	};
} knh_Token_struct;

typedef struct knh_tokens_t {
	struct knh_Token_t** ts;
	int c;
	int e;
} knh_tokens_t;

#define TT_RAW   TT_CONST

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* @class Stmt Object knh_Stmt_struct */
/* @flag Stmt.Adposition STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.NonNewLine STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Visible STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Typed STMTF SP(%s)->flag 'is:set:*:*' */

/* ------------------------------------------------------------------------ */

#define KNH_STT_RVALUE  0
#define KNH_RVALUE      0
#define KNH_STT_LVALUE  1
#define KNH_LVALUE      1

typedef struct knh_Stmt {
//	knh_fileid_t fileid;
//	knh_line_t   line;
//	knh_flag_t   flag;
//	knh_stmt_t   stt;
	knh_type_t   type;
	knh_line_t   line_end;
	knh_ushort_t size;
	knh_ushort_t capacity;
	union {
		Object** terms;
		struct knh_Token_t** tokens;
		struct knh_Stmt_t** stmts;
	};
	union {
		struct knh_DictMap_t* metaDictMap;
		struct knh_String_t*  errMsg;
	};
	struct knh_Stmt_t* next;
} knh_Stmt_struct;

/* ------------------------------------------------------------------------ */

#define Term         Any
#define IS_Term(o)   (IS_Token((Object*)o)||IS_Stmt((Object*)o))

/* ------------------------------------------------------------------------ */
/* @class Compiler Object knh_Compiler_struct */
/* @flag Compiler.SyntaxError CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Compiler.Stopped CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Compiler.Cancelled CPF DP(%s)->flag 'is:set:*:*' */

typedef struct knh_Compiler {
	knh_fileid_t           fileid; 
	knh_flag_t             flag;
	knh_class_t            this_cid;
	knh_ushort_t           step; /* unused */
	struct knh_NameSpace_t *ns;
	struct knh_Method_t    *method;
	knh_ushort_t vars_size;
	knh_ushort_t vars_offset;
	knh_cfield_t* vars;
	int nastep;
	int llstep;
	struct knh_Bytes_t* elf;
	struct knh_Bytes_t* dwarf;
	int line;
	struct knh_DictIdx_t* labelIdDictIdx;
	struct knh_DictSet_t* labelAddrDictSet;
	knh_Array_t*          lstacks;
} knh_Compiler_struct;

/* ------------------------------------------------------------------------ */

struct knh_Compiler_t;
typedef void   (*f_visitdecl)(Ctx*, struct knh_Stmt_t*, struct knh_Compiler_t *, struct knh_NameSpace_t *, int);
typedef void   (*f_visitname)(Ctx*, struct knh_Stmt_t*, struct knh_Compiler_t *, struct knh_NameSpace_t *, int);
typedef void   (*f_visitcmpl)(Ctx*, struct knh_Stmt_t*, struct knh_Compiler_t *, struct knh_NameSpace_t *, knh_type_t, int);

/* ------------------------------------------------------------------------ */
/* @class KLRCode Object knh_KLRCode_struct */

typedef struct {
	knh_ushort_t offset;
	knh_ushort_t line;
} knh_dwarf_t;

typedef struct knh_KLRCode {
	knhvmc_t* code;
	size_t size;
	knh_fileid_t fileid;
	knh_nsid_t nsid;
	knh_dwarf_t* dwarf;
	size_t dsize;
} knh_KLRCode_struct;

/* ======================================================================== */

#ifdef OLD
#define KNH_PERROR_BUFSIZ   1024

#define KNH_PERROR(ctx, fid, line, pe, fmt, ...) \
	if(fmt != NULL){ \
		char buf_[KNH_PERROR_BUFSIZ]; \
		knh_snprintf(buf_, sizeof(buf_), ": " fmt, ## __VA_ARGS__); \
		knh_perror(ctx, fid, line, pe, buf_); \
	}else { \
		knh_perror(ctx, fid, line, pe, NULL); \
	} \

#define KNH_TOKEN_PERROR(ctx, tk, pe, fmt, ...) \
	if(fmt != NULL){ \
		char buf_[KNH_PERROR_BUFSIZ]; \
		knh_snprintf(buf_, sizeof(buf_), ": " fmt, ## __VA_ARGS__); \
		knh_Token_perror(ctx, tk, pe, buf_); \
	}else { \
		knh_Token_perror(ctx, tk, pe, NULL); \
	} \

#endif

/* ************************************************************************ */

#ifdef __cplusplus 
}
#endif

#endif /*CLASS_KONOHAC_T_H_*/
