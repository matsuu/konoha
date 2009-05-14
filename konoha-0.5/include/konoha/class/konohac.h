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
/* @flag Token.BOL TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.TailWildCard TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.TopDot TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Getter TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Setter TKF SP(%s)->flag 'is:set:*:*' */

/* @flag Token.ExceptionType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.NotNullType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.IteratorType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.ArrayType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.NullableType TKF SP(%s)->flag 'is:set:*:*' */

#define knh_Token_isUnsafeType(o)  knh_Token_isTailWildCard(o)
#define knh_Token_setUnsafeType(o, b) knh_Token_setTailWildCard(o, b)

/* ------------------------------------------------------------------------ */

#define knh_Token_isTyped(o)    (TT_CONST <= SP(o)->tt && SP(o)->tt <=TT_NOP)

typedef struct knh_Token {
	knh_type_t   type;
	union {
		knh_token_t   tt_next;
		knh_short_t   index;   /* STACK, FIELD, GLOBAL, SYSVAL, DEFVAL */
		knh_methodn_t mn;
		knh_token_t   tt_op;
		knh_fieldn_t  fn;
		knh_class_t   cid;
	};
	union {
		Object* data;
		struct knh_Array_t*  list;
		struct knh_String_t* text;
		struct knh_Token_t* token;
		struct knh_Method_t* mtd;
		struct knh_Int_t *num;
	};
} knh_Token_struct;

typedef struct knh_tokens_t {
	struct knh_Token_t** ts;
	int meta;
	int c;
	int e;
} knh_tokens_t;

#define TT_RAW   TT_CONST

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* @class Stmt Object knh_Stmt_struct */
/* @flag Stmt.Adposition STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.NonNewLine STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Typed STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Memo1 STMTF SP(%s)->flag 'is:set:*:*' */

/* MAPCAST */

#define knh_Stmt_isNNCAST(s)       knh_Stmt_isMemo1(s)
#define knh_Stmt_setNNCAST(s,b)    knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isMAPNEXT(s)      knh_Stmt_isMemo1(s)
#define knh_Stmt_setMAPNEXT(s,b)   knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isVOID(s)         knh_Stmt_isMemo1(s)
#define knh_Stmt_setVOID(s,b)      knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isTHISSUPER(s)    knh_Stmt_isMemo1(s)
#define knh_Stmt_setTHISSUPER(s,b) knh_Stmt_setMemo1(s,b)

/* ------------------------------------------------------------------------ */

#define KNH_STT_RVALUE  0
#define KNH_RVALUE      0
#define KNH_STT_LVALUE  1
#define KNH_LVALUE      1

typedef struct knh_Stmt {
	knh_type_t   type;
	knh_short_t   line_end;
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

#define KNH_LOCALSIZE 64

/* ------------------------------------------------------------------------ */
/* KLRCode */
/* ------------------------------------------------------------------------ */

typedef unsigned char          knh_opcode_t;
typedef int                    knh_labelid_t;
typedef knh_short_t            knh_sfi_t;

typedef struct {
	knh_sfi_t i;
	size_t    n;
} knh_sfx_t;

typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	void *nextaddr;
} knh_kode_t;

#define KNH_OPCODE(pc)          ((knh_kode_t*)pc)->opcode

#define KNH_ASSERT_OPCODE(c) \
	if(c > OPCODE_NOP) {\
		DBG_P("Invalid opcode=%d", (int)c); \
		KNH_ASSERT(c <= OPCODE_NOP); \
	}\

/* ------------------------------------------------------------------------ */
/* @class Asm Object knh_Asm_struct @Private */
/* @flag Asm.Cancelled  CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Asm.PROCEED    CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Asm.YEILD      CPF DP(%s)->flag 'is:set:*:*' */

#ifndef KONOHA_LOCALSIZE
#define KONOHA_LOCALSIZE 128
#endif

#define KNH_ASM_REGMAX 32

typedef struct {
	knh_short_t level;
	knh_short_t varidx;
	struct knh_Stmt_t *stmt;
} knh_asmreg_t ;

typedef struct {
	int offset;
	struct knh_Token_t *tklabel;
} knh_labeltbl_t ;

typedef knh_uint64_t  knh_rtti_t;

typedef struct knh_Asm {
	knh_flag_t             flag;
	knh_class_t            this_cid;
	struct knh_NameSpace_t *ns;
	struct knh_Method_t    *mtd;
	knh_type_t             rtype;
	knh_ushort_t vars_size;
	knh_cfield_t* vars;
	knh_rtti_t nnrtti0;
	knh_rtti_t nnrtti;
	int                     level; /* 0.3 */
	int stack;
	int globalidx;
	int llstep;

	knh_asmreg_t *regs;
	knh_ushort_t regs_size;
	knh_ushort_t regs_usedsize;

	struct knh_DictSet_t* name2labelIdDictSet;
	size_t labelmax;
	size_t labelcapacity;
	knh_labeltbl_t *labels;
	knh_Array_t*          lstacks;
	struct knh_Stmt_t*    finallyStmt;

	knh_fileid_t           fileid;
	knh_sline_t            line;
	struct knh_Bytes_t* elf;
	struct knh_Bytes_t* dwarf;
	knh_kode_t         *prev_op;

	void *dlhdr;
	struct knh_Array_t *constPools;
	struct knh_Array_t *exportsMethods;
} knh_Asm_struct;



/* ------------------------------------------------------------------------ */
/* @class KLRCode Object knh_KLRCode_struct */

typedef struct {
	knh_ushort_t offset;
	knh_ushort_t line;
} knh_dwarf_t;

typedef struct knh_KLRCode {
	knh_code_t* code;
	size_t size;
	knh_fileid_t fileid;
//	knh_nsid_t nsid;
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
