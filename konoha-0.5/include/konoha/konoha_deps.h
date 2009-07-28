#ifndef KONOHA_DEPS_H_
#define KONOHA_DEPS_H_
#include<konoha/konoha_t.h>

#ifdef KNH_USING_STDC
#include<stdlib.h>
#include<string.h>
#include<setjmp.h>
#endif


/* ======================================================================== */
/* [UNIX] */

#ifdef KONOHA_ON_UNKNOWN
	#define KNH_USING_STDC  1
	#define KONOHA_OS_ENCODING "UTF-8"
	#define KONOHA_OS_LINEFEED "\n"
	#define KONOHA_OS_DLLEXT   ".so"
#endif

#ifdef KONOHA_ON_LINUX
#define		KNH_USING_POSIX 1
#define		KNH_USING_UNIX  1
#define     KNH_USING_SOCKET 1
#define 	KNH_USING_THREAD   1
#define     KNH_USING_PTHREAD  1
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
#endif

#ifdef KONOHA_ON_MACOSX
#define 	KNH_USING_POSIX    1
#define 	KNH_USING_UNIX     1
#define 	KNH_USING_SOCKET   1
#define 	KNH_USING_ICONV    1
#define 	KNH_USING_REGEX    1
#define 	KNH_USING_SQLITE3  1
#define 	KNH_USING_THREAD   1
#define     KNH_USING_PTHREAD  1
#define 	KONOHA_OS_ENCODING "UTF-8"
#define 	KONOHA_OS_LINEFEED "\n"
#define 	KONOHA_OS_DLLEXT ".dylib"
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_ON_LKM
#define KNH_USING_INT32      1
#define KNH_USING_NOFLOAT    1
#define KNH_USING_NOFILE     1

#define KNH_EXT_QSORT  1
#define KNH_EXT_SETJMP 1

#define FILEPATH_BUFSIZ     80  /* TO SAVE STACKSIZE */
#define KONOHA_HOMEPATH     "/dev/konoha"   /* meaningless */

#undef KNH_USING_SOCKET
#undef KNH_USING_ICONV
#undef KNH_USING_REGEX
#undef KNH_USING_SQLITE3
#undef KNH_USING_KONOHAGET
#undef KNH_USING_PTHREAD
#undef KNH_USING_THREAD
#undef KNH_USING_READLINE

#define KONOHA_OS_ENCODING "UTF-8"
#define KONOHA_OS_LINEFEED "\n"
#define KONOHA_OS_DLLEXT   ""

#endif

/* ======================================================================== */
/* [WINDOWS] */

#ifdef KONOHA_ON_WINDOWS
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
#define     KONOHA_FOLDER "Konoha"
#endif

#ifdef KONOHA_ON_MINGW
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

#ifdef KONOHA_ON_CYGWIN
#define 	KNH_USING_POSIX    1
#define 	KNH_USING_UNIX     1
#define 	KNH_USING_REGEX    1
#define 	KONOHA_OS_LINEFEED "\r\n"
#define 	KONOHA_OS_DLLEXT ".dll.a"
#endif

/* ======================================================================== */
/* [TEABOARD] */

#ifdef KONOHA_ON_TB
#define 	KNH_USING_BTRON    1
#define 	KNH_USING_TKAPI    1
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

#ifndef KONOHA_FOLDER
#define KONOHA_FOLDER ".konoha"
#endif

#ifndef KNHAPI
#ifdef  KONOHA_ON_WINDOWS
#define KNHAPI(T)         T __declspec(dllexport)
#else
#define KNHAPI(T)         T
#endif
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

#if defined(KNH_USING_POSIX) && !defined(KONOHA_ON_LKM)
#include<dlfcn.h>
#endif

/* ------------------------------------------------------------------------ */

#ifdef ALT_GETENV
	#define knh_getenv(n)           ALT_getenv(n)
#else
	#define knh_getenv(n)           getenv(n)
#endif


#ifndef FILEPATH_BUFSIZ
#define FILEPATH_BUFSIZ  256
#endif

/* ======================================================================== */

#endif /*KONOHA_DEPS_H_*/
