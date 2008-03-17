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

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif


/* ======================================================================== */
/* [macros] */

#define _STRUCT_newid         0
#define _STRUCT_TUPLE(s)      (knh_struct_t)(sizeof(s)/sizeof(Object*))

/* ======================================================================== */
/* [global] */

#ifndef KONOHA_TSTRUCT_SIZE
#define KONOHA_TSTRUCT_SIZE 256
#endif 

#define TSTRUCTDB_SIZE  (KONOHA_TSTRUCT_SIZE * sizeof(knh_tstruct_t))

knh_tstruct_t *tstructList           = NULL;
size_t     tstructList_size         = 0;

/* ------------------------------------------------------------------------ */

void knh_tstruct_ginit(void)
{
	DEBUG_ASSERT(tstructList == NULL);	
	tstructList = (knh_tstruct_t*)knh_malloc(NULL, TSTRUCTDB_SIZE);
	tstructList_size = 0;
	size_t i;
	for(i = 0; i < KONOHA_TSTRUCT_SIZE; i++) {
		tstructList[i].size       = 0;
		tstructList[i].name       = "";
		tstructList[i].finit      = knh_tstruct_init__default;
		tstructList[i].fcopy      = NULL;
		tstructList[i].fcompr     = knh_tstruct_compare__default;
		tstructList[i].ftravr     = knh_tstruct_traverse__default;
	}
}

/* ------------------------------------------------------------------------ */

void knh_tstruct_gtraverse(Ctx *ctx, f_gc gc)
{
	DEBUG_ASSERT(tstructList != NULL);
	knh_free(tstructList, TSTRUCTDB_SIZE);
	tstructList = NULL;
}

/* ------------------------------------------------------------------------ */


knh_struct_t 
KNH_TSTRUCT(Ctx *ctx, knh_struct_t sid, size_t size, char *name, f_struct_init f0, f_struct_copy f1, f_struct_compare f2, f_struct_traverse f3)
{
	KNH_ASSERT(tstructList != NULL);
	if(tstructList_size == KONOHA_TSTRUCT_SIZE) {
		KNH_THROWs(ctx, "OutOfMemory!!: overflow KONOHA_TSTRUCT_SIZE");
		return 0;
	}

	if(sid == STRUCT_newid) sid = tstructList_size;
	KNH_ASSERT(sid == tstructList_size);
	tstructList_size++;

#ifdef KONOHA_SAFEMODE
	if(size % sizeof(void*) != 0) {
		DEBUG("%s has a particular size %d", name, (int)size);
	}
#endif

	tstructList[sid].size     = KNH_SIZE(size);
	tstructList[sid].name     = name;
	tstructList[sid].finit    = (f0 == NULL) ? knh_tstruct_init__default : f0;
	tstructList[sid].fcopy    = f1;
	tstructList[sid].fcompr   = (f2 == NULL) ? knh_tstruct_compare__default:  f2;
	tstructList[sid].ftravr   = (f3 == NULL) ? knh_tstruct_traverse__default: f3;
	return sid;
}

/* ------------------------------------------------------------------------ */

void knh_tstruct_init__default(Ctx *ctx, Struct *s1, int init, Object *cs)
{

}

/* ------------------------------------------------------------------------ */

knh_int_t knh_tstruct_compare__default(Ctx *ctx, Struct *s1, Struct *s2)
{
	return s1 - s2;
}

/* ------------------------------------------------------------------------ */

void knh_tstruct_traverse__default(Ctx *ctx, Struct *s, f_gc gc)
{

}

/* ======================================================================== */
/* [size] */

INLINE
size_t knh_tstruct_size(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return tstructList[sid].size;	
}

/* ------------------------------------------------------------------------ */

INLINE
bsize_t knh_tstruct_bsize(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return (bsize_t)(tstructList[sid].size / sizeof(Object*));	
}

/* ------------------------------------------------------------------------ */

char *knh_tstruct_name(knh_struct_t sid)
{
	if(sid < tstructList_size) {
		return tstructList[sid].name;
	}
	DEBUG("unknown sid=%d", sid);
	return "STRUCT_unknown";
}

#define _STRUCTN(sid)   knh_tstruct_name(sid)

/* ======================================================================== */
/* [structs] */

INLINE
f_struct_init knh_tstruct_finit(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return tstructList[sid].finit;
}

/* ------------------------------------------------------------------------ */

INLINE
f_struct_copy knh_tstruct_fcopy(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return tstructList[sid].fcopy;	
}

/* ------------------------------------------------------------------------ */

INLINE
f_struct_compare knh_tstruct_fcompare(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return tstructList[sid].fcompr;	
}

/* ------------------------------------------------------------------------ */

INLINE
f_struct_traverse knh_tstruct_ftraverse(knh_struct_t sid)
{
	KNH_ASSERT(sid < tstructList_size);
	return tstructList[sid].ftravr;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
