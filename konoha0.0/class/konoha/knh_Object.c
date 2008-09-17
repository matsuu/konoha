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

#define _knh_Object_cid(o)           (o)->h.cid
#define _knh_Object_bcid(o)          (o)->h.bcid

/* ======================================================================== */
/* [init] */

Object *new_Object__init(Ctx *ctx, knh_flag_t flag, knh_class_t cid)
{
	DEBUG_ASSERT_cid(cid);
		
	switch(knh_tClass[cid].bcid) {
	
	case CLASS_Nue :       
		KNH_ASSERT(ctx == NULL); /* stop */
		return (Object*)KNH_NULL;
	case CLASS_Boolean :   
		KNH_ASSERT(ctx == NULL); /* stop */
		return (Object*)KNH_FALSE;
	case CLASS_Class :     
		KNH_ASSERT(ctx == NULL); /* stop */
		return (Object*)knh_tClass[CLASS_Object].class_cid;

	case CLASS_Int :       case CLASS_IntX :
	case CLASS_Float :     case CLASS_FloatX :
	case CLASS_Int64:      case CLASS_Int64X :
	case CLASS_String :    case CLASS_StringX :
		KNH_ASSERT(ctx == NULL); /* stop */
		return knh_tClass[cid].fdefault(ctx, cid);

	case CLASS_Context:
		{
			KNH_ASSERT(ctx == NULL); /* stop */
			return (Object*)ctx;
		}
		
	case CLASS_Bytes :
		{
			KNH_ASSERT((knh_tClass[cid].size == 0));
			knh_Bytes_t *b = (knh_Bytes_t*)new_Object(ctx, flag, cid);
			b->buf = (knh_uchar_t*)NULL;
			b->size = 0;
			return (Object*)b;
		}

	case CLASS_Range:
	case CLASS_Tuple2:
		{
			KNH_ASSERT((knh_tClass[cid].size == 0));
			knh_Tuple2_t *t = (knh_Tuple2_t*)new_Object(ctx, flag, cid);
			KNH_INITv(t->first, KNH_NULL);
			KNH_INITv(t->second, KNH_NULL);
			return (Object*)t;
		}
		
	case CLASS_Array :
		{
			KNH_ASSERT((knh_tClass[cid].size == 0));
			knh_Array_t *a = (knh_Array_t*)new_Object(ctx, flag, cid);
			a->list = NULL;
			a->size = 0;
			return (Object*)a;
		}
	

	case CLASS_Object:
	default :
		{
			return new_Object(ctx, flag, cid);
		}
	}
}

/* ======================================================================== */
/* [copy] */

Object *knh_Object_copy(Ctx *ctx, Object *b)
{
	if(knh_Object_isImmutable(b)) {
		return b;
	}
	DBG2_P("!IMMUTABLE %s", CLASSN(knh_Object_cid(b)));
	return b;
}

/* ======================================================================== */
/* [commons] */

knh_hcode_t knh_Object_hashCode(Object *o)
{
	if(o->h.cid == CLASS_Object) {
		return (knh_hcode_t)o / sizeof(Object*);
	}
	else {
		return knh_tStruct[o->h.bcid].fhashCode(o);
	}
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_Object_tobytes(Ctx *ctx, Object *o)
{
	switch(o->h.bcid) {
		case STRUCT_String : return knh_String_tobytes((String*)o);
		case STRUCT_Bytes : return knh_Bytes_tobytes((Bytes*)o);
	}
	TODO();
	return STEXT("");
}

/* ======================================================================== */
/* [structs] */

/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* @map Object String! */

String* knh_Object_String(Ctx *ctx, Object *o, Mapper *map)
{
	return knh_Object_movableText(ctx, o, METHODN__s, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

