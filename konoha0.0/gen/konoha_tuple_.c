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

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

void knh_Tuple1_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple1 *b  = (Tuple1*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple1_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple1 *b  = (Tuple1*)s;
	Tuple1 *b2 = (Tuple1*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple1_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple1 *b  = (Tuple1*)s;
	Tuple1 *b2 = (Tuple1*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple1_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple1 *b  = (Tuple1*)s;
	gc(ctx, b->v[0]);
}

void knh_Tuple2_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple2 *b  = (Tuple2*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple2_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple2 *b  = (Tuple2*)s;
	Tuple2 *b2 = (Tuple2*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple2_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple2 *b  = (Tuple2*)s;
	Tuple2 *b2 = (Tuple2*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple2_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple2 *b  = (Tuple2*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
}

void knh_Tuple3_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple3 *b  = (Tuple3*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple3_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple3 *b  = (Tuple3*)s;
	Tuple3 *b2 = (Tuple3*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple3_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple3 *b  = (Tuple3*)s;
	Tuple3 *b2 = (Tuple3*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple3_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple3 *b  = (Tuple3*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
}

void knh_Tuple4_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple4 *b  = (Tuple4*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple4_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple4 *b  = (Tuple4*)s;
	Tuple4 *b2 = (Tuple4*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple4_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple4 *b  = (Tuple4*)s;
	Tuple4 *b2 = (Tuple4*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple4_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple4 *b  = (Tuple4*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
}

void knh_Tuple5_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple5 *b  = (Tuple5*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple5_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple5 *b  = (Tuple5*)s;
	Tuple5 *b2 = (Tuple5*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple5_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple5 *b  = (Tuple5*)s;
	Tuple5 *b2 = (Tuple5*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple5_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple5 *b  = (Tuple5*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
}

void knh_Tuple6_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple6 *b  = (Tuple6*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple6_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple6 *b  = (Tuple6*)s;
	Tuple6 *b2 = (Tuple6*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple6_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple6 *b  = (Tuple6*)s;
	Tuple6 *b2 = (Tuple6*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple6_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple6 *b  = (Tuple6*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
}

void knh_Tuple7_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple7 *b  = (Tuple7*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple7_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple7 *b  = (Tuple7*)s;
	Tuple7 *b2 = (Tuple7*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple7_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple7 *b  = (Tuple7*)s;
	Tuple7 *b2 = (Tuple7*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple7_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple7 *b  = (Tuple7*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
}

void knh_Tuple8_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple8 *b  = (Tuple8*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple8_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple8 *b  = (Tuple8*)s;
	Tuple8 *b2 = (Tuple8*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple8_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple8 *b  = (Tuple8*)s;
	Tuple8 *b2 = (Tuple8*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple8_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple8 *b  = (Tuple8*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
}

void knh_Tuple9_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple9 *b  = (Tuple9*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple9_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple9 *b  = (Tuple9*)s;
	Tuple9 *b2 = (Tuple9*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple9_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple9 *b  = (Tuple9*)s;
	Tuple9 *b2 = (Tuple9*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple9_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple9 *b  = (Tuple9*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
}

void knh_Tuple10_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple10 *b  = (Tuple10*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple10_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple10 *b  = (Tuple10*)s;
	Tuple10 *b2 = (Tuple10*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple10_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple10 *b  = (Tuple10*)s;
	Tuple10 *b2 = (Tuple10*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple10_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple10 *b  = (Tuple10*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
}

void knh_Tuple11_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple11 *b  = (Tuple11*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
		KNH_INITv(b->v[10], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
		KNH_INITv(b->v[10], knh_ClassStruct_safevalue(ctx, cs, 10));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple11_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple11 *b  = (Tuple11*)s;
	Tuple11 *b2 = (Tuple11*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
	KNH_SETv(ctx, b2->v[10], b->v[10]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple11_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple11 *b  = (Tuple11*)s;
	Tuple11 *b2 = (Tuple11*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[10], b2->v[10]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple11_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple11 *b  = (Tuple11*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
	gc(ctx, b->v[10]);
}

void knh_Tuple12_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple12 *b  = (Tuple12*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
		KNH_INITv(b->v[10], KNH_NULL);
		KNH_INITv(b->v[11], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
		KNH_INITv(b->v[10], knh_ClassStruct_safevalue(ctx, cs, 10));
		KNH_INITv(b->v[11], knh_ClassStruct_safevalue(ctx, cs, 11));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple12_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple12 *b  = (Tuple12*)s;
	Tuple12 *b2 = (Tuple12*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
	KNH_SETv(ctx, b2->v[10], b->v[10]);
	KNH_SETv(ctx, b2->v[11], b->v[11]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple12_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple12 *b  = (Tuple12*)s;
	Tuple12 *b2 = (Tuple12*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[10], b2->v[10]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[11], b2->v[11]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple12_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple12 *b  = (Tuple12*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
	gc(ctx, b->v[10]);
	gc(ctx, b->v[11]);
}

void knh_Tuple13_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple13 *b  = (Tuple13*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
		KNH_INITv(b->v[10], KNH_NULL);
		KNH_INITv(b->v[11], KNH_NULL);
		KNH_INITv(b->v[12], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
		KNH_INITv(b->v[10], knh_ClassStruct_safevalue(ctx, cs, 10));
		KNH_INITv(b->v[11], knh_ClassStruct_safevalue(ctx, cs, 11));
		KNH_INITv(b->v[12], knh_ClassStruct_safevalue(ctx, cs, 12));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple13_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple13 *b  = (Tuple13*)s;
	Tuple13 *b2 = (Tuple13*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
	KNH_SETv(ctx, b2->v[10], b->v[10]);
	KNH_SETv(ctx, b2->v[11], b->v[11]);
	KNH_SETv(ctx, b2->v[12], b->v[12]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple13_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple13 *b  = (Tuple13*)s;
	Tuple13 *b2 = (Tuple13*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[10], b2->v[10]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[11], b2->v[11]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[12], b2->v[12]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple13_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple13 *b  = (Tuple13*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
	gc(ctx, b->v[10]);
	gc(ctx, b->v[11]);
	gc(ctx, b->v[12]);
}

void knh_Tuple14_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple14 *b  = (Tuple14*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
		KNH_INITv(b->v[10], KNH_NULL);
		KNH_INITv(b->v[11], KNH_NULL);
		KNH_INITv(b->v[12], KNH_NULL);
		KNH_INITv(b->v[13], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
		KNH_INITv(b->v[10], knh_ClassStruct_safevalue(ctx, cs, 10));
		KNH_INITv(b->v[11], knh_ClassStruct_safevalue(ctx, cs, 11));
		KNH_INITv(b->v[12], knh_ClassStruct_safevalue(ctx, cs, 12));
		KNH_INITv(b->v[13], knh_ClassStruct_safevalue(ctx, cs, 13));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple14_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple14 *b  = (Tuple14*)s;
	Tuple14 *b2 = (Tuple14*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
	KNH_SETv(ctx, b2->v[10], b->v[10]);
	KNH_SETv(ctx, b2->v[11], b->v[11]);
	KNH_SETv(ctx, b2->v[12], b->v[12]);
	KNH_SETv(ctx, b2->v[13], b->v[13]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple14_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple14 *b  = (Tuple14*)s;
	Tuple14 *b2 = (Tuple14*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[10], b2->v[10]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[11], b2->v[11]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[12], b2->v[12]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[13], b2->v[13]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple14_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple14 *b  = (Tuple14*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
	gc(ctx, b->v[10]);
	gc(ctx, b->v[11]);
	gc(ctx, b->v[12]);
	gc(ctx, b->v[13]);
}

void knh_Tuple15_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Tuple15 *b  = (Tuple15*)s;
	if(cs == NULL) {
		KNH_INITv(b->v[0], KNH_NULL);
		KNH_INITv(b->v[1], KNH_NULL);
		KNH_INITv(b->v[2], KNH_NULL);
		KNH_INITv(b->v[3], KNH_NULL);
		KNH_INITv(b->v[4], KNH_NULL);
		KNH_INITv(b->v[5], KNH_NULL);
		KNH_INITv(b->v[6], KNH_NULL);
		KNH_INITv(b->v[7], KNH_NULL);
		KNH_INITv(b->v[8], KNH_NULL);
		KNH_INITv(b->v[9], KNH_NULL);
		KNH_INITv(b->v[10], KNH_NULL);
		KNH_INITv(b->v[11], KNH_NULL);
		KNH_INITv(b->v[12], KNH_NULL);
		KNH_INITv(b->v[13], KNH_NULL);
		KNH_INITv(b->v[14], KNH_NULL);
	}else {
		KNH_INITv(b->v[0], knh_ClassStruct_safevalue(ctx, cs, 0));
		KNH_INITv(b->v[1], knh_ClassStruct_safevalue(ctx, cs, 1));
		KNH_INITv(b->v[2], knh_ClassStruct_safevalue(ctx, cs, 2));
		KNH_INITv(b->v[3], knh_ClassStruct_safevalue(ctx, cs, 3));
		KNH_INITv(b->v[4], knh_ClassStruct_safevalue(ctx, cs, 4));
		KNH_INITv(b->v[5], knh_ClassStruct_safevalue(ctx, cs, 5));
		KNH_INITv(b->v[6], knh_ClassStruct_safevalue(ctx, cs, 6));
		KNH_INITv(b->v[7], knh_ClassStruct_safevalue(ctx, cs, 7));
		KNH_INITv(b->v[8], knh_ClassStruct_safevalue(ctx, cs, 8));
		KNH_INITv(b->v[9], knh_ClassStruct_safevalue(ctx, cs, 9));
		KNH_INITv(b->v[10], knh_ClassStruct_safevalue(ctx, cs, 10));
		KNH_INITv(b->v[11], knh_ClassStruct_safevalue(ctx, cs, 11));
		KNH_INITv(b->v[12], knh_ClassStruct_safevalue(ctx, cs, 12));
		KNH_INITv(b->v[13], knh_ClassStruct_safevalue(ctx, cs, 13));
		KNH_INITv(b->v[14], knh_ClassStruct_safevalue(ctx, cs, 14));
	}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple15_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple15 *b  = (Tuple15*)s;
	Tuple15 *b2 = (Tuple15*)s2;
	KNH_SETv(ctx, b2->v[0], b->v[0]);
	KNH_SETv(ctx, b2->v[1], b->v[1]);
	KNH_SETv(ctx, b2->v[2], b->v[2]);
	KNH_SETv(ctx, b2->v[3], b->v[3]);
	KNH_SETv(ctx, b2->v[4], b->v[4]);
	KNH_SETv(ctx, b2->v[5], b->v[5]);
	KNH_SETv(ctx, b2->v[6], b->v[6]);
	KNH_SETv(ctx, b2->v[7], b->v[7]);
	KNH_SETv(ctx, b2->v[8], b->v[8]);
	KNH_SETv(ctx, b2->v[9], b->v[9]);
	KNH_SETv(ctx, b2->v[10], b->v[10]);
	KNH_SETv(ctx, b2->v[11], b->v[11]);
	KNH_SETv(ctx, b2->v[12], b->v[12]);
	KNH_SETv(ctx, b2->v[13], b->v[13]);
	KNH_SETv(ctx, b2->v[14], b->v[14]);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple15_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
	Tuple15 *b  = (Tuple15*)s;
	Tuple15 *b2 = (Tuple15*)s2;
	knh_int_t res;
	res = knh_Object_compare(ctx, b->v[0], b2->v[0]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[1], b2->v[1]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[2], b2->v[2]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[3], b2->v[3]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[4], b2->v[4]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[5], b2->v[5]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[6], b2->v[6]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[7], b2->v[7]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[8], b2->v[8]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[9], b2->v[9]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[10], b2->v[10]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[11], b2->v[11]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[12], b2->v[12]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[13], b2->v[13]);
	if(res != 0) return res;
	res = knh_Object_compare(ctx, b->v[14], b2->v[14]);
	if(res != 0) return res;
	return res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple15_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Tuple15 *b  = (Tuple15*)s;
	gc(ctx, b->v[0]);
	gc(ctx, b->v[1]);
	gc(ctx, b->v[2]);
	gc(ctx, b->v[3]);
	gc(ctx, b->v[4]);
	gc(ctx, b->v[5]);
	gc(ctx, b->v[6]);
	gc(ctx, b->v[7]);
	gc(ctx, b->v[8]);
	gc(ctx, b->v[9]);
	gc(ctx, b->v[10]);
	gc(ctx, b->v[11]);
	gc(ctx, b->v[12]);
	gc(ctx, b->v[13]);
	gc(ctx, b->v[14]);
}

#ifdef __cplusplus
}
#endif
