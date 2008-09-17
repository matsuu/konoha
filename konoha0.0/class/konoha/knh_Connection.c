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
/* [drivers] */

static
knh_connptr_t *knh_Connection_open__NOP(Ctx *ctx, knh_bytes_t url)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
ResultSet* knh_Connection_query__NOP(Ctx *ctx, knh_connptr_t *ptr, char *sql)
{
	KNH_NOTICE(ctx, "Already Closed!!");
	return (ResultSet*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Connection_close__NOP(Ctx *ctx, knh_connptr_t *ptr)
{

}

/* ------------------------------------------------------------------------ */

static
int knh_ResultSet_next__NOP(Ctx *ctx, knh_rshdlr_t *rsptr, struct knh_ResultSet_t *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_ResultSet_free__NOP(knh_rshdlr_t *rsptr)
{

}

static knh_db_drvapi_t DB__NOP = {
	KNH_DRVAPI_TYPE__DB, "NOP",
	knh_Connection_open__NOP,
	knh_Connection_query__NOP,
	knh_Connection_close__NOP,
	knh_ResultSet_next__NOP,
	knh_ResultSet_free__NOP
};

/* ======================================================================== */

knh_db_drvapi_t *
knh_System_getDataBaseDriver(Ctx *ctx, knh_bytes_t name)
{
	if(name.len == 0) {
		return &DB__NOP;
	}
	else {
		knh_db_drvapi_t *p = (knh_db_drvapi_t *)knh_System_getDRVAPI(ctx, KNH_DRVAPI_TYPE__DB, name);
		if(p == NULL) {
			KNH_WARNING(ctx, "DB: unsupported scheme '%s'", name);
			p = &DB__NOP;
		}
		return p;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addDataBaseDriver(Ctx *ctx, char *alias, knh_db_drvapi_t *d)
{
	KNH_TDRVAPI(ctx, alias, (knh_drvapi_t*)d);
}

/* ======================================================================== */
/* [structs] */

void knh_Connection_struct_init(Ctx *ctx, knh_Connection_struct *b, int init, Object *cs)
{
	b->connptr = NULL;
	KNH_INITv(b->urn, TS_EMPTY);
	b->df = &DB__NOP;
}

/* ------------------------------------------------------------------------ */

#define _knh_Connection_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_Connection_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void knh_Connection_struct_traverse(Ctx *ctx, knh_Connection_struct *b, f_traverse ftr)
{
	ftr(ctx, UP(b->urn));
	if(IS_SWEEP(ftr) && b->connptr != NULL) {
		b->df->close_conn(ctx, b->connptr);
		b->connptr = NULL;
	}
}

/* ======================================================================== */
/* [constructors] */

void knh_Connection_open(Ctx *ctx, Connection *o, String *urn)
{
	knh_bytes_t u = knh_String_tobytes(urn);
	knh_index_t idx = knh_bytes_index(u, ':');
	KNH_SETv(ctx, DP(o)->urn, urn);
	if(idx == -1) {
		KNH_ASSERT(DP(o)->connptr == NULL);
		DP(o)->df = knh_System_getDataBaseDriver(ctx, STEXT(""));
	}
	else {
		DP(o)->df = knh_System_getDataBaseDriver(ctx, knh_bytes_first(u, idx));
		DP(o)->connptr = DP(o)->df->open_conn(ctx, u);
		if(DP(o)->connptr == NULL) {
			DP(o)->df = &DB__NOP;
		}
	}
}

/* ------------------------------------------------------------------------ */

Connection* new_Connection(Ctx *ctx, String *urn)
{
	knh_Connection_t *o = (Connection*)new_Object_malloc(ctx, FLAG_Connection, CLASS_Connection, sizeof(knh_Connection_struct));
	knh_Connection_struct_init(ctx, DP(o), 0, NULL);
	knh_Connection_open(ctx, o, urn);
	return o;
}

/* ------------------------------------------------------------------------ */
/* @method void Connection.close() */

void knh_Connection_close(Ctx *ctx, Connection *o)
{
	DP(o)->df->close_conn(ctx, DP(o)->connptr);
	DP(o)->connptr = NULL;
	DP(o)->df = &DB__NOP;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
