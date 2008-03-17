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

/* ======================================================================== */
/* [package] */

void knh_package_konohac_ginit(Ctx *ctx)
{

	KNH_TSTRUCT(ctx, STRUCT_Token, sizeof(knh_Token),
		"Token",
		knh_Token_struct_init,
		knh_Token_struct_copy, 
		knh_Token_struct_compare, 
		knh_Token_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Stmt, sizeof(knh_Stmt),
		"Stmt",
		knh_Stmt_struct_init,
		knh_Stmt_struct_copy, 
		knh_Stmt_struct_compare, 
		knh_Stmt_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Cmpl, sizeof(knh_Cmpl),
		"Cmpl",
		knh_Cmpl_struct_init,
		knh_Cmpl_struct_copy, 
		knh_Cmpl_struct_compare, 
		knh_Cmpl_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_VirtualMachineCode, sizeof(knh_VirtualMachineCode),
		"VirtualMachineCode",
		knh_VirtualMachineCode_struct_init,
		knh_VirtualMachineCode_struct_copy, 
		knh_VirtualMachineCode_struct_compare, 
		knh_VirtualMachineCode_struct_traverse);
	KNH_TCLASS(ctx, KNH_CFLAG_Token,
		new_String__STEXT(ctx, CLASS_String, "konohac.Token"),
		CLASS_Token, STRUCT_Token, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Stmt,
		new_String__STEXT(ctx, CLASS_String, "konohac.Stmt"),
		CLASS_Stmt, STRUCT_Stmt, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Cmpl,
		new_String__STEXT(ctx, CLASS_String, "konohac.Cmpl"),
		CLASS_Cmpl, STRUCT_Cmpl, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_VirtualMachineCode,
		new_String__STEXT(ctx, CLASS_String, "konohac.VirtualMachineCode"),
		CLASS_VirtualMachineCode, STRUCT_VirtualMachineCode, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Stmt__s, /*delta*/0, 
		TYPE_void, CLASS_Stmt, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Stmt__dump, /*delta*/0, 
		TYPE_void, CLASS_Stmt, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_VirtualMachineCode__dump, /*delta*/0, 
		TYPE_void, CLASS_VirtualMachineCode, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Method__code, /*delta*/0, 
		TYPE_void, CLASS_Method, METHODN__code, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Token__s, /*delta*/0, 
		TYPE_void, CLASS_Token, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Token__dump, /*delta*/0, 
		TYPE_void, CLASS_Token, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

}

#ifdef __cplusplus
}
#endif
