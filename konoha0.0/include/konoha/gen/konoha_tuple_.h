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

#ifndef KONOHA_TUPLE__H
#define KONOHA_TUPLE__H

#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

void knh_Tuple1_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple1_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple1_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple1_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple2_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple2_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple2_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple2_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple3_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple3_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple3_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple3_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple4_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple4_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple4_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple4_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple5_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple5_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple5_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple5_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple6_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple6_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple6_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple6_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple7_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple7_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple7_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple7_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple8_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple8_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple8_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple8_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple9_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple9_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple9_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple9_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple10_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple10_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple10_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple10_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple11_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple11_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple11_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple11_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple12_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple12_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple12_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple12_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple13_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple13_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple13_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple13_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple14_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple14_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple14_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple14_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Tuple15_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple15_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple15_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple15_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_TUPLE__H*/
