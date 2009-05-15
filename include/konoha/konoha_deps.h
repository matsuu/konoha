#ifndef KONOHA_DEPS_H_
#define KONOHA_DEPS_H_
#include"konoha_t.h"
#include<stdlib.h>
#include<string.h>

/* ======================================================================== */
/* [UNIX] */

#ifdef KONOHA_OS__UNKONWN
	#define KNH_USING_POSIX 1
	#define KNH_USING_UNIX  1
	#define KONOHA_OS_ENCODING "UTF-8"
	#define KONOHA_OS_LINEFEED "\n"
#endif

#ifdef KONOHA_OS__LINUX
#define		KNH_USING_POSIX 1
#define		KNH_USING_UNIX  1
#define     KNH_USING_SOCKET 1
#define		KONOHA_OS_ENCODING "UTF-8"
#define 	KNH_USING_KONOHAGET 1
#ifdef HAVE_ICONV_H
#define		KNH_USING_ICONV 1
#endif
//#ifdef HAVE_REGEX_H
#define		KNH_USING_REGEX 1
//#endif
#define		KONOHA_OS_LINEFEED "\n"
#define		KONOHA_OS_DLLEXT   ".so"
#ifdef KONOHA_CC_WITH_ECLIPSE
#define 	KNH_USING_READLINE 1
#define		KONOHA_MONOLITHIC  1
#endif
#endif

#ifdef KONOHA_OS__MACOSX
#define 	KNH_USING_POSIX    1
#define 	KNH_USING_UNIX     1
#define 	KNH_USING_SOCKET   1
#define 	KNH_USING_ICONV    1
#define 	KNH_USING_REGEX    1
#define 	KNH_USING_SQLITE3  1
#define 	KNH_USING_KONOHAGET 1
#define 	KONOHA_OS_ENCODING "UTF-8"
#define 	KONOHA_OS_LINEFEED "\n"
#define 	KONOHA_OS_DLLEXT ".dylib"
#ifdef KONOHA_CC_WITH_ECLIPSE
#define 	KNH_USING_READLINE 1
#define		KONOHA_MONOLITHIC  1
#endif
#endif

/* ======================================================================== */
/* [WINDOWS] */

#ifdef KONOHA_OS__WINDOWS
#include<windows.h>
#define 	KNH_USING_WIN32    1
#define 	KNH_USING_WINDOWS  1
#define     KNH_USING_MATH     1
#define 	KONOHA_OS_LINEFEED "\r\n"
#ifdef KNHAPI_IMPORTS
#define 	KNHAPI(T)     __declspec(dllimport) T __cdecl
#else
#define 	KNHAPI(T)     __declspec(dllexport) T __cdecl
#endif

#define 	KNH_EXPORTS(T)     __declspec(dllexport) T __cdecl

#define 	KONOHA_OS_DLLEXT ".dll"
#define		KONOHA_OS_FILE_SEPARATOR '\\'
#endif

#ifdef KONOHA_OS__MINGW
#define 	KNH_USING_WIN32    1
#define 	KNH_USING_WINDOWS  1
#define 	KONOHA_OS_LINEFEED "\r\n"
#ifdef KNHAPI_IMPORTS
#define 	KNHAPI(T) __declspec(dllimport) T __cdecl
#else
#define 	KNHAPI(T) __declspec(dllexport) T __cdecl
#endif
#define 	KNH_EXPORTS(T)  __declspec(dllexport) T __cdecl
#define 	KONOHA_OS_DLLEXT ".dll"
#define		KONOHA_OS_FILE_SEPARATOR '\\'
#ifndef HAVE_CONFIG_H
#define 	KNH_USING_ICONV       1
#define 	HAVE_LOCALCHARSET_H   1
#endif
#endif

#ifdef KONOHA_OS__CYGWIN
#define 	KNH_USING_POSIX    1
#define 	KNH_USING_UNIX     1
#define 	KNH_USING_REGEX    1
#define 	KONOHA_OS_LINEFEED "\r\n"
#define 	KONOHA_OS_DLLEXT ".dll.a"
#endif

