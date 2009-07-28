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

/*--------------------------------------------------------------------------*/
/* Class Definition */


class GV;
class GVC;
class Agraph;
class Agnode;
class Agedge;

/*-------------------------------------------------------------------------*/
/*GV*/

/**
 * グラフ、ノード、エッジに対して属性値を付加する
 * @param obj 属性値を付加させたい対象
 * @param name 属性の種類
 * @param value 具体的な値
 * @param deff 通常与えなくてよい( "" )
 */

void GV.agSafeset(Any obj,String name,String value,String deff);

/*-----------------------------------------------------------------------------*/
/*GVC*/

/**
 * GVC を作る
 */

GVC GVC.new();

/**
 * 描画エンジンを起動する
 * @param argv コマンドラインからの引数 
 */

void GVC.gvParseArgs(String[] argv);

/**
 * 描画エンジンを用いて描く
 * @param g Agraph
 */

void GVC.gvLayoutJobs(Agraph g);

/**
 * オプションによってグラフを描く
 * @param g Agraph
 */

void GVC.gvRenderJobs(Agraph g);

/**
 * 描画データの破棄
 * @param g Agraph
 */

void GVC.gvFreeLayout(Agraph g);

/**
 * コンテキストの破棄
 */

void GVC.gvFreeContext();

/*------------------------------------------------------------------------*/
/*Agraph*/

/**
 * グラフを作る
 * @param name グラフの内部的な名前（描画はされない）
 * @param kind 属性値（通常１でよい）
 */

Agraph Agraph.new(String name,int kind);

/**
 * グラフ作成を終える
 */

void Agraph.agclose();

/*------------------------------------------------------------------------*/
/*Agnode*/

/**
 * ノードを作る
 * @param g Agraph
 * @param name ノード名
 */

Agnode Agnode.new(Agraph g,String name);

/*------------------------------------------------------------------------*/
/*Agedge*/

/**
 * ノード間を繋ぐエッジを作る
 * @param g Agraph
 * @param start エッジの送り手(ノード）
 * @param end エッジの受け手(ノード）
 */

Agedge Agedge.new(Agraph g,Agnode start,Agnode end);





