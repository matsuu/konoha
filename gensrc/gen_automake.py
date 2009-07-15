#!/usr/bin/python
import os, fnmatch
import itertools

#----------------------------------------------------#

MAKEFILE = "../build/Makefile.amz"

#----------------------------------------------------#

file_object = open(MAKEFILE, 'w')



def all_files(root, patterns='*', prefix = "libkonoha_la_SOURCES += " , yield_path=False):
	patterns = patterns.split(";");
	for path, subdirs, files in os.walk(root):
		if yield_path:
			yield "libkonoha_la_includedir = $(includedir)/" + path
			
		files.sort()
		for name in files:
			for pattern in patterns:
				if fnmatch.fnmatch(name, pattern) and not name.startswith('.'):
					yield prefix + os.path.join(path, name)
					break

def anyTrue(predicate, sequence):
	return True in itertools.imap(predicate, sequence)
def endsWith(s, *endings):
	return anyTrue(s.endswith, endings)


#---------------------------------------#
# script starts from here               #
#---------------------------------------#

file_object.writelines("""# this Makefile is generated from ../pygen/gen_Makefile.py
# shinpei@ynu(c)2008

# make target for libtool.
CFLAGS = -g3 -O3 -pipe
lib_LTLIBRARIES = libkonoha.la

libkonoha_la_LDFLAGS = -no-undefined -release 0 -version-info 5:0:0
#if LDL
#libkonoha_la_LDFLAGS += -ldl
#endif

AM_CPPFLAGS = -I../include
#if MINGW
#AM_CPPFLAGS += -DKONOHA_ON_MINGW
#endif
libkonoha_la_SOURCES = 
""")

#------------------------------------------#
# source parse for libkonoha               #
#------------------------------------------#

for path in all_files('../src', '*.c'):
	if endsWith(path, 'konoha.c'):
		print "skip konoha.c"
	else:
		file_object.writelines(path + "\n")

#------------------------------------------#
# header installing                        #
#------------------------------------------#

def all_headers(root, patterns="*"):
    for path, subdirs, files in os.walk(root):
        if (path.find(".svn") == -1): 
            if subdirs:
                for dir in subdirs:
                    if not dir.startswith("."):
                        yield "libkonoha_la_include" + dir + "dir = $(includedir)/" + os.path.join(path, dir)
                        yield "libkonoha_la_include" + dir + "_HEADERS = "
                        for i in listfiles(os.path.join(path, dir), patterns, prefix = "libkonoha_la_include" + dir + "_HEADERS += "):
                            yield i

def listfiles(root, pattern="*", prefix=""):
    files = os.listdir(root)
    for name in files:
        if fnmatch.fnmatch(name, pattern) and not name.startswith('.'):
            yield prefix + os.path.join(root, name)

file_object.writelines("""libkonoha_la_includedir = $(includedir)
libkonoha_la_include_HEADERS = ../include/konoha.h
""")

for i in all_headers("../include", "*.h"):
    file_object.writelines(i + "\n")

#file_object.writelines("libkonoha_la_include_HEADERS = \n");
#for path in all_files('../include', '*.h',"libkonoha_la_include_HEADERS += ", True):
#	file_object.writelines(path + "\n");

#-----------------------------------------#
# for dist script file for konoha         #
#-----------------------------------------#

def distfiles(root, pattern="*"):
  for path,sub,files in os.walk(root):
   if ( path.find(".svn") == -1 ):
    name = path.split("dist/")[1]
    yield name + "dir = " + "/usr/local/konoha/" + name
    yield "dist_" + name + "_SCRIPTS ="
    files.sort()
    for file in files:
      if fnmatch.fnmatch(file,pattern):
        yield "dist_" + name + "_SCRIPTS += "  + os.path.join(path,file)

for i in distfiles("../dist/sample","*.k"):
  file_object.writelines(i + "\n")

#-----------------------------------------#
# for klip                                #
#-----------------------------------------#
#
#def klipfiles(root, pattern="*"):
#  for path,sub,files in os.walk(root):
#   if ( path.find(".svn") == -1 ):
#    name = path.replace("../","")
#    name2 = name.replace("/","")
#    yield name2 + "dir = " + "/usr/local/konoha/" + name
#    yield "dist_" + name2 + "_SOURCES ="
#    files.sort()
#    for file in files:
#      if fnmatch.fnmatch(file,pattern):
#        yield "dist_" + name2 + "_SCRIPTS += "  + os.path.join(path,file)
#
#file_object.writelines( "scriptdir = /usr/local/konoha/script\n" )
#for i in klipfiles("../../script/klip"):
#  file_object.writelines( i + "\n" )

#-----------------------------------------#
# for executable file "konoha"            #
#-----------------------------------------#

file_object.writelines("""bin_PROGRAMS = konoha

konoha_SOURCES = ../src/konoha.c
konoha_INCLUDES = ../include
konoha_LDADD = libkonoha.la""")

file_object.close()


