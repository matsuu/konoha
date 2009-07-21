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

#include <konoha.h>
#include <unistd.h>
#include <stdlib.h>
#include <cimc/cimc.h>
#include <CimClientLib/cmci.h>
#include <CimClientLib/native.h>
#include <CimClientLib/cmcimacs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* Exception  */

static
void knh_throw_CIMException(Ctx *ctx, int rc, char *msg)
{
	//TODO: throw CIM!! with parameters
	KNH_THROWs(ctx, "CIM!!");
}

/* ------------------------------------------------------------------------ */

static
void knh_throw_CIMCStatus(Ctx *ctx, CIMCStatus *status)
{
	//TODO: throw CIM!! with parameters
	KNH_THROWs(ctx, "CIM!!");
}

/* ======================================================================== */
/* [CIMCEnv] WBET/XML Only */

static CIMCEnv *knh_sharedCIMEnv = NULL;

static CIMCEnv *getCIMCEnv(Ctx *ctx)
{
	if(knh_sharedCIMEnv == NULL) {
		int rc;
		char *msg;
		knh_sharedCIMEnv = NewCIMCEnv("XML", 0, &rc, &msg);
		if(knh_sharedCIMEnv == NULL) {
			knh_throw_CIMException(ctx, rc, msg);
		}
	}
	return knh_sharedCIMEnv;
}

/* ======================================================================== */
/* [CIMObjectPath] */

static
void knh_fgfree_CIMCObjectPath(Ctx *ctx, knh_Glue_t *g)
{
	CIMCObjectPath *op = (CIMCObjectPath*)g->ptr;
	op->ft->release(op);
}

/* ------------------------------------------------------------------------ */
/* @method CIMObjectPath CIMObjectPath(String! path) */

METHOD CIMObjectPath_new(Ctx *ctx, knh_sfp_t *sfp)
{
	CIMCEnv *env = getCIMCEnv(ctx);
	char *path = p_char(sfp[1]);
	CIMCStatus status;
	CIMCObjectPath *op = env->ft->newObjectPath(env, path, NULL, &status);
	if(op == NULL || status.rc == 0) {
		knh_throw_CIMCStatus(ctx, &status);
	}
	knh_Glue_init(ctx, sfp[0].glue, op, knh_fgfree_CIMCObjectPath);
}

/* ------------------------------------------------------------------------ */
/* @method void CIMObjectPath.%s(OutputStream! w, String! m) */

METHOD CIMCObjectPath__s(Ctx *ctx, knh_sfp_t *sfp)
{
	CIMCObjectPath *op = ((sfp[0].glue)->ptr);
	CIMCString *cs = op->ft->toString(op, NULL);
	KNH_RETURN(ctx,sfp,new_String(ctx,B((char*)cs->hdl),NULL));
}

/* ======================================================================== */
/* [CIMClient] */

static
void knh_fgfree_CIMCClient(Ctx *ctx, knh_Glue_t *g)
{
	CIMCClient *cc = (CIMCClient*)g->ptr;
	cc->ft->release(cc);
}

/* ------------------------------------------------------------------------ */
/* @method CIMClient CIMClient.new(String! url) */

METHOD CIMClient_new(Ctx *ctx, knh_sfp_t *sfp)
{
	CIMCEnv *env = getCIMCEnv(ctx);
	CIMCClient *cc;
	CIMCStatus status;
	if(IS_NULL(sfp[0].s)) {
		char *pwd = konoha_getPassword(ctx, STEXT("konoha"));
		cc = env->ft->connect(env, "localhost", "http", "5988", "konoha", pwd, &status);
	}
	else {
		knh_bytes_t url = knh_String_tobytes(sfp[1].s);
		char bfscheme[20], bfhost[256];
		char bfuname[20], bfport[20];
		int port = 5988;
		knh_bytes_parseURLscheme(url, bfscheme, sizeof(bfscheme));
		knh_bytes_parseURLhost(url, bfhost, sizeof(bfhost));
		knh_bytes_parseURLuname(url, bfuname, sizeof(bfuname));
		knh_bytes_parseURLport(url, &port);
		knh_snprintf(bfport, sizeof(bfport), "%d", port);
		cc = env->ft->connect(env, bfhost, bfscheme, bfport, bfuname, konoha_getPassword(ctx, url), &status);
	}
	if(cc == NULL || status.rc == 0) {
		knh_throw_CIMCStatus(ctx, &status);
	}
	knh_Glue_init(ctx, sfp[0].glue, cc, knh_fgfree_CIMCClient);
}

/* ------------------------------------------------------------------------ */

static
ITRNEXT knh_enumClassNames(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	CIMCEnumeration *enm = (CIMCEnumeration *)DP(sfp[0].it)->ref;
	if(enm != NULL) {
		if(enm->ft->hasNext(enm, NULL)) {
			CIMCData data = enm->ft->getNext(enm, NULL);
			CIMCObjectPath *op = data.value.ref;
			CIMCString *path = op->ft->toString(op, NULL);
			String *s = new_String(ctx, B(path->ft->getCharPtr(path, NULL)), NULL);
			KNH_ITRNEXT(ctx, sfp, n, s);
		}
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */

static
void knh_ffree_CIMCEnumeration(void *ref)
{
	CIMCEnumeration *enm = (CIMCEnumeration *)ref;
	if(enm != NULL) {
		enm->ft->release(enm);
	}
}

/* ------------------------------------------------------------------------ */
/* @method String.. CIMClient.enumClassNames(CIMObjectPath! path) */

METHOD CIMCClient_enumClassNames(Ctx *ctx, knh_sfp_t *sfp)
{
	CIMCClient *cc = ((sfp[0].glue)->ptr);
	CIMCObjectPath *op = ((sfp[1].glue)->ptr);
	CIMCEnumeration *enm = NULL;
	if(cc != NULL && op != NULL) {
		CIMCStatus status;
		enm = cc->ft->enumClassNames(cc, op, 0, &status);
		if(status.rc == 0) {
			knh_throw_CIMCStatus(ctx, &status);
		}
	}
	KNH_RETURN(ctx, sfp,
		new_GlueIterator(ctx, CLASS_String, enm, knh_enumClassNames, knh_ffree_CIMCEnumeration));
}

/* ------------------------------------------------------------------------ */

// init
KNH_EXPORTS(int) init(Ctx *ctx)
{
    KNH_NOTICE(ctx, "loading sfcc..");
    return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

