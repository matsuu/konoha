/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#include<konoha.h>
#define _USE_MATH_DEFINES     /* for Visual C++ */
#include<math.h>              /* @using math -lm */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

static
knh_IntConstData_t IntConstData[] = {
	{NULL}  // end of const data
};

static
knh_FloatConstData_t FloatConstData[] = {
	{"math.Math.PI", M_PI},   // pi
	{"math.Math.E", M_E},   // base of natural logarithm, e
	{NULL}  // end of const data
};

static
knh_StringConstData_t StringConstData[] = {
	{NULL}  // end of const data
};

/* ------------------------------------------------------------------------ */
// >>> @Singleton class Math;
// >>> float Math.sin(float x);

METHOD Math_sin(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, sin(p_double(sfp[1])));
}

/* ------------------------------------------------------------------------ */
// >>> float Math.abs(float x);

METHOD Math_abs(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, fabs(p_double(sfp[1])));
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) init(Ctx *ctx)
{
	KNH_NOTICE(ctx, "loading math ..");
	konoha_loadIntConstData(ctx, IntConstData);
	konoha_loadFloatConstData(ctx, FloatConstData);
	konoha_loadStringConstData(ctx, StringConstData);
	return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
