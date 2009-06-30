/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2009-      Konoha Software Foundation
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
#include<curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

static
void knh_curl_gfree(Ctx *ctx, knh_Glue_t *g)
{
	curl_easy_cleanup((CURL*)g->ptr);
}

/* ------------------------------------------------------------------------ */
/* @method This! Curl.new() */

METHOD Curl_new(Ctx *ctx, knh_sfp_t *sfp)
{
	CURL* curl = curl_easy_init();
	knh_Glue_init(ctx, sfp[0].glue, curl, knh_curl_gfree);
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method void Curl.setopt(Int! type, Any data) */
// cutting from http://www.phpmanual.jp/function.curl-setopt.html

METHOD Curl_easySetOpt(Ctx *ctx, knh_sfp_t *sfp)
{
	CURL* curl = (CURL*)p_cptr(sfp[0]);
	FILE* fp = NULL;
	if(curl != NULL) {
		knh_int_t curlopt = p_int(sfp[1]);
		switch(curlopt) {
		case CURLOPT_AUTOREFERER:
//		case CURLOPT_BINARYTRANSFER:
		case CURLOPT_COOKIESESSION:
		case CURLOPT_CRLF:
		case CURLOPT_DNS_USE_GLOBAL_CACHE:
		case CURLOPT_FAILONERROR:
		case CURLOPT_FILETIME:
		case CURLOPT_FOLLOWLOCATION:
		case CURLOPT_FORBID_REUSE:
		case CURLOPT_FRESH_CONNECT:
		case CURLOPT_FTP_USE_EPRT:
		case CURLOPT_FTP_USE_EPSV:
		case CURLOPT_FTPAPPEND:
//		case CURLOPT_FTPASCII:
		case CURLOPT_FTPLISTONLY:
		case CURLOPT_HEADER:
		case CURLOPT_HTTPGET:
		case CURLOPT_HTTPPROXYTUNNEL:
//		case CURLOPT_MUTE:
		case CURLOPT_NETRC:
		case CURLOPT_NOBODY:
		case CURLOPT_NOPROGRESS: /*	default TRUE */
		case CURLOPT_NOSIGNAL:
		case CURLOPT_POST:
		case CURLOPT_PUT:
//		case CURLOPT_RETURNTRANSFER:
		case CURLOPT_SSL_VERIFYPEER:
		case CURLOPT_TRANSFERTEXT:
		case CURLOPT_UNRESTRICTED_AUTH:
		case CURLOPT_UPLOAD:
		case CURLOPT_VERBOSE:
			if(IS_Boolean(sfp[2].o)) {
				if(sfp[2].bvalue) {
					curl_easy_setopt(curl, curlopt, 1);
				}
				else {
					curl_easy_setopt(curl, curlopt, 0);
				}
			}
			else if(IS_Int(sfp[2].o)) {
				if(p_int(sfp[2]) == 0) {
					curl_easy_setopt(curl, curlopt, 0);
				}
				else {
					curl_easy_setopt(curl, curlopt, 1);
				}
			}
			else {
				if(knh_Context_isStrict(ctx)) {
					KNH_THROWs(ctx, "Type!!: data must be Boolean");
				}
				KNH_WARNING(ctx, "curl_easy_setopt: data must be Boolean");
			}
			break;
		case CURLOPT_BUFFERSIZE:
		case CURLOPT_CLOSEPOLICY:
		case CURLOPT_CONNECTTIMEOUT:
		case CURLOPT_DNS_CACHE_TIMEOUT:
		case CURLOPT_FTPSSLAUTH:
		case CURLOPT_HTTP_VERSION:
		case CURLOPT_HTTPAUTH:
		case CURLAUTH_ANY:
		case CURLAUTH_ANYSAFE:
		case CURLOPT_INFILESIZE:
		case CURLOPT_LOW_SPEED_LIMIT:
		case CURLOPT_LOW_SPEED_TIME:
		case CURLOPT_MAXCONNECTS:
		case CURLOPT_MAXREDIRS:
		case CURLOPT_PORT:
		case CURLOPT_PROXYAUTH:
		case CURLOPT_PROXYPORT:
		case CURLOPT_PROXYTYPE:
		case CURLOPT_RESUME_FROM:
		case CURLOPT_SSL_VERIFYHOST:
		case CURLOPT_SSLVERSION:
		case CURLOPT_TIMECONDITION:
		case CURLOPT_TIMEOUT:
		case CURLOPT_TIMEVALUE:
			if(IS_Int(sfp[2].o)) {
				curl_easy_setopt(curl, curlopt, p_int(sfp[2]));
			}
			else {
				if(knh_Context_isStrict(ctx)) {
					KNH_THROWs(ctx, "Type!!: data must be Int");
				}
				KNH_WARNING(ctx, "curl_easy_setopt: data must be Int");
			}
			break;
		case CURLOPT_CAINFO:
		case CURLOPT_CAPATH:
		case CURLOPT_COOKIE:
		case CURLOPT_COOKIEFILE: /* filename */
		case CURLOPT_COOKIEJAR:
		case CURLOPT_CUSTOMREQUEST:
//		case CURLOPT_EGBSOCKET:
		case CURLOPT_ENCODING:
		case CURLOPT_FTPPORT:
		case CURLOPT_INTERFACE:
		case CURLOPT_KRB4LEVEL:
		case CURLOPT_POSTFIELDS:
		case CURLOPT_PROXY:
		case CURLOPT_PROXYUSERPWD:
		case CURLOPT_RANDOM_FILE:
		case CURLOPT_RANGE:
		case CURLOPT_REFERER:
		case CURLOPT_SSL_CIPHER_LIST:
		case CURLOPT_SSLCERT:
//		case CURLOPT_SSLCERTPASSWD:
		case CURLOPT_SSLCERTTYPE:
		case CURLOPT_SSLENGINE:
		case CURLOPT_SSLENGINE_DEFAULT:
		case CURLOPT_SSLKEY:
//		case CURLOPT_SSLKEYPASSWD:
		case CURLOPT_SSLKEYTYPE:
		case CURLOPT_URL:
		case CURLOPT_USERAGENT:
		case CURLOPT_USERPWD:
			if(IS_String(sfp[2].o)) {
				curl_easy_setopt(curl, curlopt, p_char(sfp[2]));
			}
			else {
				if(knh_Context_isStrict(ctx)) {
					KNH_THROWs(ctx, "Type!!: data must be String");
				}
				KNH_WARNING(ctx, "curl_easy_setopt: data must be String");
			}
			break;
		case CURLOPT_FILE:
		case CURLOPT_INFILE:
		case CURLOPT_STDERR:
		case CURLOPT_WRITEHEADER:
			if(IS_OutputStream(sfp[2].o)) {
				fp = (FILE*)sfp[2].w->b->fd;
				curl_easy_setopt(curl, curlopt, fp);
			}
			else {
                if(knh_Context_isStrict(ctx)) {
                    KNH_THROWs(ctx, "Type!!: data must be InputStream");
                }
                KNH_WARNING(ctx, "curl_easy_setopt: data must be InputStream");
            }
			break;
		default :
			KNH_WARNING(ctx, "curl_easy_setopt: unknown option =%d", curlopt);
			break;
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Curl.easyPerform() */

METHOD Curl_easyPerform(Ctx *ctx, knh_sfp_t *sfp)
{
	CURL* curl = (CURL*)p_cptr(sfp[0]);
	CURLcode res;
	if(curl != NULL) {
		res = curl_easy_perform(curl);
		if ( res != CURLE_OK ){
			KNH_WARNING(ctx, "[curl] perform");
			KNH_RETURN_Boolean(ctx, sfp, 0);
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, 1);
}


/* ------------------------------------------------------------------------ */
/* @method Any Curl.easyGetInfo(Int! type) */

METHOD Curl_easyGetInfo(Ctx *ctx, knh_sfp_t *sfp)
{
	CURL* curl = (CURL*)p_cptr(sfp[0]);
	long* lngbuf = NULL;
	double* dblbuf = NULL;
	char* strbuf = NULL;
    if(curl != NULL) {
        knh_int_t curlinfo = p_int(sfp[1]);
        switch(curlinfo) {
		case CURLINFO_HEADER_SIZE:
		case CURLINFO_REQUEST_SIZE:
			curl_easy_getinfo(curl, curlinfo, &lngbuf);
			KNH_RETURN_Int(ctx, sfp, (long)lngbuf);
			break;
		case CURLINFO_REDIRECT_TIME:
		case CURLINFO_TOTAL_TIME:
		case CURLINFO_NAMELOOKUP_TIME:
		case CURLINFO_CONNECT_TIME:
		case CURLINFO_PRETRANSFER_TIME:
		case CURLINFO_STARTTRANSFER_TIME:
		case CURLINFO_SIZE_UPLOAD:
		case CURLINFO_SIZE_DOWNLOAD:
		case CURLINFO_SPEED_DOWNLOAD:
		case CURLINFO_SPEED_UPLOAD:
			curl_easy_getinfo(curl, curlinfo, &dblbuf);
			KNH_RETURN_Float(ctx, sfp, *dblbuf);
			break;
		case CURLINFO_EFFECTIVE_URL:
		case CURLINFO_CONTENT_TYPE:
			curl_easy_getinfo(curl, curlinfo, &strbuf);
			KNH_RETURN(ctx, sfp, new_String(ctx,B(strbuf),NULL));
			break;
		default:
			KNH_WARNING(ctx, "curl_easy_getinfo: unknown info =%d", curlinfo);
			break;
		}
	}
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ======================================================================== */
/* [ConstData] */

static
knh_IntConstData_t IntConstData[] = {
	{"Curl.CURLOPT_HEADER", CURLOPT_HEADER},
	{"Curl.CURLOPT_NOBODY", CURLOPT_NOBODY},
	{"Curl.CURLOPT_URL", CURLOPT_URL},
	{"Curl.CURLOPT_FILE", CURLOPT_FILE},
	{"Curl.CURLINFO_EFFECTIVE_URL", CURLINFO_EFFECTIVE_URL},
	{"Curl.CURLINFO_CONTENT_TYPE", CURLINFO_CONTENT_TYPE},
	{"Curl.CURLINFO_HEADER_SIZE", CURLINFO_HEADER_SIZE},
	{"Curl.CURLINFO_REQUEST_SIZE",CURLINFO_REQUEST_SIZE},
	{"Curl.CURLINFO_SIZE_DOWNLOAD", CURLINFO_SIZE_DOWNLOAD},
	{NULL}  // end of const data
};

/* ------------------------------------------------------------------------ */

KNH_EXPORTS(int) init(Ctx *ctx)
{
	KNH_NOTICE(ctx, "loading curl..");
	konoha_loadIntConstData(ctx, IntConstData);

	return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

