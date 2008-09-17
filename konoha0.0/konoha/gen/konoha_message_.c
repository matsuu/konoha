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


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

static int local_lang = 0;

/* ------------------------------------------------------------------------ */

static char* knh_system_lang[] = {
    "en", 
#ifdef KNH_USING_ICONV
    "ja",
#endif
    "debug"
};

int knh_system_langid(char *lang)
{
    int i;
    for(i = 0; i < KONOHA_LANG_MAXSIZ; i++) {
        if(knh_strncmp(knh_system_lang[i], lang, 2) == 0) return i;
    }
    return local_lang;
}

/* ------------------------------------------------------------------------ */

void knh_Compiler_setLang(char *lang)
{
#ifdef KNH_USING_ICONV
    local_lang = knh_system_langid(lang);
#endif
    //return local_lang;
}

/* ------------------------------------------------------------------------ */

static int knh_message_typedata[] = {
    /* KMSG_NAME */ 0,
    /* KMSG_ERRATA */ 0,
    /* KMSG_ETIME */ 0,
    /* KMSG_TYPEINF */ 0,
    /* KMSG_ERROR */ 0,
    /* KMSG_WARNING */ 0,
    /* KMSG_INFO */ 0,
    /* KMSG_ESYNTAX */ 1,
    /* KMSG_EFORGET_PARENTHESIS */ 2,
    /* KMSG_EMISMATCH */ 1,
    /* KMSG_WUNCLOSED */ 2,
    /* KMSG_WASCII */ 2,
    /* KMSG_WEOF */ 2,
    /* KMSG_WSEMICOLON */ 2,
    /* KMSG_IGSTMT */ 2,
    /* KMSG_ETOKEN */ 1,
    /* KMSG_ELENGTH */ 2,
    /* KMSG_WCLASSN */ 2,
    /* KMSG_WCONSTN */ 2,
    /* KMSG_WCMETHODN */ 2,
    /* KMSG_WNAME */ 2,
    /* KMSG_WIGNORED */ 2,
    /* KMSG_TEXPTN */ 1,
    /* KMSG_TNSNAME */ 1,
    /* KMSG_TFURN */ 1,
    /* KMSG_TCURN */ 1,
    /* KMSG_TNSCLASSN */ 1,
    /* KMSG_TTYPEN */ 1,
    /* KMSG_TMETHODN */ 1,
    /* KMSG_TCLASSTN */ 1,
    /* KMSG_TSTR */ 1,
    /* KMSG_TVARN */ 1,
    /* KMSG_TCLASSN */ 1,
    /* KMSG_TARGS */ 1,
    /* KMSG_TNAME */ 1,
    /* KMSG_TCMETHODN */ 1,
    /* KMSG_TMT */ 1,
    /* KMSG_TANY */ 1,
    /* KMSG_TSTMT1 */ 1,
    /* KMSG_TPEXPR */ 1,
    /* KMSG_TCATCHPARAM */ 1,
    /* KMSG_ELVALUE */ 1,
    /* KMSG_WTYPEINF */ 2,
    /* KMSG_NOTHERECONST */ 1,
    /* KMSG_NOTHERECLASSCONST */ 1,
    /* KMSG_NNCONST */ 1,
    /* KMSG_DUPCONST */ 1,
    /* KMSG_ENEXTPREV */ 1,
    /* KMSG_EEMPTYEXPR */ 1,
    /* KMSG_ETRINARY */ 1,
    /* KMSG_EBUILTINFUNC */ 1,
    /* KMSG_EPSTMT3 */ 1,
    /* KMSG_EPEACH */ 1,
    /* KMSG_WLET */ 2,
    /* KMSG_WEMPTYPEXPR */ 2,
    /* KMSG_WEMPTYARGS */ 2,
    /* KMSG_WTRUEFALSE */ 2,
    /* KMSG_USCRIPT */ 1,
    /* KMSG_UUOPTION */ 1,
    /* KMSG_UURN */ 1,
    /* KMSG_UPACKAGE */ 1,
    /* KMSG_UCONSTN */ 1,
    /* KMSG_UVARN */ 1,
    /* KMSG_USYSTEMVARN */ 1,
    /* KMSG_UCLASSN */ 1,
    /* KMSG_UTAG */ 1,
    /* KMSG_UTYPEN */ 1,
    /* KMSG_UMETHODN */ 1,
    /* KMSG_UFUNCN */ 1,
    /* KMSG_ULABEL */ 1,
    /* KMSG_UOP */ 1,
    /* KMSG_UOP1 */ 1,
    /* KMSG_UOP2 */ 2,
    /* KMSG_UNEW */ 1,
    /* KMSG_UMAP */ 1,
    /* KMSG_INTOVERFLOW */ 2,
    /* KMSG_FLOATOVERFLOW */ 2,
    /* KMSG_INT64OVERFLOW */ 2,
    /* KMSG_ETOOFEWPARAMS */ 1,
    /* KMSG_WTOOMANYPARAMS */ 2,
    /* KMSG_EOP2 */ 1,
    /* KMSG_EOPCMP */ 2,
    /* KMSG_ENULLPARAM */ 1,
    /* KMSG_WNULLPARAM */ 2,
    /* KMSG_ETYPEPARAM */ 1,
    /* KMSG_ENULLRETURN */ 1,
    /* KMSG_WNULLRETURN */ 2,
    /* KMSG_ETYPERETURN */ 2,
    /* KMSG_ENULLLET */ 1,
    /* KMSG_ENULL */ 1,
    /* KMSG_WNULLLET */ 2,
    /* KMSG_WNULL */ 2,
    /* KMSG_ETYPELET */ 1,
    /* KMSG_ETYPE */ 1,
    /* KMSG_WDUPFUNCNAME */ 2,
    /* KMSG_USCLASSFUNC */ 2,
    /* KMSG_IGNNTYPE */ 3,
    /* KMSG_EEXTENDS */ 1,
    /* KMSG_EIMPLEMENTS */ 1,
    /* KMSG_DIFFDECL */ 2,
    /* KMSG_DIFFCLASSN */ 2,
    /* KMSG_DIFFNEWTYPE */ 1,
    /* KMSG_DIFFRTYPE */ 1,
    /* KMSG_DIFFPSIZE */ 1,
    /* KMSG_DIFFPTYPE */ 1,
    /* KMSG_DIFFPNAME */ 2,
    /* KMSG_TOOMANYVARS */ 1,
    /* KMSG_EOUTERLOOP */ 2,
    /* KMSG_IGFIELDVALUE */ 1,
    /* KMSG_IGSCRIPTNAME */ 1,
    /* KMSG_IGFIELDNAME */ 1,
    /* KMSG_NORETURN */ 1,
    /* KMSG_NORETURNVALUE */ 1,
    /* KMSG_IGRETURN */ 2,
    /* KMSG_AHISTORIC */ 2,
    /* KMSG_AOVERRIDE */ 2,
    /* KMSG_EOVERRIDE */ 1,
    /* KMSG_TOABSTRACT */ 2,
    0
};

