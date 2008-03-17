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

void
knh_Cmpl_declareClass(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_class_t cid, knh_class_t supcid)
{
	DEBUG_ASSERT(b->this_cid == cid);
	DEBUG("b->this_cid=%s, cid=%s, supcid=%s", CLASSN(b->this_cid), CLASSN(cid), CLASSN(supcid));

	if(KNH_FLAG_IS(knh_tclass_cflag(supcid), KNH_FLAG_CF_NA)) {
		knh_Token_setPerrored(tke, 0);
		MC_EPRINT(ctx, tke, MC_ERROR, "you cann't extend %s", CLASSN(supcid));
		supcid = CLASS_Object;
	}

	knh_int_t i;
	knh_struct_t sid = b->vars_size;
	if(!(sid < CLASS_Prototype)) {
		knh_Token_setPerrored(tke, 0);
		MC_EPRINT(ctx, tke, MC_LANG, "%s has too many fields: %d (< %d)", CLASSN(b->this_cid), (int)b->vars_size, (int)CLASS_Prototype);
		for(i = CLASS_Prototype; i < b->vars_size; i++) {
			knh_Token_setPerrored(tke, 0);
			MC_EPRINT(ctx, tke, MC_IGNORED, "%s in %s", FIELDN(b->vars[i].fn), CLASSN(b->this_cid));
		}
		sid = CLASS_Prototype - 1;
	}
	ClassStruct *cs = new_ClassStruct(ctx, b->vars_size);
	for(i = 0; i < sid; i++) {
		cs->fields[i].flag = b->vars[i].flag;
		cs->fields[i].type = b->vars[i].type;
		cs->fields[i].fn   = b->vars[i].fn;
		KNH_SETv(ctx, cs->fields[i].value, b->vars[i].value);
	}
	KNH_TCLASS_STRUCT(ctx, flag, cid, sid, supcid, cs);

#if defined(KONOHA_DEBUGMODE)
	DEBUG("HERE IS DEFINED STRUCT");
	knh_cfield_dump(ctx, cs->fields, 0, cs->fsize, KNH_STDOUT);
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
