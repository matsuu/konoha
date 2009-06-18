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

/* ************************************************************************ */

#include"commons.h"

#ifndef KONOHA_OS__LKM
#include<time.h>
#ifdef KNH_USING_POSIX
#include<unistd.h>
#endif
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [random] */

void init_genrand(unsigned long s);
void init_genrand64(unsigned long long seed);
unsigned long genrand_int31(void);
unsigned long long genrand64_int63(void);
double genrand_real1(void);
double genrand64_real1(void);

/* ------------------------------------------------------------------------ */

void knh_srand(knh_uint_t seed)
{
	if(seed == 0) {
#ifdef KONOHA_OS__LKM
		seed = 1;
#else
#ifdef KNH_USING_POSIX
		seed = (knh_uint_t)time(NULL) + getpid();
#else
		seed = (knh_uint_t)time(NULL);
#endif
#endif
	}
#ifdef KNH_USING_INT32
	init_genrand((unsigned long)seed);
#else
	init_genrand64((unsigned long long int)seed);
#endif
}

/* ------------------------------------------------------------------------ */

knh_uint_t knh_rand()
{
#ifdef KNH_USING_INT32
	return (knh_uint_t)genrand_int31();
#else
	return (knh_uint_t)genrand64_int63();
#endif
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_float_rand()
{
#ifdef KNH_USING_INT32
	return (knh_float_t)genrand_real1();
#else
	return (knh_float_t)genrand64_real1();
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
