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

#define _KNH_FLAG_CF2OF(f)        (f)

/* ------------------------------------------------------------------------ */

#ifndef BOT_TCLASS_newId
#define BOT_TCLASS_newId
#define EOT_TCLASS_newId
#endif

/* ======================================================================== */
/* [globals] */

#ifndef KONOHA_TCLASS_SIZE
#define KONOHA_TCLASS_SIZE 1024
#endif 

#define TCLASSDB_SIZE  (KONOHA_TCLASS_SIZE * sizeof(knh_tclass_t))

static knh_tclass_t    *tclassList           = NULL;
static size_t          tclassList_size      = 0;

/* ------------------------------------------------------------------------ */

void knh_tclass_ginit()
{
	DEBUG_ASSERT(tclassList == NULL);
	size_t i;
	tclassList = (knh_tclass_t*)knh_malloc(NULL, TCLASSDB_SIZE);
	tclassList_size = 0;
	for(i = 0; i < KONOHA_TCLASS_SIZE; i++) {
		tclassList[i].count    = 0;
		tclassList[i].cflag    = 0;
		tclassList[i].oflag    = 0;
		tclassList[i].topsid   = 0;
		tclassList[i].offset   = 0;
		tclassList[i].sid      = 0;
		tclassList[i].supcid   = 0;
		tclassList[i].keyidx   = -1;
		tclassList[i].name     = NULL;
		tclassList[i].class    = NULL;
		tclassList[i].cstruct  = NULL;
		tclassList[i].crel     = NULL;
		tclassList[i].spec     = NULL;
		if(i < KONOHA_TSTRUCT_SIZE) {
			tclassList[i].topsid   = i;
		}
	}
}

/* ------------------------------------------------------------------------ */
	
void knh_tclass_gtraverse(Ctx *ctx, f_gc gc)
{
	DEBUG_ASSERT(tclassList != NULL);
	knh_int_t i;
	/* tclass */
	if(IS_SWEEP(gc)) {
		for(i = tclassList_size - 1; i >= 0; i--) {
			if(tclassList[i].name != NULL) {
				knh_ClassStruct_toAbstractAll(ctx, tclassList[i].cstruct);
			}
		}
		for(i = tclassList_size - 1; i >= 0; i--) {
			if(tclassList[i].name != NULL) {
				gc(ctx, tclassList[i].class);
				gc(ctx, tclassList[i].cstruct);
				gc(ctx, tclassList[i].crel);
				gc(ctx, tclassList[i].spec);
			}
		}
	}else {
		for(i = tclassList_size - 1; i >= 0; i--) {
			if(tclassList[i].name != NULL) {
				gc(ctx, tclassList[i].class);
				gc(ctx, tclassList[i].cstruct);
				gc(ctx, tclassList[i].crel);
				gc(ctx, tclassList[i].spec);
			}
		}
	}

#ifdef KONOHA_SAFEMODE	
	if(IS_SWEEP(gc)) {
		for(i = 0; i < tclassList_size; i++) {
			if(tclassList[i].name == NULL) continue;
			if(tclassList[i].count != 0 && i != CLASS_String) {
				knh_tmemory_beginMemoryLeakNotice();
				fprintf(stderr, "CLASS %s (cid=%d) remains: %ld\n", 
					knh_String_tochar(tclassList[i].name), (int)i, tclassList[i].count);
			}
		}
	}
#endif

	for(i = tclassList_size - 1; i >= 0; i--) {
		if(tclassList[i].name != NULL)
			gc(ctx, tclassList[i].name);
	}
	
#ifdef KONOHA_SAFEMODE	
	if(IS_SWEEP(gc)) {
		if(tclassList[CLASS_String].count != 0) {
			knh_tmemory_beginMemoryLeakNotice();
			fprintf(stderr, "CLASS String (cid=%d) remains: %ld\n", CLASS_String, tclassList[CLASS_String].count);
		}
	}
#endif

	if(IS_SWEEP(gc)) {
		knh_free(tclassList, TCLASSDB_SIZE);
		tclassList = NULL;
	}
}

