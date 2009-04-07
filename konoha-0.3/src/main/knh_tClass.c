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

#define KNH_TCLASS_C
#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

void KNH_ACLASS(Ctx *ctx, knh_class_t cid, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s[]", CLASSN(p1));
	konoha_addGenericsClass(ctx, cid, new_String(ctx, B(buf), NULL), CLASS_Array, p1, CLASS_Nue);
}

/* ------------------------------------------------------------------------ */

void KNH_ICLASS(Ctx *ctx, knh_class_t cid, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s..", CLASSN(p1));
	konoha_addGenericsClass(ctx, cid, new_String(ctx, B(buf), NULL), CLASS_Iterator, p1, CLASS_Nue);
}

/* ======================================================================== */
/* [SPEC] */

static
Object *knh_ClassTable_fdefault__CSPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *cs = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	return UP(DP(cs)->defvalue);
}

/* ------------------------------------------------------------------------ */

knh_class_t
KNH_XCLASS(Ctx *ctx, knh_class_t cid, knh_class_t bcid, ClassSpec *cs)
{
	if(cid == CLASS_newid) {
		cid = knh_ClassTable_newId(ctx);
	}else {
		KNH_ASSERT(cid + 1 == ctx->share->ClassTableSize);
		ctx->share->ClassTableSize = cid;
	}

	char bufcn[CLASSNAME_BUFSIZ];
	knh_snprintf(bufcn, sizeof(bufcn), KNH_CLASSSPEC_FMT, CLASSN(bcid), knh_String_tochar(DP(cs)->urn));
	konoha_seClassTableName(ctx, cid, new_String(ctx, B(bufcn), NULL));
	DP(cs)->cid = cid;

	ctx->share->ClassTable[cid].bcid   = bcid;
	ctx->share->ClassTable[cid].supcid = bcid;

	if(bcid == CLASS_Int) bcid = CLASS_IntX;
	else if(bcid == CLASS_Float) bcid = CLASS_FloatX;
	else if(bcid == CLASS_String) bcid = CLASS_StringX;

	DBG2_P("%s\n\tcopying from %s", bufcn, CLASSN(bcid));
	ctx->share->ClassTable[cid].cflag  = ctx->share->ClassTable[bcid].cflag;
	ctx->share->ClassTable[cid].oflag  = ctx->share->ClassTable[bcid].oflag;
	ctx->share->ClassTable[cid].offset = ctx->share->ClassTable[bcid].offset;

	ctx->share->ClassTable[cid].sid  = ctx->share->ClassTable[bcid].sid;
	ctx->share->ClassTable[cid].size = ctx->share->ClassTable[bcid].size;
	ctx->share->ClassTable[cid].bsize  = ctx->share->ClassTable[bcid].bsize;

	KNH_ASSERT(ctx->share->ClassTable[cid].cstruct == NULL);
	KNH_INITv(ctx->share->ClassTable[cid].cstruct, ctx->share->ClassTable[bcid].cstruct);

	if(ctx->share->ClassTable[cid].cmap == NULL) {
		KNH_INITv(ctx->share->ClassTable[cid].cmap, new_ClassMap0(ctx, 4));
	}
	else {
		KNH_ASSERT(IS_ClassMap(ctx->share->ClassTable[cid].cmap));
	}
	KNH_ASSERT(ctx->share->ClassTable[cid].cspec == NULL);
	KNH_INITv(ctx->share->ClassTable[cid].cspec, cs);
	ctx->share->ClassTable[cid].fdefault = knh_ClassTable_fdefault__CSPEC;
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t konoha_getcid(Ctx *ctx, char *lname)
{
	DBG2_P("lname='%s'", lname);
	return knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, B(lname));
}

/* ------------------------------------------------------------------------ */

knh_class_t konoha_findcid(Ctx *ctx, knh_bytes_t lname)
{
	DBG2_P("lname='%s'", lname.buf);
	knh_class_t cid = knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, lname);
	if(cid != CLASS_unknown) {
		return cid;
	}
	if(knh_bytes_endsWith(lname, STEXT("[]"))) {
		lname.len -= 2;
		cid = knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, lname);
		if(cid == CLASS_unknown || knh_class_isPrivate(cid)) {
			return CLASS_Array;
		}
		return knh_class_Array(ctx, cid);
	}
	if(knh_bytes_endsWith(lname, STEXT(".."))) {
		lname.len -= 2;
		cid = knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, lname);
		if(cid == CLASS_unknown || knh_class_isPrivate(cid)) {
			return CLASS_Iterator;
		}
		return knh_class_Iterator(ctx, cid);
	}
	if(lname.buf[lname.len-1] == '}') {
		knh_index_t loc = knh_bytes_index(lname, '{');
		if(loc != -1) {
			knh_bytes_t urn = knh_bytes_last(lname, loc+1); urn.len -= 1;
			urn = knh_Runtime_aliasURN(ctx, urn);
			knh_class_t bcid = knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, knh_bytes_first(lname, loc));
			DBG2_P("cid=%d,%s", bcid, CLASSN(bcid));
			ClassSpec *cs = (ClassSpec*)konoha_geClassTableSpec(ctx, bcid, urn);
			if(IS_NOTNULL(cs)) {
				KNH_SETv(ctx, DP(cs)->urn, new_String(ctx, urn, NULL));
				return KNH_XCLASS(ctx, DP(cs)->cid, bcid, cs);
			}
			return bcid;
		}
	}
	return cid;
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
