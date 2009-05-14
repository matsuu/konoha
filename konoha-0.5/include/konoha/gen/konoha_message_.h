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

#ifndef KONOHA_MESSAGE__H
#define KONOHA_MESSAGE__H

#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
#define KONOHA_LANG                     "en"
#define KONOHA_LANG__en                 0
#define KONOHA_LANG__ja                 1
#define KONOHA_LANG__debug              2
#define KONOHA_LANG_MAXSIZ              3

/* ------------------------------------------------------------------------ */
#define KMSG_NAME                       0
#define KMSG_LANG                       1
#define KMSG_CLASS                      2
#define KMSG_CONST                      3
#define KMSG_OPERATOR                   4
#define KMSG_METHOD                     5
#define KMSG_FORMATTER                  6
#define KMSG_MAPPING                    7
#define KMSG_ERRATA                     8
#define KMSG_ERROR                      9
#define KMSG_WARNING                    10
#define KMSG_INFO                       11
#define KMSG_FMTERR                     12
#define KMSG_UTOKEN                     13
#define KMSG_WCHAR                      14
#define KMSG_WLENGTH                    15
#define KMSG_IGBLOCK                    16
#define KMSG_EMISMATCH                  17
#define KMSG_WASCII                     18
#define KMSG_WEOF                       19
#define KMSG_NOTHERE                    20
#define KMSG_UUSING                     21
#define KMSG_ESYNTAX                    22
#define KMSG_EFUTURE                    23
#define KMSG_WSEMICOLON                 24
#define KMSG_TPATH                      25
#define KMSG_TTYPEN                     26
#define KMSG_TCLASSN                    27
#define KMSG_TNAME                      28
#define KMSG_TVARN                      29
#define KMSG_WEMPTY                     30
#define KMSG_CPREOP                     31
#define KMSG_ENEXTPREV                  32
#define KMSG_UOP                        33
#define KMSG_UOP1                       34
#define KMSG_UOP2                       35
#define KMSG_UCONSTN                    36
#define KMSG_UVARN                      37
#define KMSG_USYSTEMVARN                38
#define KMSG_UCLASSN                    39
#define KMSG_UTAG                       40
#define KMSG_UTYPEN                     41
#define KMSG_UMETHODN                   42
#define KMSG_UNEW                       43
#define KMSG_UMAP                       44
#define KMSG_UPATH                      45
#define KMSG_UPACKAGE                   46
#define KMSG_DIFFDECL                   47
#define KMSG_TOOMANYVARS                48
#define KMSG_WTRUEFALSE                 49
#define KMSG_WNUMOVERFLOW               50
#define KMSG_FMTARGS                    51
#define KMSG_ASSIGNMENT                 52
#define KMSG_ETYPEFMT                   53
#define KMSG_ENULLFMT                   54
#define KMSG_IGFIELDVALUE               55
#define KMSG_IGQNAME                    56
#define KMSG_NNCONST                    57
#define KMSG_DUPCONST                   58
#define KMSG_ELVALUE                    59
#define KMSG_EBUILTINFUNC               60
#define KMSG_ETOOFEWPARAMS              61
#define KMSG_WTOOMANYPARAMS             62
#define KMSG_EOPCMP                     63
#define KMSG_NORETURNVALUE              64
#define KMSG_IGRETURN                   65
#define KMSG_DIFFCLASSN                 66
#define KMSG_DIFFNEWTYPE                67
#define KMSG_DIFFRTYPE                  68
#define KMSG_DIFFPSIZE                  69
#define KMSG_DIFFPTYPE                  70
#define KMSG_DIFFPNAME                  71
#define KMSG_AOVERRIDE                  72
#define KMSG_EOVERRIDE                  73
#define KMSG_EEXTENDS                   74
#define KMSG_EIMPLEMENTS                75
#define KMSG_EABORT                     76
#define KMSG_ULABEL                     77
#define KMSG_ETRY                       78
#define KMSG_TOABSTRACT                 79
#define KMSG_MAXSIZ                     80

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
int knh_system_langid(char *lang);
void knh_Asm_setLang(char *lang);
int knh_message_type(int e);
char *knh_message_text(int e);
char *knh_message_tochar(int e);

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_MESSAGE__H*/
