/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2007       Akihide Takai <atatai at sourceforge.jp>
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

#ifdef KONOHA_USING_MYSQL
	/* @using mysql -lmysqlclient */
	/* @driver mysql Connection ResultSet */
	#include<mysql/mysql.h>
#endif/*KONOHA_USING_MYSQL*/

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif
	
/* ======================================================================== */
// char *url = "mysql://(hostname)/(DB)";

knh_connptr_t *
knh_Connection_open__mysql(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd)
{
#ifdef KONOHA_USING_MYSQL
	MYSQL *conn;
	conn = mysql_init(NULL);
	if(mysql_real_connect(conn, "localhost", "root", "", "test", 0, NULL, 0)==NULL) {
		KNH_THROWs(ctx, "SQL!!: connection error");
	}
	return (knh_connptr_t*)conn;
#else
	return NULL;
#endif/*KONOHA_USING_MYSQL*/
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_ResultSet_next__mysql(Ctx *ctx, knh_rsptr_t *rsptr, ResultSet *b)
{
#ifdef KONOHA_USING_MYSQL
	MYSQL_ROW row;
	int i = 0;
	if((row = mysql_fetch_row(rsptr)) != NULL) {
		knh_ResultSet_initData(ctx, b); /* DO NOT TOUCH */
		for(i = 0; i < b->column_size; i++) {
			if(row[i] == NULL) {
				knh_ResultSet_set__null(ctx, b, i);
				continue;
			}
			switch(b->column[i].dbtype) {
			case MYSQL_TYPE_TINY:
			case MYSQL_TYPE_SHORT:
			case MYSQL_TYPE_LONG:
			case MYSQL_TYPE_INT24:
			case MYSQL_TYPE_BIT:
				knh_ResultSet_set__int(ctx, b, i, knh_bytes_toint(B(row[i])));
				break;
			case MYSQL_TYPE_DECIMAL:
			case MYSQL_TYPE_FLOAT:
			case MYSQL_TYPE_DOUBLE:
				knh_ResultSet_set__float(ctx, b, i, knh_bytes_tofloat(B(row[i])));
				break;
			case MYSQL_TYPE_LONGLONG:
				knh_ResultSet_set__int64(ctx, b, i, knh_bytes_toint64(B(row[i])));
				break;
			default:
				knh_ResultSet_set__bytes(ctx, b, i, B(row[i])); /* char* ==> knh_bytes_t */
				break;
			}
		}
		return 1; /* if you have a tuple */
	}
#else
	return 0; /* if nothing */
#endif/*KONOHA_USING_MYSQL*/
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_free__mysql(knh_rsptr_t *rsptr)
{
#ifdef KONOHA_USING_MYSQL
	mysql_free_result(rsptr);
#endif/*KONOHA_USING_MYSQL*/
}

/* ------------------------------------------------------------------------ */

knh_ResultSet* 
knh_Connection_query__mysql(Ctx *ctx, knh_connptr_t *conn, char *sql)
{
#ifdef KONOHA_USING_MYSQL
	MYSQL_RES *result;
	int i = 0;	
	MYSQL_FIELD *field;
	if(mysql_query((MYSQL*)conn, sql)) {
		KNH_THROWs(ctx, "query error");
	}
	result = mysql_store_result((MYSQL*)conn);
	if(result==NULL) {
		if(mysql_error((MYSQL*)conn)) {
			KNH_THROWs(ctx, "result is NULL");
		} else {
			KNH_THROWs(ctx, "unknown error");
		}
	}

	ResultSet *tuple = new_ResultSet(ctx, mysql_field_count((MYSQL*)conn), result, knh_ResultSet_next__mysql, knh_ResultSet_free__mysql);

	while((field = mysql_fetch_field(result)) != NULL) {
		tuple->column[i].dbtype = field->type;
		i++;
	}
	
	/* if you can get Meta information */ //[name text, price int]
	/*if(possible) {
		//knh_ResultSet_initMetaInfo(ctx, tuple, 0, type, name);
		knh_ResultSet_initMetaInfo(ctx, tuple, 0, CLASS_String, "name");
		knh_ResultSet_initMetaInfo(ctx, tuple, 1, CLASS_Int, "price");
	}*/
	return tuple;
#else
	return KNH_NULL;
#endif/*KONOHA_USING_MYSQL*/
}

/* ------------------------------------------------------------------------ */

void knh_Connection_close__mysql(Ctx *ctx, knh_connptr_t *conn)
{
#ifdef KONOHA_USING_MYSQL
	mysql_close((MYSQL*)conn);
#endif/*KONOHA_USING_MYSQL*/
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif
