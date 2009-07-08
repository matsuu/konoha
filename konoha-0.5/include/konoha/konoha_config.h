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

#ifndef KONOHA_CONFIG_H_
#define KONOHA_CONFIG_H_

/* ======================================================================== */
/* You are aggreed to use konoha under the following License */

#define KONOHA_LICENSE         "LGPL3.0"
#define KONOHA_UNDER_LGPL3      3

/* ======================================================================== */
/* configure */

#define KNH_USING_RCGC         1
#define KNH_USING_FASTMALLOC   1
#define KNH_USING_UNBOXFIELD   1

/* ======================================================================== */
/* Manifesto */

#ifdef PACKAGE_NAME
#define KONOHA_NAME      PACKAGE_NAME
#define KONOHA_VERSION   PACKAGE_VERSION
#else
#define KONOHA_NAME     "konoha"
#define KONOHA_MAJOR_VERSION "0.5"
#define KONOHA_VERSION  "0.5RC"
#endif

#define KONOHA_XCODE    "toguro"
#define KONOHA_URL		"http://konoha.sourceforge.jp/"
#define KONOHA_URLBASE  "kttp://konoha.sourceforge.jp/wiki/"

#define KONOHA_BUILDID_TOOOLD  545
#define KNH_CHECK_VERSION(id)  ((id) <= KONOHA_BUILDID_TOOOLD)

/* ======================================================================== */
/* COMMON */

#define KONOHA_TSTRUCT_SIZE                64
#define KONOHA_TCLASS_SIZE                 256
#define KONOHA_TEXP_SIZE                   128

/* object specification */
#define KONOHA_PAGESIZE                    4096
#define KONOHA_FIELDSIZE                   64
#define KONOHA_STACKSIZE                   4096

#define KONOHA_SMALLPAGESIZE               256

#define KONOHA_ERROR_MSG_SIZE              256
#define KONOHA_INT_SETBUF                  256
#define KONOHA_DEFAULT_ARRAY_SIZE           16
#define KONOHA_STRING_BUFSIZ               128
#define CLASSNAME_BUFSIZ                   128

/* object specification */

#define KNH_USING_I18N                     1
#define KONOHA_ENCODING                    "UTF-8"

/* ======================================================================== */

#ifdef KONOHA_ON_LINUX
#define KONOHA_OS "linux"
#endif

#ifdef KONOHA_ON_CYGWIN
#define KONOHA_OS "cygwin"
#endif

#ifdef KONOHA_ON_MINGW
#define KONOHA_OS "mingw"
#endif

#ifdef KONOHA_ON_MACOSX
#define KONOHA_OS "macosx"
#endif

#ifdef KONOHA_ON_TB
#define KONOHA_OS "teaboard"
#endif

#define KNH_USING_STDC   1

#ifdef KONOHA_ON_LKM
	#undef KNH_USING_STDC
	#define KONOHA_OS "LKM"
#endif


/* ======================================================================== */
/* [CC] */
/* cpp -dM /dev/null */

#ifdef __GNUC__
	#define KONOHA_CC_VERSION "GCC " __VERSION__
	#if defined(__i386__) || defined(__x86_64__)
		#if defined(KONOHA_ON_LKM)
			#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,25))
				#define KNH_CC_FASTCALL   fastcall
			#else
				#define KNH_CC_FASTCALL   __attribute__((fastcall))
			#endif
		#else
			#define KNH_CC_FASTCALL  __attribute__((fastcall))
		#endif
		#define likely(x)       __builtin_expect(!!(x), 1)
		#define unlikely(x)     __builtin_expect(!!(x), 0)
	#else
		#define KNH_CC_FASTCALL   /* __attribute__((fastcall)) */
	#endif
	#define KNH_CC_LABELPTR   1
	#ifndef KONOHA_OS
		#ifdef __linux__
			#define KONOHA_OS  "linux"
			#define KONOHA_ON_LINUX       1
		#endif
		#ifdef __APPLE__
			#define KONOHA_OS  "macosx"
			#define KONOHA_ON_MACOSX      1
		#endif
		#ifdef __WIN32__
			#define KONOHA_OS  "mingw"
			#define KONOHA_ON_MINGW          1
		#endif
		#ifdef __CYGWIN__
			#define KONOHA_OS  "cygwin"
			#define KONOHA_ON_CYGWIN     1
		#endif
		#ifdef TBMX1
			#define KONOHA_OS  "teaboard"
			#define KONOHA_ON_TB       1
		#endif
	#endif/*KONOHA_OS*/
#endif/*__GNUC__*/

#ifdef _MSC_VER
//#define KNH_DBGMODE2
#define KNH_CC_FASTCALL  /* __fastcall */
#if _MSC_VER == 1500
	#define KONOHA_CC_VERSION "Microsoft Visual C++ 9.0 (1500)"
#else
	#define KONOHA_CC_VERSION "Microsoft Visual C++"
#endif
	#ifndef KONOHA_OS
		#define KONOHA_OS  "windows"
		#define KONOHA_ON_WINDOWS
	#endif
#define _CRT_SECURE_NO_WARNINGS
#endif  /* _MSC_VER */

#ifndef KONOHA_OS
	#define KONOHA_OS  "unknown"
	#define KONOHA_ON_UNKNOWN
#endif

#ifndef KONOHA_CC_VERSION
#define KONOHA_CC_VERSION "UNKNOWN COMPILER"
#endif

#ifndef likely
#define likely(x)	   (x)
#define unlikely(x)	   (x)
#endif

#ifndef KONOHA_CPU
#define KONOHA_CPU ""
#endif

#if defined(__LP64__)
#define KONOHA_PLATFORM (KONOHA_OS KONOHA_CPU "_64")
#else
#define KONOHA_PLATFORM KONOHA_OS "_32"
#endif

/* ======================================================================== */
/* [OPTIONS_DEPS] */

/* ======================================================================== */

#define KNH_SECUREMODE 1

#define SECURE_bzero(o, s)  knh_bzero(o, s)

/* ======================================================================== */

#if !defined(L1_CACHE_BYTES) && !defined(KONOHA_ON_LKM)
#define L1_CACHE_BYTES   32
#endif

/* ======================================================================== */
/* ======================================================================== */


#endif /*KONOHA_CONFIG_H_*/