/* ======================================================================== */
/* [WINDOWS] */

#ifdef KONOHA_OS__TB
#define 	KNH_USING_BTRON    1
#define 	KONOHA_OS_ENCODING KONOHA_ENCODING
#define 	KONOHA_OS_LINEFEED "\n"
#define 	KONOHA_OS_DLLEXT ".so"
#define     ALT_GETENV
#undef      KNH_USING_I18N
#endif

/* ======================================================================== */
/* [KNHAPI] */

#ifndef KNHAPI_
#ifdef KNHAPI
#define KNHAPI_(T)       KNHAPI(T)
#else
#define KNHAPI_(T)       T KNH_CC_FASTCALL
#endif
#endif

#ifndef KNHAPI
#define KNHAPI(T)         T
#define KNH_EXPORTS(T)    T
#endif

#ifdef KONOHA_MONOLITHIC
#undef KNHAPI
#define KNHAPI(T)        T
#define KNH_EXPORTS(T)   T
#endif

#ifndef KONOHA_OS_FILE_SEPARATOR
#define KONOHA_OS_FILE_SEPARATOR  '/'
#endif

#ifdef KNH_CC_LABELPTR
#define KNH_USING_THREADEDCODE 1
#else
#undef KNH_USING_THREADEDCODE
#endif

#ifdef KNH_USING_THREAD
#if !defined(KNH_USING_PTHREAD) && defined(KNH_USING_POSIX)
#define KNH_USING_PTHREAD 1
#endif
#endif

/* ======================================================================== */
/* [CONFIG_H] */

#if !defined(KNH_USING_ICONV) && defined(HAVE_LIBICONV)
#define 	KNH_USING_ICONV 1
#endif

#if !defined(KNH_USING_REGEX) && defined(HAVE_REGCOMP)
#define 	KNH_USING_REGEX 1
#endif

/* ======================================================================== */

#ifndef KNH_USING_ICONV
#undef KNH_USING_I18N
#endif

/* ======================================================================== */
/* [stdlib] */

#ifdef ALT_SNPRINTF
#define knh_snprintf(b,n,fmt, ...)     ALT_snprintf(b,n,fmt, ## __VA_ARGS__)
#else
#ifdef _MSC_VER
#define knh_snprintf(b,n,fmt, ...)     _snprintf_s(b,n, _TRUNCATE, fmt, ## __VA_ARGS__)
#else
#define knh_snprintf(b,n,fmt, ...)     snprintf(b,n,fmt, ## __VA_ARGS__)
#endif
#endif

/* ------------------------------------------------------------------------ */

#define knh_strlen(c)                  strlen(c)
#define knh_memcpy(d, s, n)            memcpy(d,s,n)
#define knh_bzero(s, n)                memset(s,0,n)
#define knh_strcmp(s1, s2)             strcmp(s1,s2)
#define knh_strncmp(s1, s2, n)         strncmp(s1,s2,n)

/* ------------------------------------------------------------------------ */

#ifdef ALT_SORT
#define  knh_sort(b,s,w,f)     ALT_sort(b,s,w,f)
#define  knh_qsort(b,s,w,f)    ALT_qsort(b,s,w,f)
#else
#define  knh_sort(b,s,w,f)     qsort(b,s,w,f)
#define  knh_qsort(b,s,w,f)    qsort(b,s,w,f)
#endif

/* ======================================================================== */

#ifdef KNH_USING_POSIX
#include<dlfcn.h>
#define KNH_RTLD_LAZY               RTLD_LAZY
#else
#define KNH_RTLD_LAZY               0
#endif

/* ------------------------------------------------------------------------ */

#ifdef ALT_GETENV
	#define knh_getenv(n)           ALT_getenv(n)
#else
	#define knh_getenv(n)           getenv(n)
#endif

/* ======================================================================== */

#endif /*KONOHA_DEPS_H_*/