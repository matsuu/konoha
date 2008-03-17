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

/* ------------------------------------------------------------------------ */
/* [macros] */

#ifndef BOT_TEXPT_newId
#define BOT_TEXPT_newId
#define EOT_TEXPT_newId
#endif

/* ======================================================================== */
/* [global] */

#ifndef KONOHA_TEXPT_SIZE
#define KONOHA_TEXPT_SIZE 1024
#endif 

#define TEXPTDB_SIZE  (KONOHA_TEXPT_SIZE * sizeof(knh_texpt_t))

static knh_texpt_t  *texptList           = NULL;
static size_t    texptList_size          = 0;
static HashSet  *texptNameHashSet        = NULL;

/* ------------------------------------------------------------------------ */

void knh_texpt_ginit()
{
	size_t i;
	texptList = (knh_texpt_t*)knh_malloc(NULL, TEXPTDB_SIZE);
	texptList_size = 1;
	for(i = 0; i < KONOHA_TEXPT_SIZE; i++) {
		texptList[i].flag     = 0;
		texptList[i].parent   = 1;
		texptList[i].name     = NULL;
	}
	KNH_INITv(texptNameHashSet, new_HashSet(NULL, 0));
}

/* ------------------------------------------------------------------------ */

void knh_texpt_gtraverse(Ctx *ctx, f_gc gc)
{
	knh_int_t i;
	gc(ctx, texptNameHashSet);
	/* texpt */
	if(IS_SWEEP(gc)) {
		for(i = 0; i < texptList_size; i++) {
			if(texptList[i].name != NULL) {
				gc(ctx, texptList[i].name);
			}
			texptList[i].parent = 1;
		}
		knh_free(texptList, TEXPTDB_SIZE);
		texptNameHashSet = NULL;
		texptList = NULL;
	}else {
		for(i = 0; i < texptList_size; i++) {
			if(texptList[i].name != NULL) {
				gc(ctx, texptList[i].name);
			}
		}
	}
}

/* ------------------------------------------------------------------------ */
/* [new] */

knh_expt_t knh_texpt_newId(Ctx *ctx) 
{
	if(texptList_size == KONOHA_TEXPT_SIZE) {
		KNH_THROWs(ctx, "OutOfMemory!!: KONOHA_TEXPT_SIZE");
		return 0;
	}
	BOT_TEXPT_newId;
	knh_expt_t newid = texptList_size++;
	EOT_TEXPT_newId;
	return newid;
}

/* ------------------------------------------------------------------------ */
/* [field] */

INLINE
knh_bool_t knh_texpt_isvalid(knh_expt_t eid)
{
	return (0 < eid && eid < texptList_size);
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_flag_t knh_texpt_flag(knh_expt_t eid)
{
	KNH_ASSERT(knh_texpt_isvalid(eid));
	return texptList[eid].flag;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_expt_t knh_texpt_parent(knh_expt_t eid)
{
	KNH_ASSERT(knh_texpt_isvalid(eid));
	return texptList[eid].parent;
}

/* ------------------------------------------------------------------------ */


knh_bool_t knh_texpt_isa(knh_expt_t eid, knh_expt_t parent) 
{
	KNH_ASSERT(knh_texpt_isvalid(eid));
	KNH_ASSERT(parent < texptList_size);
	if(eid == parent || parent == 1) return 1;
	if(eid == 1) return 0;
	while((eid = texptList[eid].parent) != 1) {
		if(eid == parent) return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

#define _EXPTN(eid)   knh_String_tochar(knh_texpt_name(eid))

INLINE 
String *knh_texpt_name(knh_expt_t eid)
{
	KNH_ASSERT(knh_texpt_isvalid(eid));
	return texptList[eid].name;
}

/* ------------------------------------------------------------------------ */
/* [TABLE] */


knh_expt_t TEXPT(Ctx *ctx, knh_flag_t flag, knh_class_t eid, knh_bytes_t ename, char *pname)
{
	if(eid == EXPT_newid) {
		eid = knh_texpt_newId(ctx);
	}else {
		KNH_ASSERT(eid == texptList_size);
		texptList_size++;
	}
	KNH_ASSERT(knh_texpt_isvalid(eid));
		
	knh_expt_t parent = EXPT_Exception;
	if(pname != NULL) {
		parent = knh_texpt_forname(ctx, B(pname), EXPT_NoSuchException);
		if(parent == EXPT_NoSuchException) {
			DEBUG("NoSuchException!!: %s", pname);
			parent = EXPT_Exception;
		}
	}

	KNH_ASSERT(texptList[eid].name == NULL);
	texptList[eid].flag = flag;
	texptList[eid].parent = parent;
	KNH_INITv(texptList[eid].name, new_String__fast(ctx, CLASS_String__expt, ename));
	knh_HashSet_put(ctx, texptNameHashSet, 
		knh_String_hcode(texptList[eid].name), texptList[eid].name, eid);
	DEBUG("Generating new Exception eid=%d name='%s'", eid, knh_String_tochar(texptList[eid].name));
	return eid;
}

/* ------------------------------------------------------------------------ */
/* [forname] */

/* Allow msg like 'Exception!!: Dont\'t stop me' */

knh_expt_t knh_texpt_forname(Ctx *ctx, knh_bytes_t msg, knh_expt_t def)
{
	knh_int_t loc = knh_bytes_index(msg, '!');
	if(loc == -1 && msg.buf[loc+1] != '!') {
		return def;
	}
	knh_bytes_t enm = knh_bytes_first(msg, loc+2);
	if(enm.len == 0) return EXPT_Exception; /* '!!' */
	knh_expt_t eid = (knh_expt_t)knh_HashSet_get__b(ctx, texptNameHashSet, enm);
	if(eid != 0) return eid;
	if(msg.buf[loc+2] == '!') return EXPT_NoSuchException;
	return TEXPT(ctx, KNH_FLAG_EF_GENERATED, EXPT_newid, enm, NULL);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
