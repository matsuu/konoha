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

/* ../driver/mysql/knh_Connection__mysql.c */;
knh_connptr_t * knh_Connection_open__mysql(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd);;
knh_bool_t knh_ResultSet_next__mysql(Ctx *ctx, knh_rsptr_t *rsptr, ResultSet *b);;
void knh_ResultSet_free__mysql(knh_rsptr_t *rsptr);;
knh_ResultSet* knh_Connection_query__mysql(Ctx *ctx, knh_connptr_t *conn, char *sql);;
void knh_Connection_close__mysql(Ctx *ctx, knh_connptr_t *conn);;
/* ======================================================================== */

/* ======================================================================== */
/* [driver] */

#ifdef KONOHA_MONOLITHIC
void knh_driver_mysql_ginit(Ctx *ctx)
{

	KNH_TFUNC_CONNECTION_OPEN(ctx, "knh_Connection_open__mysql", knh_Connection_open__mysql);
	KNH_TFUNC_CONNECTION_QUERY(ctx, "knh_Connection_query__mysql", knh_Connection_query__mysql);
	KNH_TFUNC_CONNECTION_CLOSE(ctx, "knh_Connection_close__mysql", knh_Connection_close__mysql);
	KNH_TFUNC_RESULTSET_NEXT(ctx, "knh_ResultSet_next__mysql", knh_ResultSet_next__mysql);
	KNH_TFUNC_RESULTSET_FREE(ctx, "knh_ResultSet_free__mysql", knh_ResultSet_free__mysql);
}
#endif/*KONOHA_MONOLITHIC*/

#ifdef __cplusplus
}
#endif
