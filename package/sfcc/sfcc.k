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
 
 

if(!System.hasLib("cimcclient0")) {
    /*	OUT << "you need sfcc (libcimcclient0)" << EOL;
}


/* ------------------------------------------------------------------------ */
/* Class Definition */

class CIMObjectPath;
class CIMClient;

/* ------------------------------------------------------------------------ */
/* CIMObjectPath */

/**
 * CIMObjectPath を作る
 * @param path オブジェクトパス
 */

CIMObjectPath CIMObjectPath.new(String path);

/* ------------------------------------------------------------------------ */
/* CIMClient */

/**
 * CIMClient を作る
 * @param url - 接続先のCIM Object Manager をあらわすURL
 */

CIMClient CIMClient.new(String url);

/**
 * クラス名の一覧をイテレータとしてえる
 * @param op CIMObjectPath
 * @param flag フラグ（省略可能)
 * @return クラス名の一覧
 */

String.. CIMClient.enumClassNames(CIMObjectPath op, Int? flag);
