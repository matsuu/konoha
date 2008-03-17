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
/* [declare] */

void knh_Cmpl_initDecl(Ctx *ctx, Cmpl *b)
{
	b->vars_size = 0;
	b->vars_offset = 0;
	knh_int_t i;
	for(i = 0; i < KONOHA_LOCALVAR_SIZE; i++) {
		b->vars[i].flag  = 0;
		b->vars[i].type  = TYPE_Any;
		b->vars[i].fn    = FIELDN_NONAME;
		KNH_SETv(ctx, b->vars[i].value, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* [this] */

void
knh_Cmpl_initThisVariable(Ctx *ctx, Cmpl *b, knh_class_t this_cid) 
{
	DEBUG_ASSERT(b->vars_size == 0);
	b->vars[0].flag = 0;
	b->vars[0].type = this_cid;
	b->vars[0].fn   = FIELDN_this;
	KNH_SETv(ctx, b->vars[0].value, KNH_NULL);
	b->vars_size = 1;
}

/* ------------------------------------------------------------------------ */
/* [variable] */

void
knh_Cmpl_declareGlobalVariable(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, int isasis, Object *value)
{
	knh_class_t cid = knh_Object_cid(b->nsproto);	
	knh_index_t idx = knh_Class_indexOfField(cid, fn);
	if(idx == -1) {
		idx = knh_Class_initField(ctx, cid, flag, type, fn, value);
		if(idx == -1) {
			MC_EPRINT(ctx, tke, MC_LANG, "%s has too many field variables.", CLASSN(cid));
			return;
		}
		KNH_SETv(ctx, KNH_FIELDn(b->nsproto, idx), value);
		return;
	}
	else {
		knh_cfield_t *cf = knh_Class_fieldAt(cid, idx);
		if(cf->type != type) {
			if(type != TYPE_any) {
				MC_EPRINT(ctx, tke, MC_IGNORED, "%s%s %s is redefined differently.", TYPEQN(cf->type), FIELDN(fn));
			}
			return;
		}
		if(!isasis) {
			cf->flag |= flag;
			KNH_SETv(ctx, KNH_FIELDn(b->nsproto, idx), value);
		}
	}
}

/* ------------------------------------------------------------------------ */

void
knh_Cmpl_declareVariable(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	fn = FIELDN_UNMASK(fn);
	knh_index_t idx = 0;
	for(idx = 0; idx < KONOHA_LOCALVAR_SIZE; idx++) {
		if(b->vars[idx].fn == FIELDN_NONAME) {
			b->vars[idx].flag = flag;
			b->vars[idx].fn   = fn;
			b->vars[idx].type = type;
			KNH_SETv(ctx, b->vars[idx].value, value);
			knh_cfield_safetype(&(b->vars[idx]));
			b->vars_size = idx + 1;
			return;
		}
		if(b->vars[idx].fn == fn) {
			if(b->vars[idx].type != type) {
				if(type != TYPE_any) {
					MC_EPRINT(ctx, tke, MC_IGNORED, "%s%s %s is redefined differently.", TYPEQN(b->vars[idx].type), FIELDN(fn));
				}
				return;
			}
			//b->vars[idx].flag |= flag;
			return;
		}
	}
	MC_EPRINT(ctx, tke, MC_LANG, "too many variables.");
}

/* ------------------------------------------------------------------------ */
/* [indexOf/typeOf/valueOf] */
/* ------------------------------------------------------------------------ */

knh_index_t 
knh_Cmpl_indexOfVariable(Cmpl *b, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	knh_index_t idx = 0;
	for(idx = 0; idx < b->vars_size; idx++) {
		if(b->vars[idx].fn == fn) {
			return idx;
		}
		if(b->vars[idx].fn == FIELDN_NONAME) {
			return -1;
		}
	}
	return -1;
}

#define _knh_Cmpl_indexOfGlobalVariable(mc, fnq)       knh_Class_queryField(knh_Object_cid(mc->nsproto), fnq)
#define _knh_Cmpl_indexOfFieldVariable(mc, fnq)        knh_Class_queryField(mc->this_cid, fnq)

/* ------------------------------------------------------------------------ */

knh_cfield_t *knh_Cmpl_cfieldOfVariable(Cmpl *b, knh_index_t idx)
{
	DEBUG_ASSERT(idx != -1 && idx < KONOHA_LOCALVAR_SIZE);
	DEBUG_ASSERT(b->vars[idx].fn != FIELDN_NONAME);
	return &(b->vars[idx]);
}

//#define _knh_Cmpl_cfieldOfGlobalVariable(mc, idx)       knh_Class_cfield(knh_Object_cid(mc->nsproto), idx)
//#define _knh_Cmpl_cfieldOfFieldVariable(mc, idx)        knh_Class_cfield(mc->this_cid, idx)
//#define _knh_Cmpl_cfieldOfLocalVariable(mc, idx)        knh_Cmpl_cfieldOfVariable(b, idx)

/* ======================================================================== */
/* [name] */

knh_bool_t 
knh_Cmpl_existsName(Cmpl *b, knh_fieldn_t fnq)
{
	if(FIELDN_IS_U2(fnq)) {
		goto L_GLOBAL;
	}

	if(FIELDN_IS_U1(fnq)) {
		goto L_FIELD;
	}
	
	knh_index_t idx = knh_Cmpl_indexOfVariable(b, FIELDN_UNMASK(fnq));
	if(idx != -1) {
		return 1;
	}
	
	L_FIELD:;
	idx = knh_Class_queryField(b->this_cid, fnq);
	if(idx != -1) {
		return 1;
	}
	
	L_GLOBAL:;
	idx = knh_Class_queryField(knh_Object_cid(b->nsproto), fnq);
	if(idx != -1) {
		return 1;
	}
	return 0;
}




///* ------------------------------------------------------------------------ */
//
//knh_bool_t 
//knh_Cmpl_isGlobalName(Ctx *ctx, Cmpl *b, Token *tk)
//{
//	knh_fieldn_t fnq = knh_Token_tofieldn(ctx, tk);
//
//	if(FIELDN_IS_U2(fnq)) {
//		goto L_GLOBAL;
//	}
//
//	if(FIELDN_IS_U1(fnq)) {
//		goto L_FIELD;
//	}
//	
//	knh_index_t idx = knh_Cmpl_indexOfVariable(b, FIELDN_UNMASK(fnq));
//	if(idx != -1) {
//		return 0;
//	}
//	
//	L_FIELD:;
//	idx = knh_Class_queryField(b->this_cid, fnq);
//	if(idx != -1) {
//		return 0;
//	}
//	
//	L_GLOBAL:;
//	idx = knh_Class_queryField(knh_Object_cid(b->nsproto), fnq);
//	if(idx != -1) {
//		return 1;
//	}
//	return 0;
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
