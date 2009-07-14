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

#define MAX_STR 12

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
	char* str = NULL;
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
				str = (char*)alloca(sizeof(char)*(sfp[2].s->size + 1));
				strncpy(str,(char*)sfp[2].s->str,sfp[2].s->size);
				str[sfp[2].s->size] = '\0';
				curl_easy_setopt(curl, curlopt, str);
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
	char *strptr = NULL;
	long lngptr = 0;
	double dblptr = 0;
	char ret[MAX_STR] = {'\0'};
    if(curl != NULL) {
        knh_int_t curlinfo = p_int(sfp[1]);
        switch(curlinfo) {
		case CURLINFO_HEADER_SIZE:
		case CURLINFO_REQUEST_SIZE:
			curl_easy_getinfo(curl, curlinfo, &lngptr);
			strptr = ret;
			sprintf(strptr,"%ld",lngptr);
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
			curl_easy_getinfo(curl, curlinfo, &dblptr);
			strptr = ret;
			sprintf(strptr,"%g",dblptr);
			break;
		case CURLINFO_EFFECTIVE_URL:
		case CURLINFO_CONTENT_TYPE:
			curl_easy_getinfo(curl, curlinfo, &strptr);
			break;
		default:
			KNH_WARNING(ctx, "curl_easy_getinfo: unknown info =%d", curlinfo);
			break;
		}
		KNH_RETURN(ctx, sfp, new_String(ctx,B(strptr),NULL));				
	}
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ======================================================================== */
/* [ConstData] */

