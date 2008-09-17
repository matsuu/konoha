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
/* [tConst] */

knh_bool_t knh_tConst_exists(Ctx *ctx, knh_bytes_t name)
{
	DictMap *tcmap = DP(knh_rootSystem)->tConstDictMap;
	return (knh_DictMap_index__b(tcmap, name) != -1);
}

/* ------------------------------------------------------------------------ */

Object *knh_tConst_value(Ctx *ctx, knh_bytes_t name)
{
	DictMap *tcmap = DP(knh_rootSystem)->tConstDictMap;
	return knh_DictMap_get__b(ctx, tcmap, name);
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_tClass_addClassConst(Ctx *ctx, knh_class_t cid, knh_bytes_t name, Object *value)
{
	if(cid == CLASS_unknown) {
		return 0;
	}
	else {
		DictMap *tcmap = DP(knh_rootSystem)->tConstDictMap;
		char bufcn[CLASSNAME_BUFSIZ*2];
		size_t i;
		knh_snprintf(bufcn, sizeof(bufcn), "%s.%s", CLASSN(cid), (char*)name.buf);
		name = B(bufcn);
		if(knh_DictMap_index__b(tcmap, name) != -1) {
			return 0;
		}
		knh_DictMap_append(ctx, tcmap, new_String(ctx, name, NULL), value);

		knh_snprintf(bufcn, sizeof(bufcn), "%s_%s", knh_String_tochar(knh_tClass[cid].sname), (char*)name.buf);
		name = B(bufcn);
		for(i = 0; i < name.len; i++) {
			bufcn[i] = toupper(bufcn[i]);
		}
		if(knh_DictMap_index__b(tcmap, name) == -1) {
			knh_DictMap_append(ctx, tcmap, new_String(ctx, name, NULL), value);
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

void KNH_TCONST(Ctx *ctx, String *name, Object *value)
{
	DictMap *tcmap = DP(knh_rootSystem)->tConstDictMap;
	knh_DictMap_append(ctx, tcmap, name, (Object*)value);
}

/* ------------------------------------------------------------------------ */

void KNH_TCONST__T(Ctx *ctx, char *name, Object *value)
{
	DictMap *tcmap = DP(knh_rootSystem)->tConstDictMap;
	knh_DictMap_append(ctx, tcmap, new_String__T(ctx, name), (Object*)value);
}

/* ======================================================================== */

Object *knh_tConst_systemValue(Ctx *ctx, int n)
{
	switch(n) {
		case VM_CONST_CTX:     return (Object*)ctx;
		case VM_CONST_STDIN:   return (Object*)((ctx)->in);
		case VM_CONST_STDOUT:  return (Object*)((ctx)->out);
		case VM_CONST_STDERR:  return (Object*)((ctx)->err);
	}
	DBG_P("unknown system const n=%d", n);
	return KNH_NULL;
}

/* ======================================================================== */
/* [uname] */


#ifdef __cplusplus
}
#endif
