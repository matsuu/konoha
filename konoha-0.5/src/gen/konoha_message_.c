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

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

static int local_lang = 0;

/* ------------------------------------------------------------------------ */

static char* knh_system_lang[] = {
    "en", 
#ifdef KNH_USING_I18N
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

void knh_Asm_setLang(char *lang)
{
#ifdef KNH_USING_I18N
    local_lang = knh_system_langid(lang);
#endif
    //return local_lang;
}

/* ------------------------------------------------------------------------ */

static int knh_message_typedata[] = {
    /* KMSG_NAME */ 0,
    /* KMSG_LANG */ 0,
    /* KMSG_CLASS */ 0,
    /* KMSG_CONST */ 0,
    /* KMSG_OPERATOR */ 0,
    /* KMSG_METHOD */ 0,
    /* KMSG_FORMATTER */ 0,
    /* KMSG_MAPPING */ 0,
    /* KMSG_ERRATA */ 0,
    /* KMSG_ERROR */ 0,
    /* KMSG_WARNING */ 0,
    /* KMSG_INFO */ 0,
    /* KMSG_FMTERR */ 0,
    /* KMSG_UTOKEN */ 1,
    /* KMSG_WCHAR */ 2,
    /* KMSG_WLENGTH */ 2,
    /* KMSG_IGBLOCK */ 1,
    /* KMSG_EMISMATCH */ 1,
    /* KMSG_WASCII */ 2,
    /* KMSG_WEOF */ 2,
    /* KMSG_NOTHERE */ 1,
    /* KMSG_UUSING */ 1,
    /* KMSG_ESYNTAX */ 1,
    /* KMSG_EFUTURE */ 1,
    /* KMSG_WSEMICOLON */ 2,
    /* KMSG_TPATH */ 1,
    /* KMSG_TTYPEN */ 1,
    /* KMSG_TCLASSN */ 1,
    /* KMSG_TNAME */ 1,
    /* KMSG_TVARN */ 1,
    /* KMSG_WEMPTY */ 2,
    /* KMSG_CPREOP */ 2,
    /* KMSG_ENEXTPREV */ 1,
    /* KMSG_UOP */ 1,
    /* KMSG_UOP1 */ 1,
    /* KMSG_UOP2 */ 1,
    /* KMSG_UCONSTN */ 1,
    /* KMSG_UVARN */ 1,
    /* KMSG_USYSTEMVARN */ 1,
    /* KMSG_UCLASSN */ 1,
    /* KMSG_UTAG */ 1,
    /* KMSG_UTYPEN */ 1,
    /* KMSG_UMETHODN */ 1,
    /* KMSG_UNEW */ 1,
    /* KMSG_UMAP */ 1,
    /* KMSG_UPATH */ 1,
    /* KMSG_UPACKAGE */ 1,
    /* KMSG_DIFFDECL */ 2,
    /* KMSG_TOOMANYVARS */ 1,
    /* KMSG_WTRUEFALSE */ 2,
    /* KMSG_WNUMOVERFLOW */ 2,
    /* KMSG_FMTARGS */ 0,
    /* KMSG_ASSIGNMENT */ 0,
    /* KMSG_ETYPEFMT */ 1,
    /* KMSG_ENULLFMT */ 1,
    /* KMSG_IGFIELDVALUE */ 1,
    /* KMSG_IGQNAME */ 2,
    /* KMSG_NNCONST */ 1,
    /* KMSG_DUPCONST */ 1,
    /* KMSG_ELVALUE */ 1,
    /* KMSG_EBUILTINFUNC */ 1,
    /* KMSG_ETOOFEWPARAMS */ 1,
    /* KMSG_WTOOMANYPARAMS */ 2,
    /* KMSG_EOPCMP */ 1,
    /* KMSG_NORETURNVALUE */ 1,
    /* KMSG_IGRETURN */ 1,
    /* KMSG_DIFFCLASSN */ 2,
    /* KMSG_DIFFNEWTYPE */ 1,
    /* KMSG_DIFFRTYPE */ 1,
    /* KMSG_DIFFPSIZE */ 1,
    /* KMSG_DIFFPTYPE */ 1,
    /* KMSG_DIFFPNAME */ 2,
    /* KMSG_AOVERRIDE */ 2,
    /* KMSG_EOVERRIDE */ 1,
    /* KMSG_EEXTENDS */ 1,
    /* KMSG_EIMPLEMENTS */ 1,
    /* KMSG_EABORT */ 1,
    /* KMSG_ULABEL */ 1,
    /* KMSG_ETRY */ 1,
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
#ifdef KNH_USING_I18N
        /* ja */ "このは" ,

#endif
        "NAME",
    
    /* KMSG_LANG */ 
        /* en */ "English",
#ifdef KNH_USING_I18N
        /* ja */ "日本語" ,

#endif
        "LANG",
    
    /* KMSG_CLASS */ 
        /* en */ "CLASSNAME",
#ifdef KNH_USING_I18N
        /* ja */ "クラス" ,

#endif
        "CLASS",
    
    /* KMSG_CONST */ 
        /* en */ "CONST",
#ifdef KNH_USING_I18N
        /* ja */ "定数" ,

#endif
        "CONST",
    
    /* KMSG_OPERATOR */ 
        /* en */ "OPERATOR",
#ifdef KNH_USING_I18N
        /* ja */ "演算子" ,

#endif
        "OPERATOR",
    
    /* KMSG_METHOD */ 
        /* en */ "METHOD",
#ifdef KNH_USING_I18N
        /* ja */ "メソッド" ,

#endif
        "METHOD",
    
    /* KMSG_FORMATTER */ 
        /* en */ "FORMATTER",
#ifdef KNH_USING_I18N
        /* ja */ "フォーマッタ" ,

#endif
        "FORMATTER",
    
    /* KMSG_MAPPING */ 
        /* en */ "MAPPING",
#ifdef KNH_USING_I18N
        /* ja */ "マッピング" ,

#endif
        "MAPPING",
    
    /* KMSG_ERRATA */ 
        /* en */ "ERRATA",
#ifdef KNH_USING_I18N
        /* ja */ "訂正" ,

#endif
        "ERRATA",
    
    /* KMSG_ERROR */ 
        /* en */ "error",
#ifdef KNH_USING_I18N
        /* ja */ "エラー" ,

#endif
        "ERROR",
    
    /* KMSG_WARNING */ 
        /* en */ "warning",
#ifdef KNH_USING_I18N
        /* ja */ "警告" ,

#endif
        "WARNING",
    
    /* KMSG_INFO */ 
        /* en */ "info",
#ifdef KNH_USING_I18N
        /* ja */ "お知らせ" ,

#endif
        "INFO",
    
    /* KMSG_FMTERR */ 
        /* en */ "Source!!: Running error source at %s:%d",
#ifdef KNH_USING_I18N
        /* ja */ "Source!!: ファイル'%s'の%d行目のエラーを強制的に実行しました" ,

#endif
        "FMTERR",
    
    /* KMSG_UTOKEN */ 
        /* en */ "Syntax Error: undefined token",
#ifdef KNH_USING_I18N
        /* ja */ "未定義の字句を用いました" ,

#endif
        "UTOKEN",
    
    /* KMSG_WCHAR */ 
        /* en */ "You have used an illegal character. Ignoring the reminder.",
#ifdef KNH_USING_I18N
        /* ja */ "利用不可能な文字を用いたため、これ以降の文字は無視されました" ,

#endif
        "WCHAR",
    
    /* KMSG_WLENGTH */ 
        /* en */ "You will reduce the length of the name",
#ifdef KNH_USING_I18N
        /* ja */ "トークンが長過ぎるため、一部、省略しました" ,

#endif
        "WLENGTH",
    
    /* KMSG_IGBLOCK */ 
        /* en */ "Due to syntax error, this block was ignored",
#ifdef KNH_USING_I18N
        /* ja */ "パース不可能なシンタックスエラーのため、このブロックは無視されました" ,

#endif
        "IGBLOCK",
    
    /* KMSG_EMISMATCH */ 
        /* en */ "You have used a mismatched block/parenthesis",
#ifdef KNH_USING_I18N
        /* ja */ "括弧の対応をあわせてください" ,

#endif
        "EMISMATCH",
    
    /* KMSG_WASCII */ 
        /* en */ "Don't use non-ASCII characters",
#ifdef KNH_USING_I18N
        /* ja */ "ASCII文字（半角）をお使いください" ,

#endif
        "WASCII",
    
    /* KMSG_WEOF */ 
        /* en */ "You will close this file at a new line",
#ifdef KNH_USING_I18N
        /* ja */ "行の途中でファイルが終端しています" ,

#endif
        "WEOF",
    
    /* KMSG_NOTHERE */ 
        /* en */ "You are not able to use HERE",
#ifdef KNH_USING_I18N
        /* ja */ "ここでは使えません" ,

#endif
        "NOTHERE",
    
    /* KMSG_UUSING */ 
        /* en */ "You have used an unsupported using option",
#ifdef KNH_USING_I18N
        /* ja */ "サポート外のusingオプションが利用されました" ,

#endif
        "UUSING",
    
    /* KMSG_ESYNTAX */ 
        /* en */ "Syntax Error",
#ifdef KNH_USING_I18N
        /* ja */ "文法的な間違いがあります" ,

#endif
        "ESYNTAX",
    
    /* KMSG_EFUTURE */ 
        /* en */ "Syntax Error. This will be supported in the near future.",
#ifdef KNH_USING_I18N
        /* ja */ "将来、サポートの予定です。今のところ、使用はご控えください" ,

#endif
        "EFUTURE",
    
    /* KMSG_WSEMICOLON */ 
        /* en */ "Add ';' at the end of the statement",
#ifdef KNH_USING_I18N
        /* ja */ "文末にはセミコロン(;)を追加してください" ,

#endif
        "WSEMICOLON",
    
    /* KMSG_TPATH */ 
        /* en */ "Give a illegal path",
#ifdef KNH_USING_I18N
        /* ja */ "正しくパスをあたえてください" ,

#endif
        "TPATH",
    
    /* KMSG_TTYPEN */ 
        /* en */ "Give a type",
#ifdef KNH_USING_I18N
        /* ja */ "正しい型名を与えてください" ,

#endif
        "TTYPEN",
    
    /* KMSG_TCLASSN */ 
        /* en */ "Give the right Class name",
#ifdef KNH_USING_I18N
        /* ja */ "正しいクラス名を与えてください" ,

#endif
        "TCLASSN",
    
    /* KMSG_TNAME */ 
        /* en */ "Give a illegal name",
#ifdef KNH_USING_I18N
        /* ja */ "正しく名前をあたえてください" ,

#endif
        "TNAME",
    
    /* KMSG_TVARN */ 
        /* en */ "You have used an illegal variable",
#ifdef KNH_USING_I18N
        /* ja */ "変数名として利用できない名前を用いました" ,

#endif
        "TVARN",
    
    /* KMSG_WEMPTY */ 
        /* en */ "Is it really empty?",
#ifdef KNH_USING_I18N
        /* ja */ "空っぽです" ,

#endif
        "WEMPTY",
    
    /* KMSG_CPREOP */ 
        /* en */ "Unsupported this operator",
#ifdef KNH_USING_I18N
        /* ja */ "前置演算子は後置演算子として扱われます" ,

#endif
        "CPREOP",
    
    /* KMSG_ENEXTPREV */ 
        /* en */ "This expression dose not support ++/-- operators",
#ifdef KNH_USING_I18N
        /* ja */ "--演算,++演算が評価できない式です" ,

#endif
        "ENEXTPREV",
    
    /* KMSG_UOP */ 
        /* en */ "You have used an unsupported operator",
#ifdef KNH_USING_I18N
        /* ja */ "定義されていない演算子を用いました" ,

#endif
        "UOP",
    
    /* KMSG_UOP1 */ 
        /* en */ "This operator is unary",
#ifdef KNH_USING_I18N
        /* ja */ "この演算子は、単項演算子です" ,

#endif
        "UOP1",
    
    /* KMSG_UOP2 */ 
        /* en */ "This operator is binary",
#ifdef KNH_USING_I18N
        /* ja */ "この演算子は、２項演算子です" ,

#endif
        "UOP2",
    
    /* KMSG_UCONSTN */ 
        /* en */ "You have used an undefined CONST",
#ifdef KNH_USING_I18N
        /* ja */ "未定義の定数を使用しました" ,

#endif
        "UCONSTN",
    
    /* KMSG_UVARN */ 
        /* en */ "You have used an undefined variable",
#ifdef KNH_USING_I18N
        /* ja */ "未宣言の変数を使用しました" ,

#endif
        "UVARN",
    
    /* KMSG_USYSTEMVARN */ 
        /* en */ "You have used an undefined system variable",
#ifdef KNH_USING_I18N
        /* ja */ "未定義のシステム変数を使用しました" ,

#endif
        "USYSTEMVARN",
    
    /* KMSG_UCLASSN */ 
        /* en */ "You have used an undefined Class name",
#ifdef KNH_USING_I18N
        /* ja */ "未定義のクラス名を使用しました" ,

#endif
        "UCLASSN",
    
    /* KMSG_UTAG */ 
        /* en */ "You have used an undefined class tag",
#ifdef KNH_USING_I18N
        /* ja */ "未定義のクラスタグを使用しました" ,

#endif
        "UTAG",
    
    /* KMSG_UTYPEN */ 
        /* en */ "You have used an undefined type",
#ifdef KNH_USING_I18N
        /* ja */ "未定義の型を使用しました" ,

#endif
        "UTYPEN",
    
    /* KMSG_UMETHODN */ 
        /* en */ "You have used an undefined method",
#ifdef KNH_USING_I18N
        /* ja */ "定義されていないメソッドを使用しました" ,

#endif
        "UMETHODN",
    
    /* KMSG_UNEW */ 
        /* en */ "You have used an undefined constructor",
#ifdef KNH_USING_I18N
        /* ja */ "定義されていないコンストラクタを用いました" ,

#endif
        "UNEW",
    
    /* KMSG_UMAP */ 
        /* en */ "You have used an undefined mapping",
#ifdef KNH_USING_I18N
        /* ja */ "マッピングは定義されていません" ,

#endif
        "UMAP",
    
    /* KMSG_UPATH */ 
        /* en */ "Cannot open the specifed path",
#ifdef KNH_USING_I18N
        /* ja */ "指定されたパスが開けません" ,

#endif
        "UPATH",
    
    /* KMSG_UPACKAGE */ 
        /* en */ "Cannot import package",
#ifdef KNH_USING_I18N
        /* ja */ "パッケージのインポートを失敗しました" ,

#endif
        "UPACKAGE",
    
    /* KMSG_DIFFDECL */ 
        /* en */ "The type has been defined diffrently",
#ifdef KNH_USING_I18N
        /* ja */ "既に別の型で宣言されています" ,

#endif
        "DIFFDECL",
    
    /* KMSG_TOOMANYVARS */ 
        /* en */ "Sorry. You used much more variables than we expected",
#ifdef KNH_USING_I18N
        /* ja */ "変数を多く宣言しすぎました" ,

#endif
        "TOOMANYVARS",
    
    /* KMSG_WTRUEFALSE */ 
        /* en */ NULL,
#ifdef KNH_USING_I18N
        /* ja */ "Booleanの定数には、trueかfalseを用いましょう" ,

#endif
        "WTRUEFALSE",
    
    /* KMSG_WNUMOVERFLOW */ 
        /* en */ "The given number was overflowed",
#ifdef KNH_USING_I18N
        /* ja */ "数値の最大値もしくは最小値の範囲外です" ,

#endif
        "WNUMOVERFLOW",
    
    /* KMSG_FMTARGS */ 
        /* en */ "#%d",
#ifdef KNH_USING_I18N
        /* ja */ "第%d引数" ,

#endif
        "FMTARGS",
    
    /* KMSG_ASSIGNMENT */ 
        /* en */ "assignment",
#ifdef KNH_USING_I18N
        /* ja */ "代入" ,

#endif
        "ASSIGNMENT",
    
    /* KMSG_ETYPEFMT */ 
        /* en */ "Incompatible type occurs at %s",
#ifdef KNH_USING_I18N
        /* ja */ "%sにおいて型が一致しません" ,

#endif
        "ETYPEFMT",
    
    /* KMSG_ENULLFMT */ 
        /* en */ "Null exception will always throw at %s",
#ifdef KNH_USING_I18N
        /* ja */ "%sにおいてnullは利用できません" ,

#endif
        "ENULLFMT",
    
    /* KMSG_IGFIELDVALUE */ 
        /* en */ "Only const value is allowed for initializing the field variable",
#ifdef KNH_USING_I18N
        /* ja */ "フィールド変数の初期値は定数のみ認められます" ,

#endif
        "IGFIELDVALUE",
    
    /* KMSG_IGQNAME */ 
        /* en */ "The qualifier for variable was ignored",
#ifdef KNH_USING_I18N
        /* ja */ "変数の修飾子は無視されました" ,

#endif
        "IGQNAME",
    
    /* KMSG_NNCONST */ 
        /* en */ "Give the const value at the right hand",
#ifdef KNH_USING_I18N
        /* ja */ "左辺に定数を与えてください" ,

#endif
        "NNCONST",
    
    /* KMSG_DUPCONST */ 
        /* en */ "Cannot redefine the given CONST name",
#ifdef KNH_USING_I18N
        /* ja */ "同じ定数名で再定義することはできません" ,

#endif
        "DUPCONST",
    
    /* KMSG_ELVALUE */ 
        /* en */ "Invalid L-VALUE",
#ifdef KNH_USING_I18N
        /* ja */ "代入可能な変数名を与えてください" ,

#endif
        "ELVALUE",
    
    /* KMSG_EBUILTINFUNC */ 
        /* en */ "Invalid use of built-in function",
#ifdef KNH_USING_I18N
        /* ja */ "組み込み関数の用法が正しくありません" ,

#endif
        "EBUILTINFUNC",
    
    /* KMSG_ETOOFEWPARAMS */ 
        /* en */ "This method needs more parameter(s)",
#ifdef KNH_USING_I18N
        /* ja */ "与えられた引数の数が少な過ぎます" ,

#endif
        "ETOOFEWPARAMS",
    
    /* KMSG_WTOOMANYPARAMS */ 
        /* en */ "Some parameter(s) was overtaken",
#ifdef KNH_USING_I18N
        /* ja */ "与えられた引数の数が多過ぎます" ,

#endif
        "WTOOMANYPARAMS",
    
    /* KMSG_EOPCMP */ 
        /* en */ "Gosh!! Comparison of different types",
#ifdef KNH_USING_I18N
        /* ja */ "型が異なるため比較することはできません" ,

#endif
        "EOPCMP",
    
    /* KMSG_NORETURNVALUE */ 
        /* en */ "This will return a default value",
#ifdef KNH_USING_I18N
        /* ja */ "return文がないため、デフォルト値を返します" ,

#endif
        "NORETURNVALUE",
    
    /* KMSG_IGRETURN */ 
        /* en */ "Returning value was ignored",
#ifdef KNH_USING_I18N
        /* ja */ "return文の戻り値は無視されました" ,

#endif
        "IGRETURN",
    
    /* KMSG_DIFFCLASSN */ 
        /* en */ "The Class names are not identical",
#ifdef KNH_USING_I18N
        /* ja */ "class 文のクラス名とメソッドのクラス名が異なります" ,

#endif
        "DIFFCLASSN",
    
    /* KMSG_DIFFNEWTYPE */ 
        /* en */ "The Class names are not identical",
#ifdef KNH_USING_I18N
        /* ja */ "コンストラクタ(new メソッド）のクラスが異なります" ,

#endif
        "DIFFNEWTYPE",
    
    /* KMSG_DIFFRTYPE */ 
        /* en */ "Different returning type was given",
#ifdef KNH_USING_I18N
        /* ja */ "既存のメソッドと戻り値の型が一致しません" ,

#endif
        "DIFFRTYPE",
    
    /* KMSG_DIFFPSIZE */ 
        /* en */ "The size of parameters was different",
#ifdef KNH_USING_I18N
        /* ja */ "既存のメソッドと引数の数が一致しません" ,

#endif
        "DIFFPSIZE",
    
    /* KMSG_DIFFPTYPE */ 
        /* en */ "Different parameter type was given",
#ifdef KNH_USING_I18N
        /* ja */ "既存のメソッドと引数の型が一致しません" ,

#endif
        "DIFFPTYPE",
    
    /* KMSG_DIFFPNAME */ 
        /* en */ "Different parameter name was given",
#ifdef KNH_USING_I18N
        /* ja */ "既存のメソッドと引数名が異なります" ,

#endif
        "DIFFPNAME",
    
    /* KMSG_AOVERRIDE */ 
        /* en */ "Add @Override, if you will redefine/redeclare",
#ifdef KNH_USING_I18N
        /* ja */ "再定義しなおすときは@Overrideが必要です" ,

#endif
        "AOVERRIDE",
    
    /* KMSG_EOVERRIDE */ 
        /* en */ "@Override is not allowed",
#ifdef KNH_USING_I18N
        /* ja */ "オーバーライドは許可されていません" ,

#endif
        "EOVERRIDE",
    
    /* KMSG_EEXTENDS */ 
        /* en */ "Extending @Final class is not allowed",
#ifdef KNH_USING_I18N
        /* ja */ "finalクラスを拡張することはできません" ,

#endif
        "EEXTENDS",
    
    /* KMSG_EIMPLEMENTS */ 
        /* en */ "@Interface is required",
#ifdef KNH_USING_I18N
        /* ja */ "インターフェースとして実装するためには、@Interfaceが必要です" ,

#endif
        "EIMPLEMENTS",
    
    /* KMSG_EABORT */ 
        /* en */ "Syntax Error. Otherwise, you'll find some compiler bugs.",
#ifdef KNH_USING_I18N
        /* ja */ "文法的な間違いがあります（もしくは、コンパイラのバグかも知れません）" ,

#endif
        "EABORT",
    
    /* KMSG_ULABEL */ 
        /* en */ "You have used an undefined label",
#ifdef KNH_USING_I18N
        /* ja */ "未定義のラベルを用いました" ,

#endif
        "ULABEL",
    
    /* KMSG_ETRY */ 
        /* en */ "Don't use nested try clause",
#ifdef KNH_USING_I18N
        /* ja */ "try 節はネストして使うことはできません" ,

#endif
        "ETRY",
    
    /* KMSG_TOABSTRACT */ 
        /* en */ "This method is abstract, because of cancelling compliation",
#ifdef KNH_USING_I18N
        /* ja */ "コンパイルが中断されたため、抽象メソッドとして定義されました" ,

#endif
        "TOABSTRACT",
    
};

/* ------------------------------------------------------------------------ */


#ifndef KNH_USING_I18N
#undef KONOHA_LANG_MAXSIZ
#define KONOHA_LANG_MAXSIZ 2
#endif


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
