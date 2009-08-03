import os, sys

# ---------------------------------------------------------------------------

LINE = '''
/* ------------------------------------------------------------------------ */
'''

DLINE = '''
/* ======================================================================== */
'''

# ---------------------------------------------------------------------------

def write_println(f, msg = ''):
	f.write(msg+'\n')

def write_line(f):
	f.write(LINE)

def write_dline(f):
	f.write(DLINE)

def write_comment(f, msg):
	f.write('/* %s */\n' % msg)

def write_chapter(f, msg):
	f.write(DLINE)
	write_comment(f, msg)

def write_section(f, msg):
	f.write(LINE)
	write_comment(f, msg)

def write_define(f, name, value='', n=40):
	s = '#define %s ' % name
	while(len(s) < n) : s+=' '
	f.write(s)
	f.write(value)
	f.write('\n')

def write_ifndef(f, name, value='', n=40):
	f.write('#ifndef %s\n' % name)
	write_define(f, name, value, n)
	f.write('#endif\n')

def write_ifdef(f, n):
	f.write('''
#ifdef  %s''' % n.upper())

def write_else(f, n):
	f.write('''
#else /*%s*/
''' % n.upper())

def write_endif(f, n):
	f.write('''
#endif/*%s*/
''' % n.upper())

# ---------------------------------------------------------------------------

def write_license(f):
	f.write('''/****************************************************************************
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
''')

def write_begin_c(f):
	f.write('''
#ifdef __cplusplus 
extern "C" {
#endif
''')

def write_end_c(f):
	f.write('''
#ifdef __cplusplus
}
#endif
''')

# ---------------------------------------------------------------------------

def getdict(d, n, defv):
	if d.has_key(n): return d[n]
	return defv

def read_settings(fn):
	KNH_DATA = {}
	try:
		f = open(fn)
		exec(f)
		f.close()
		return KNH_DATA
	except OSError, e:
		print e
		return KNH_DATA

# ---------------------------------------------------------------------------

def nz_fname(fname):
	if fname.rfind('/') > 0: return fname[fname.rfind('/')+1:]
	return fname

def open_h(fname, lists):
	f = open(fname, 'w')
	write_license(f)
	d = nz_fname(fname).replace('.', '_'). upper()
	f.write('''
#ifndef %s
#define %s
''' % (d, d))

	for i in lists:
		f.write('''
#include%s''' % i)
	if len(lists) > 0: f.write('\n\n')
	write_begin_c(f)
	write_dline(f)
	return f

def open_h2(fname, lists):
	f = open(fname, 'w')
	write_license(f)
	d = nz_fname(fname).replace('.', '_'). upper()
	f.write('''
#ifndef %s
#define %s
''' % (d, d))

	for i in lists:
		f.write('''
#include%s''' % i)
	if len(lists) > 0: f.write('\n\n')
	return f

# ---------------------------------------------------------------------------

def close_h(f, fname):
	d = nz_fname(fname).replace('.', '_'). upper()
	write_end_c(f)
	write_dline(f)
	f.write('''
#endif/*%s*/
''' % d)
	f.close()

# ---------------------------------------------------------------------------

def open_c(fname, lists):
	f = open(fname, 'w')
	write_license(f)
	for i in lists:
		f.write('''
#include%s''' % i)
	if len(lists) > 0: f.write('\n\n')
	write_begin_c(f)
	write_dline(f)
	return f

def close_c(f, fname):
	write_end_c(f)
	f.close()

def get_serial_number():
	f = open('SERIAL_NUMBER')
	n = int(f.readline())
	f.close()
	n += 1
	f = open('SERIAL_NUMBER', 'w')
	f.write('%d\n' % n)
	f.close()
	return n

# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------

def parse_options(option):
	d = {}
	if option is None: return d
	for t in option.split():
		if t.find('(') > 0:
			t = t.replace('(', ' ').replace(')', '')
			t = t.split()
			d[t[0]] = t[1]
		else:
			d[t] = 1
	return d

# ---------------------------------------------------------------------------

