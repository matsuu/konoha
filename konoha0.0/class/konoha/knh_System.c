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
/* [constructors] */


System *new_System(Ctx *ctx)
{
	System *b = (System*)knh_Object_malloc(ctx, CLASS_System);
	KNH_INITv(b->in,  new_InputStream__FILE(ctx, stdin));
	KNH_INITv(b->out, new_OutputStream__FILE(ctx, stdout));
	KNH_INITv(b->err, new_OutputStream__FILE(ctx, stderr));
	KNH_INITv(b->props, new_DictMap(ctx, 256));
	KNH_INITv(b->rootDir, KNH_NULL);
	return b;
}

/* ======================================================================== */
/* [properties] */

char *
knh_bytes_nzenvkey(knh_bytes_t t, char *buf, size_t bufsiz)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(i < bufsiz) {
			buf[i] = toupper(t.buf[i]);
		}
		else {
			buf[bufsiz-1] = 0;
			return buf;
		}
	}
	buf[i] = 0;
	return buf;
}

/* ------------------------------------------------------------------------ */
/* @method Any System.getProperty(String! key) */

Any* knh_System_getProperty(Ctx *ctx, System *b, knh_bytes_t key)
{
	if(knh_bytes_startsWith(key, STEXT("env."))) {
		char envkey[256];
		knh_bytes_nzenvkey(knh_bytes_last(key, 4), envkey, sizeof(envkey));
		char *v = getenv(envkey);
		if(v == NULL) {
			return KNH_NULL;
		}
		return new_String__fast(ctx, CLASS_String, B(v));
	}
	return knh_DictMap_getb(ctx, b->props, key);
}

/* ------------------------------------------------------------------------ */
/* @method void System.setProperty(String! key, Any value) */

void knh_System_setProperty(Ctx *ctx, System *b, String *key, Any *value)
{
	knh_DictMap_set(ctx, b->props, key, value);
}

/* ======================================================================== */
/* [rootDir] */

/* ------------------------------------------------------------------------ */

char* knh_system_rootDir()
{
	System *b = (System*)knh_System_ROOT();
	if(IS_NULL(b->rootDir)) {
		char *p = getenv("KONOHA_HOME");
		if(p != NULL) {
			KNH_SETv(NULL, b->rootDir, new_String__fast(NULL, CLASS_String, B(p)));
		}
		else {
			char buf[KONOHA_FILEN_SIZE];
//			knh_file_getInstalledHomePath(buf, sizeof(buf));
//			DEBUG("%s", buf);
			knh_snprintf(buf, sizeof(buf), "/usr/konoha");
			KNH_SETv(NULL, b->rootDir, new_String__fast(NULL, CLASS_String, B(buf)));
		}
	}
	return knh_String_tochar(b->rootDir);
}

/* ------------------------------------------------------------------------ */

char* knh_system_path(char *buf, size_t bufsiz, char *sub, char *file)
{
	if(file == NULL || file[0] == 0) {
		knh_snprintf(buf, bufsiz, "%s/%s", knh_system_rootDir(), sub);
	}
	else{
		knh_snprintf(buf, bufsiz, "%s/%s/%s", knh_system_rootDir(), sub, file);
	}
#ifdef KONOHA_OS__WIN32
	size_t i;
	for(i = 0; i < bufsiz; i++) {
		if(buf[i] == 0) break;
		if(buf[i] == '/') {
			buf[i] = '¥¥';
		}
	}
#endif
	return buf;
}

/* ======================================================================== */
/* [movabletext] */

/* @method void System.%dump(OutputStream w, Any m) */

void knh_System__dump(Ctx *ctx, System *b, OutputStream *w, Any *m)
{
	
}


#ifdef __cplusplus
}
#endif
