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

#include"gen/manifesto.h"

/* ======================================================================== */
/* __GNUC__ */

/* cpp -dM /dev/null */

#ifdef __GNUC__
	#define KONOHA_CC_VERSION __VERSION__

	#ifdef __linux__
		#define KONOHA_OS  "linux"
		#define KONOHA_OS__LINUX       1
		#define KONOHA_API__POSIX      1
		#define KONOHA_USING_UNIX      1
	#endif

	#ifdef __APPLE__
		#define KONOHA_OS  "darwin"
		#define KONOHA_OS__MACOSX      1
		#define KONOHA_API__POSIX      1
		#define KONOHA_USING_UNIX      1
	#endif
	
	#ifdef __WIN32__
		#define KONOHA_OS  "Windows(MinGW)"
		#define KONOHA_OS__WINDOWS     1
		#define KONOHA_API__WIN32      1
		#define KONOHA_USING_WINDOWS   1
	#endif

	#ifdef __CYGWIN__
		#define KONOHA_OS  "Windows(cygwin)"
		#define KONOHA_OS__CYGWIN
		#define KONOHA_API_POSIX        1
		#define KONOHA_USING_UNIX       1
		#define KONOHA_PRELINK_READLINE 1
	#endif

#endif

/* ======================================================================== */
/* [MSC] */

#ifdef  _MSC_VER
	#define KONOHA_CC_VERSION _MSC_VER
	#define KONOHA_OS  "Windows"
	#define KONOHA_OS__WINDOWS
	#define KONOHA_API__WIN32       1
	#define KONOHA_USING_WINDOWS    1
#endif  /* _MSC_VER */

/* ======================================================================== */
/* [OS] */

#ifndef KONOHA_OS
	#define KONOHA_OS    "unknown"
	#define KONOHA_OS__UNKNOWN
	#define KONOHA_API_POSIX        1
#endif

/* ======================================================================== */
/* COMMON */

#define KONOHA_VERSION  "0.0"
#ifndef KONOHA_CC_VERSION
#define KONOHA_CC_VERSION "unknown compiler"
#endif

#define KONOHA_TERM_COLOR                  1

#define KONOHA_C_ARCH   "gcc32"

#define KONOHA_TSTRUCT_SIZE                128
#define KONOHA_TGLOBAL_SIZE                256
#define KONOHA_TCLASS_SIZE                 1024
#define KONOHA_TEXP_SIZE                   256

/* object specification */

#define KONOHA_FIELDSIZE                   64
#define KONOHA_STACK_SIZE                  4096
#define KONOHA_ERROR_MSG_SIZE              256
#define KONOHA_INT_SETBUF                  256
#define KONOHA_DEFAULT_ARRAY_SIZE           16
#define KONOHA_STRING_BUFSIZ               128
#define CLASSNAME_BUFSIZ                   128

/* object specification */

#define KONOHA_ENCODING                    "utf-8"

#define KONOHA_OS_LINEFEED                 "\n"
#define KONOHA_PRINT_MAX_NESTS             3
#define KONOHA_PRINT_MAX_ITEMS             64


/* ======================================================================== */
/* Language Specification */

#define KONOHA_NAME_SIZE    40
#define KONOHA_FILEN_SIZE   256
#define KONOHA_URN_SIZE     256

/* ======================================================================== */
/* ======================================================================== */

/* Runtime */
#define KONOHA_OBJECT_COPY                 1
#define KONOHA_RUNTIME_SINGLE              1

/* ======================================================================== */

#ifdef KONOHA_MONOLITHIC
	#ifndef KONOHA_PACKAGE
		#define KONOHA_PACKAGE 1
	#endif
#endif

#endif /*KONOHA_CONFIG_H_*/