def check_ifdef(d):
	ifdef = ''
	endif = ''
	if d.has_key('@ifdef'):
		ifdef = '#ifdef  KNH_IMPORT_%s_\n' % d['@ifdef']
		endif = '#endif/*KNH_IMPORT_%s_*/\n' %d['@ifdef']
	return ifdef, endif

# ---------------------------------------------------------------------------

def alias_lname(cname):
	if cname.find('_') > 0:
		return cname.split('_')[1]
	return cname

def STRUCT_cname(cname):
	return 'STRUCT_%s' % cname

def STRUCT_sname(cname):
	return 'STRUCT_%s' % cname

def SAFE_cname(t) :
	t = t.replace('..', '__')
	t = t.replace('!', '')
	t = t.replace('::', '__')
	t = t.replace(':', '__')
	return t	

def CLASS_cname(cname) :
	return 'CLASS_%s' % SAFE_cname(cname)

def TYPE_cname(t) :
	if t.endswith("!") :
		return CLASS_cname(t)
	return 'TYPE_%s' % SAFE_cname(t)

def DEBUG_cname(cname):
	return 'DEBUG_%s' % cname

def FIELDN_name(fn):
    return 'FIELDN_%s' % fn

def SAFE_mname(mname):
	return mname.replace('::', '__').replace(':', '__').replace('%', '_')

def METHODN_mname(mname):
    return 'METHODN_%s' % SAFE_mname(mname)

# ---------------------------------------------------------------------------

DEBUG = None

def debug_print(msg):
	if not DEBUG: print msg
	
def nz_dir(dir):
	if dir.endswith('/'): return dir[:len(dir)-1]
	return dir

# ---------------------------------------------------------------------------
## parser

def functype_filter(text):
	#text = text.replace('METHOD ', ' ').replace('', '').replace('_', '').replace('','')
	text = text.replace('', '').replace('_', '').replace('','')
	prev = ' '
	text2 = ''
	for c in text:
		if c == ' ' and prev == ' ':
			continue
		text2 += c
		prev = c
	if text2.endswith(' '): text2 = text2[:len(text2)-1]
	if text2.endswith('\t'): text2 = text2[:len(text2)-1]
	if not text2.endswith(')'):
		debug_print('Invalid functype: %s' % text2)
		return None
	return text2

def parse_functype(text):
	if text.find('@Private') > 0 : return None
	func = ''
	for ln in text.split('\n'):
		if ln.startswith('/') or ln.startswith('#'):
			continue
		if ln.find('{') >= 0:
			func += ' ' + ln.replace('{', '')
			return functype_filter(func)
		func += ' ' + ln
	return None

# ---------------------------------------------------------------------------

def parse_flag(pre, ln):
	loc = ln.find(']')
	if loc == -1: return '0'
	t = ln[:loc].split('[')
	pre = pre + '_'
	return (pre + t[1].replace('|', '|'+pre)).upper()

def nz_cparam(tn, vn):
	if vn.startswith('*'): return nz_cparam(tn+'*', vn[1:])
	return tn, vn

def parse_funcname(functype):
	if not functype.endswith(')'):
		debug_print('Invalid functype: %s' % functype)
	t = functype.replace('(', ' ').split()
	tn, funcname = nz_cparam(t[0], t[1])
	return funcname

def list_topair(list):
	t1 = list[0]
	t2 = list[1]
	return t1, t2, list[2:]

def parse_funcparams(functype):
	if not functype.endswith(')'):
		debug_print('Invalid functype: %s' % functype)
	t = functype.replace('(', ' ').replace(',', ' ').replace(')', '').split()
	params = []
	while len(t) > 1:
		tt, tn, t = list_topair(t)
		params.append(nz_cparam(tt, tn))
	return params

#------------------------------------------------------------------------------------

FUNCMAP = {}

def FUNCMAP_found(funcname):
	FUNCMAP[funcname] = funcname

def FUNCMAP_exists(funcname):
	return FUNCMAP.has_key(funcname)
