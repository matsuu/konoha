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
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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
/* [ClassTable] */

knh_struct_t knh_StructTable_newId(Ctx *ctx)
{
	knh_class_t newid;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	size_t structmax = ctx->share->ClassTableSize;
	if(KNH_TSTRUCT_SIZE < structmax) structmax = KNH_TSTRUCT_SIZE;
	if(!(ctx->share->StructTableSize < structmax)) {
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		KNH_EXIT("Enlarge KNH_TSTRUCT_SIZE %d", KNH_TSTRUCT_SIZE);
		return CLASS_unknown;
	}
	newid = ctx->share->StructTableSize;
	ctx->share->StructTableSize++;
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return newid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_ClassTable_newId(Ctx *ctx)
{
	knh_class_t newid;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	if(ctx->share->StructTableSize < ctx->share->ClassTableSize) {
		ctx->share->ClassTableSize--;
		newid = ctx->share->ClassTableSize;
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		return newid;
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	KNH_EXIT("Enlarge KNH_TCLASS_SIZE %d", KNH_TCLASS_SIZE);
	return CLASS_unknown;
}

/* ------------------------------------------------------------------------ */

static knh_Class_t *new_Class(Ctx *ctx, knh_class_t cid)
{
	knh_Class_t *o = (knh_Class_t*)new_hObject(ctx, FLAG_Class, CLASS_Class, CLASS_Class);
	o->cid = cid;
	o->type = cid;
	return o;
}

/* ------------------------------------------------------------------------ */

void konoha_setClassName(Ctx *ctx, knh_class_t cid, String *lname)
{
	KNH_ASSERT_cid(cid);
	//KNH_NOTICE(ctx, "added new class: %s", knh_String_tochar(lname));
	KNH_ASSERT(ctx->share->ClassTable[cid].class_cid == NULL);
	KNH_INITv(ctx->share->ClassTable[cid].class_cid, new_Class(ctx, cid));
	KNH_INITv(ctx->share->ClassTable[cid].lname, lname);
	{
		knh_bytes_t n = knh_String_tobytes(lname);
		knh_index_t idx = knh_bytes_index(n, '{');
		if(idx != -1) {
			KNH_INITv(ctx->share->ClassTable[cid].sname, lname);
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
			KNH_INITv(ctx->share->ClassTable[cid].sname, lname);
		}
		else {
			KNH_INITv(ctx->share->ClassTable[cid].sname, new_String(ctx, knh_bytes_last(n, idx + 1), lname));
		}
	}
	//DBG2_P("NEW CLASS: %s, %s", knh_String_tochar(lname), knh_String_tochar(ctx->share->ClassTable[cid].sname));
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_DictSet_append(ctx, DP(ctx->sys)->ClassNameDictSet, lname, cid+1);
	if(knh_String_startsWith(lname, STEXT("konoha."))) {
		knh_DictSet_append(ctx, DP(ctx->sys)->ClassNameDictSet, ctx->share->ClassTable[cid].sname, cid+1);
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
}

/* ------------------------------------------------------------------------ */
/* [name] */

char *knh_ClassTable_CLASSN(Ctx *ctx, knh_class_t cid)
{
	if(cid == CLASS_unknown) {
		return "unknown";
	}
	KNH_ASSERT_cid(cid);
	DBG2_ASSERT(ctx->share->ClassTable[cid].sname != NULL);
	if(knh_String_startsWith(ctx->share->ClassTable[cid].lname, STEXT("konoha."))) {
		return knh_String_tochar(ctx->share->ClassTable[cid].sname);
	}
	else {
		return knh_String_tochar(ctx->share->ClassTable[cid].lname);
	}
}

/* ------------------------------------------------------------------------ */
/* [default] */

static
knh_Object_t *knh_fdefault__CONST(Ctx *ctx, knh_class_t cid)
{
	return ctx->share->ClassTable[cid].cspec;
}

/* ------------------------------------------------------------------------ */

static
knh_Object_t *knh_fdefault__INIT(Ctx *ctx, knh_class_t cid)
{
	//DBG2_P("%s", CLASSN(cid));
	KNH_ASSERT(IS_NULL(ctx->share->ClassTable[cid].cspec));
	Object *v = new_Object_init(ctx, ctx->share->ClassTable[cid].oflag | KNH_FLAG_OF_IMMUTABLE, cid, 0);
	KNH_SETv(ctx, ctx->share->ClassTable[cid].cspec, v);
	ctx->share->ClassTable[cid].fdefault = knh_fdefault__CONST;
	return ctx->share->ClassTable[cid].cspec;
}

/* ------------------------------------------------------------------------ */

void konoha_setClassDefaultValue(Ctx *ctx, knh_class_t cid, Object *value, knh_fdefault fdefault)
{
	KNH_ASSERT_cid(cid);
	if(ctx->share->ClassTable[cid].cspec == NULL) {
		KNH_INITv(ctx->share->ClassTable[cid].cspec, value);
	}
	else {
		KNH_SETv(ctx, ctx->share->ClassTable[cid].cspec, value);
	}
	if(fdefault == NULL) {
		if(IS_NULL(value) && cid != CLASS_Nue) {
			fdefault = knh_fdefault__INIT;
		}
		else {
			fdefault = knh_fdefault__CONST;
		}
	}
	ctx->share->ClassTable[cid].fdefault = fdefault;
}

/* ------------------------------------------------------------------------ */

#define _KNH_DEF(ctx, cid)  konoha_getClassDefaultValue(ctx, cid)

Object *konoha_getClassDefaultValue(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	return ctx->share->ClassTable[cid].fdefault(ctx, cid);
}

/* ------------------------------------------------------------------------ */

#define _KNH_DEF(ctx, cid)  konoha_getClassDefaultValue(ctx, cid)

Object *konoha_getDefaultValue(Ctx *ctx, knh_type_t type)
{
	if(IS_NNTYPE(type)) {
		knh_class_t cid = CLASS_type(type);
		KNH_ASSERT_cid(cid);
		return ctx->share->ClassTable[cid].fdefault(ctx, cid);
	}
	else {
		return KNH_NULL;
	}
}

/* ======================================================================== */
/* [PARAM] */

void konoha_setClassParam(Ctx *ctx, knh_class_t cid, knh_class_t p1, knh_class_t p2)
{
	KNH_ASSERT_cid(cid);
	//KNH_ASSERT(ctx->share->ClassTable[cid].p1 == CLASS_Nue);
	ctx->share->ClassTable[cid].p1 = p1;
	ctx->share->ClassTable[cid].p2 = p2;
	if(!knh_class_isCyclic(cid)) {
		if(knh_class_isCyclic(p1) || knh_class_isCyclic(p2)) {
			knh_class_setCyclic(cid, 1);
		}
	}
}

/* ------------------------------------------------------------------------ */

knh_class_t
konoha_addGenericsClass(Ctx *ctx, knh_class_t cid, String *name, knh_class_t bcid, knh_class_t p1, knh_class_t p2)
{
	if(cid == CLASS_newid) {
		cid = knh_ClassTable_newId(ctx);
	}else {
		KNH_ASSERT(cid + 1 == ctx->share->ClassTableSize);
		ctx->share->ClassTableSize = cid;
	}
	knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[cid]);
	KNH_ASSERT(bcid < cid);
	KNH_ASSERT(ctx->share->ClassTable[cid].class_cid == NULL);

	TC->cflag  = ctx->share->ClassTable[bcid].cflag;
	TC->oflag  = ctx->share->ClassTable[bcid].oflag;

	TC->sid    = ctx->share->ClassTable[bcid].sid;

	TC->bcid   = bcid;
	TC->supcid = ctx->share->ClassTable[bcid].supcid;
	//TC->supcid = bcid;

	TC->offset = ctx->share->ClassTable[bcid].offset;

	TC->size = ctx->share->ClassTable[bcid].size;
	TC->bsize  = ctx->share->ClassTable[bcid].bsize;

	konoha_setClassName(ctx, cid, name);
	KNH_INITv(TC->cstruct, ctx->share->ClassTable[bcid].cstruct);
	KNH_INITv(TC->cmap, new_ClassMap0(ctx, 0));
	konoha_setClassDefaultValue(ctx, cid, KNH_NULL, NULL);
	konoha_setClassParam(ctx, cid, p1, p2);
	return cid;
}

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
Object *knh_ClassTable_fdefault__ISPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	return UP(DP(u)->ivalue);
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
	konoha_setClassName(ctx, cid, new_String(ctx, B(bufcn), NULL));

	ctx->share->ClassTable[cid].bcid   = bcid;
	ctx->share->ClassTable[cid].supcid = bcid;

//	if(bcid == CLASS_Int) bcid = CLASS_IntX;
//	else if(bcid == CLASS_Float) bcid = CLASS_FloatX;
//	else if(bcid == CLASS_String) bcid = CLASS_StringX;

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
	TODO();
	ctx->share->ClassTable[cid].fdefault = knh_ClassTable_fdefault__ISPEC;
	return cid;
}

/* ======================================================================== */
/* [ClassStruct] */

//#define _knh_tstruct_isNative(sid)   (sid < KONOHA_TSTRUCT_SIZE)

ClassStruct* new_ClassStruct0(Ctx *ctx, int field_size, int method_size)
{
	knh_ClassStruct_t* cs = (knh_ClassStruct_t*)new_Object_bcid(ctx, CLASS_ClassStruct, field_size);
	KNH_SETv(ctx, cs->methods, new_Array0(ctx, method_size));
	return cs;
}

/* ------------------------------------------------------------------------ */
/* [field] */

knh_index_t knh_Class_indexOfField(Ctx *ctx, knh_class_t cid, knh_fieldn_t fn)
{
	L_TAIL:;
	KNH_ASSERT_cid(cid);
	{
		knh_index_t idx = -1;
		ClassStruct *cs = ctx->share->ClassTable[cid].cstruct;
		if(cs->fields != NULL) {
			for(idx = 0; idx < cs->fsize; idx++) {
				if(cs->fields[idx].fn == fn) {
					return ctx->share->ClassTable[cid].offset + idx;
				}
			}
			idx = -1;
		}
		if(ctx->share->ClassTable[cid].offset == 0) return -1;
		cid = ctx->share->ClassTable[cid].supcid;
	}
	goto L_TAIL;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_Class_queryField(Ctx *ctx, knh_class_t cid, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	L_TAIL:;
	KNH_ASSERT_cid(cid);
	{
		ClassStruct *cs = ctx->share->ClassTable[cid].cstruct;
		knh_index_t idx = -1;
		if(FIELDN_IS_SUPER(fnq)) {
			fnq = fn;
			goto L_SUPER;
		}
		if(cs->fields != NULL) {
			for(idx = 0; idx < cs->fsize; idx++) {
				if(cs->fields[idx].fn == fn) {
					return ctx->share->ClassTable[cid].offset + idx;
				}
			}
			idx = -1;
		}
		L_SUPER:;
		if(ctx->share->ClassTable[cid].offset == 0) return -1;
		cid = ctx->share->ClassTable[cid].supcid;
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

knh_cfield_t *knh_Class_fieldAt(Ctx *ctx, knh_class_t cid, size_t n)
{
	KNH_ASSERT_cid(cid);
	KNH_ASSERT(/*0 <= n &&*/ n < ctx->share->ClassTable[cid].size);
	L_TAIL:;
	{
		ClassStruct *cs = ctx->share->ClassTable[cid].cstruct;;
		size_t offset = ctx->share->ClassTable[cid].offset;
		if(offset <= n) {
			if(cs->fields == NULL) {
				return NULL;
			}
			else {
				return &(cs->fields[n - offset]);
			}
		}
		KNH_ASSERT_cid(cid);
		cid = ctx->share->ClassTable[cid].supcid;
	}
	goto L_TAIL;
}


/* ------------------------------------------------------------------------ */
/* [movabletext] */

void knh_cfield_dump(Ctx *ctx, knh_cfield_t *f, size_t offset, size_t fsize, OutputStream *w)
{
	size_t idx = 0;
	for(idx = 0; idx < fsize; idx++) {
		if(f[idx].fn == FIELDN_NONAME) {
			knh_printf(ctx, w, "[%d] -\n", (offset+idx));
			continue;
		}
		if(f[idx].fn == FIELDN_register || f[idx].type == CLASS_unknown) continue;
		knh_printf(ctx, w, "[%d] %T %N = %O\n", (offset+idx), f[idx].type, f[idx].fn, f[idx].value);
	}
}

/* ======================================================================== */
/* [ClassMap] */

ClassMap* new_ClassMap0(Ctx *ctx, knh_ushort_t capacity)
{
	if(capacity < KNH_FASTMALLOC_SIZE) capacity = KNH_FASTMALLOC_BSIZE;
	knh_ClassMap_t *o = (knh_ClassMap_t*)new_Object_bcid(ctx, CLASS_ClassMap, capacity);
	knh_ClassMap_setSorted(o, 1);
	return o;
}


/* ------------------------------------------------------------------------ */

int knh_ClassMap_isDefault(Ctx *ctx, ClassMap *o)
{
	return (o == ctx->share->ClassTable[CLASS_Any].cmap);
}

/* ------------------------------------------------------------------------ */

void knh_ClassTable_readyClassMap(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	KNH_ASSERT(cid != CLASS_Any);
	if(ctx->share->ClassTable[cid].cmap == ctx->share->ClassTable[CLASS_Any].cmap) {
		KNH_SETv(ctx, ctx->share->ClassTable[cid].cmap, new_ClassMap0(ctx, 4));
	}
}

/* ------------------------------------------------------------------------ */

void knh_ClassMap_resize(Ctx *ctx, ClassMap *o, size_t newsize)
{
	Mapper **newlist = (Mapper**)KNH_MALLOC(ctx, newsize * sizeof(Mapper*));
	knh_bzero(newlist, newsize);
	knh_intptr_t i;
	for(i = 0; i < DP(o)->size; i++) {
		newlist[i] = DP(o)->maplist[i];
	}
	KNH_FREE(ctx, DP(o)->maplist, DP(o)->capacity * sizeof(Mapper*));
	DP(o)->maplist = newlist;
	DP(o)->capacity = newsize;
}

/* ------------------------------------------------------------------------ */

int
knh_ClassMap_util_cmp(const Mapper *m1, const Mapper *m2)
{
	int res = DP(m1)->flag - DP(m2)->flag;
	return (res == 0) ? DP(m2)->tcid - DP(m1)->tcid : res;
}

/* ------------------------------------------------------------------------ */

void knh_ClassMap_sort(Ctx *ctx, ClassMap *o)
{
	if(!knh_ClassMap_isSorted(o)) {
		knh_qsort(DP(o)->maplist, DP(o)->size, sizeof(Mapper*),
					(int (*)(const void*, const void*))knh_ClassMap_util_cmp);
		knh_ClassMap_setSorted(o, 1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_ClassMap_add(Ctx *ctx, ClassMap *o, Mapper *map)
{
	KNH_ASSERT(!knh_ClassMap_isDefault(ctx, o));
	if(DP(o)->size == DP(o)->capacity) {
		knh_ClassMap_resize(ctx, o, DP(o)->capacity + 8);
	}
	KNH_ASSERT(DP(o)->maplist[DP(o)->size] == NULL);
	KNH_INITv(DP(o)->maplist[DP(o)->size], map);
	DP(o)->size++;
}

/* ======================================================================== */
/* [movabletext] */

/* @method void ClassMap.%dump(OutputStream w, String m) */

void knh_ClassMap__dump(Ctx *ctx, ClassMap *o, OutputStream *w, String *m)
{
	int i;
	for(i = 0; i < DP(o)->size; i++) {
		knh_printf(ctx, w, "[%d]\t", i);
		knh_Mapper__k(ctx, DP(o)->maplist[i], w, m);
		knh_write_EOL(ctx, w);
	}
}

/* ======================================================================== */

void knh_ClassMap__man(Ctx *ctx, ClassMap *o, OutputStream *w, knh_class_t cid)
{
//	if(knh_ClassMap_isDefault(o)) {
//		return;
//	}
	int i;
	int hasCaption = 0, from = 0;
	L_TAIL:;
	knh_ClassMap_sort(ctx, o);
	for(i = 0; i < DP(o)->size; i++) {
		if(hasCaption == 0) {
			knh_write__s(ctx, w, _("Mapper"));
			knh_write_EOL(ctx, w);
			hasCaption = 1;
		}
		if(from == 0) {
			knh_write_TAB(ctx, w);
			knh_write_cid(ctx, w, cid);
			knh_write_EOL(ctx, w);
			from = 1;
		}
		Mapper *mpr = DP(o)->maplist[i];
		knh_write_TAB(ctx, w); knh_write_TAB(ctx, w);
		if(knh_Mapper_isSynonym(mpr)) {
			knh_write__s(ctx, w, "=== ");
		}
		else if(knh_Mapper_isTotal(mpr)) {
			knh_write__s(ctx, w, "==> ");
		}
		else {
			knh_write__s(ctx, w, "--> ");
		}
		knh_write_cid(ctx, w, DP(mpr)->tcid);
		knh_write_EOL(ctx, w);
	}
	if(ctx->share->ClassTable[cid].supcid != CLASS_Object) {
		cid = ctx->share->ClassTable[cid].supcid;
		o = ctx->share->ClassTable[cid].cmap;
		from = 0;
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
