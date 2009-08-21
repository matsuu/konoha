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
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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
/* [constructors] */

void knh_Connection_open(Ctx *ctx, Connection *o, String *urn)
{
	knh_bytes_t u = knh_String_tobytes(urn);
	knh_index_t idx = knh_bytes_index(u, ':');
	KNH_SETv(ctx, DP(o)->urn, urn);
	if(idx == -1) {
		KNH_ASSERT(DP(o)->conn == NULL);
		DP(o)->df = knh_System_getDefaultDBDriver();
	}
	else {
		DP(o)->df = knh_System_getDBDriver(ctx, knh_bytes_first(u, idx));
		DP(o)->conn = DP(o)->df->dbopen(ctx, u);
		if(DP(o)->conn == NULL) {
			DP(o)->df = knh_System_getDefaultDBDriver();
		}
	}
}

/* ------------------------------------------------------------------------ */

Connection* new_Connection(Ctx *ctx, String *urn)
{
	knh_Connection_t *o = (Connection*)new_Object_bcid(ctx, CLASS_Connection, 0);
	knh_Connection_open(ctx, o, urn);
	return o;
}

/* ------------------------------------------------------------------------ */
/* @method void Connection.close() */

void knh_Connection_close(Ctx *ctx, Connection *o)
{
	DP(o)->df->dbclose(ctx, DP(o)->conn);
	DP(o)->conn = NULL;
	DP(o)->df = NULL;
;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
