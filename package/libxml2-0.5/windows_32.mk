CC=cl
LINK32=link.exe

# path to "konoha.lib"
KONOHA_LIB="konoha.lib"

#path to konoha's include dir
KONOHA_INCLUDE="../include"

#path to libxml2's include dir
EXT_INCLUDE="./etx/include"

LINK32DLL_FLAGS=\
 /nologo /dll /LTCG /incremental:no\
 /DEFAULTLIB:"./libxml2.lib"\
 /machine:I386 /out:"libxml2_windows_32.dll"\
 /implib:"./libxml2_windows_32.lib"

.PHONY: all
all: libxml2_windows_32.dll

CFLAGS=\
  /nologo\
  /c /TP /Od /Oy /GL /W3\
  /D_WINDOWS\
  /I$(EXT_INCLUDE)\
  /I$(KONOHA_INCLUDE)\

xml.obj : "./src/xml.c"
    $(CC) $(CFLAGS) /Fo"xml.obj" "src/xml.c"

xmlreader.obj : "./src/xmlreader.c"
    $(CC) $(CFLAGS)  /Fo"xmlreader.obj" "src/xmlreader.c"

libxml2_windows_32.dll : xml.obj xmlreader.obj
    $(LINK32) $(LINK32DLL_FLAGS) $(KONOHA_LIB) xml.obj xmlreader.obj

.PHONY: clean
clean :
      -@erase /Q *.OBJ
