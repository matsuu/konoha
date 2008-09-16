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
/* [macros] */

#define _KNH_FLAG_CF2OF(f)        (f)
#define _knh_tClass_isPMZ(cid)    (knh_tClass[cid].p1 != CLASS_Nue)

static knh_Object_t *knh_tClass_fdefault__INIT(Ctx *ctx, knh_class_t cid);

/* ======================================================================== */
/* [global] */

#define SIZEOF_TCLASS  (KNH_TCLASS_SIZE * sizeof(knh_tClass_t))

knh_tClass_t    *knh_tClass           = NULL;
static size_t    knh_tClassSize       = 0;

/* ======================================================================== */
/* [sync] */

#define KNH_SLOCK()
#define KNH_UNSLOCK()

/* ------------------------------------------------------------------------ */

void knh_tClass_init0(void)
{
	KNH_ASSERT(knh_tClass == NULL);
	size_t i;
	knh_tClass = (knh_tClass_t*)KNH_MALLOC(NULL, SIZEOF_TCLASS);
	knh_tClassSize = 0;
	for(i = 0; i < KNH_TCLASS_SIZE; i++) {
		knh_tClass[i].cflag    = 0;
		knh_tClass[i].oflag    = 0;
		knh_tClass[i].bcid     = 0;
		knh_tClass[i].supcid   = 0;
		knh_tClass[i].p1       = CLASS_Nue;   /* @deps knh_tClass_isPMZ(cid)*/
		knh_tClass[i].p2       = CLASS_Nue;
		knh_tClass[i].offset   = 0;
		knh_tClass[i].sid      = 0;
		knh_tClass[i].size     = 0;
		knh_tClass[i].bsize    = 0;
		knh_tClass[i].keyidx   = -1;
		knh_tClass[i].keyidx2   = -1;

		knh_tClass[i].sname     = NULL;
		knh_tClass[i].lname     = NULL;
		knh_tClass[i].class_cid    = NULL;
		knh_tClass[i].cstruct  = NULL;
		knh_tClass[i].cmap     = NULL;
		knh_tClass[i].cspec    = NULL;
		knh_tClass[i].fdefault   = knh_tClass_fdefault__INIT;
		//knh_tClass[i].fcompare = knh_tClass_fcompare__default;
	}
}

/* ------------------------------------------------------------------------ */

void knh_tClass_traverse(Ctx *ctx, f_traverse f)
{
	KNH_ASSERT(knh_tClass != NULL);
	int i;
	/* tclass */
	if(IS_SWEEP(f)) {
		for(i = knh_tClassSize - 1; i >= 0; i--) {
			if(knh_tClass[i].sname != NULL) {
				knh_ClassStruct_toAbstractAll(ctx, knh_tClass[i].cstruct);
			}
		}
	}
	for(i = knh_tClassSize - 1; i >= 0; i--) {
		if(knh_tClass[i].sname != NULL) {
			f(ctx, (knh_Object_t*)knh_tClass[i].sname);
			f(ctx, (knh_Object_t*)knh_tClass[i].lname);
			f(ctx, (knh_Object_t*)knh_tClass[i].class_cid);
			f(ctx, (knh_Object_t*)knh_tClass[i].cstruct);
			f(ctx, (knh_Object_t*)knh_tClass[i].cmap);
			f(ctx, (knh_Object_t*)knh_tClass[i].cspec);
		}
	}
	if(IS_SWEEP(f)) {
		KNH_FREE(knh_tClass, SIZEOF_TCLASS);
		knh_tClass = NULL;
	}
}

/* ======================================================================== */
/* [newid] */

