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

/* ------------------------------------------------------------------------ */

knh_bool_t knh_tconst_exists(Ctx *ctx, knh_bytes_t name)
{
	return 0;
}

/* ------------------------------------------------------------------------ */


Object *knh_tconst_value(Ctx *ctx, knh_bytes_t name)
{
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */


knh_type_t knh_tconst_type(Ctx *ctx, knh_bytes_t name)
{
	return TYPE_any;
}

//void knh_tconst_set_value(Ctx *ctx, FL *fl, knh_bytes_t name, Object *value)
//{
//
//}

/* ======================================================================== */
/* [uname] */

char *knh_tconst_uname(void)
{
	return KONOHA_OS;
}

//struct utsname {
//    char sysname[];
//    char nodename[];
//    char release[];
//    char version[];
//    char machine[];
//#ifdef _GNU_SOURCE
//    char domainname[];
//#endif
//};


///* ======================================================================== */
///* [default] */
//
//
//Object *knh_tclassp_getDefaultValue(Ctx *ctx, knh_class_t cpid)
//{
//	if(TYPE_ISPLURAL(cpid)) {
//		return new_Iterator(ctx, TYPE_TOSCLASS(cpid), KNH_NULL, NULL);
//	}
//	switch(cpid) {
//	case CLASS_String: return knh_String_EMPTY();
//	case CLASS_Int: return new_Int__fast(ctx, CLASS_Int, 0);
//	}
//	return KNH_NULL;
//}

#ifdef __cplusplus
}
#endif
