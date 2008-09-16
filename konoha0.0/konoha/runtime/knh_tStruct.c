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

/* ************************************************************************ */

#define KNH_TSTRUCT_C

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* [global] */

#define _KNH_FLAG_SF_FIELD          KNH_FLAG_T1

#define _STRUCT_ISFIELD(sid)        ((sid & KNH_FLAG_SF_FIELD) == KNH_FLAG_SF_FIELD)
#define _BSIZE_TOSID(bsize)         (((knh_struct_t)bsize)|KNH_FLAG_SF_FIELD)
#define _STRUCT_FIELD(bsize)        (((knh_struct_t)bsize)|KNH_FLAG_SF_FIELD)
#define _STRUCT_FIELDSIZE(sid)      (sid & (~KNH_FLAG_SF_FIELD))
#define _STRUCT_UNMASK(sid)         (sid & (~KNH_FLAG_SF_FIELD))

/* ------------------------------------------------------------------------ */

#define SIZEOF_TSTRUCT    (KNH_TSTRUCT_SIZE * sizeof(knh_tStruct_t))

knh_tStruct_t *knh_tStruct    = NULL;
static size_t  knh_tStructSize   = 0;

/* ------------------------------------------------------------------------ */

int IS_sid(knh_struct_t sid)
{
	return (sid < knh_tStructSize);
}

#define _DEBUG_ASSERT_sid(sid)   KNH_ASSERT(IS_sid(sid))

/* ------------------------------------------------------------------------ */

static
void knh_tStruct_finit__nop(Ctx *ctx, void *s1, int init, Object *cs)
{

}

/* ------------------------------------------------------------------------ */

static
void knh_tStruct_ftraverse__nop(Ctx *ctx, void *s, f_traverse f)
{

}

/* ------------------------------------------------------------------------ */

static knh_hcode_t knh_Object_fhashCode__default(Object* o1)
{
	return ((knh_hcode_t)o1) / sizeof(Object*);
}

/* ------------------------------------------------------------------------ */

static int knh_Object_fcompareTo__default(Object *o1, Object *o2)
{
	return (int)(o1 - o2);
}

/* ------------------------------------------------------------------------ */

void knh_tStruct_init0(void)
{
	KNH_ASSERT(knh_tStruct == NULL);
	knh_tStruct = (knh_tStruct_t*)KNH_MALLOC(NULL, SIZEOF_TSTRUCT);
	knh_tStructSize = 0;
	size_t i;
	for(i = 0; i < KNH_TSTRUCT_SIZE; i++) {
		knh_tStruct[i].size       = 0;
		knh_tStruct[i].name       = "";
		knh_tStruct[i].finit      = knh_tStruct_finit__nop;
		knh_tStruct[i].fcopy      = NULL;
//		knh_tStruct[i].fcompare   = knh_tStruct_fcompare__default;
		knh_tStruct[i].ftraverse  = knh_tStruct_ftraverse__nop;
		knh_tStruct[i].fhashCode  = knh_Object_fhashCode__default;
		knh_tStruct[i].fcompareTo = knh_Object_fcompareTo__default;
	}
}

/* ------------------------------------------------------------------------ */

void knh_tStruct_traverse(Ctx *ctx, f_traverse f)
{
	KNH_ASSERT(knh_tStruct != NULL);
	if(IS_SWEEP(f)) {
		KNH_FREE(knh_tStruct, SIZEOF_TSTRUCT);
		knh_tStruct = NULL;
		knh_tStructSize = 0;
	}
}

/* ------------------------------------------------------------------------ */

knh_struct_t
KNH_TSTRUCT(Ctx *ctx,
		knh_struct_t sid, size_t size, char *name,
		f_tStruct_init f0, f_tStruct_copy f1, /* f_tStruct_compare f2,*/ f_tStruct_traverse f3,
		f_hashCode f4, f_compareTo f5)
{
	KNH_ASSERT(knh_tStruct != NULL);
	if(!(knh_tStructSize < KNH_TSTRUCT_SIZE)) {
		KNH_EXIT("enlarge KNH_TSTRUCT_SIZE %d", KNH_TSTRUCT_SIZE);
		return 0;
	}

	if(sid == STRUCT_newid) sid = knh_tStructSize;
	KNH_ASSERT(sid == knh_tStructSize);
	knh_tStructSize++;

	if(size % sizeof(Object*) != 0) {
		DBG2_P("%s has a particular size %d", name, (int)size);
	}

	knh_tStruct[sid].size      = size;
	knh_tStruct[sid].name      = name;
	knh_tStruct[sid].finit     = (f0 == NULL) ? knh_tStruct_finit__nop : f0;
	knh_tStruct[sid].fcopy     = f1;
//	knh_tStruct[sid].fcompare  = (f2 == NULL) ? knh_tStruct_fcompare__default:  f2;
	knh_tStruct[sid].ftraverse = (f3 == NULL) ? knh_tStruct_ftraverse__nop: f3;
	if(f4 != NULL) {
		knh_tStruct[sid].fhashCode  = f4;
	}
	if(f5 != NULL) {
		knh_tStruct[sid].fcompareTo = f5;
	}
	return sid;
}

/* ======================================================================== */
/* [size] */

//INLINE
//bsize_t knh_tstruct_bsize(knh_struct_t sid)
//{
//	KNH_ASSERT(sid < knh_tStructSize);
//	return (bsize_t)(knh_tStruct[sid].size / sizeof(Object*));
//}

/* ------------------------------------------------------------------------ */

char *knh_tstruct_name(knh_struct_t sid)
{
	if(sid < knh_tStructSize) {
		return knh_tStruct[sid].name;
	}
	DBG2_P("unknown sid=%d", sid);
	return "STRUCT_unknown";
}

#define _STRUCTN(sid)   knh_tstruct_name(sid)

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
