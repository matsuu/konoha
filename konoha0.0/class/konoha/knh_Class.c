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

#define _CLASS_newid          ((knh_class_t)-1)
#define _CLASS_unknown        ((knh_class_t)-2)

#define _knh_Class_cid(c)     (knh_class_t)(c)->cid

/* ------------------------------------------------------------------------ */

knh_Class_t *new_Class__type(Ctx *ctx, knh_type_t type)
{
	knh_Class_t *o = (knh_Class_t*)new_PObject0(ctx, FLAG_Class, CLASS_Class, CLASS_Class);
	o->type = type;
	o->cid = TYPE_UNMASK(type);
	return o;
}

/* ------------------------------------------------------------------------ */

Object *knh_Class_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)knh_tClass[CLASS_Class].class_cid;
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_Class_hashCode(Class *o)
{
	return (knh_hcode_t)o->cid;
}

/* ------------------------------------------------------------------------ */

int knh_Class_compareTo(Class *o, Class *o2)
{
	return knh_strcmp(CLASSN(o->cid), CLASSN(o2->cid));
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