knh_class_t knh_tClass_newId(Ctx *ctx)
{
	knh_class_t newid;
	KNH_SLOCK();
	if(!(knh_tClassSize < KNH_TCLASS_SIZE)) {
		KNH_EXIT("Enlarge KNH_TCLASS_SIZE %d", KNH_TCLASS_SIZE);
		return CLASS_unknown;
	}
	newid = knh_tClassSize;
	knh_tClassSize++;
	KNH_UNSLOCK();
	return newid;
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_tClass_size(void)
{
	return knh_tClassSize;
}


/* ------------------------------------------------------------------------ */

INLINE
int IS_cid(knh_class_t cid)
{
	return (cid < knh_tClassSize);
}

#define _DEBUG_ASSERT_cid(cid)    KNH_ASSERT(IS_cid(cid))

/* ------------------------------------------------------------------------ */

static
knh_Class_t *new_Class0(Ctx *ctx, knh_class_t cid)
{
	knh_Class_t *o = (knh_Class_t*)new_PObject0(ctx, FLAG_Class, CLASS_Class, CLASS_Class);
	o->cid = cid;
	o->type = cid;
	return o;
}

/* ------------------------------------------------------------------------ */

INLINE
void KNH_TCLASS_NAME(Ctx *ctx, knh_class_t cid, String *lname)
{
	DEBUG_ASSERT_cid(cid);
	KNH_ASSERT(knh_tClass[cid].class_cid == NULL);
	KNH_INITv(knh_tClass[cid].class_cid, new_Class0(ctx, cid));
	KNH_INITv(knh_tClass[cid].lname, lname);
	//DBG2_P("lname='%s'", knh_String_tochar(lname));
	knh_NameSpace_setClass(ctx, knh_rootNameSpace, lname, cid);
	{
		knh_bytes_t n = knh_String_tobytes(lname);
		knh_index_t idx = knh_bytes_index(n, '{');
		if(idx != -1) {
			KNH_INITv(knh_tClass[cid].sname, lname);
			return;
		}
		if(knh_bytes_endsWith(n, STEXT(".."))) {
			n.len -= 2;
			idx = knh_bytes_rindex(n, '.');
			n.len += 2;
		}
		else {
			idx = knh_bytes_rindex(n, '.');
		}
		if(idx == -1) {
			KNH_INITv(knh_tClass[cid].sname, lname);
		}
		else {
			KNH_INITv(knh_tClass[cid].sname, new_String0(ctx, knh_bytes_last(n, idx + 1), lname));
		}
	}
}


/* ======================================================================== */
/* [name] */

#define _CLASSN(cid)   knh_String_tochar(knh_tClass[cid].lname)
#define _CLASSNo(o)    knh_String_tochar(knh_tClass[(o)->h.cid].lname)

INLINE
String *knh_tClass_name(knh_class_t cid)
{
	DBG2_ASSERT(cid < knh_tClassSize, "unknown cid = %d, perhaps? %d", cid, TYPE_UNMASK(cid));
	return knh_tClass[cid].lname;
}

/* ======================================================================== */
/* [value] */

static
knh_Object_t *knh_tClass_fdefault__CSPECVALUE(Ctx *ctx, knh_class_t cid)
{
	return knh_tClass[cid].cspec;
}

/* ------------------------------------------------------------------------ */

static
knh_Object_t *knh_tClass_fdefault__INIT(Ctx *ctx, knh_class_t cid)
{
	//DBG2_P("%s", CLASSN(cid));
	KNH_ASSERT(IS_NULL(knh_tClass[cid].cspec));
	Object *v = new_Object__init(ctx, knh_tClass[cid].oflag | KNH_FLAG_OF_IMMUTABLE, cid);
	KNH_SETv(ctx, knh_tClass[cid].cspec, v);
	knh_tClass[cid].fdefault = knh_tClass_fdefault__CSPECVALUE;
	return knh_tClass[cid].cspec;
}

/* ------------------------------------------------------------------------ */

Object *knh_tClass_defaultValue(Ctx *ctx, knh_class_t cid)
{
	DEBUG_ASSERT_cid(cid);
	return knh_tClass[cid].fdefault(ctx, cid);
}

/* ======================================================================== */
/* [TABLE] */

knh_class_t
KNH_TCLASS__T(Ctx *ctx, knh_flag_t flag, char *text, knh_class_t cid, knh_struct_t sid, knh_class_t supcid, knh_Object_t *cspec, f_default fdefault, int method_size)
{
	//DBG2_P("%s(cid=%d)", knh_String_tochar(name), cid);
	if(cid == CLASS_newid) {
		KNH_ASSERT(ctx != NULL);
		cid = knh_tClass_newId(ctx);
	}else {
		KNH_ASSERT(ctx == NULL);
		if(!(cid < knh_tClassSize)) {
			knh_tClassSize = cid + 1;
		}
	}


	KNH_TCLASS_NAME(ctx, cid, new_String__T(ctx, text));

	knh_tClass[cid].cflag  = flag;
	knh_tClass[cid].oflag  = KNH_FLAG_CF2OF(flag);

	knh_tClass[cid].bcid   = cid;
	knh_tClass[cid].supcid = supcid;
	if(supcid == CLASS_Object) {
		knh_tClass[cid].offset = 0;
	}else {
		KNH_ASSERT(supcid < cid);
		knh_tClass[cid].offset = knh_tClass[supcid].bsize;
	}

	knh_tClass[cid].sid    = sid;
	if(STRUCT_ISFIELD(sid)) {
		knh_tClass[cid].bsize = (knh_tClass[cid].offset + STRUCT_FIELDSIZE(sid));
		knh_tClass[cid].size = knh_tClass[cid].bsize * sizeof(knh_Object_t*);
//		if(knh_tClass[supcid].bcid == CLASS_Object) {
			knh_tClass[cid].bcid = CLASS_Object;
//		}
	}
	else {
		knh_tClass[cid].size = (knh_tClass[cid].offset * sizeof(knh_Object_t*)) + knh_tStruct[cid].size;
		knh_tClass[cid].bsize  = knh_tClass[cid].size / sizeof(knh_Object_t*);
	}

	KNH_ASSERT(knh_tClass[cid].cstruct == NULL);
	KNH_INITv(knh_tClass[cid].cstruct, new_ClassStruct0(ctx, sid, method_size));

	KNH_ASSERT(knh_tClass[cid].cmap == NULL);
	KNH_INITv(knh_tClass[cid].cmap, new_ClassMap0(ctx, 4));

	KNH_ASSERT(knh_tClass[cid].cspec == NULL);
	KNH_INITv(knh_tClass[cid].cspec, cspec);

	if(fdefault == NULL) {
		if(knh_Object_cid(cspec) == cid) {
			fdefault = knh_tClass_fdefault__CSPECVALUE;
		}
		else {
			KNH_ASSERT(IS_NULL(cspec));
			fdefault = knh_tClass_fdefault__INIT;
		}
	}
	knh_tClass[cid].fdefault = fdefault;
	return cid;
}

/* ======================================================================== */
/* [PARAM] */

void KNH_TCLASS_DEFAULT(Ctx *ctx, knh_class_t cid, Object *value, f_default fdefault)
{
	DEBUG_ASSERT_cid(cid);
	KNH_ASSERT(knh_tClass[cid].cspec == NULL);
	KNH_INITv(knh_tClass[cid].cspec, value);
	if(fdefault == NULL) {
		if(IS_NULL(value)) {
			fdefault = knh_tClass_fdefault__INIT;
		}
		else {
			fdefault = knh_tClass_fdefault__CSPECVALUE;
		}
	}
	knh_tClass[cid].fdefault = fdefault;
}

/* ------------------------------------------------------------------------ */

void KNH_TCLASS_PARAM(Ctx *ctx, knh_class_t cid, knh_class_t p1, knh_class_t p2)
{
	DEBUG_ASSERT_cid(cid);
	KNH_ASSERT(knh_tClass[cid].p1 == CLASS_Nue);
	knh_tClass[cid].p1 = p1;
	knh_tClass[cid].p2 = p2;
	if(!knh_class_isCyclic(cid)) {
		if(knh_class_isCyclic(p1) || knh_class_isCyclic(p2)) {
			knh_class_setCyclic(cid, 1);
		}
	}
}

/* ------------------------------------------------------------------------ */

knh_class_t KNH_TPMZCLASS(Ctx *ctx, knh_class_t cid, String *name, knh_class_t bcid, knh_class_t p1, knh_class_t p2)
{
	if(cid == CLASS_newid) {
		KNH_ASSERT(ctx != NULL);
		cid = knh_tClass_newId(ctx);
	}else {
		KNH_ASSERT(ctx == NULL);
		if(!(cid < knh_tClassSize)) {
			knh_tClassSize = cid + 1;
		}
	}
	knh_tClass_t *TC = (knh_tClass_t*)(&knh_tClass[cid]);
	KNH_ASSERT(bcid < cid);
	KNH_ASSERT(knh_tClass[cid].class_cid == NULL);

	TC->cflag  = knh_tClass[bcid].cflag;
	TC->oflag  = knh_tClass[bcid].oflag;

	TC->sid    = knh_tClass[bcid].sid;

	TC->bcid   = bcid;
	TC->supcid = knh_tClass[bcid].supcid;
	//TC->supcid = bcid;

	TC->offset = knh_tClass[bcid].offset;

	TC->size = knh_tClass[bcid].size;
	TC->bsize  = knh_tClass[bcid].bsize;

	KNH_TCLASS_NAME(ctx, cid, name);
	KNH_INITv(TC->cstruct, knh_tClass[bcid].cstruct);
	KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
	KNH_TCLASS_DEFAULT(ctx, cid, KNH_NULL, NULL);
	KNH_TCLASS_PARAM(ctx, cid, p1, p2);
	return cid;
}

/* ------------------------------------------------------------------------ */

void KNH_ACLASS(Ctx *ctx, knh_class_t cid, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s[]", CLASSN(p1));
	KNH_TPMZCLASS(ctx, cid, new_String0(ctx, B(buf), NULL), CLASS_Array, p1, CLASS_Nue);
}

/* ------------------------------------------------------------------------ */

void KNH_ICLASS(Ctx *ctx, knh_class_t cid, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s..", CLASSN(p1));
	KNH_TPMZCLASS(ctx, cid, new_String0(ctx, B(buf), NULL), CLASS_Iterator, p1, CLASS_Nue);
}

/* ======================================================================== */
/* [SPEC] */

static
Object *knh_tClass_fdefault__CSPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *cs = (ClassSpec*)knh_tClass[cid].cspec;
	return UP(DP(cs)->defvalue);
}