int knh_message_type(int e)
{
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    return knh_message_typedata[e];
}

/* ------------------------------------------------------------------------ */

static char* knh_message_data[] = {
    /* KMSG_NAME */ 
        /* en */ "Konoha",
#ifdef KNH_USING_ICONV
        /* ja */ "このは",
#endif
        "NAME",
    
    /* KMSG_ERRATA */ 
        /* en */ "ERRATA",
#ifdef KNH_USING_ICONV
        /* ja */ "訂正",
#endif
        "ERRATA",
    
    /* KMSG_ETIME */ 
        /* en */ "Elapsed Time",
#ifdef KNH_USING_ICONV
        /* ja */ "実行時間",
#endif
        "ETIME",
    
    /* KMSG_TYPEINF */ 
        /* en */ "type inferencing",
#ifdef KNH_USING_ICONV
        /* ja */ "型推論",
#endif
        "TYPEINF",
    
    /* KMSG_ERROR */ 
        /* en */ "error",
#ifdef KNH_USING_ICONV
        /* ja */ "エラー",
#endif
        "ERROR",
    
    /* KMSG_WARNING */ 
        /* en */ "warning",
#ifdef KNH_USING_ICONV
        /* ja */ "警告",
#endif
        "WARNING",
    
    /* KMSG_INFO */ 
        /* en */ "info",
#ifdef KNH_USING_ICONV
        /* ja */ "お知らせ",
#endif
        "INFO",
    
    /* KMSG_ESYNTAX */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_ICONV
        /* ja */ "文法的な間違いがあります（ただしコンパイラのバグの可能性もあります）",
#endif
        "ESYNTAX",
    
    /* KMSG_EFORGET_PARENTHESIS */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_ICONV
        /* ja */ "{の前で括弧を閉じ忘れています",
#endif
        "EFORGET_PARENTHESIS",
    
    /* KMSG_EMISMATCH */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_ICONV
        /* ja */ "括弧の対応をあわせてください",
#endif
        "EMISMATCH",
    
    /* KMSG_WUNCLOSED */ 
        /* en */ "You will need a closing symbol",
#ifdef KNH_USING_ICONV
        /* ja */ "閉じてください",
#endif
        "WUNCLOSED",
    
    /* KMSG_WASCII */ 
        /* en */ "Don't use non-ASCII characters",
#ifdef KNH_USING_ICONV
        /* ja */ "ASCII文字（半角）をお使いください",
#endif
        "WASCII",
    
    /* KMSG_WEOF */ 
        /* en */ "You will close this file at a new line",
#ifdef KNH_USING_ICONV
        /* ja */ "行の途中でファイルが終端しています",
#endif
        "WEOF",
    
    /* KMSG_WSEMICOLON */ 
        /* en */ "Add ';' at the end of the statement",
#ifdef KNH_USING_ICONV
        /* ja */ "文末にはセミコロン(;)を追加してください",
#endif
        "WSEMICOLON",
    
    /* KMSG_IGSTMT */ 
        /* en */ "This statement might be meaningless",
#ifdef KNH_USING_ICONV
        /* ja */ "無効果なステートメントなため無視されました",
#endif
        "IGSTMT",
    
    /* KMSG_ETOKEN */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_ICONV
        /* ja */ "名前でも演算子でもありません",
#endif
        "ETOKEN",
    
    /* KMSG_ELENGTH */ 
        /* en */ "You will reduce the length of the name",
#ifdef KNH_USING_ICONV
        /* ja */ "名前の長さを短くしてください",
#endif
        "ELENGTH",
    
    /* KMSG_WCLASSN */ 
        /* en */ "Give the right Class name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいクラス名に修正してください",
#endif
        "WCLASSN",
    
    /* KMSG_WCONSTN */ 
        /* en */ "Give the right CONST name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい定数名に修正してください",
#endif
        "WCONSTN",
    
    /* KMSG_WCMETHODN */ 
        /* en */ "Give the right Class.method name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいクラスメソッド名に修正してください",
#endif
        "WCMETHODN",
    
    /* KMSG_WNAME */ 
        /* en */ "Give the right name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい名前に修正してください",
#endif
        "WNAME",
    
    /* KMSG_WIGNORED */ 
        /* en */ "The following tokens was ignored",
#ifdef KNH_USING_ICONV
        /* ja */ "次の字句は無視されました",
#endif
        "WIGNORED",
    
    /* KMSG_TEXPTN */ 
        /* en */ "Give the right Exception!! name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい例外名を与えてください",
#endif
        "TEXPTN",
    
    /* KMSG_TNSNAME */ 
        /* en */ "Give the right namespace(package) name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい名前空間名を与えてください",
#endif
        "TNSNAME",
    
    /* KMSG_TFURN */ 
        /* en */ "Give the right file path for konoha script (*.k)",
#ifdef KNH_USING_ICONV
        /* ja */ "スクリプトファイル(*.k)のパスを与えてください",
#endif
        "TFURN",
    
    /* KMSG_TCURN */ 
        /* en */ "Give a Class name or URN",
#ifdef KNH_USING_ICONV
        /* ja */ "クラス名かURNを与えてください",
#endif
        "TCURN",
    
    /* KMSG_TNSCLASSN */ 
        /* en */ "Give the right package.Class",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいパッケージ名付きのクラス名を与えてください",
#endif
        "TNSCLASSN",
    
    /* KMSG_TTYPEN */ 
        /* en */ "Give the right type name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい型名を与えてください",
#endif
        "TTYPEN",
    
    /* KMSG_TMETHODN */ 
        /* en */ "Give the right method name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいメソッド名を与えてください",
#endif
        "TMETHODN",
    
    /* KMSG_TCLASSTN */ 
        /* en */ "Give the right Class:tag name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいクラス名（タグ付き）を与えてください",
#endif
        "TCLASSTN",
    
    /* KMSG_TSTR */ 
        /* en */ "Give the right \"string\"",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい文字列を与えてください",
#endif
        "TSTR",
    
    /* KMSG_TVARN */ 
        /* en */ "Give the right variable name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい変数名を与えてください",
#endif
        "TVARN",
    
    /* KMSG_TCLASSN */ 
        /* en */ "Give the right Class name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいクラス名を与えてください",
#endif
        "TCLASSN",
    
    /* KMSG_TARGS */ 
        /* en */ "Give parameter(s) correctly",
#ifdef KNH_USING_ICONV
        /* ja */ "正しくパラメータをあたえてください",
#endif
        "TARGS",
    
    /* KMSG_TNAME */ 
        /* en */ "Give the right name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい名前を与えてください",
#endif
        "TNAME",
    
    /* KMSG_TCMETHODN */ 
        /* en */ "Give the right Class.method name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいクラス名付きメソッド名を与えてください",
#endif
        "TCMETHODN",
    
    /* KMSG_TMT */ 
        /* en */ "Give the right formatter name",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいフォーマッタ名を与えてください",
#endif
        "TMT",
    
    /* KMSG_TANY */ 
        /* en */ "Give the right token",
#ifdef KNH_USING_ICONV
        /* ja */ "正しいトークンを与えてください",
#endif
        "TANY",
    
    /* KMSG_TSTMT1 */ 
        /* en */ "Start a statement correctly",
#ifdef KNH_USING_ICONV
        /* ja */ "正しく行をはじめてください",
#endif
        "TSTMT1",
    
    /* KMSG_TPEXPR */ 
        /* en */ "Start a statement correctly",
#ifdef KNH_USING_ICONV
        /* ja */ "正しく条件式を与えてください",
#endif
        "TPEXPR",
    
    /* KMSG_TCATCHPARAM */ 
        /* en */ "catch needs a parameter",
#ifdef KNH_USING_ICONV
        /* ja */ "catch文のパラメータを与えてください",
#endif
        "TCATCHPARAM",
    
    /* KMSG_ELVALUE */ 
        /* en */ "Invalid L-VALUE",
#ifdef KNH_USING_ICONV
        /* ja */ "代入可能な変数名を与えてください",
#endif
        "ELVALUE",
    
    /* KMSG_WTYPEINF */ 
        /* en */ "Impossible to infer the type",
#ifdef KNH_USING_ICONV
        /* ja */ "型推論ができませんでした．Any型を使います",
#endif
        "WTYPEINF",
    
    /* KMSG_NOTHERECONST */ 
        /* en */ "Defining CONST is allowed within the script or the class-field scope",
#ifdef KNH_USING_ICONV
        /* ja */ "定数が定義できるのはスクリプトかクラス内のみです",
#endif
        "NOTHERECONST",
    
    /* KMSG_NOTHERECLASSCONST */ 
        /* en */ "Defining Class.CONST is not allowed here",
#ifdef KNH_USING_ICONV
        /* ja */ "この位置ではクラス名を付きで定数は定義できません",
#endif
        "NOTHERECLASSCONST",
    
    /* KMSG_NNCONST */ 
        /* en */ "Give the const value at the right hand",
#ifdef KNH_USING_ICONV
        /* ja */ "左辺に定数を与えてください",
#endif
        "NNCONST",
    
    /* KMSG_DUPCONST */ 
        /* en */ "Cannot redefine the given CONST name",
#ifdef KNH_USING_ICONV
        /* ja */ "同じ定数名で再定義することはできません",
#endif
        "DUPCONST",
    
    /* KMSG_ENEXTPREV */ 
        /* en */ "This expression dose not support ++/-- operators",
#ifdef KNH_USING_ICONV
        /* ja */ "--演算,++演算が評価できない式です",
#endif
        "ENEXTPREV",
    
    /* KMSG_EEMPTYEXPR */ 
        /* en */ "Give the right expression",
#ifdef KNH_USING_ICONV
        /* ja */ "正しい式をあたえてください",
#endif
        "EEMPTYEXPR",
    
    /* KMSG_ETRINARY */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_ICONV
        /* ja */ "三項演算子のtrueとfalseの式はコロン(:)で区切ってください",
#endif
        "ETRINARY",
    
    /* KMSG_EBUILTINFUNC */ 
        /* en */ "Invalid use of built-in function",
#ifdef KNH_USING_ICONV
        /* ja */ "組み込み関数の用法が正しくありません",
#endif
        "EBUILTINFUNC",
    
    /* KMSG_EPSTMT3 */ 
        /* en */ NULL,
#ifdef KNH_USING_ICONV
        /* ja */ "正しくfor(stmt;expr;stmt) 文を書いてください",
#endif
        "EPSTMT3",
    
    /* KMSG_EPEACH */ 
        /* en */ NULL,
#ifdef KNH_USING_ICONV
        /* ja */ "foreach(.. from .. where..) 文を書いてください",
#endif
        "EPEACH",
    
    /* KMSG_WLET */ 
        /* en */ "Don't use the assignment within a condition",
#ifdef KNH_USING_ICONV
        /* ja */ "条件式では代入を使わないでください",
#endif
        "WLET",
    
    /* KMSG_WEMPTYPEXPR */ 
        /* en */ "Don't use the empty condition",
#ifdef KNH_USING_ICONV
        /* ja */ "空っぽの条件式では困ります",
#endif
        "WEMPTYPEXPR",
    
    /* KMSG_WEMPTYARGS */ 
        /* en */ "You will need some parameters",
#ifdef KNH_USING_ICONV
        /* ja */ "引数を与えてください",
#endif
        "WEMPTYARGS",
    
    /* KMSG_WTRUEFALSE */ 
        /* en */ NULL,
#ifdef KNH_USING_ICONV
        /* ja */ "Booleanの定数には、trueかfalseを用いましょう",
#endif
        "WTRUEFALSE",
    
    /* KMSG_USCRIPT */ 
        /* en */ "Cannot open the script file",
#ifdef KNH_USING_ICONV
        /* ja */ "スクリプトファイルが開けません",
#endif
        "USCRIPT",
    
    /* KMSG_UUOPTION */ 
        /* en */ "You have used an unsupported using option",
#ifdef KNH_USING_ICONV
        /* ja */ "サポート外のusingオプションが利用されました",
#endif
        "UUOPTION",
    
    /* KMSG_UURN */ 
        /* en */ "Cannot download from the given URN",
#ifdef KNH_USING_ICONV
        /* ja */ "URNの参照先がダウンロードできません",
#endif
        "UURN",
    
    /* KMSG_UPACKAGE */ 
        /* en */ "You're attempting to use an uninstalled package",
#ifdef KNH_USING_ICONV
        /* ja */ "未インストールのパッケージを利用しようとしました",
#endif
        "UPACKAGE",
    
    /* KMSG_UCONSTN */ 
        /* en */ "You have used an undefined CONST",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義の定数を使用しました",
#endif
        "UCONSTN",
    
    /* KMSG_UVARN */ 
        /* en */ "You have used an undefined variable",
#ifdef KNH_USING_ICONV
        /* ja */ "未宣言の変数を使用しました",
#endif
        "UVARN",
    
    /* KMSG_USYSTEMVARN */ 
        /* en */ "You have used an undefined system variable",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義のシステム変数を使用しました",
#endif
        "USYSTEMVARN",
    
    /* KMSG_UCLASSN */ 
        /* en */ "You have used an undefined Class name",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義のクラス名を使用しました",
#endif
        "UCLASSN",
    
    /* KMSG_UTAG */ 
        /* en */ "You have used an undefined class tag",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義のクラスタグを使用しました",
#endif
        "UTAG",
    
    /* KMSG_UTYPEN */ 
        /* en */ "You have used an undefined type",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義の型を使用しました",
#endif
        "UTYPEN",
    
    /* KMSG_UMETHODN */ 
        /* en */ "You have used an undefined method",
#ifdef KNH_USING_ICONV
        /* ja */ "定義されていないメソッドを使用しました",
#endif
        "UMETHODN",
    
    /* KMSG_UFUNCN */ 
        /* en */ "You have used an undefined function",
#ifdef KNH_USING_ICONV
        /* ja */ "定義されていない関数メソッドを使用しました",
#endif
        "UFUNCN",
    
    /* KMSG_ULABEL */ 
        /* en */ "You have used an undefined label",
#ifdef KNH_USING_ICONV
        /* ja */ "未定義のラベルを用いました",
#endif
        "ULABEL",
    
    /* KMSG_UOP */ 
        /* en */ "You have used an unsupported operator",
#ifdef KNH_USING_ICONV
        /* ja */ "定義されていない演算子を用いました",
#endif
        "UOP",
    
    /* KMSG_UOP1 */ 
        /* en */ "This operator is unary",
#ifdef KNH_USING_ICONV
        /* ja */ "この演算子は、単項演算子です",
#endif
        "UOP1",
    
    /* KMSG_UOP2 */ 
        /* en */ "This operator is binary",
#ifdef KNH_USING_ICONV
        /* ja */ "この演算子は、２項演算子です",
#endif
        "UOP2",
    
    /* KMSG_UNEW */ 
        /* en */ "You have used an undefined constructor",
#ifdef KNH_USING_ICONV
        /* ja */ "定義されていないコンストラクタを用いました",
#endif
        "UNEW",
    
    /* KMSG_UMAP */ 
        /* en */ "You have used an undefined mapping",
#ifdef KNH_USING_ICONV
        /* ja */ "マッピングは定義されていません",
#endif
        "UMAP",
    
    /* KMSG_INTOVERFLOW */ 
        /* en */ "The given Int value was overflowed",
#ifdef KNH_USING_ICONV
        /* ja */ "整数(Int)の最大値もしくは最小値を超えました",
#endif
        "INTOVERFLOW",
    
    /* KMSG_FLOATOVERFLOW */ 
        /* en */ "The given Float value was overflowed",
#ifdef KNH_USING_ICONV
        /* ja */ "浮動点少数(Float)の最大値もしくは最小値を超えました",
#endif
        "FLOATOVERFLOW",
    
    /* KMSG_INT64OVERFLOW */ 
        /* en */ "The given Int64 value was overflowed",
#ifdef KNH_USING_ICONV
        /* ja */ "64ビット整数の最大値もしくは最小値を超えました",
#endif
        "INT64OVERFLOW",
    
    /* KMSG_ETOOFEWPARAMS */ 
        /* en */ "This method needs more parameter(s)",
#ifdef KNH_USING_ICONV
        /* ja */ "与えられた引数の数が少な過ぎます",
#endif
        "ETOOFEWPARAMS",
    
    /* KMSG_WTOOMANYPARAMS */ 
        /* en */ "Some parameter(s) was overtaken",
#ifdef KNH_USING_ICONV
        /* ja */ "与えられた引数の数が多過ぎます",
#endif
        "WTOOMANYPARAMS",
    
    /* KMSG_EOP2 */ 
        /* en */ "This operator is always binary",
#ifdef KNH_USING_ICONV
        /* ja */ "この演算子は、2項演算子専用です",
#endif
        "EOP2",
    
    /* KMSG_EOPCMP */ 
        /* en */ "Comparison of different types might lead to an unexpected confusion",
#ifdef KNH_USING_ICONV
        /* ja */ "型が異なるため比較することはできません",
#endif
        "EOPCMP",
    
    /* KMSG_ENULLPARAM */ 
        /* en */ "Null!! always occurs at the given argument",
#ifdef KNH_USING_ICONV
        /* ja */ "次のメソッド引数で必ずNull例外が発生します",
#endif
        "ENULLPARAM",
    
    /* KMSG_WNULLPARAM */ 
        /* en */ "Null!! might occur at the given argument",
#ifdef KNH_USING_ICONV
        /* ja */ "次のメソッド引数においてNull例外が発生する可能性があります",
#endif
        "WNULLPARAM",
    
    /* KMSG_ETYPEPARAM */ 
        /* en */ "Incompatible type occurs at the given argument",
#ifdef KNH_USING_ICONV
        /* ja */ "次のメソッド引数の型が一致しません",
#endif
        "ETYPEPARAM",
    
    /* KMSG_ENULLRETURN */ 
        /* en */ "Null!! always occurs when returning",
#ifdef KNH_USING_ICONV
        /* ja */ "このメソッドではnullをreturnすることはできません",
#endif
        "ENULLRETURN",
    
    /* KMSG_WNULLRETURN */ 
        /* en */ "Null!! might occurs when returning",
#ifdef KNH_USING_ICONV
        /* ja */ "return時にNull例外が発生する可能性があります",
#endif
        "WNULLRETURN",
    
    /* KMSG_ETYPERETURN */ 
        /* en */ "Incompatible type occurs when returning",
#ifdef KNH_USING_ICONV
        /* ja */ "return文の型が一致しません",
#endif
        "ETYPERETURN",
    
    /* KMSG_ENULLLET */ 
        /* en */ "Don't assign null",
#ifdef KNH_USING_ICONV
        /* ja */ "Nullを代入することはできません",
#endif
        "ENULLLET",
    
    /* KMSG_ENULL */ 
        /* en */ "Don't use null",
#ifdef KNH_USING_ICONV
        /* ja */ "Nullは与えられません",
#endif
        "ENULL",
    
    /* KMSG_WNULLLET */ 
        /* en */ "Null!! might occur when assigning the variable",
#ifdef KNH_USING_ICONV
        /* ja */ "代入時にNull例外が発生する可能性があります",
#endif
        "WNULLLET",
    
    /* KMSG_WNULL */ 
        /* en */ "Null!! might occur",
#ifdef KNH_USING_ICONV
        /* ja */ "Null例外が発生する可能性があります",
#endif
        "WNULL",
    
    /* KMSG_ETYPELET */ 
        /* en */ "Imcompatible types occurs at the assignment",
#ifdef KNH_USING_ICONV
        /* ja */ "代入の右辺と左辺式の型が一致しません",
#endif
        "ETYPELET",
    
    /* KMSG_ETYPE */ 
        /* en */ "Imcompatible types occurs",
#ifdef KNH_USING_ICONV
        /* ja */ "型が一致しません",
#endif
        "ETYPE",
    
    /* KMSG_WDUPFUNCNAME */ 
        /* en */ "Naming conflict occurs between functions",
#ifdef KNH_USING_ICONV
        /* ja */ "スタティック関数名とメソッド名が重複しています",
#endif
        "WDUPFUNCNAME",
    
    /* KMSG_USCLASSFUNC */ 
        /* en */ "Naming conflict occurs between functions",
#ifdef KNH_USING_ICONV
        /* ja */ "与えられたクラスはクラス関数をサポートしていません",
#endif
        "USCLASSFUNC",
    
    /* KMSG_IGNNTYPE */ 
        /* en */ "NonNull attribute is ignored",
#ifdef KNH_USING_ICONV
        /* ja */ "NonNull属性は無視されました",
#endif
        "IGNNTYPE",
    
    /* KMSG_EEXTENDS */ 
        /* en */ "Extending @Final class is not allowed",
#ifdef KNH_USING_ICONV
        /* ja */ "finalクラスを拡張することはできません",
#endif
        "EEXTENDS",
    
    /* KMSG_EIMPLEMENTS */ 
        /* en */ "@Interface is required",
#ifdef KNH_USING_ICONV
        /* ja */ "インターフェースとして実装するためには、@Interfaceが必要です",
#endif
        "EIMPLEMENTS",
    
    /* KMSG_DIFFDECL */ 
        /* en */ "The type has been defined diffrently",
#ifdef KNH_USING_ICONV
        /* ja */ "既に別の型で宣言されています",
#endif
        "DIFFDECL",
    
    /* KMSG_DIFFCLASSN */ 
        /* en */ "The Class names are not identical",
#ifdef KNH_USING_ICONV
        /* ja */ "class 文のクラス名とメソッドのクラス名が異なります",
#endif
        "DIFFCLASSN",
    
    /* KMSG_DIFFNEWTYPE */ 
        /* en */ "The Class names are not identical",
#ifdef KNH_USING_ICONV
        /* ja */ "コンストラクタ(new メソッド）のクラスが異なります",
#endif
        "DIFFNEWTYPE",
    
    /* KMSG_DIFFRTYPE */ 
        /* en */ "Different returning type was given",
#ifdef KNH_USING_ICONV
        /* ja */ "既存のメソッドと戻り値の型が一致しません",
#endif
        "DIFFRTYPE",
    
    /* KMSG_DIFFPSIZE */ 
        /* en */ "The size of parameters was different",
#ifdef KNH_USING_ICONV
        /* ja */ "既存のメソッドと引数の数が一致しません",
#endif
        "DIFFPSIZE",
    
    /* KMSG_DIFFPTYPE */ 
        /* en */ "Different parameter type was given",
#ifdef KNH_USING_ICONV
        /* ja */ "既存のメソッドと引数の型が一致しません",
#endif
        "DIFFPTYPE",
    
    /* KMSG_DIFFPNAME */ 
        /* en */ "Different parameter name was given",
#ifdef KNH_USING_ICONV
        /* ja */ "既存のメソッドと引数名が異なります",
#endif
        "DIFFPNAME",
    
    /* KMSG_TOOMANYVARS */ 
        /* en */ "Sorry. You used much more variables than we expected",
#ifdef KNH_USING_ICONV
        /* ja */ "変数を多く宣言しすぎました",
#endif
        "TOOMANYVARS",
    
    /* KMSG_EOUTERLOOP */ 
        /* en */ "Ignored because of the outer loop",
#ifdef KNH_USING_ICONV
        /* ja */ "ループの内側でないため無視されます",
#endif
        "EOUTERLOOP",
    
    /* KMSG_IGFIELDVALUE */ 
        /* en */ "Only const value is allowed for initializing the field variable",
#ifdef KNH_USING_ICONV
        /* ja */ "フィールド変数の初期値は定数のみ認められます",
#endif
        "IGFIELDVALUE",
    
    /* KMSG_IGSCRIPTNAME */ 
        /* en */ "Don't declare a new script variable HERE",
#ifdef KNH_USING_ICONV
        /* ja */ "ここではスクリプト変数を新たに宣言することはできません",
#endif
        "IGSCRIPTNAME",
    
    /* KMSG_IGFIELDNAME */ 
        /* en */ "Don't declare a new field variable HERE",
#ifdef KNH_USING_ICONV
        /* ja */ "ここではフィールド変数を新たに宣言することはできません",
#endif
        "IGFIELDNAME",
    
    /* KMSG_NORETURN */ 
        /* en */ "You don't declare a new field variable HERE",
#ifdef KNH_USING_ICONV
        /* ja */ "return文がありません",
#endif
        "NORETURN",
    
    /* KMSG_NORETURNVALUE */ 
        /* en */ "return SOME value",
#ifdef KNH_USING_ICONV
        /* ja */ "return文に正しい戻り値を与えてください",
#endif
        "NORETURNVALUE",
    
    /* KMSG_IGRETURN */ 
        /* en */ "Returning value was ignored",
#ifdef KNH_USING_ICONV
        /* ja */ "return文のパラメータは無視されました",
#endif
        "IGRETURN",
    
    /* KMSG_AHISTORIC */ 
        /* en */ "Add @Historic, if you want to use this old-style statement",
#ifdef KNH_USING_ICONV
        /* ja */ "このステートメントを使用するためには@Historicが必要です",
#endif
        "AHISTORIC",
    
    /* KMSG_AOVERRIDE */ 
        /* en */ "Add @Override, if you will redefine/redeclare",
#ifdef KNH_USING_ICONV
        /* ja */ "再定義しなおすときは@Overrideが必要です",
#endif
        "AOVERRIDE",
    
    /* KMSG_EOVERRIDE */ 
        /* en */ "@Override is not allowed",
#ifdef KNH_USING_ICONV
        /* ja */ "オーバーライドは許可されていません",
#endif
        "EOVERRIDE",
    
    /* KMSG_TOABSTRACT */ 
        /* en */ "This method is abstract, because of cancelling compliation",
#ifdef KNH_USING_ICONV
        /* ja */ "コンパイルが中断されたため、抽象メソッドとして定義されました",
#endif
        "TOABSTRACT",
    
};

char *knh_message_text(int e)
{
    char *msg;
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    msg = knh_message_data[e * (KONOHA_LANG_MAXSIZ) + local_lang];
    if(msg != NULL) return msg;
    return knh_message_data[e * (KONOHA_LANG_MAXSIZ) + KONOHA_LANG__debug];
}

/* ------------------------------------------------------------------------ */

char *knh_message_tochar(int e)
{
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    return knh_message_data[e * (KONOHA_LANG_MAXSIZ) + KONOHA_LANG__debug];
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
