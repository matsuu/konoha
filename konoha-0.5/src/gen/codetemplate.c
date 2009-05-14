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

#include<konoha/konoha_dev.h>
#include<konoha/gen/konohac_klr_.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_CODETEMPLATE
#define NPC
#ifdef _HERE_
#undef _HERE_ 
#endif
#define _HERE_ NULL, 0
#define JUMP0 *(0xffffffff)
#define JUMP1 *(0x00000001)
//static volatile knh_sfp_t *reset_ifneed = NULL;	

static
METHOD jc0_HALT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_HALT(ctx);
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVa(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVa(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVa(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVn(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVn(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVn(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVo(ctx, (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVo(ctx, (1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVo(ctx, (-1), ((Object*)2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVx(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVx(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVx(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_MOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVx(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVDEF(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVDEF(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVDEF(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVSYS(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVSYS(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVSYS(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVs(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVs(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVs(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVs(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVo(ctx, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVo(ctx, (1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVo(ctx, (-1), (2), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVo(ctx, (-1), (-1), ((Object*)3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVx(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVx(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVx(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVx(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVx(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVDEF(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVDEF(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVDEF(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVDEF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVDEF(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVSYS(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVSYS(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVSYS(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVSYS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVSYS(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxi(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxi(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxi(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_MOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxi(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVSI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsi(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVSI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsi(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVSI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsi(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVSI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsi(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVOI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVoi(ctx, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVOI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVoi(ctx, (1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVOI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVoi(ctx, (-1), (2), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVOI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVoi(ctx, (-1), (-1), ((Object*)3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxi(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxi(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxi(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxi(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxi(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxio(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxio(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxio(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxio(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxio(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (-1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (-1), (2), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (-1), (-1), (3), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (-1), (-1), (-1), (4), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_XMOVXBXI(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXi(ctx, (-1), (-1), (-1), (-1), (5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxf(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxf(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxf(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_MOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxf(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVSF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsf(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVSF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsf(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVSF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsf(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVSF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsf(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVOF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVof(ctx, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVOF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVof(ctx, (1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVOF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVof(ctx, (-1), (2), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVOF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVof(ctx, (-1), (-1), ((Object*)3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxf(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxf(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxf(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxf(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxf(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXFO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxfo(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXFO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxfo(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXFO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxfo(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXFO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxfo(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXFO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxfo(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (-1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (-1), (2), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (-1), (-1), (3), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (-1), (-1), (-1), (4), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_XMOVXBXF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxBXf(ctx, (-1), (-1), (-1), (-1), (5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxb(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxb(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxb(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_MOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MOVxb(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVSB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsb(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVSB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsb(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVSB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsb(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVSB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVsb(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVOB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVob(ctx, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVOB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVob(ctx, (1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVOB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVob(ctx, (-1), (2), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVOB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVob(ctx, (-1), (-1), ((Object*)3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_XMOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxb(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_XMOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxb(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_XMOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxb(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_XMOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxb(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_XMOVXB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_XMOVxb(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SWAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SWAP(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SWAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SWAP(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_SWAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SWAP(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_PINIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PINIo(ctx, (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_PINIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PINIo(ctx, (1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_PINIO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PINIo(ctx, (-1), ((Object*)2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SETESP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SETESP(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SETESP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SETESP(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_CHECKESP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CHECKESP(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_CHECKESP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CHECKESP(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_RET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RET(ctx);
	__asm__ __volatile__("int3");
}


static
METHOD jc0_RETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETn(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_RETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETn(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_RETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETn(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_RETA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETa(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_RETA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETa(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_RETA(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETa(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_RETO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETo(ctx, (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_RETO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETo(ctx, (1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_RETO(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETo(ctx, (-1), ((Object*)2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_RETX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETx(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_RETX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETx(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_RETX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETx(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_RETX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_RETx(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOX(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOX(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOX(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOXnc(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOXnc(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_BOXnc(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_NNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOX(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_NNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOX(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_NNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOX(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_NNBOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOXnc(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_NNBOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOXnc(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_NNBOXNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNBOXnc(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_UNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_UNBOX(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_UNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_UNBOX(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISNULL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNULL(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISNULL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNULL(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISNULLX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNULLx(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISNULLX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNULLx(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ISNULLX(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNULLx(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISTYPE(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISTYPE(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ISTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISTYPE(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISNNTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNNTYPE(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISNNTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNNTYPE(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ISNNTYPE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ISNNTYPE(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FCALL(ctx, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FCALL(ctx, (1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FCALL(ctx, (-1), (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FCALL(ctx, (-1), (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_FCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FCALL(ctx, (-1), (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SCALL(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SCALL(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_SCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SCALL(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_SCALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SCALL(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_AINVOKE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AINVOKE(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_AINVOKE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AINVOKE(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_AINVOKE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AINVOKE(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_AINVOKE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AINVOKE(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_CALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CALL(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_CALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CALL(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_CALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CALL(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_CALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CALL(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ACALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ACALL(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ACALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ACALL(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ACALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ACALL(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ACALL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ACALL(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (-1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (1), (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (-1), (2), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (-1), (-1), (3), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (-1), (-1), (-1), (4), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_NEW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEW(ctx, (-1), (-1), (-1), (-1), (5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_TOSTR(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTR(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_TOSTR(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTR(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_TOSTR(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTR(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_TOSTRF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTRf(ctx, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_TOSTRF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTRf(ctx, (1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_TOSTRF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTRf(ctx, (-1), (2), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_TOSTRF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TOSTRf(ctx, (-1), (-1), ((Object*)3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAP(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAP(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_SMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAP(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SMAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPnc(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SMAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPnc(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_SMAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPnc(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAP(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAP(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAP(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPnc(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPnc(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MAPNC(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPnc(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_AMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AMAP(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_AMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AMAP(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_AMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AMAP(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_NNMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNMAP(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_NNMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNMAP(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_NNMAP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NNMAP(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_JMP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JMP(ctx, NPC, JUMP0);
	__asm__ __volatile__("int3");
}


static
METHOD jc1_JMP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JMP(ctx, NPC, JUMP1);
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BJIFT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFT(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BJIFT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFT(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BJIFT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFT(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BJIFF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BJIFF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BJIFF(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BJIFF_LOOP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF_LOOP(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BJIFF_LOOP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF_LOOP(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BJIFF_LOOP(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bJIFF_LOOP(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_JIFNUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNUL(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_JIFNUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNUL(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_JIFNUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNUL(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_JIFNN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNN(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_JIFNN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNN(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_JIFNN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_JIFNN(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_NEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEXT(ctx, NPC, JUMP0, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_NEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEXT(ctx, NPC, JUMP1, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_NEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEXT(ctx, NPC, JUMP0, (2), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_NEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEXT(ctx, NPC, JUMP0, (-1), (3), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_NEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_NEXT(ctx, NPC, JUMP0, (-1), (-1), (4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP1, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP0, (2), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP0, (-1), (3), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP0, (-1), (-1), (4), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_INEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_INEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), (5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP1, (-1), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP0, (2), (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP0, (-1), (3), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (4), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_MAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_MAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), (5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP1, (-1), (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP0, (2), (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP0, (-1), (3), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (4), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc5_SMAPNEXT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_SMAPNEXT(ctx, NPC, JUMP0, (-1), (-1), (-1), ((Object*)5));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_TRY(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TRY(ctx, NPC, JUMP0, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_TRY(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TRY(ctx, NPC, JUMP1, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_TRY(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TRY(ctx, NPC, JUMP0, (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_TRYEND(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TRYEND(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_TRYEND(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_TRYEND(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_CATCH(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CATCH(ctx, NPC, JUMP0, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_CATCH(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CATCH(ctx, NPC, JUMP1, (-1), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_CATCH(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CATCH(ctx, NPC, JUMP0, (2), (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_CATCH(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CATCH(ctx, NPC, JUMP0, (-1), (3), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc4_CATCH(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_CATCH(ctx, NPC, JUMP0, (-1), (-1), ((Object*)4));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_THROW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROW(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_THROW(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROW(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_THROWS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROWs(ctx, ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_THROWS(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROWs(ctx, ((Object*)1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_THROW_AGAIN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROW_AGAIN(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_THROW_AGAIN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_THROW_AGAIN(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_P(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_P(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_P(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_P(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_P(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_P(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_P(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_P(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_PMSG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PMSG(ctx, (-1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_PMSG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PMSG(ctx, (1), ((Object*)-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_PMSG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_PMSG(ctx, (-1), ((Object*)2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ICAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iCAST(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ICAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iCAST(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_INCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_inCAST(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_INCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_inCAST(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fCAST(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fCAST(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FNCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fnCAST(ctx, (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FNCAST(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fnCAST(ctx, (1));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_BNOT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bNOT(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_BNOT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bNOT(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_BNOT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_bNOT(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_INEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEG(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_INEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEG(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_INEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEG(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADD(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADD(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADD(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADD(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADDn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADDn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADDn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iADDn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUB(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUB(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ISUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUB(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ISUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUB(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ISUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUBn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ISUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUBn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ISUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUBn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ISUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iSUBn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMUL(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMUL(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMUL(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMUL(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMULn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMULn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMULn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMULn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIV(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIV(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIV(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIV(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIVn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIVn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIVn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iDIVn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IMOD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMOD(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IMOD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMOD(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IMOD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMOD(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IMOD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMOD(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IMODN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMODn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IMODN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMODn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IMODN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMODn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IMODN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iMODn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQ(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQ(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQ(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQ(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iEQn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_INEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQ(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_INEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQ(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_INEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQ(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_INEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQ(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_INEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_INEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_INEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_INEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iNEQn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ILT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLT(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ILT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLT(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ILT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLT(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ILT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLT(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ILTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ILTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ILTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ILTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ILTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTE(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ILTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTE(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ILTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTE(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ILTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTE(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ILTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTEn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ILTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTEn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ILTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTEn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ILTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iLTEn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGT(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGT(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGT(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGT(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTE(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTE(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTE(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTE(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTEn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTEn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTEn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_iGTEn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FNEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEG(ctx, (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FNEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEG(ctx, (1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FNEG(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEG(ctx, (-1), (2));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADD(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADD(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADD(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FADD(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADD(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADDn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADDn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADDn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FADDN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fADDn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FSUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUB(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FSUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUB(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FSUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUB(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FSUB(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUB(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FSUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUBn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FSUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUBn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FSUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUBn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FSUBN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fSUBn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMUL(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMUL(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMUL(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FMUL(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMUL(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMULn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMULn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMULn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FMULN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fMULn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIV(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIV(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIV(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FDIV(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIV(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIVn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIVn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIVn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FDIVN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fDIVn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQ(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQ(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQ(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQ(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fEQn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FNEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQ(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FNEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQ(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FNEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQ(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FNEQ(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQ(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FNEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FNEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FNEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FNEQN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fNEQn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FLT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLT(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FLT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLT(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FLT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLT(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FLT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLT(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FLTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FLTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FLTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FLTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FLTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTE(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FLTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTE(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FLTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTE(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FLTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTE(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FLTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTEn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FLTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTEn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FLTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTEn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FLTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fLTEn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGT(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGT(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGT(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FGT(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGT(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FGTN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTE(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTE(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTE(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FGTE(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTE(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTEn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTEn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTEn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FGTEN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_fGTEn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_AGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_AGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_AGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_AGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_AGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_AGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_AGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_AGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_AGETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IAGETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FAGET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FAGETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FAGETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_ASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_ASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_ASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_ASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_ASETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_IASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_IASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_IASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_IASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_IASETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASET(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASET(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASET(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FASET(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASET(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static
METHOD jc0_FASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASETn(ctx, (-1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc1_FASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASETn(ctx, (1), (-1), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc2_FASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASETn(ctx, (-1), (2), (-1));
	__asm__ __volatile__("int3");
}


static
METHOD jc3_FASETN(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	JIT_FASETn(ctx, (-1), (-1), (3));
	__asm__ __volatile__("int3");
}


static knh_fmethod codeTempList[139][6] = {
	{jc0_HALT},
	{jc0_MOVA,jc1_MOVA,jc2_MOVA},
	{jc0_MOVN,jc1_MOVN,jc2_MOVN},
	{jc0_MOVO,jc1_MOVO,jc2_MOVO},
	{jc0_MOVX,jc1_MOVX,jc2_MOVX,jc3_MOVX},
	{jc0_MOVDEF,jc1_MOVDEF,jc2_MOVDEF},
	{jc0_MOVSYS,jc1_MOVSYS,jc2_MOVSYS},
	{jc0_XMOVS,jc1_XMOVS,jc2_XMOVS,jc3_XMOVS},
	{jc0_XMOVO,jc1_XMOVO,jc2_XMOVO,jc3_XMOVO},
	{jc0_XMOVX,jc1_XMOVX,jc2_XMOVX,jc3_XMOVX,jc4_XMOVX},
	{jc0_XMOVDEF,jc1_XMOVDEF,jc2_XMOVDEF,jc3_XMOVDEF},
	{jc0_XMOVSYS,jc1_XMOVSYS,jc2_XMOVSYS,jc3_XMOVSYS},
	{jc0_MOVXI,jc1_MOVXI,jc2_MOVXI,jc3_MOVXI},
	{jc0_XMOVSI,jc1_XMOVSI,jc2_XMOVSI,jc3_XMOVSI},
	{jc0_XMOVOI,jc1_XMOVOI,jc2_XMOVOI,jc3_XMOVOI},
	{jc0_XMOVXI,jc1_XMOVXI,jc2_XMOVXI,jc3_XMOVXI,jc4_XMOVXI},
	{jc0_XMOVXIO,jc1_XMOVXIO,jc2_XMOVXIO,jc3_XMOVXIO,jc4_XMOVXIO},
	{jc0_XMOVXBXI,jc1_XMOVXBXI,jc2_XMOVXBXI,jc3_XMOVXBXI,jc4_XMOVXBXI,jc5_XMOVXBXI},
	{jc0_MOVXF,jc1_MOVXF,jc2_MOVXF,jc3_MOVXF},
	{jc0_XMOVSF,jc1_XMOVSF,jc2_XMOVSF,jc3_XMOVSF},
	{jc0_XMOVOF,jc1_XMOVOF,jc2_XMOVOF,jc3_XMOVOF},
	{jc0_XMOVXF,jc1_XMOVXF,jc2_XMOVXF,jc3_XMOVXF,jc4_XMOVXF},
	{jc0_XMOVXFO,jc1_XMOVXFO,jc2_XMOVXFO,jc3_XMOVXFO,jc4_XMOVXFO},
	{jc0_XMOVXBXF,jc1_XMOVXBXF,jc2_XMOVXBXF,jc3_XMOVXBXF,jc4_XMOVXBXF,jc5_XMOVXBXF},
	{jc0_MOVXB,jc1_MOVXB,jc2_MOVXB,jc3_MOVXB},
	{jc0_XMOVSB,jc1_XMOVSB,jc2_XMOVSB,jc3_XMOVSB},
	{jc0_XMOVOB,jc1_XMOVOB,jc2_XMOVOB,jc3_XMOVOB},
	{jc0_XMOVXB,jc1_XMOVXB,jc2_XMOVXB,jc3_XMOVXB,jc4_XMOVXB},
	{jc0_SWAP,jc1_SWAP,jc2_SWAP},
	{jc0_PINIO,jc1_PINIO,jc2_PINIO},
	{jc0_SETESP,jc1_SETESP},
	{jc0_CHECKESP,jc1_CHECKESP},
	{jc0_RET},
	{jc0_RETN,jc1_RETN,jc2_RETN},
	{jc0_RETA,jc1_RETA,jc2_RETA},
	{jc0_RETO,jc1_RETO,jc2_RETO},
	{jc0_RETX,jc1_RETX,jc2_RETX,jc3_RETX},
	{jc0_BOX,jc1_BOX,jc2_BOX},
	{jc0_BOXNC,jc1_BOXNC,jc2_BOXNC},
	{jc0_NNBOX,jc1_NNBOX,jc2_NNBOX},
	{jc0_NNBOXNC,jc1_NNBOXNC,jc2_NNBOXNC},
	{jc0_UNBOX,jc1_UNBOX},
	{jc0_ISNULL,jc1_ISNULL},
	{jc0_ISNULLX,jc1_ISNULLX,jc2_ISNULLX},
	{jc0_ISTYPE,jc1_ISTYPE,jc2_ISTYPE},
	{jc0_ISNNTYPE,jc1_ISNNTYPE,jc2_ISNNTYPE},
	{jc0_FCALL,jc1_FCALL,jc2_FCALL,jc3_FCALL,jc4_FCALL},
	{jc0_SCALL,jc1_SCALL,jc2_SCALL,jc3_SCALL},
	{jc0_AINVOKE,jc1_AINVOKE,jc2_AINVOKE,jc3_AINVOKE},
	{jc0_CALL,jc1_CALL,jc2_CALL,jc3_CALL},
	{jc0_ACALL,jc1_ACALL,jc2_ACALL,jc3_ACALL},
	{jc0_NEW,jc1_NEW,jc2_NEW,jc3_NEW,jc4_NEW,jc5_NEW},
	{jc0_TOSTR,jc1_TOSTR,jc2_TOSTR},
	{jc0_TOSTRF,jc1_TOSTRF,jc2_TOSTRF,jc3_TOSTRF},
	{jc0_SMAP,jc1_SMAP,jc2_SMAP},
	{jc0_SMAPNC,jc1_SMAPNC,jc2_SMAPNC},
	{jc0_MAP,jc1_MAP,jc2_MAP},
	{jc0_MAPNC,jc1_MAPNC,jc2_MAPNC},
	{jc0_AMAP,jc1_AMAP,jc2_AMAP},
	{jc0_NNMAP,jc1_NNMAP,jc2_NNMAP},
	{jc0_JMP,jc1_JMP},
	{jc0_BJIFT,jc1_BJIFT,jc2_BJIFT},
	{jc0_BJIFF,jc1_BJIFF,jc2_BJIFF},
	{jc0_BJIFF_LOOP,jc1_BJIFF_LOOP,jc2_BJIFF_LOOP},
	{jc0_JIFNUL,jc1_JIFNUL,jc2_JIFNUL},
	{jc0_JIFNN,jc1_JIFNN,jc2_JIFNN},
	{jc0_NEXT,jc1_NEXT,jc2_NEXT,jc3_NEXT,jc4_NEXT},
	{jc0_INEXT,jc1_INEXT,jc2_INEXT,jc3_INEXT,jc4_INEXT,jc5_INEXT},
	{jc0_MAPNEXT,jc1_MAPNEXT,jc2_MAPNEXT,jc3_MAPNEXT,jc4_MAPNEXT,jc5_MAPNEXT},
	{jc0_SMAPNEXT,jc1_SMAPNEXT,jc2_SMAPNEXT,jc3_SMAPNEXT,jc4_SMAPNEXT,jc5_SMAPNEXT},
	{jc0_TRY,jc1_TRY,jc2_TRY},
	{jc0_TRYEND,jc1_TRYEND},
	{jc0_CATCH,jc1_CATCH,jc2_CATCH,jc3_CATCH,jc4_CATCH},
	{jc0_THROW,jc1_THROW},
	{jc0_THROWS,jc1_THROWS},
	{jc0_THROW_AGAIN,jc1_THROW_AGAIN},
	{jc0_P,jc1_P,jc2_P,jc3_P},
	{jc0_PMSG,jc1_PMSG,jc2_PMSG},
	{jc0_ICAST,jc1_ICAST},
	{jc0_INCAST,jc1_INCAST},
	{jc0_FCAST,jc1_FCAST},
	{jc0_FNCAST,jc1_FNCAST},
	{jc0_BNOT,jc1_BNOT,jc2_BNOT},
	{jc0_INEG,jc1_INEG,jc2_INEG},
	{jc0_IADD,jc1_IADD,jc2_IADD,jc3_IADD},
	{jc0_IADDN,jc1_IADDN,jc2_IADDN,jc3_IADDN},
	{jc0_ISUB,jc1_ISUB,jc2_ISUB,jc3_ISUB},
	{jc0_ISUBN,jc1_ISUBN,jc2_ISUBN,jc3_ISUBN},
	{jc0_IMUL,jc1_IMUL,jc2_IMUL,jc3_IMUL},
	{jc0_IMULN,jc1_IMULN,jc2_IMULN,jc3_IMULN},
	{jc0_IDIV,jc1_IDIV,jc2_IDIV,jc3_IDIV},
	{jc0_IDIVN,jc1_IDIVN,jc2_IDIVN,jc3_IDIVN},
	{jc0_IMOD,jc1_IMOD,jc2_IMOD,jc3_IMOD},
	{jc0_IMODN,jc1_IMODN,jc2_IMODN,jc3_IMODN},
	{jc0_IEQ,jc1_IEQ,jc2_IEQ,jc3_IEQ},
	{jc0_IEQN,jc1_IEQN,jc2_IEQN,jc3_IEQN},
	{jc0_INEQ,jc1_INEQ,jc2_INEQ,jc3_INEQ},
	{jc0_INEQN,jc1_INEQN,jc2_INEQN,jc3_INEQN},
	{jc0_ILT,jc1_ILT,jc2_ILT,jc3_ILT},
	{jc0_ILTN,jc1_ILTN,jc2_ILTN,jc3_ILTN},
	{jc0_ILTE,jc1_ILTE,jc2_ILTE,jc3_ILTE},
	{jc0_ILTEN,jc1_ILTEN,jc2_ILTEN,jc3_ILTEN},
	{jc0_IGT,jc1_IGT,jc2_IGT,jc3_IGT},
	{jc0_IGTN,jc1_IGTN,jc2_IGTN,jc3_IGTN},
	{jc0_IGTE,jc1_IGTE,jc2_IGTE,jc3_IGTE},
	{jc0_IGTEN,jc1_IGTEN,jc2_IGTEN,jc3_IGTEN},
	{jc0_FNEG,jc1_FNEG,jc2_FNEG},
	{jc0_FADD,jc1_FADD,jc2_FADD,jc3_FADD},
	{jc0_FADDN,jc1_FADDN,jc2_FADDN,jc3_FADDN},
	{jc0_FSUB,jc1_FSUB,jc2_FSUB,jc3_FSUB},
	{jc0_FSUBN,jc1_FSUBN,jc2_FSUBN,jc3_FSUBN},
	{jc0_FMUL,jc1_FMUL,jc2_FMUL,jc3_FMUL},
	{jc0_FMULN,jc1_FMULN,jc2_FMULN,jc3_FMULN},
	{jc0_FDIV,jc1_FDIV,jc2_FDIV,jc3_FDIV},
	{jc0_FDIVN,jc1_FDIVN,jc2_FDIVN,jc3_FDIVN},
	{jc0_FEQ,jc1_FEQ,jc2_FEQ,jc3_FEQ},
	{jc0_FEQN,jc1_FEQN,jc2_FEQN,jc3_FEQN},
	{jc0_FNEQ,jc1_FNEQ,jc2_FNEQ,jc3_FNEQ},
	{jc0_FNEQN,jc1_FNEQN,jc2_FNEQN,jc3_FNEQN},
	{jc0_FLT,jc1_FLT,jc2_FLT,jc3_FLT},
	{jc0_FLTN,jc1_FLTN,jc2_FLTN,jc3_FLTN},
	{jc0_FLTE,jc1_FLTE,jc2_FLTE,jc3_FLTE},
	{jc0_FLTEN,jc1_FLTEN,jc2_FLTEN,jc3_FLTEN},
	{jc0_FGT,jc1_FGT,jc2_FGT,jc3_FGT},
	{jc0_FGTN,jc1_FGTN,jc2_FGTN,jc3_FGTN},
	{jc0_FGTE,jc1_FGTE,jc2_FGTE,jc3_FGTE},
	{jc0_FGTEN,jc1_FGTEN,jc2_FGTEN,jc3_FGTEN},
	{jc0_AGET,jc1_AGET,jc2_AGET,jc3_AGET},
	{jc0_AGETN,jc1_AGETN,jc2_AGETN,jc3_AGETN},
	{jc0_IAGET,jc1_IAGET,jc2_IAGET,jc3_IAGET},
	{jc0_IAGETN,jc1_IAGETN,jc2_IAGETN,jc3_IAGETN},
	{jc0_FAGET,jc1_FAGET,jc2_FAGET,jc3_FAGET},
	{jc0_FAGETN,jc1_FAGETN,jc2_FAGETN,jc3_FAGETN},
	{jc0_ASET,jc1_ASET,jc2_ASET,jc3_ASET},
	{jc0_ASETN,jc1_ASETN,jc2_ASETN,jc3_ASETN},
	{jc0_IASET,jc1_IASET,jc2_IASET,jc3_IASET},
	{jc0_IASETN,jc1_IASETN,jc2_IASETN,jc3_IASETN},
	{jc0_FASET,jc1_FASET,jc2_FASET,jc3_FASET},
	{jc0_FASETN,jc1_FASETN,jc2_FASETN,jc3_FASETN},

};

knh_fmethod konoha_getCodeTemplate(int opcode, int pos)
{
	return codeTempList[opcode][pos];
}

#endif/*KONOHA_CODETEMPLATE*/

#ifdef __cplusplus
}
#endif
