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
knh_connptr_t * knh_Connection_open__mysql(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd);
knh_ResultSet* knh_Connection_query__mysql(Ctx *ctx, knh_connptr_t *conn, char *sql);
void knh_Connection_close__mysql(Ctx *ctx, knh_connptr_t *conn);

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [structs] */

void knh_Connection_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Connection *b =  (Connection*)s1;
	b->conn = NULL;
	KNH_INITv(b->urn, knh_String_EMPTY());
	b->drv.fopen  = knh_Connection_open__nop;
	b->drv.fquery = knh_Connection_query__nop;
	b->drv.fclose = knh_Connection_close__nop;
}

/* ------------------------------------------------------------------------ */

#define _knh_Connection_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_Connection_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void knh_Connection_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Connection *b = (Connection*)s;
	gc(ctx, b->urn);
	if(IS_SWEEP(gc) && b->conn != NULL) {
		b->drv.fclose(ctx, b->conn);
		b->conn = NULL;
	}
}

/* ======================================================================== */
/* [constructors] */

void knh_Connection_init(Ctx *ctx, Connection *b, knh_bytes_t urn)
{
	knh_index_t idx = knh_bytes_index(urn, ':');
	if(idx == -1) {
		return ;	
	}
	
	knh_bytes_t drv = knh_bytes_first(urn, idx);
	if(ISB(drv, "ubiql")) {
		b->drv.fopen = knh_Connection_open__ubiql;
		b->drv.fquery = knh_Connection_query__ubiql;
		b->drv.fclose = knh_Connection_close__ubiql;
	}
//	else if(ISB(drv, "mysql")) {
//		b->drv.fopen = knh_Connection_open__mysql;
//		b->drv.fquery = knh_Connection_query__mysql;
//		b->drv.fclose = knh_Connection_close__mysql;
//	}
	else {
		b->drv.fopen = (f_connptr_open)knh_system_loadDriverFunc(ctx, drv,   "knh_Connection_open", knh_Connection_open__nop);
		b->drv.fquery = (f_connptr_query)knh_system_loadDriverFunc(ctx, drv, "knh_Connection_query", knh_Connection_query__nop);
		b->drv.fclose = (f_connptr_close)knh_system_loadDriverFunc(ctx, drv, "knh_Connection_close", knh_Connection_close__nop);
	}
	
	b->conn = b->drv.fopen(ctx, urn, NULL, NULL);
	if(b->conn == NULL) {
		b->drv.fquery = knh_Connection_query__nop;
		b->drv.fclose = knh_Connection_close__nop;
	}
}

/* ------------------------------------------------------------------------ */

Connection* new_Connection(Ctx *ctx, String *urn)
{
	Connection *b = (Connection*)knh_Object_malloc0(ctx, KNH_FLAG_Connection, CLASS_Connection, sizeof(Connection));
	knh_Connection_struct_init(ctx, (Struct*)b, 0, NULL);
	KNH_SETv(ctx, b->urn, urn);
	knh_Connection_init(ctx, b, knh_String_tobytes(urn));
	return b;
}

/* ======================================================================== */
/* [nop] */

/* ------------------------------------------------------------------------ */
/* @method void Connection.close() */

void knh_Connection_close(Ctx *ctx, Connection *b)
{
	b->drv.fclose(ctx, b->conn);
	b->drv.fquery = knh_Connection_query__nop;
	b->drv.fclose = knh_Connection_close__nop;
	b->conn = NULL;
}

/* ======================================================================== */
/* [nop] */

knh_connptr_t *
knh_Connection_open__nop(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

ResultSet* 
knh_Connection_query__nop(Ctx *ctx, knh_connptr_t *ptr, char *sql)
{
	return KNH_NULL;
}	

/* ------------------------------------------------------------------------ */

void knh_Connection_close__nop(Ctx *ctx, knh_connptr_t *ptr)
{

}

/* ======================================================================== */
/* [TFUNC] */

void
KNH_TFUNC_CONNECTION_OPEN(Ctx *ctx, char *n, f_connptr_open f)
{
	if(f == NULL) f = knh_Connection_open__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_CONNECTION_QUERY(Ctx *ctx, char *n, f_connptr_query f)
{
	if(f == NULL) f = knh_Connection_query__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_CONNECTION_CLOSE(Ctx *ctx, char *n, f_connptr_close f)
{
	if(f == NULL) f = knh_Connection_close__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
