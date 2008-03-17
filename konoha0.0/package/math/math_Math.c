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

#include<konoha/konoha_config.h>

#ifdef KONOHA_PACKAGE

#include<math.h>    /* @using math -lm */
#include<konoha/konoha_dev.h>

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [info] */

char *package_version__math(void)
{
	return "1.0";
}

/* ------------------------------------------------------------------------ */

char *package_copyright__math(void)
{
	/* Why don't you add your name ? */
	return "Copyright (c) 2007, Kimio Kuramitsu, Konoha Software Foundation";
}

/* ------------------------------------------------------------------------ */

char *package_license__math(void)
{
#ifdef KONOHA_UNDER_GPL
	return "GNU Public License " KONOHA_UNDER_GPL;
#else
	return "Konoha Software Foundation License 1.0";
#endif
}

/* ------------------------------------------------------------------------ */

char *package_homepage__math(void)
{
	return "http://konoha.sourceforge.jp/";
}

/* ------------------------------------------------------------------------ */

char *package_prefix__math(void)
{
	return "knh";
}

/* ======================================================================== */
/* [struct] */


/* ======================================================================== */
/* [class] */

static Object *staticMath = NULL;

/* ------------------------------------------------------------------------ */

Object *knh_Math_initValue(Ctx *ctx, knh_class_t cid)
{
	if(staticMath == NULL) {
		staticMath = knh_Object_malloc(ctx, cid);
		KNH_TGLOBAL(staticMath);
	}
	return staticMath;
}


/* ------------------------------------------------------------------------ */

CLASS knh__Math(Ctx *ctx, knh_flag_t flag, String *name, knh_class_t super_cid)
{
	KNH_TCLASS(ctx, 
		flag,          /* NO NEED TO CHANGE */
		name,          /* NO NEED TO CHANGE */
		CLASS_newid,   /* NO NEED TO CHANGE */
		STRUCT_Object, /* struct id */
		super_cid,     /* NO NEED TO CHANGE */
		KNH_NULL,
		knh_Math_initValue, 
		0);
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method Float! Math.sin(Float! *v) */

METHOD knh__Math_sin(Ctx *ctx, Object **sfp)
{
#if defined(KNH_FLOAT_TYPE__LONG_DOUBLE)
	Float *v = new_Float(ctx, (knh_float_t)sinl((long double)knh_Number_tofloat(sfp[1])));
#elif defined(KNH_FLOAT_TYPE__FLOAT)
	Float *v = new_Float(ctx, (knh_float_t)sinf((float)knh_Number_tofloat(sfp[1])));
#else
	Float *v = new_Float(ctx, (knh_float_t)sin((double)knh_Number_tofloat(sfp[1])));
#endif
	METHOD_RETURN(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif/*KONOHA_PACKAGE*/