/* ======================================================================== */
/* [newid] */

knh_class_t knh_tclass_newId(Ctx *ctx) 
{
	if(tclassList_size == KONOHA_TCLASS_SIZE) {
		KNH_THROWs(ctx, "OutOfMemory!!: KONOHA_TCLASS_SIZE");
		return 0;
	}
	BOT_TCLASS_newId;
	knh_class_t newid = tclassList_size++;
	EOT_TCLASS_newId;
	return newid;
}

/* ======================================================================== */
/* [util] */

INLINE
knh_bool_t knh_tclass_isvalid(knh_class_t cid)
{
	return (cid < tclassList_size);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_tclass_t* knh_tclass_table(knh_class_t cid)
{
	DEBUG_ASSERT (cid < tclassList_size);
	return &(tclassList[cid]);
}


/* ======================================================================== */
/* [count] */

INLINE 
void knh_tclass_count_inc(knh_class_t cid)
{
	(tclassList[cid].count)++;
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_tclass_count_dec(knh_class_t cid)
{
	(tclassList[cid].count)--;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_flag_t knh_tclass_cflag(knh_class_t cid)
{
	return tclassList[cid].cflag;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_flag_t knh_tclass_oflag(knh_class_t cid)
{
	return tclassList[cid].oflag;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_struct_t knh_tclass_topsid(knh_class_t cid)
{
	return tclassList[cid].topsid;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_ushort_t knh_tclass_offset(knh_class_t cid)
{
	return tclassList[cid].offset;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_struct_t knh_tclass_sid(knh_class_t cid)
{
	return tclassList[cid].sid;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_ushort_t knh_tclass_supcid(knh_class_t cid)
{
	return tclassList[cid].supcid;
}

/* ======================================================================== */
/* [keyidx] */

INLINE
knh_index_t knh_tclass_keyidx(knh_class_t cid)
{
	return tclassList[cid].keyidx;
}

/* ======================================================================== */
/* [name] */

#define _CLASSN(cid)   knh_String_tochar(knh_tclass_name(cid))
#define _CLASSNo(o)    CLASSN(knh_Object_cid(o))

INLINE 
String *knh_tclass_name(knh_class_t cid)
{
	SAFE_ASSERT(cid < tclassList_size, "unknown cid = %d, perhaps? %d", cid, TYPE_UNMASK(cid));
	return tclassList[cid].name;
}

/* ======================================================================== */
/* [class] */

INLINE 
Class *knh_tclass_class(knh_class_t cid)
{
	if(cid == CLASS_unknown) return KNH_NULL;
	KNH_ASSERT(cid < tclassList_size);
	return tclassList[cid].class;
}


/* ------------------------------------------------------------------------ */

INLINE 
knh_class_t knh_tclass_bcid(knh_class_t cid)
{
	if(TYPE_ISPLURAL(cid)) return CLASS_Iterator;
	KNH_ASSERT(cid < tclassList_size);
	return ((Class*)tclassList[cid].class)->bcid;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_class_t knh_tclass_ensurebcid(knh_class_t bcid, knh_class_t cid)
{
	return (bcid == knh_tclass_bcid(cid)) ? cid : bcid;
}

/* ======================================================================== */
/* [cstruct] */

INLINE 
ClassStruct *knh_tclass_cstruct(knh_class_t cid)
{
	KNH_ASSERT(cid < tclassList_size);
	return tclassList[cid].cstruct;
}

/* ------------------------------------------------------------------------ */

INLINE
bsize_t knh_tclass_bsize(knh_class_t cid)
{
	return (knh_tclass_offset(cid) + knh_tstruct_bsize(tclassList[cid].sid));
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_tclass_size(knh_class_t cid)
{
	return (knh_tclass_bsize(cid) * sizeof(Object*));
}

/* ======================================================================== */
/* [crel] */

INLINE 
ClassRel *knh_tclass_crel(knh_class_t cid)
{
	KNH_ASSERT(cid < tclassList_size);
	return tclassList[cid].crel;
}

/* ======================================================================== */
/* [spec] */

INLINE 
Object *knh_tclass_spec(knh_class_t cid)
{
	KNH_ASSERT(cid < tclassList_size);
	return tclassList[cid].spec;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_class_isSingleton(knh_class_t b)
{
	KNH_ASSERT(b < tclassList_size);
	return (knh_Object_cid(tclassList[b].spec) == b);
}

/* ------------------------------------------------------------------------ */

ObjectNULL *knh_tclass_fvalue__singleton(Ctx *ctx, knh_class_t cid)
{
	return tclassList[cid].spec;
}

/* ======================================================================== */
/* [value] */

ObjectNULL *knh_tclass_fvalue__default(Ctx *ctx, knh_class_t cid)
{
	DEBUG("%s", CLASSN(cid));
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_tclass_hasDefaultValue(knh_class_t cid)
{
	if(TYPE_ISPLURAL(cid)) { return 1; }
	return (tclassList[cid].fvalue != knh_tclass_fvalue__default);
}

/* ------------------------------------------------------------------------ */

Object *knh_tclass_value(Ctx *ctx, knh_class_t cid, Object *alt)
{
	if(TYPE_ISPLURAL(cid)) {
		return tclassList[CLASS_Iterator].fvalue(ctx, TYPE_UNMASK(cid));
	}
	KNH_ASSERT(cid < tclassList_size);
	if(tclassList[cid].fvalue != knh_tclass_fvalue__default) {
		return alt;
	}
	return tclassList[cid].fvalue(ctx, cid);
}

/* ------------------------------------------------------------------------ */

Object *knh_tclass_safevalue(Ctx *ctx, knh_class_t cid)
{
	if(TYPE_ISPLURAL(cid)) {
		return tclassList[CLASS_Iterator].fvalue(ctx, TYPE_UNMASK(cid));
	}
	KNH_ASSERT(cid < tclassList_size);
	DEBUG_ASSERT(tclassList[cid].fvalue != knh_tclass_fvalue__default);
	return tclassList[cid].fvalue(ctx, cid);
}

/* ======================================================================== */
/* [TABLE] */

knh_class_t 
KNH_TCLASS(Ctx *ctx, knh_flag_t flag, String *name, knh_class_t cid, knh_struct_t sid, knh_class_t supcid, Object *spec, f_value fvalue, int isize, ...)
{
	//DEBUG("%s: %s(cid=%d)", __func__, name.buf, cid)
	if(cid == CLASS_newid) {
		cid = knh_tclass_newId(ctx);
	}else {
		if(cid < tclassList_size) {
		
		}else {
			tclassList_size = cid + 1;
		}			
	}
	
	DEBUG_ASSERT(tclassList[cid].name == NULL);

	if(supcid == CLASS_Object) {
		tclassList[cid].topsid = sid;
		tclassList[cid].offset = 0; 
	}else {
		tclassList[cid].topsid = tclassList[supcid].topsid;
		tclassList[cid].offset = knh_tclass_bsize(supcid);
	}
	tclassList[cid].cflag  = flag;
	tclassList[cid].oflag  = KNH_FLAG_CF2OF(flag);
	tclassList[cid].sid    = sid;
	tclassList[cid].supcid = supcid; 

	KNH_INITv(tclassList[cid].name, name);
	knh_NameSpace_setClass(ctx, knh_NameSpace_SYSTEM(), name, cid);
	KNH_INITv(tclassList[cid].class, new_Class__base(ctx, cid, cid));
	
	DEBUG_ASSERT(tclassList[cid].cstruct == NULL);
	KNH_INITv(tclassList[cid].cstruct, new_ClassStruct(ctx, sid));
	
	DEBUG_ASSERT(tclassList[cid].crel == NULL);
	KNH_INITv(tclassList[cid].crel, new_ClassRel(ctx, 4));

	DEBUG_ASSERT(tclassList[cid].spec == NULL);
	KNH_INITv(tclassList[cid].spec, spec); 

	if(fvalue == NULL) {
		if(knh_Object_cid(spec) == cid) {
			fvalue = knh_tclass_fvalue__singleton;
		}else if(CLASS_Int <= cid && cid < CLASS_Bytes) {
			fvalue = knh_tclass_fvalue__spec;
		}else {
			fvalue = knh_tclass_fvalue__default;		
		}
	}
	tclassList[cid].fvalue = fvalue;
	return cid;
}

/* ======================================================================== */
/* [SPEC] */

ObjectNULL *knh_tclass_fvalue__spec(Ctx *ctx, knh_class_t cid)
{
	knh_ClassSpec *cs = (knh_ClassSpec*)tclassList[cid].spec;
	DEBUG_ASSERT(IS_SPEC(cs));
	return cs->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

knh_class_t 
KNH_TCLASS_SPEC(Ctx *ctx, knh_class_t bcid, Object *spec)
{
	DEBUG_ASSERT(IS_SPEC(spec));
	knh_ClassSpec *cs = (knh_ClassSpec*)spec;

	char cname[CLASSNAME_BUFSIZ];
	knh_snprintf(cname, sizeof(cname), KNH_CLASSSPEC_FMT, CLASSN(bcid), knh_String_tochar(cs->spec.urn));
	//DEBUG("new spec size=%d,%d '%s'", CLASSNAME_BUFSIZ, sizeof(cname), cname);
	knh_class_t cid = cs->spec.cid;
	
	DEBUG_ASSERT(tclassList[cid].name == NULL);
	tclassList[cid].topsid = tclassList[bcid].topsid;
	tclassList[cid].offset = 0; 

	tclassList[cid].cflag  = tclassList[bcid].cflag;
	tclassList[cid].oflag  = KNH_FLAG_CF2OF(tclassList[cid].cflag);
	tclassList[cid].sid    = tclassList[bcid].topsid;
	tclassList[cid].supcid = CLASS_Object;

	KNH_INITv(tclassList[cid].name, new_String__fast(ctx, CLASS_String__class, B(cname)));
	knh_NameSpace_setClass(ctx, knh_NameSpace_SYSTEM(), tclassList[cid].name, cid);
	KNH_INITv(tclassList[cid].class, new_Class__base(ctx, bcid, cid));
	
	DEBUG_ASSERT(tclassList[cid].cstruct == NULL);
	KNH_INITv(tclassList[cid].cstruct, tclassList[bcid].cstruct);
	
	DEBUG_ASSERT(tclassList[cid].crel == NULL);
	KNH_INITv(tclassList[cid].crel, new_ClassRel(ctx, 4));

	DEBUG_ASSERT(tclassList[cid].spec == NULL);
	KNH_INITv(tclassList[cid].spec, spec); 

	tclassList[cid].fvalue = knh_tclass_fvalue__spec;
	return cid;
}

///* ------------------------------------------------------------------------ */
//
//char *
//knh_nzformat_urn(char *buf, size_t bufsiz, char *urn)
//{
//	/* http://www.site.org/hoge/ ==> http://site.org/hoge */
//	knh_snprintf(buf, bufsiz, "%s", urn);
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_class_t knh_tclass_urn(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn, knh_class_t def)
//{
//	char namebuf[CLASSNAME_BUFSIZ];
//	knh_snprintf(namebuf, sizeof(namebuf), "%s+%s", CLASSN(bcid), urn.buf);
//	
//	NameSpace *ns = knh_NameSpace_SYSTEM();
//	knh_class_t cid = knh_NameSpace_getClass(ctx, ns, B(namebuf));
//	if(cid != CLASS_unknown) return cid;
//	if(def == CLASS_newid) {
//		knh_nzformat_urn(namebuf, sizeof(namebuf), (char*)urn.buf);
//		knh_ClassSpec *spec = (knh_ClassSpec*)knh_loader_load_spec(ctx, bcid, namebuf);
//		if(IS_NULL(spec)) {
//			return CLASS_unknown;
//		}
//		KNH_TCLASS_SPEC(ctx, bcid, spec);
//	}
//	return def;
//}

/* ------------------------------------------------------------------------ */
/* [TCLASS_NEW, TCLASS_STRUCT] */

knh_class_t 
KNH_TCLASS_NEWCLASS(Ctx *ctx, String *name)
{
	knh_class_t cid = knh_tclass_newId(ctx);
	tclassList[cid].topsid = 0;
	tclassList[cid].offset = 0; 
	tclassList[cid].cflag  = KNH_FLAG_CF_NA;
	tclassList[cid].oflag  = 0;
	tclassList[cid].sid    = 0;
	tclassList[cid].supcid = 0; 

	DEBUG_ASSERT(tclassList[cid].name == NULL);
	KNH_INITv(tclassList[cid].name, name);
	knh_NameSpace_setClass(ctx, ((Context*)ctx)->runtime->ns, name, cid);

	KNH_INITv(tclassList[cid].class, new_Class__base(ctx, cid, cid));
	
	DEBUG_ASSERT(tclassList[cid].cstruct == NULL);
	KNH_INITv(tclassList[cid].cstruct, tclassList[0].cstruct);
	
	DEBUG_ASSERT(tclassList[cid].crel == NULL);
	KNH_INITv(tclassList[cid].crel, new_ClassRel(ctx, 4));

	DEBUG_ASSERT(tclassList[cid].spec == NULL);
	KNH_INITv(tclassList[cid].spec, KNH_NULL); 

	tclassList[cid].fvalue = knh_tclass_fvalue__default;		
	;
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t 
KNH_TCLASS_STRUCT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_struct_t sid, knh_class_t supcid, ClassStruct *cs)
{
	DEBUG_ASSERT(knh_tclass_isvalid(cid));
	DEBUG_ASSERT(tclassList[cid].name != NULL);
	DEBUG_ASSERT(sid < STRUCT_Prototype);

	if(supcid == CLASS_Object) {
		tclassList[cid].topsid = sid;
		tclassList[cid].offset = 0; 
	}else {
		tclassList[cid].topsid = tclassList[supcid].topsid;
		tclassList[cid].offset = knh_tclass_bsize(supcid);
	}

	tclassList[cid].cflag  = flag;
	tclassList[cid].oflag  = KNH_FLAG_CF2OF(flag);
	tclassList[cid].sid    = sid;
	tclassList[cid].supcid = supcid; 

	if(KNH_FLAG_IS(flag, KNH_FLAG_CF_SYSTEM)) {
		knh_NameSpace_setClass(ctx, knh_NameSpace_SYSTEM(), tclassList[cid].name, cid);
	}

	DEBUG_ASSERT(tclassList[cid].cstruct != NULL);
	KNH_SETv(ctx, tclassList[cid].cstruct, cs);
	;
	return cid;
}

/* ------------------------------------------------------------------------ */
/* [load] */

void
knh_tclass_load(Ctx *ctx, knh_bytes_t nsname)
{
	TODO();
}

/* ------------------------------------------------------------------------ */

void
knh_NameSpace_import(Ctx *ctx, NameSpace *ns, knh_bytes_t p)
{
	if(p.buf[p.len-1] == '*') {
		p.len--;
	}

	DEBUG_ASSERT(p.buf[p.len-1] == '.');
	
	int i;
	for(i = 0; i < tclassList_size; i++) {
		if(tclassList[i].name == NULL) continue;
		DEBUG_ASSERT(IS_String(tclassList[i].name));
		knh_bytes_t cname = knh_String_tobytes(tclassList[i].name);
		if(knh_bytes_startsWith(cname, p) && isupper(cname.buf[p.len])) {
			knh_NameSpace_setLocalName(ctx, ns, tclassList[i].name, (knh_class_t)i);
		}
	}
}


/* ------------------------------------------------------------------------ */
/* [ARRAY] */

knh_class_t
knh_type_toarray(Ctx *ctx, knh_type_t type)
{
	return CLASS_Array;
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
