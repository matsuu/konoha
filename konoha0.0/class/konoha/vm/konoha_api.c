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


char *knh_readline(char *prompt);


/* ======================================================================== */
/* [konoha] */

static size_t tglobal_numof_konoha = 0;
static knh_uint_t tglobal_konohaid = 0;


/* ------------------------------------------------------------------------ */

knh_bool_t konoha_initcheck(void)
{
#ifdef KONOHA_SAFEMODE
	fprintf(stderr, "\taddress sizeof(void*) = %d bytes\n", (int)sizeof(void *));
	fprintf(stderr, "\tint sizeof(knh_int_t) = %d bytes\n", (int)sizeof(knh_int_t));
	fprintf(stderr, "\tfloat sizeof(knh_float_t) = %d bytes\n", (int)sizeof(knh_float_t));
	fprintf(stderr, "\tlong sizeof(knh_long_t) = %d bytes\n", (int)sizeof(knh_int64_t));
	fprintf(stderr, "\tshort sizeof(knh_short_t) = %d bytes\n", (int)sizeof(knh_short_t));
	fprintf(stderr, "\tObject(header) sizeof(hObject) = %d bytes\n", (int)sizeof(hObject));
#endif
	DEBUG_ASSERT(sizeof(knh_int_t) == sizeof(void *));
 	DEBUG_ASSERT(sizeof(knh_short_t) * 2 == sizeof(knh_int_t));
 	return 1;
 }

/* ------------------------------------------------------------------------ */


konoha_t konoha_open(void)
{
	tglobal_numof_konoha++;
	if(knh_Nue_NULL() == NULL) {
		knh_konoha_ginit();
		konoha_t konoha = {KONOHA_MAGIC, knh_Runtime_ROOT()};
		return konoha;
	}
	tglobal_konohaid++;
	Runtime *runtime = new_Runtime(NULL, tglobal_konohaid);
	knh_Object_refc_inc(runtime);
	konoha_t konoha = {KONOHA_MAGIC, runtime};
	return konoha;
}

/* ------------------------------------------------------------------------ */

void konoha_close(konoha_t konoha)
{
	if(konoha.magic == KONOHA_MAGIC) {
		Runtime *runtime = (Runtime*)konoha.mectx;
		if(!IS_Runtime(runtime)) {
			fprintf(stderr, "konoha: Maybe already closed\n");
			return;
		}
		tglobal_numof_konoha--;
		if(runtime->runtime_id != 0) {
			knh_Object_refc_dec(NULL, runtime);
		}
		if(tglobal_numof_konoha == 0) {
			knh_konoha_gtraverse(NULL, knh_sweep);
			DEBUG_ASSERT(knh_Runtime_ROOT() == NULL);
#ifdef KONOHA_DEBUGMODE
		konoha_stat_tmapmap_cache();
#endif
#ifdef KONOHA_SAFEMODE	
			if(knh_tmemory_used_size() != 0) {
				fprintf(stderr, "konoha: TOTALLY memory is leaked: %d bytes\n", (int)knh_tmemory_used_size());
			}
			knh_tmemory_endMemoryLeakNotice();
#endif
		}
	}
	else if(konoha.magic == KONOHA_CTX_MAGIC) {
		Context *ctx = (Context*)konoha.mectx;
		if(!IS_Context(ctx)) return;
		knh_Runtime_removeContext(NULL, ctx->runtime, knh_String_tobytes(ctx->name));
	}
	else{
		fprintf(stderr, "This is not a konoha Scripting Engine\n");
	}
}

/* ======================================================================== */
/* [context] */


Ctx *konoha_ctx(konoha_t konoha)
{
	if(konoha.magic == KONOHA_MAGIC) {
		Runtime *runtime = (Runtime*)konoha.mectx;
		if(!IS_Runtime(runtime)) return NULL;
		return knh_Runtime_getContext(NULL, runtime, STEXT("main"));
	}
	else if(konoha.magic == KONOHA_CTX_MAGIC) {
		Ctx *ctx = (Ctx*)konoha.mectx;
		if(!IS_Context(ctx)) return NULL;
		return ctx;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */


konoha_t konoha_context(konoha_t konoha, char *name)
{
	Runtime *rt;
	if(konoha.magic == KONOHA_MAGIC) {
		rt = (Runtime*)konoha.mectx;
	}
	else if(konoha.magic == KONOHA_CTX_MAGIC) {
		rt = ((Context*)konoha.mectx)->runtime;
	}
	else {
		goto L_ERR;
	}
	if(IS_Runtime(rt)) {
		konoha_t m = {KONOHA_CTX_MAGIC, knh_Runtime_getContext(NULL, rt, B(name))};
		return m;
	}
	L_ERR:;
	fprintf(stderr, "This is not a konoha Scripting Engine\n");
	konoha_t m = {0,NULL};
	return m;
}

/* ======================================================================== */
/* [konoha] */

void konoha_eval(konoha_t konoha, char *script)
{
	Ctx *ctx = konoha_ctx(konoha);
	if(ctx == NULL) return;

	knh_buffer_t cb = knh_Context_buffer(ctx);
	knh_Bytes_write(ctx, cb.ba, B(script));
	{
		InputStream *in = new_InputStream__Bytes(ctx, cb.ba, cb.pos, knh_Bytes_size(cb.ba));
		in->filen = knh_tfilen_forname(ctx, STEXT("(eval)"));
		knh_konohac_eval(ctx, NSN_main, in);
		knh_buffer_clear(cb);
	}
}

/* ------------------------------------------------------------------------ */

void konoha_read(konoha_t konoha, knh_nsn_t nsn, char *fpath)
{
	Ctx *ctx = konoha_ctx(konoha);
	if(ctx == NULL) return;
	FILE *fp = fopen(fpath, "r");
	if(fp == NULL) {
		fprintf(stderr, "konoha: Cannot open: %s\n", fpath);
		return;
	}
	
	InputStream *in = new_InputStream__FILE(ctx, fp);
	in->filen = knh_tfilen_forname(ctx, B(fpath));
	knh_konohac_eval(ctx, nsn, in);
}




#ifdef __cplusplus
}
#endif
