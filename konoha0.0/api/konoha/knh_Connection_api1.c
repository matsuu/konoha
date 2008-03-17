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
/* [constructor] */

/* ------------------------------------------------------------------------ */
/* @method Connection! Connection.new(String! urn) */

METHOD knh__Connection_new(Ctx *ctx, Object **sfp)
{
	Connection *b = (Connection*)sfp[0];
	KNH_SETv(ctx, b->urn, sfp[1]);
	knh_Connection_init(ctx, b, knh_String_tobytes(sfp[1]));
	VM_RET(ctx, sfp[0]);
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method ResultSet Connection.query(String! query) */

METHOD knh__Connection_query(Ctx *ctx, Object **sfp)
{
	Connection *b = (Connection*)sfp[0];
	String *query = (String*)sfp[1];
	
	ResultSet *rs = b->drv.fquery(ctx, b->conn, knh_String_tochar(query));
	METHOD_RETURN(ctx, sfp, rs);
//	
//	if(IS_ResultSet(rs)) {
//		if(IS_Class(sfp[2])) {
//			knh_ResultSet_initTargetClass(rs, knh_Class_cid(sfp[2]));
//		}
//		ret = knh_ResultSet_Iterator(ctx, rs, KNH_NULL);
//	}
//	VM_RET(ctx, ret);
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