/* ------------------------------------------------------------------------ */

knh_class_t
KNH_XCLASS(Ctx *ctx, knh_class_t cid, knh_class_t bcid, ClassSpec *cs)
{
	if(cid == CLASS_newid) {
		cid = knh_tClass_newId(ctx);
	}else {
		if(!(cid < knh_tClassSize)) {
			knh_tClassSize = cid + 1;
		}
	}

	char bufcn[CLASSNAME_BUFSIZ];
	knh_snprintf(bufcn, sizeof(bufcn), KNH_CLASSSPEC_FMT, CLASSN(bcid), knh_String_tochar(DP(cs)->urn));
	KNH_TCLASS_NAME(ctx, cid, new_String0(ctx, B(bufcn), NULL));
	DP(cs)->cid = cid;

	knh_tClass[cid].bcid   = bcid;
	knh_tClass[cid].supcid = bcid;

	if(bcid == CLASS_Int) bcid = CLASS_IntX;
	else if(bcid == CLASS_Float) bcid = CLASS_FloatX;
	else if(bcid == CLASS_String) bcid = CLASS_StringX;
	else if(bcid == CLASS_Int64) bcid = CLASS_Int64X;

	DBG2_P("%s\n\tcopying from %s", bufcn, CLASSN(bcid));
	knh_tClass[cid].cflag  = knh_tClass[bcid].cflag;
	knh_tClass[cid].oflag  = knh_tClass[bcid].oflag;
	knh_tClass[cid].offset = knh_tClass[bcid].offset;

	knh_tClass[cid].sid  = knh_tClass[bcid].sid;
	knh_tClass[cid].size = knh_tClass[bcid].size;
	knh_tClass[cid].bsize  = knh_tClass[bcid].bsize;

	KNH_ASSERT(knh_tClass[cid].cstruct == NULL);
	KNH_INITv(knh_tClass[cid].cstruct, knh_tClass[bcid].cstruct);

	if(knh_tClass[cid].cmap == NULL) {
		KNH_INITv(knh_tClass[cid].cmap, new_ClassMap0(ctx, 4));
	}
	else {
		KNH_ASSERT(IS_ClassMap(knh_tClass[cid].cmap));
	}
	KNH_ASSERT(knh_tClass[cid].cspec == NULL);
	KNH_INITv(knh_tClass[cid].cspec, cs);
	knh_tClass[cid].fdefault = knh_tClass_fdefault__CSPEC;
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_tClass_findcid(Ctx *ctx, knh_bytes_t lname)
{
	DBG2_P("lname='%s'", lname.buf);
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, lname);
	if(cid != CLASS_unknown) {
		return cid;
	}
	if(knh_bytes_endsWith(lname, STEXT("[]"))) {
		lname.len -= 2;
		cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, lname);
		if(cid == CLASS_unknown || knh_class_isPrivate(cid)) {
			return CLASS_Array;
		}
		return knh_class_Array(ctx, cid);
	}
	if(knh_bytes_endsWith(lname, STEXT(".."))) {
		lname.len -= 2;
		cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, lname);
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
			knh_class_t bcid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, knh_bytes_first(lname, loc));
			DBG2_P("cid=%d,%s", bcid, CLASSN(bcid));
			ClassSpec *cs = (ClassSpec*)knh_System_loadClassSpec(ctx, bcid, urn);
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
