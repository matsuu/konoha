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
/* [prototype] */

/* ../package/math/math_Math.c */;
char *package_version__math(void);;
char *package_copyright__math(void);;
char *package_license__math(void);;
char *package_homepage__math(void);;
char *package_prefix__math(void);;
Object *knh_Math_initValue(Ctx *ctx, knh_class_t cid);;
CLASS knh__Math(Ctx *ctx, knh_flag_t flag, String *name, knh_class_t super_cid);;
METHOD knh__Math_sin(Ctx *ctx, Object **sfp);;
/* ======================================================================== */

/* ======================================================================== */
/* [package] */

#ifdef KONOHA_MONOLITHIC
void knh_package_math_ginit(Ctx *ctx)
{

	KNH_TFUNC(ctx, "package_version__math", (void*)package_version__math);
	KNH_TFUNC(ctx, "package_copyright__math", (void*)package_copyright__math);
	KNH_TFUNC(ctx, "package_license__math", (void*)package_license__math);
	KNH_TFUNC(ctx, "package_homepage__math", (void*)package_homepage__math);
	KNH_TFUNC(ctx, "package_prefix__math", (void*)package_prefix__math);
	KNH_TFUNC(ctx, "knh__Math", (void*)knh__Math);
	KNH_TFUNC(ctx, "knh__Math_sin", (void*)knh__Math_sin);
}
#endif/*KONOHA_MONOLITHIC*/

#ifdef __cplusplus
}
#endif