static
knh_IntConstData_t IntConstData[] = {
	{"Curl.OPT_AUTOREFERER", CURLOPT_AUTOREFERER},
	{"Curl.OPT_COOKIESESSION", CURLOPT_COOKIESESSION},
	{"Curl.OPT_CRLF", CURLOPT_CRLF},
	{"Curl.OPT_DNS_USE_GLOBAL_CACHE", CURLOPT_DNS_USE_GLOBAL_CACHE},
	{"Curl.OPT_FAILONERROR", CURLOPT_FAILONERROR},
	{"Curl.OPT_FILETIME", CURLOPT_FILETIME},
	{"Curl.OPT_FOLLOWLOCATION", CURLOPT_FOLLOWLOCATION},
	{"Curl.OPT_FORBID_REUSE", CURLOPT_FORBID_REUSE},
	{"Curl.OPT_FRESH_CONNECT", CURLOPT_FRESH_CONNECT},
	{"Curl.OPT_FTP_USE_EPRT", CURLOPT_FTP_USE_EPRT},
	{"Curl.OPT_FTP_USE_EPSV", CURLOPT_FTP_USE_EPSV},
	{"Curl.OPT_FTPAPPEND", CURLOPT_FTPAPPEND},
	{"Curl.OPT_FTPLISTONLY", CURLOPT_FTPLISTONLY},
	{"Curl.OPT_HEADER", CURLOPT_HEADER},
	{"Curl.OPT_HTTPGET", CURLOPT_HTTPGET},
	{"Curl.OPT_HTTPPROXYTUNNEL", CURLOPT_HTTPPROXYTUNNEL},
	{"Curl.OPT_NETRC", CURLOPT_NETRC},
	{"Curl.OPT_NOBODY", CURLOPT_NOBODY},
	{"Curl.OPT_NOPROGRESS", CURLOPT_NOPROGRESS},
	{"Curl.OPT_NOSIGNAL", CURLOPT_NOSIGNAL},
	{"Curl.OPT_POST", CURLOPT_POST},
	{"Curl.OPT_PUT", CURLOPT_PUT},
	{"Curl.OPT_SSL_VERIFYPEER", CURLOPT_SSL_VERIFYPEER},
	{"Curl.OPT_TRANSFERTEXT", CURLOPT_TRANSFERTEXT},
	{"Curl.OPT_UNRESTRICTED_AUTH", CURLOPT_UNRESTRICTED_AUTH},
	{"Curl.OPT_UPLOAD", CURLOPT_UPLOAD},
	{"Curl.OPT_VERBOSE", CURLOPT_VERBOSE},
	{"Curl.OPT_BUFFERSIZE", CURLOPT_BUFFERSIZE},
	{"Curl.OPT_CLOSEPOLICY", CURLOPT_CLOSEPOLICY},
	{"Curl.OPT_CONNECTTIMEOUT", CURLOPT_CONNECTTIMEOUT},
	{"Curl.OPT_DNS_CACHE_TIMEOUT", CURLOPT_DNS_CACHE_TIMEOUT},
	{"Curl.OPT_FTPSSLAUTH", CURLOPT_FTPSSLAUTH},
	{"Curl.OPT_HTTP_VERSION", CURLOPT_HTTP_VERSION},
	{"Curl.OPT_HTTPAUTH", CURLOPT_HTTPAUTH},
	{"Curl.AUTH_ANY", CURLAUTH_ANY},
	{"Curl.AUTH_ANYSAFE", CURLAUTH_ANYSAFE},
	{"Curl.OPT_INFILESIZE", CURLOPT_INFILESIZE},
	{"Curl.OPT_LOW_SPEED_LIMIT", CURLOPT_LOW_SPEED_LIMIT},
	{"Curl.OPT_LOW_SPEED_TIME", CURLOPT_LOW_SPEED_TIME},
	{"Curl.OPT_MAXCONNECTS", CURLOPT_MAXCONNECTS},
	{"Curl.OPT_MAXREDIRS", CURLOPT_MAXREDIRS},
	{"Curl.OPT_PORT", CURLOPT_PORT},
	{"Curl.OPT_PROXYAUTH", CURLOPT_PROXYAUTH},
	{"Curl.OPT_PROXYPORT", CURLOPT_PROXYPORT},
	{"Curl.OPT_PROXYTYPE", CURLOPT_PROXYTYPE},
	{"Curl.OPT_RESUME_FROM", CURLOPT_RESUME_FROM},
	{"Curl.OPT_SSL_VERIFYHOST", CURLOPT_SSL_VERIFYHOST},
	{"Curl.OPT_SSLVERSION", CURLOPT_SSLVERSION},
	{"Curl.OPT_TIMECONDITION", CURLOPT_TIMECONDITION},
	{"Curl.OPT_TIMEOUT", CURLOPT_TIMEOUT},
	{"Curl.OPT_TIMEVALUE", CURLOPT_TIMEVALUE},
	{"Curl.OPT_CAINFO", CURLOPT_CAINFO},
	{"Curl.OPT_CAPATH", CURLOPT_CAPATH},
	{"Curl.OPT_COOKIE", CURLOPT_COOKIE},
	{"Curl.OPT_COOKIEFILE", CURLOPT_COOKIEFILE},
	{"Curl.OPT_COOKIEJAR", CURLOPT_COOKIEJAR},
	{"Curl.OPT_CUSTOMREQUEST", CURLOPT_CUSTOMREQUEST},
	{"Curl.OPT_ENCODING", CURLOPT_ENCODING},
	{"Curl.OPT_FTPPORT", CURLOPT_FTPPORT},
	{"Curl.OPT_INTERFACE", CURLOPT_INTERFACE},
	{"Curl.OPT_KRB4LEVEL", CURLOPT_KRB4LEVEL},
	{"Curl.OPT_POSTFIELDS", CURLOPT_POSTFIELDS},
	{"Curl.OPT_PROXY", CURLOPT_PROXY},
	{"Curl.OPT_PROXYUSERPWD", CURLOPT_PROXYUSERPWD},
	{"Curl.OPT_RANDOM_FILE", CURLOPT_RANDOM_FILE},
	{"Curl.OPT_RANGE", CURLOPT_RANGE},
	{"Curl.OPT_REFERER", CURLOPT_REFERER},
	{"Curl.OPT_SSL_CIPHER_LIST", CURLOPT_SSL_CIPHER_LIST},
	{"Curl.OPT_SSLCERT", CURLOPT_SSLCERT},
	{"Curl.OPT_SSLCERTTYPE", CURLOPT_SSLCERTTYPE},
	{"Curl.OPT_SSLENGINE", CURLOPT_SSLENGINE},
	{"Curl.OPT_SSLENGINE_DEFAULT", CURLOPT_SSLENGINE_DEFAULT},
	{"Curl.OPT_SSLKEY", CURLOPT_SSLKEY},
	{"Curl.OPT_SSLKEYTYPE", CURLOPT_SSLKEYTYPE},
	{"Curl.OPT_URL", CURLOPT_URL},
	{"Curl.OPT_USERAGENT", CURLOPT_USERAGENT},
	{"Curl.OPT_USERPWD", CURLOPT_USERPWD},
	{"Curl.OPT_FILE", CURLOPT_FILE},
	{"Curl.OPT_INFILE", CURLOPT_INFILE},
	{"Curl.OPT_STDERR", CURLOPT_STDERR},
	{"Curl.OPT_WRITEHEADER", CURLOPT_WRITEHEADER},
	{"Curl.INFO_HEADER_SIZE", CURLINFO_HEADER_SIZE},
	{"Curl.INFO_REQUEST_SIZE", CURLINFO_REQUEST_SIZE},
	{"Curl.INFO_REDIRECT_TIME", CURLINFO_REDIRECT_TIME},
	{"Curl.INFO_TOTAL_TIME", CURLINFO_TOTAL_TIME},
	{"Curl.INFO_NAMELOOKUP_TIME", CURLINFO_NAMELOOKUP_TIME},
	{"Curl.INFO_CONNECT_TIME", CURLINFO_CONNECT_TIME},
	{"Curl.INFO_PRETRANSFER_TIME", CURLINFO_PRETRANSFER_TIME},
	{"Curl.INFO_STARTTRANSFER_TIME", CURLINFO_STARTTRANSFER_TIME},
	{"Curl.INFO_SIZE_UPLOAD", CURLINFO_SIZE_UPLOAD},
	{"Curl.INFO_SIZE_DOWNLOAD", CURLINFO_SIZE_DOWNLOAD},
	{"Curl.INFO_SPEED_DOWNLOAD", CURLINFO_SPEED_DOWNLOAD},
	{"Curl.INFO_SPEED_UPLOAD", CURLINFO_SPEED_UPLOAD},
	{"Curl.INFO_EFFECTIVE_URL", CURLINFO_EFFECTIVE_URL},
	{"Curl.INFO_CONTENT_TYPE", CURLINFO_CONTENT_TYPE},
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

