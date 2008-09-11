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

#ifndef KONOHA_GLOBAL_H_
#define KONOHA_GLOBAL_H_

#include<konoha/gen/konoha_class_.h>

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#ifndef KNH_TINT_MIN
#define KNH_TINT_MIN -1  /* @property */
#endif

#ifndef KNH_TINT_MAX
#ifdef KNH_FASTMODE
#define KNH_TINT_MAX 1024  /* @property */
#else
#define KNH_TINT_MAX 256  /* @property */
#endif
#endif

#ifndef KNH_TOBJECT_C
	extern knh_Object_t*        knh_constNull;
	extern knh_Object_t*        knh_constVoid;
	extern knh_Object_t*        knh_constTrue;
	extern knh_Object_t*        knh_constFalse;
	extern knh_System_t        *knh_rootSystem;
	extern knh_Int_t**          knh_tInt;
	extern knh_String_t       **knh_tString;
	extern knh_MethodField_t  **knh_tMethodField;

#define KNH_NULL            knh_constNull
//#define KNH_NULL            ALT_NULL()
#define KNH_VOID            knh_constVoid
#define KNH_TRUE            knh_constTrue
#define KNH_FALSE           knh_constFalse
#define KNH_SYSTEM          knh_rootSystem

#endif

/* ------------------------------------------------------------------------ */

#ifndef KNH_TSTRUCT_SIZE
#define KNH_TSTRUCT_SIZE 1024
#endif

#define STRUCT_newid         ((knh_struct_t)-1)

#ifndef KNH_TSTRUCT_C
	extern const knh_tStruct_t       *knh_tStruct;
#endif

/* ------------------------------------------------------------------------ */

#ifndef KNH_TCLASS_SIZE
#define KNH_TCLASS_SIZE 1024
#endif

#ifndef KNH_TCLASS_C
	extern const knh_tClass_t       *knh_tClass;
#endif


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_GLOBAL_H_*/
