CC=cl
LINK32=link.exe

# path to "konoha.lib"
KONOHA_LIB="konoha.lib"

LINK32DLL_FLAGS=\
 /nologo /dll /LTCG /incremental:no\
 /DEFAULTLIB:"libxml2.lib"\
 /machine:I386 /out:"libxml2_windows_32.dll"\
 /implib:"./libxml2_windows_32.lib"

.PHONY: all
all: libxml2_windows_32.dll

CFLAGS=\
  /nologo\
  /c /TP /Od /Oy /GL /W3\
  /D_WINDOWS\
  /I"..\..\konoha-0.5\windows\libxml2\include"\
  /I"..\..\konoha-0.5\windows\include"\
  /I"..\..\konoha-0.5\include"

xml.obj : "xml.c"
    $(CC) $(CFLAGS) /Fo"xml.obj" "xml.c"

xmlreader.obj : "xmlreader.c"
    $(CC) $(CFLAGS)  /Fo"xmlreader.obj" "xmlreader.c"

libxml2_windows_32.dll : xml.obj xmlreader.obj
    $(LINK32) $(LINK32DLL_FLAGS) $(KONOHA_LIB) xml.obj xmlreader.obj

.PHONY: clean
clean :
      -@erase /Q *.OBJ
