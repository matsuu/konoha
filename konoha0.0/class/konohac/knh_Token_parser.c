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

/* ************************************************************************ */

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [Bytes] */


knh_bool_t knh_Bytes_isTripleQuote(Bytes *b, knh_int_t ch)
{
	if(b->size > 2 && 
		b->value[b->size-1] == ch && 
		b->value[b->size-2] == ch &&
		b->value[b->size-3] == ch) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */
/* [Token] */

Token *new_Token__ch(Ctx *ctx, InputStream *in, int_byte_t ch)
{
	char buf[2] = {ch, 0};
	return new_Token__parse(ctx, 0, in->filen, in->line, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_Token_toMismatchedBlock(Ctx *ctx, Token *b, int_byte_t ch, InputStream *in)
{
	char buf[KONOHAC_ERROR_BUFSIZ];
	knh_snprintf(buf, KONOHAC_ERROR_BUFSIZ, "SyntaxError!!: Mismatched '%c'[%d]", (int)ch, (int)in->line);
	b->tt = TT_ERR;
	KNH_SETv(ctx, b->data, new_String__fast(ctx, CLASS_String, B(buf)));
}

/* ======================================================================== */
/* [parser] */

void knh_Token_padd(Ctx *ctx, Token *b, Token *tk)
{
	if(knh_Token_tokens_size(b) > 0) {
		Token *tkp = knh_Tokens(b, knh_Token_tokens_size(b)-1);
		if(tk->tt == TT_PARENTHESIS) {
			knh_Token_setNextParenthesis(tkp, 1);
		}
		if(tk->tt == TT_BRACE) {
			knh_Token_setNextBrace(tkp, 1);
		}
		if(tk->tt == TT_BRANCET) {
			if(knh_Token_isCLASSTN(tkp) && knh_Token_tokens_size(tk) == 0) {
				/* Class[] */ 
				DEBUG("Array!! %s[]", knh_Token_tochar(tkp));
				knh_Token_setArrayType(tkp, 1);
				KNH_LOPEN(ctx, 0);
				KNH_LPUSH(ctx, tk);
				KNH_LCLOSE(ctx);
				return ;
			}
			else {
				knh_Token_setNextBrancet(tkp, 1);
			}
		}
	}
	knh_Token_tokens_add(ctx, b, tk);
}

/* ------------------------------------------------------------------------ */

void knh_Token_padd__cb(Ctx *ctx, Token *b, knh_buffer_t cb, InputStream *in)
{
	knh_bytes_t t = knh_buffer_tobytes(cb);
	if(t.len == 0) {
		return ;
	}
	if(t.buf[0] == '.' && t.len == 1) {
		TODO();
		knh_buffer_clear(cb);
		return;
	}
	if(knh_Token_tokens_size(b) > 0) {
		Token *tkp = knh_Tokens(b, knh_Token_tokens_size(b)-1);
		if(knh_Token_isTYPEN(tkp)) {
			if(t.buf[0] == '.' && t.buf[1] == '.' && t.buf[2] == '\0') {
				knh_Token_setIteratorType(tkp, 1);
				knh_buffer_clear(cb);
				return;
			}
			if(t.buf[0] == '!' && t.buf[1] == '!' && t.buf[2] == '\0') {
				knh_Token_setExceptionType(tkp, 1);
				knh_buffer_clear(cb);
				return;
			}
			if(t.buf[0] == '!' && t.buf[2] == '\0') {
				knh_Token_setNotNullType(tkp, 1);
				knh_buffer_clear(cb);
				return;
			}
		}
	}
	knh_Token_padd(ctx, b, new_Token__parse(ctx, 0, in->filen, in->line, t));
	knh_buffer_clear(cb);
}

/* ------------------------------------------------------------------------ */

#define MODE_NUM   1
#define MODE_NAME  2
#define MODE_OP    3
#define MODE_PROPN 4

void knh_Token_parse(Ctx *ctx, Token *b, InputStream *in)
{
	knh_int_t ch, prev = '\n', quote, mode;
	knh_buffer_t cb = knh_Context_buffer(ctx);
	
	MAIN_PART:;
	mode = 0; prev = '\n';
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		MAIN_PART_INLOOP:;
		switch(ch) {
		case '"': case '\'': case '`' :
			knh_Token_padd__cb(ctx, b, cb, in);
			quote = ch;
			goto QUOTED_PART;
			break;
			
		case ' ': case '\t': case '\r':
		case '\n': case '\v':
			knh_Token_padd__cb(ctx, b, cb, in);
			mode = 0;
			break;
	
		case '{':
			if(b->tt == TT_PARENTHESIS) {
				MC_EPRINT(ctx, b, MC_INFO, "you probably forgot ')'");
			}	
		case '(': case '[':
			if(mode == MODE_NUM) {
				quote = ch;
				goto TAG_PART;
			} 
			knh_Token_padd__cb(ctx, b, cb, in);
			Token *tk = new_Token__ch(ctx, in, ch);
			knh_Token_parse(ctx, tk, in);
			knh_Token_padd(ctx, b, tk);
			mode = 0;
			break;

		case ')': 
			knh_Token_padd__cb(ctx, b, cb, in);
			if(b->tt != TT_PARENTHESIS) {
				knh_Token_toMismatchedBlock(ctx, b, ch, in);
			}
			return ;

		case '}':  
			knh_Token_padd__cb(ctx, b, cb, in);
			if(b->tt != TT_BRACE) {
				knh_Token_toMismatchedBlock(ctx, b, ch, in);
			}
			return ;

		case ']': 
			knh_Token_padd__cb(ctx, b, cb, in);
			if(b->tt != TT_BRANCET) {
				knh_Token_toMismatchedBlock(ctx, b, ch, in);
			}
			return ;

		case '$': 
			knh_Token_padd__cb(ctx, b, cb, in);
			knh_Bytes_putc(ctx, cb.ba, ch);
			mode = MODE_PROPN;
			break;
					
		case '@': case '%':
			knh_Token_padd__cb(ctx, b, cb, in);
			knh_Bytes_putc(ctx, cb.ba, ch);
			mode = MODE_NAME;
			break;
					
		case ',': case ';':
			knh_Token_padd__cb(ctx, b, cb, in);
			knh_Token_padd(ctx, b, new_Token__ch(ctx, in, ch));
			mode = 0;
			break;
			
		case ':': 
			if(mode == MODE_PROPN) {
				ch = knh_InputStream_getc(ctx, in); 
				if(ch == '/') {  /* URN */
					knh_Bytes_putc(ctx, cb.ba, ':');
					knh_Bytes_putc(ctx, cb.ba, '/');
					goto URN_PART;	
				}
				knh_Bytes_putc(ctx, cb.ba, ':');
				goto MAIN_PART_INLOOP;
			}
			if(mode == MODE_NAME) {
				ch = knh_InputStream_getc(ctx, in); 
				if(ch == ';') {
					knh_Bytes_putc(ctx, cb.ba, ':');
					goto MAIN_PART_INLOOP;
				}
				if(ch == '(' || ch == '[' || ch == ':') {   /* tag */
					quote = ch;
					goto TAG_PART;
				}
				if(ch == '/') {  /* URN */
					knh_Bytes_putc(ctx, cb.ba, ':');
					knh_Bytes_putc(ctx, cb.ba, '/');
					goto URN_PART;	
				}
				if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') { /* label */
					knh_Bytes_putc(ctx, cb.ba, ':');
					mode = 0; prev = ':';
					goto MAIN_PART_INLOOP;
				}
				if(ch == '+' || ch == '<') {
					knh_Token_padd__cb(ctx, b, cb, in);
					knh_Bytes_putc(ctx, cb.ba, ':');
					knh_Bytes_putc(ctx, cb.ba, ch);
					knh_Token_padd__cb(ctx, b, cb, in);
					mode = 0;
					break;					
				}
				/* separate 'a:b' ==> 'a : b' */
				knh_Token_padd__cb(ctx, b, cb, in);
				knh_Token_padd(ctx, b, new_Token__ch(ctx, in, ':'));
				mode = 0;
				goto MAIN_PART_INLOOP;
			}
			knh_Token_padd__cb(ctx, b, cb, in);
			knh_Token_padd(ctx, b, new_Token__ch(ctx, in, ':'));
			mode = 0; prev = ':';
			break;
		
		case '.':
			ch = knh_InputStream_getc(ctx, in); 
			if(ch == ';') {
				goto MAIN_PART_INLOOP;
			}
			if(ch == '*') {  /* class.* */
				knh_Bytes_putc(ctx, cb.ba, '.');
				knh_Bytes_putc(ctx, cb.ba, ch);
				knh_Token_padd__cb(ctx, b, cb, in);
				break;
			}
			if(ch != '.') {  /* a.b */
				knh_Bytes_putc(ctx, cb.ba, '.');
				goto MAIN_PART_INLOOP;
			}
			/* a..b ==> a .. b */
			knh_Token_padd__cb(ctx, b, cb, in);

			knh_Bytes_putc(ctx, cb.ba, '.');
			knh_Bytes_putc(ctx, cb.ba, '.');
			mode = MODE_OP; prev = '.';
			break; 

		case '#':
			knh_Token_padd__cb(ctx, b, cb, in);
			if(in->line == 1) {
				goto LINE_COMMENT;
			}
			knh_Token_padd(ctx, b, new_Token__ch(ctx, in, ch));
			mode = 0; break;

		case '*':
			if(mode == MODE_PROPN) {  /* $env.* */
				knh_Bytes_putc(ctx, cb.ba, ch);
				knh_Token_padd__cb(ctx, b, cb, in);
				mode = 0;
				break;
			}
		
		case '+': case '^': case '=': case '<': case '>': 
		case '&': case '~': case '?': case '!':
			if(mode != MODE_OP) {
				knh_Token_padd__cb(ctx, b, cb, in);
			}
			knh_Bytes_putc(ctx, cb.ba, ch);
			mode = MODE_OP;
			break;
		
		case '-':
			if(mode == MODE_OP) {
				if(prev != '-') {
					knh_Token_padd__cb(ctx, b, cb, in);
					mode = 0;
				}				
			}
			else {
				knh_Token_padd__cb(ctx, b, cb, in);
			}
			if(mode != 0) {
				knh_Bytes_putc(ctx, cb.ba, '-');
				mode = MODE_OP; break;
			}
			ch = knh_InputStream_getc(ctx, in); 
			if(isdigit(ch)) {
				knh_Bytes_putc(ctx, cb.ba, '-');
				knh_Bytes_putc(ctx, cb.ba, ch);
				mode = MODE_NUM;
				break;		
			}
			if(isalpha(ch) || ch == '_' || ch == '$' || ch == '%' 
				|| ch == '(' || ch == '[' || ch == '{' ) {
				knh_Token_padd(ctx, b, new_Token__ch(ctx, in, '_'));
				knh_Token_padd(ctx, b, new_Token__ch(ctx, in, '-'));
				mode = 0; prev = '-';
				goto MAIN_PART_INLOOP;
			}
			knh_Bytes_putc(ctx, cb.ba, '-');
			mode = MODE_OP; prev = '-';
			goto MAIN_PART_INLOOP;
				
		case '/':
			knh_Token_padd__cb(ctx, b, cb, in);
			ch = knh_InputStream_getc(ctx, in); 
			if(ch == '*') {
				goto BLOCK_COMMENT;
			}else if(ch == '/') {
				goto LINE_COMMENT;
			}
			knh_Bytes_putc(ctx, cb.ba, '/');
			mode = MODE_OP; prev = '/';
			goto MAIN_PART_INLOOP;
			break;

		case EOF :
			break;

		default:
			if(mode == MODE_OP) {
				knh_Token_padd__cb(ctx, b, cb, in);  /* spilit */
				mode = 0;
			}
			if(mode == 0 && (isalpha(ch) || ch == '_' || ch == '.')) {
				mode = MODE_NAME;
			}
			if(mode == 0 && isdigit(ch)) {
				mode = MODE_NUM;
			}
			knh_Bytes_putc(ctx, cb.ba, ch);
		} /* switch */
		prev = ch;
	}/* while */
	
	knh_Token_padd__cb(ctx, b, cb, in);
	return ;

	URN_PART:;
	mode = 0;
	quote = 1;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == '{' || ch == '[' || ch == '(') quote++;
		if(ch == '}' || ch == ']' || ch == ')') {
			quote--;
			if(quote == 0) {
				knh_Token_padd__cb(ctx, b, cb, in);
				goto MAIN_PART_INLOOP;
			}
		}
		if(ch == '\n' || ch == '\r' || ch == ' ' || ch == '\t' || ch == ';') {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
		prev = ch;
	}
	knh_Token_padd__cb(ctx, b, cb, in);
	return;

	/* -1(num) */
	TAG_PART:;
	KNH_ASSERT(quote == '[' || quote == '(' || quote == ':');
	if(mode != 0) {
		knh_Bytes_putc(ctx, cb.ba, ':');
		knh_Bytes_putc(ctx, cb.ba, ':');
	}
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == quote) {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		if(ch == ')' || ch == ']' || ch == '}') {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART_INLOOP;
		}
		if(ch == '\n' || ch == '\r' || ch == ';') {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		if(ch == ' ' || ch == '\t') {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
		prev = ch;
	}
	knh_Token_padd__cb(ctx, b, cb, in);
	return;

	/********************/

	/* 'email:java' */
		
	QUOTED_PART:;
	mode = 0;
	KNH_ASSERT(quote == '"' || quote == '\'' || quote == '`');
	ch = knh_InputStream_getc(ctx, in); 
	if(ch == quote) {
		ch = knh_InputStream_getc(ctx, in); 
		if(quote == ch) { /* triple quote */
			knh_Bytes_putc(ctx, cb.ba, ch);
			goto TRIPLE_QUOTED_PART;		
		}else {
			knh_Bytes_putc(ctx, cb.ba, '"');
			knh_Bytes_putc(ctx, cb.ba, '"');
			knh_Token_padd__cb(ctx, b, cb, in);
			mode = 0;
			goto MAIN_PART_INLOOP;
		}
	}
	else {
		knh_Bytes_putc(ctx, cb.ba, quote);			
		goto QUOTE_PART_INLOOP;
	}
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		QUOTE_PART_INLOOP:;
		knh_Bytes_putc(ctx, cb.ba, ch);
		if(ch == quote && prev != '\\') {
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}else if(ch == '\n' || ch == '\r') {
			knh_Bytes_putc(ctx, cb.ba, quote);
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		prev = ch;
	}
	knh_Bytes_putc(ctx, cb.ba, quote);
	knh_Token_padd__cb(ctx, b, cb, in);
	return;
	
	TRIPLE_QUOTED_PART:;
	mode = 0;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) { 
		if(ch == '\r') {
			continue;
		}
		if(ch == '\n') {
			if(knh_Bytes_size(cb.ba) - cb.pos == 1) continue;
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
		if(knh_Bytes_isTripleQuote(cb.ba, quote)) {
			knh_Bytes_unputc(cb.ba);
			knh_Bytes_unputc(cb.ba);
			knh_Token_padd__cb(ctx, b, cb, in);
			goto MAIN_PART;
		}
		prev = ch;
	}
	knh_Bytes_putc(ctx, cb.ba, quote);
	knh_Token_padd__cb(ctx, b, cb, in);
	return;

	LINE_COMMENT:
	mode = 0;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == '\r' || ch == '\n') {
			goto MAIN_PART;
		}
	}
	//knh_Token_padd__cb(ctx, b, cb, in);;
	return ;

	BLOCK_COMMENT:
	mode = 0;
	prev = ' '; quote = 1; 
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == '\r' || ch == '\n') {
		}
		if(prev == '*' && ch == '/') {
			quote--;
			if(quote == 0) goto MAIN_PART;
		}else if(prev == '/' && ch == '*') {
			quote++;
		}
		prev = ch;
	}
	//knh_Token_padd__cb(ctx, b, cb, in);;
	return ;			
}

