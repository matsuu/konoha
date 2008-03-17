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

#ifndef NARUTO__H
#define NARUTO__H

#include<konoha/konoha_config.h>
#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [prototype] */

/* ../api/naruto/knh_Counter_api1.c */
METHOD knh__Counter_new(Ctx *ctx, Object **sfp);
METHOD knh__Counter_count(Ctx *ctx, Object **sfp);
METHOD knh__Counter_getCount(Ctx *ctx, Object **sfp);
METHOD knh__Counter_reset(Ctx *ctx, Object **sfp);
Object* knh_Counter_Int(Ctx *ctx, Object *self, MapMap *map);
void knh_Counter__s(Ctx *ctx, Counter *b, OutputStream *w, Any *m);
/* ../class/naruto/knh_Amazon.c */
void knh_Amazon_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
Amazon *new_Amazon(Ctx *ctx);
Object *knh_Amazon_fvalue(Ctx *ctx, knh_class_t cid);
void knh_Amazon_placeOrder(Ctx *ctx, Amazon *b, String *uname, String *order);
void knh_security_RBAC(Ctx *ctx, Object **sfp);
void knh_security_Audit(Ctx *ctx, Object **sfp);
void knh_Method_weave(Ctx *ctx, Method *b, f_method f);
void knh_weave(Ctx *ctx, f_method f, Method *mtd);
/* ../class/naruto/knh_Counter.c */
void knh_Counter_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Counter_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Counter_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Object *knh_Counter_fvalue(Ctx *ctx, knh_class_t cid);
/* ======================================================================== */

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*NARUTO__H*/
