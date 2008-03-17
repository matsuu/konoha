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
/* [structs] */

void knh_Runtime_struct_init(Ctx *ctx0, Struct *s1, int init, Object *cs) 
{
	Runtime *b = (Runtime*)s1;
	b->runtime_id = 0;
	KNH_INITv(b->tmetaHashMap, new_HashMap(ctx0, 0));
	KNH_INITv(b->tnameContextDictMap, new_DictMap(ctx0, 4));
	KNH_INITv(b->tmapmapHashMap, new_HashMap(ctx0, KONOHA_TCLASS_SIZE * 2 + 1));
	KNH_INITv(b->tmethodHashMap, new_HashMap(ctx0, KONOHA_TCLASS_SIZE * 2 + 1));
	KNH_INITv(b->ns, new_NameSpace(ctx0, knh_NameSpace_SYSTEM(), knh_String_EMPTY()));
}

/* ------------------------------------------------------------------------ */

#define _knh_Runtime_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_Runtime_struct_compare NULL

/* ------------------------------------------------------------------------ */

void knh_Runtime_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Runtime *b = (Runtime*)s;
	if(IS_SWEEP(gc)) {
		//DEBUG("sweeping Runtime(%d)", (int)b->konohaid);
	}
	gc(ctx, b->tmetaHashMap);
	gc(ctx, b->tmapmapHashMap);
	gc(ctx, b->tmethodHashMap);
	gc(ctx, b->tnameContextDictMap);	
	gc(ctx, b->ns);
}

/* ======================================================================== */
/* [constructors] */


Runtime* new_Runtime(Ctx *ctx0, knh_uint_t runtime_id)
{
	Runtime *b = (Runtime*)knh_Object_malloc0(ctx0, KNH_FLAG_Runtime, CLASS_Runtime, sizeof(Runtime));
	knh_Runtime_struct_init(ctx0, (Struct*)b, 0, NULL);
	if(runtime_id == 0) {
		DEBUG_ASSERT(knh_Runtime_ROOT() == NULL);
	}
	b->runtime_id = runtime_id;
	return b;
}

/* ======================================================================== */
/* [Context] */

Context *knh_Runtime_getContext(Ctx *ctx0, Runtime *b, knh_bytes_t name)
{
	DEBUG_ASSERT(IS_Runtime(b));
	Context *cx = (Context*)knh_DictMap_getb(ctx0, b->tnameContextDictMap, name);
	if(IS_NULL(cx)) {
		String *cn = new_String__fast(ctx0, CLASS_String, name);
		cx = new_Context(ctx0, b, cn, DEFAULT_SIZE);
		knh_DictMap_set(ctx0, b->tnameContextDictMap, cn, cx);
	}
	return cx;
}

/* ------------------------------------------------------------------------ */

void knh_Runtime_removeContext(Ctx *ctx0, Runtime *b, knh_bytes_t name)
{
	DEBUG_ASSERT(IS_Runtime(b));
	if(IS_NOTNULL(knh_DictMap_getb(ctx0, b->tnameContextDictMap, name))) {
		String *cn = new_String__fast(ctx0, CLASS_String, name);
		knh_DictMap_set(ctx0, b->tnameContextDictMap, cn, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