/* ======================================================================== */

knh_bool_t knh_bytes_isLABEL(knh_bytes_t t)
{
	if((isalnum(t.buf[0]) || ismulti(t.buf[0])) && t.buf[t.len-1] == ':') {
		if(t.buf[t.len-2] != ':') return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isLABEL(Token *b)
{
    return(b->tt == TT_LABEL);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isMETAN(knh_bytes_t t)
{
	if(t.buf[0] != '@' || t.len == 1) return 0;
	knh_index_t i;
	for(i = 1; i < t.len; i++) {
		if(!isalnum(t.buf[i]) && t.buf[i] != '.') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isMETAN(Token *b)
{
	return(b->tt == TT_METAN);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isPROPN(knh_bytes_t t)
{
	if(t.buf[0] != '$' || t.len == 1) return 0;
	knh_index_t i;
	for(i = 1; i < t.len; i++) {
		if(isalnum(t.buf[i]) || t.buf[i] == '.' || t.buf[i] == '_') continue;
		if(t.buf[i] == ':' && t.buf[i+1] == ':') {
			i++;
			continue;
		}
		if(t.buf[i] == ':' && t.buf[i+1] == '/') {
			return 1; /* URN !! */
		}
		if(t.buf[i] == '*' && i == t.len - 1) break;
		return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isPROPN(Token *b)
{
    return(b->tt == TT_PROPN);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isMOVTEXT(knh_bytes_t t)
{
	if(t.buf[0] != '%' || t.len == 1) return 0;
	knh_index_t i;
	for(i = 1; i < t.len; i++) {
		if(isalnum(t.buf[i]) || t.buf[i] == '_' || t.buf[i] == '.') continue;
		if(t.buf[i] == ':' && t.buf[i+1] == ':') {
			i++;
			continue;
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isMOVTEXT(Token *b)
{
    return(b->tt == TT_MOVTEXT);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isURN(knh_bytes_t t)
{
	if(!isalpha(t.buf[0])) return 0;
	knh_index_t idx = knh_bytes_index(t, ':');
	if(idx > 0 && t.buf[idx+1] == '/') return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isURN(Token *b)
{
    return(b->tt == TT_URN);
}

///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_bytes_isCURN(knh_bytes_t t)
//{
//    if(knh_bytes_isCLASSPN(t)) return 1;
//    if(knh_bytes_isURN(t)) return 1;
//    return 0;
//}
//
///* ------------------------------------------------------------------------ */
//
//INLINE knh_bool_t knh_Token_isCURN(Token *b)
//{
//    return(knh_bytes_isCURN(knh_Token_tobytes(b)));
//}

/* ------------------------------------------------------------------------ */
/* [CLASS] */
/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isCLASSN(knh_bytes_t t)
{
	knh_index_t i;
	if(!isupper(t.buf[0])) return 0;
	for(i = 1; i < t.len; i++) {
		if(!isalnum(t.buf[i])) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isCLASSN(Token *b)
{
	return(b->tt == TT_TYPEN && knh_bytes_isCLASSN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isCONSTN(knh_bytes_t t)
{
	knh_index_t loc = knh_bytes_rindex(t, '.');
	if(loc == -1 || !knh_bytes_isCLASSN(knh_bytes_first(t, loc))) return 0;
	t = knh_bytes_last(t,loc+1);
	knh_index_t i;
	if(!isupper(t.buf[0])) return 0;
	for(i = 1; i < t.len; i++) {
		if(!isupper(t.buf[i]) && !isdigit(t.buf[i]) && t.buf[i] != '_') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isCONSTN(Token *b)
{
    return(b->tt == TT_CONSTN);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isCLASSTN(knh_bytes_t t)
{
	knh_index_t loc = knh_bytes_index(t, ':');
	if(loc == -1) {
		return knh_bytes_isCLASSN(t);
	}else {
		if(knh_bytes_isCLASSN(knh_bytes_first(t, loc)) && t.buf[loc+1] == ':') return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isCLASSTN(Token *b)
{
    return(b->tt == TT_TYPEN && knh_bytes_isCLASSTN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isTYPEN(knh_bytes_t t)
{
    if(t.len == 4 && t.buf[0] == 'v' && t.buf[1] == 'o' && t.buf[2] == 'i' && t.buf[3] == 'd') return 1;
    if(t.len == 3 && t.buf[0] == 'a' && t.buf[1] == 'n' && t.buf[2] == 'y') return 1;
    if(knh_bytes_isCLASSTN(t)) return 1;
    return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isTYPEN(Token *b)
{
    return(b->tt == TT_TYPEN && knh_bytes_isTYPEN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */
/* [NAME] */
/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isNSN(knh_bytes_t t)
{
	knh_index_t i;
	int bp = 1;
	for(i = 0; i < t.len; i++) {
		if(islower(t.buf[i])) {
			bp = 0; continue;
		}
		if(isdigit(t.buf[i]) && bp == 0) {
			continue;
		}
		if(t.buf[i] == '.' && bp == 0 && i < t.len -1) {
			bp = 1; continue;
		}
		return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isNSN(Token *b)
{
	return(b->tt == TT_NAME && knh_bytes_isNSN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isNSCLASSN(knh_bytes_t t)
{
	knh_index_t loc = knh_bytes_rindex(t, '.');
	if(loc == -1) {
		return knh_bytes_isCLASSN(t);
	}else {
		if(knh_bytes_isNSN(knh_bytes_first(t, loc))) {
			if(t.buf[loc+1] == '*' || knh_bytes_isCLASSN(knh_bytes_last(t,loc+1))) return 1;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isNSCLASSN(Token *b)
{
    return(b->tt == TT_NAME && knh_bytes_isNSCLASSN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isFIELDN(knh_bytes_t t)
{
	knh_index_t i = 0;
	while(t.buf[i] == '_') i++;
	if(i == t.len) return 1; /* __ */
	if(!islower(t.buf[i])) return 0;
	i++;
	for(; i < t.len; i++) {
		if(!isalnum(t.buf[i]) && t.buf[i] != '_') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isFIELDN(Token *b)
{
	return(b->tt == TT_NAME && knh_bytes_isFIELDN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isMETHODN(knh_bytes_t t)
{
	knh_index_t loc = knh_bytes_index(t, ':');
	if(loc == -1) {
		return knh_bytes_isFIELDN(t);
	} else {
		if(knh_bytes_isCLASSN(knh_bytes_first(t, loc)) && t.buf[loc+1] == ':') return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isMETHODN(Token *b)
{
    return(b->tt == TT_NAME && knh_bytes_isMETHODN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isCMETHODN(knh_bytes_t t)
{
    knh_index_t loc = knh_bytes_rindex(t, '.');
    if(loc == -1) {
        return knh_bytes_isMETHODN(t);
    }else {
        return (knh_bytes_isNSCLASSN(knh_bytes_first(t, loc)) 
            && knh_bytes_isMETHODN(knh_bytes_last(t,loc+1)));
    }
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isCMETHODN(Token *b)
{
    return(b->tt == TT_NAME && knh_bytes_isCMETHODN(knh_Token_tobytes(b)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isNAME(knh_bytes_t t)
{
	if(isalnum(t.buf[0]) || t.buf[0] == '_') return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isNAME(Token *b)
{
    return(b->tt == TT_NAME);
}

/* ======================================================================== */

knh_bool_t knh_bytes_isNEW(knh_bytes_t t)
{
	if(t.len == 3 && t.buf[0] == 'n' && t.buf[1] == 'e' && t.buf[2] == 'w') return 1;
	if(t.len > 5 && t.buf[0] == 'n' && t.buf[1] == 'e' && t.buf[2] == 'w' && t.buf[3] == ':' && t.buf[4] == ':') return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE knh_bool_t knh_Token_isNEW(Token *b)
{
    return(b->tt == TT_NAME && knh_bytes_isNEW(knh_Token_tobytes(b)));
}

/* ======================================================================== */
/* [OBJ] */

INLINE
knh_bool_t knh_bytes_isNUM(knh_bytes_t t)
{
	knh_int_t i, c = 0;
	if(!isdigit(t.buf[0]) && t.buf[0] != '-') return 0;
	for(i = 1; i < t.len; i++) {
		if(t.buf[i] == '.') {
			c++;
			if(c == 2) return 0;
			continue;
		}
		if(!isalnum(t.buf[i]) && t.buf[i] != '_') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_bytes_isSTR(knh_bytes_t t)
{
	return (t.len > 1 && t.buf[0] == '"');
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_bytes_isQSTR(knh_bytes_t t)
{
	return (t.len > 1 && t.buf[0] == '\'');
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_bytes_isFMTSTR(knh_bytes_t t)
{
	return (t.len > 1 && t.buf[0] == '`');
}

/* ======================================================================== */
/* [ANY] */

knh_bool_t knh_Token_isANY(Token *tk)
{
	return (IS_String(tk->data));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
