/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifndef COMMONS_H_
#define COMMONS_H_

#define KONOHA_MACROS
#include<konoha/konoha_dev.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Int, IntSpec */

#ifndef KNH_INTSPEC_INTBUF
#define KNH_INTSPEC_INTBUF 256
#endif

#ifndef KNH_INTUNIT_BUFSIZ
#define KNH_INTUNIT_BUFSIZ 80
#endif

#ifndef KNH_LONGUNIT_BUFSIZ
#define KNH_LONGUNIT_BUFSIZ 80
#endif

#ifndef KNH_FLOATUNIT_BUFSIZ
#define BUFSIZ_FLOAT 80
#endif

/* Array */

#ifndef KNH_ARRAY_INITSIZE
#define KNH_ARRAY_INITSIZE 4
#endif

/* HashMap */

#ifndef KNH_HASH_INITSIZE
#define KNH_HASH_INITSIZE 83
#endif

#ifndef KNH_HASHMAP_INITFACTOR
#define KNH_HASHMAP_INITFACTOR 0.75
#endif

#ifndef KNH_DICTMAP_INITSIZE
#define KNH_DICTMAP_INITSIZE 12
#endif

#ifdef __cplusplus
}
#endif

#endif /*COMMONS_H_*/
