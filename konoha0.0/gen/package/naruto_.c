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

/* ======================================================================== */
/* [flag] */

/* ======================================================================== */
/* [method] */

METHOD knh__Amazon_placeOrder(Ctx *ctx, Object **sfp)
{
	/* method void Amazon.placeOrder(String uname, String order)  */
	knh_Amazon_placeOrder(
		ctx,
		(knh_Amazon*)sfp[0],
		(String*)sfp[1] /* String sfp[1] => String* uname */,
		(String*)sfp[2] /* String sfp[2] => String* order */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

/* ======================================================================== */
/* [package] */

void knh_package_naruto_ginit(Ctx *ctx)
{

	KNH_TSTRUCT(ctx, STRUCT_Counter, sizeof(knh_Counter),
		"Counter",
		knh_Counter_struct_init,
		knh_Counter_struct_copy, 
		knh_Counter_struct_compare, 
		knh_Counter_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Amazon, sizeof(knh_Amazon),
		"Amazon",
		knh_Amazon_struct_init,
		knh_Amazon_struct_copy, 
		knh_Amazon_struct_compare, 
		knh_Amazon_struct_traverse);
	KNH_TCLASS(ctx, KNH_CFLAG_Counter,
		new_String__STEXT(ctx, CLASS_String, "naruto.Counter"),
		CLASS_Counter, STRUCT_Counter, CLASS_Object,
		KNH_NULL, knh_Counter_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Amazon,
		new_String__STEXT(ctx, CLASS_String, "naruto.Amazon"),
		CLASS_Amazon, STRUCT_Amazon, CLASS_Object,
		KNH_NULL, knh_Amazon_fvalue, 0); 
	KNH_TMETHOD(ctx, 
		0, 
		knh__Counter_new, NULL, /*delta*/0, 
		CLASS_Counter, CLASS_Counter, METHODN_new, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Counter_count, NULL, /*delta*/0, 
		TYPE_void, CLASS_Counter, METHODN_count, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Counter_getCount, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Counter, METHODN_getCount, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Counter_reset, NULL, /*delta*/0, 
		TYPE_void, CLASS_Counter, METHODN_reset, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Counter__s, /*delta*/0, 
		TYPE_void, CLASS_Counter, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Amazon_placeOrder, NULL, /*delta*/0, 
		TYPE_void, CLASS_Amazon, METHODN_placeOrder, 2,
		TYPE_String, FIELDN_uname,
		TYPE_String, FIELDN_order
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Counter, CLASS_Int,  
		knh_Counter_Int, KNH_NULL
	);

}

#ifdef __cplusplus
}
#endif
