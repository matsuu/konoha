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

#ifndef KONOHA_CONFIG_H_
#define KONOHA_CONFIG_H_

#include"license.h"

/* ======================================================================== */
/* Manifesto */

#define KONOHA_NAME     "konoha"
#define KONOHA_VERSION  "0.1"

/* ======================================================================== */

#ifdef KONOHA_OS__LINUX
#define KONOHA_OS "linux"
#endif

#ifdef KONOHA_OS__CYGWIN
#define KONOHA_OS "cygwin"
#endif

#ifdef KONOHA_OS__MINGW
#define KONOHA_OS "mingw"
#endif

#ifdef KONOHA_OS__MACOSX
#define KONOHA_OS "darwin"
#endif

#ifdef KONOHA_OS__TEABOARD
#define KONOHA_OS "teaboard"
#endif

/* ======================================================================== */
/* [CC] */
/* cpp -dM /dev/null */

#ifdef __GNUC__
	#define KONOHA_CC_VERSION __VERSION__
	#define KNH_CC_FASTCALL   __attribute__((fastcall))
	#define KNH_CC_LABELPTR   1
	#ifndef KONOHA_OS
		#ifdef __linux__
			#define KONOHA_OS  "Linux"
			#define KONOHA_OS__LINUX       1
		#endif
		#ifdef __APPLE__
			#define KONOHA_OS  "MacOSX"
			#define KONOHA_OS__MACOSX      1
		#endif

		#ifdef __WIN32__
			#define KONOHA_OS  "MinGW"
			#define KONOHA_OS__MINGW          1
		#endif
		#ifdef __CYGWIN__
			#define KONOHA_OS  "Cygwin"
			#define KONOHA_OS__CYGWIN
		#endif
	#endif/*KONOHA_OS*/
#endif/*__GNUC__*/

#ifdef _MSC_VER
#define KNH_CC_FASTCALL  __fastcall
#if _MSC_VER == 1500
	#define KONOHA_CC_VERSION "Microsoft Visual C++ 9.0 (1500)"
#else
	#define KONOHA_CC_VERSION "Microsoft Visual C++"
#endif
	#ifndef KONOHA_OS
		#define KONOHA_OS  "Windows"
		#define KONOHA_OS__WINDOWS
	#endif
#endif  /* _MSC_VER */

#ifndef KONOHA_OS
	#define KONOHA_OS  "unknown"
	#define KONOHA_OS__UNKNOWN
#endif

#ifndef KONOHA_CC_VERSION
#define KONOHA_CC_VERSION "unknown"
#endif

/* ======================================================================== */
/* [API] */

#ifdef KONOHA_OS__LINUX
	#define KNH_USING_POSIX 1
	#define KNH_USING_UNIX  1
	#define KNH_USING_ICONV 1
	#define KNH_USING_REGEX    1
	#define KONOHA_OS_ENCODING "UTF-8"
	#define KONOHA_OS_LINEFEED "\n"
	#ifdef KONOHA_CC_WITH_ECLIPSE
		#define KNH_USING_READLINE
	#endif
#endif

#ifdef KONOHA_OS__MACOSX
	#define KNH_USING_POSIX    1
	#define KNH_USING_UNIX     1
	#define KNH_USING_ICONV    1
	#define KNH_USING_REGEX    1
	#define KONOHA_OS_ENCODING "UTF-8"
	#define KONOHA_OS_LINEFEED "\n"
	#ifdef KONOHA_CC_WITH_ECLIPSE
		#define KNH_USING_READLINE
	#endif
#endif

#ifdef KONOHA_OS__CYGWIN
	#define KNH_USING_POSIX    1
	#define KNH_USING_UNIX     1
	#define KNH_USING_ICONV    1
	#define KNH_USING_REGEX    1
	#define KONOHA_OS_LINEFEED "\r\n"
#endif

#ifdef KONOHA_OS__MINGW
	#define KNH_USING_WIN32    1
	#define KNH_USING_WINDOWS  1
	#define KNH_USING_ICONV    1
	#define KONOHA_OS_LINEFEED "\r\n"
#ifdef KNHAPI_IMPORTS
#define KNHAPI(T)     __declspec(dllimport) T __stdcall
#else
#define KNHAPI(T)     __declspec(dllexport) T __stdcall
#endif
#endif

#ifdef KONOHA_OS__WINDOWS
	#define KNH_USING_WIN32    1
	#define KNH_USING_WINDOWS  1
	#define KNH_USING_ICONV    1
	#define KNH_USING_READLINE 1
	#define KONOHA_OS_LINEFEED "\r\n"
#ifdef KNHAPI_IMPORTS
#define KNHAPI(T) __declspec(dllimport) T __stdcall
#else
#define KNHAPI(T) __declspec(dllexport) T __stdcall
#endif
#endif

#ifdef KONOHA_OS__TEABOARD
	#define KNH_USING_BTRON    1
	#define KONOHA_OS_ENCODING KONOHA_ENCODING
	#define KONOHA_OS_LINEFEED "\n"
#endif

/* ======================================================================== */
/* [DEFUALT] */

#define KONOHA_WITH_RCGC  1                /* Reference Counting */

#ifndef KNHAPI
#define KNHAPI(T)         T
#endif

#ifdef KONOHA_CC_WITH_ECLIPSE
	#define KONOHA_MONOLITHIC  1
	#define KNH_USING_MATH    32
#endif

#ifdef KONOHA_MONOLITHIC
#undef KNHAPI
#define KNHAPI(T)        T
#endif

/* ======================================================================== */
/* COMMON */

#define KONOHA_TSTRUCT_SIZE                128
#define KONOHA_TGLOBAL_SIZE                256
#define KONOHA_TCLASS_SIZE                 1024
#define KONOHA_TEXP_SIZE                   256

/* object specification */

#define KONOHA_FIELDSIZE                   64
#define KNH_STACKSIZE                      4096
#define KONOHA_ERROR_MSG_SIZE              256
#define KONOHA_INT_SETBUF                  256
#define KONOHA_DEFAULT_ARRAY_SIZE           16
#define KONOHA_STRING_BUFSIZ               128
#define CLASSNAME_BUFSIZ                   128
#define FILENAME_BUFSIZ                  512

/* object specification */

#define KONOHA_ENCODING                    "UTF-8"

/* ======================================================================== */
/* Language Specification */

/* ======================================================================== */
/* ======================================================================== */

/* Runtime */
#define KONOHA_OBJECT_COPY                 1
#define KONOHA_RUNTIME_SINGLE              1

/* ======================================================================== */
/* ======================================================================== */
/* [Thread] */

#ifdef KNH_USING_THREAD
#define KNH_LOCK(ctx, o)            knh_Object_lock(ctx, o)
#define KNH_UNLOCK(ctx, o)          knh_Object_unlock(ctx, o)
#else
#define KNH_LOCK(ctx, o)
#define KNH_UNLOCK(ctx, o)
#endif

#endif /*KONOHA_CONFIG_H_*/
