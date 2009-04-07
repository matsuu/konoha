#Makefiile by gen_konoha.py
KONOHA=konoha
OUTDIR=.
LINK32=link.exe
DISTDIR="\Konoha"
BINDIR="\Konoha\bin"

ALL : $(OUTDIR)\$(KONOHA).dll $(OUTDIR)\$(KONOHA).exe

CLEAN :
	-@erase /Q $(OUTDIR)\*.OBJ

$(OUTDIR) :
	if not exist $(OUTDIR)/$(NULL) mkdir $(OUTDIR)

$(DISTDIR) :
	if not exist $(DISTDIR)/$(NULL) mkdir $(DISTDIR)

INSTALL : $(DISTDIR)
	-@erace /Q $(DISTDIR)\*
	if not exist $(DISTDIR)\bin\$(NULL) mkdir $(DISTDIR)\bin
	if not exist $(DISTDIR)\lib\$(NULL) mkdir $(DISTDIR)\lib
	if not exist $(DISTDIR)\package\$(NULL) mkdir $(DISTDIR)\package
	copy "$(OUTDIR)\konoha.exe" "$(DISTDIR)\bin\konoha.exe"
	copy "$(OUTDIR)\konoha.dll" "$(DISTDIR)\bin\konoha.dll"
	copy "$(OUTDIR)\ext\*.dll" "$(DISTDIR)\bin\"
	copy "$(OUTDIR)\konoha.lib" "$(DISTDIR)\lib\konoha.lib"
	copy "$(OUTDIR)\ext\iconv.lib" "$(DISTDIR)\lib\iconv.lib"
	if not exist $(DISTDIR)\package\math mkdir $(DISTDIR)\package\math
	if exist $(OUTDIR)\libknhmath.dll copy $(OUTDIR)\libknhmath.dll $(DISTDIR)\package\math\libknhmath.dll
	
CFLAGS=\
	/nologo\
	/c /TP /O2 /GL /W3\
	/DKNH_USING_ICONV\
	/I"..\include" /I".\include"

CFLAGSD=\
	/nologo\
	/c /O2 /W3 /MD\
	/Fd"$(OUTDIR)\$(KONOHA).pdb"\
	/TP\
	/Zi\
	/D_WINDOWS /DLIBICONV_PLUG /DKNH_USING_ICONV\
	/I"..\include" /I".\include"

LINK32DLL_FLAGS=\
 /nologo /dll /LTCG /incremental:no /DEFAULTLIB:"ext\iconv.lib"\
 /pdb:"$(OUTDIR)\$(KONOHA).pdb" /machine:I386 /out:"$(OUTDIR)\$(KONOHA).dll"\
 /implib:"$(OUTDIR)\$(KONOHA).lib"

LINK32_FLAGS=konoha.lib\
 /nologo /LTCG /subsystem:console /incremental:no\
 /out:"$(OUTDIR)\$(KONOHA).exe"


LINK32DLL_OBJS = \
	$(OUTDIR)\anyapi.obj\
	$(OUTDIR)\arrayapi.obj\
	$(OUTDIR)\bytes.obj\
	$(OUTDIR)\dictapi.obj\
	$(OUTDIR)\exception.obj\
	$(OUTDIR)\hashapi.obj\
	$(OUTDIR)\iterator.obj\
	$(OUTDIR)\kdbcapi.obj\
	$(OUTDIR)\numberapi.obj\
	$(OUTDIR)\objectapi.obj\
	$(OUTDIR)\streamapi.obj\
	$(OUTDIR)\stringapi.obj\
	$(OUTDIR)\systemapi.obj\
	$(OUTDIR)\knh_AffineConv.obj\
	$(OUTDIR)\knh_Array.obj\
	$(OUTDIR)\knh_array_t.obj\
	$(OUTDIR)\knh_Bytes.obj\
	$(OUTDIR)\knh_BytesConv.obj\
	$(OUTDIR)\knh_bytes_t.obj\
	$(OUTDIR)\knh_Class.obj\
	$(OUTDIR)\knh_Class_type_t.obj\
	$(OUTDIR)\knh_Closure.obj\
	$(OUTDIR)\knh_Connection.obj\
	$(OUTDIR)\knh_Context.obj\
	$(OUTDIR)\knh_Context_wbuf.obj\
	$(OUTDIR)\knh_DictIdx.obj\
	$(OUTDIR)\knh_DictMapSet.obj\
	$(OUTDIR)\knh_Exception.obj\
	$(OUTDIR)\knh_ExceptionHandler.obj\
	$(OUTDIR)\knh_Float.obj\
	$(OUTDIR)\knh_HashMap.obj\
	$(OUTDIR)\knh_HashSet.obj\
	$(OUTDIR)\knh_InputStream.obj\
	$(OUTDIR)\knh_Int.obj\
	$(OUTDIR)\knh_IntUnit.obj\
	$(OUTDIR)\knh_Iterator.obj\
	$(OUTDIR)\knh_LRUHashMap.obj\
	$(OUTDIR)\knh_Mapper.obj\
	$(OUTDIR)\knh_Method.obj\
	$(OUTDIR)\knh_NameSpace.obj\
	$(OUTDIR)\knh_Number.obj\
	$(OUTDIR)\knh_Object.obj\
	$(OUTDIR)\knh_OutputStream.obj\
	$(OUTDIR)\knh_OutputStream_write.obj\
	$(OUTDIR)\knh_Range.obj\
	$(OUTDIR)\knh_Regex.obj\
	$(OUTDIR)\knh_ResultSet.obj\
	$(OUTDIR)\knh_Runtime.obj\
	$(OUTDIR)\knh_Script.obj\
	$(OUTDIR)\knh_String.obj\
	$(OUTDIR)\knh_StringParser.obj\
	$(OUTDIR)\knh_StringUnit.obj\
	$(OUTDIR)\knh_String_mbytes.obj\
	$(OUTDIR)\knh_System.obj\
	$(OUTDIR)\knh_Tuple2.obj\
	$(OUTDIR)\OLD1.obj\
	$(OUTDIR)\OLD2.obj\
	$(OUTDIR)\OLD3.obj\
	$(OUTDIR)\OLD4.obj\
	$(OUTDIR)\asm.obj\
	$(OUTDIR)\kcode.obj\
	$(OUTDIR)\konohac.obj\
	$(OUTDIR)\parser.obj\
	$(OUTDIR)\perror.obj\
	$(OUTDIR)\stmt.obj\
	$(OUTDIR)\token.obj\
	$(OUTDIR)\tokenizer.obj\
	$(OUTDIR)\typing.obj\
	$(OUTDIR)\driver_db.obj\
	$(OUTDIR)\driver_io.obj\
	$(OUTDIR)\driver_regex.obj\
	$(OUTDIR)\posix.obj\
	$(OUTDIR)\tbmx1.obj\
	$(OUTDIR)\win32.obj\
	$(OUTDIR)\mt19937-64.obj\
	$(OUTDIR)\mt19937ar.obj\
	$(OUTDIR)\codetemplate.obj\
	$(OUTDIR)\konohac_.obj\
	$(OUTDIR)\konoha_klr_.obj\
	$(OUTDIR)\konoha_message_.obj\
	$(OUTDIR)\method_.obj\
	$(OUTDIR)\knh_tClass.obj\
	$(OUTDIR)\knh_tConst.obj\
	$(OUTDIR)\knh_tExpt.obj\
	$(OUTDIR)\knh_tMapper.obj\
	$(OUTDIR)\knh_tMethod.obj\
	$(OUTDIR)\knh_tName.obj\
	$(OUTDIR)\knh_tPackage.obj\
	$(OUTDIR)\konoha_api.obj\
	$(OUTDIR)\konoha_data.obj\
	$(OUTDIR)\konoha_ext.obj\
	$(OUTDIR)\konoha_file.obj\
	$(OUTDIR)\konoha_init.obj\
	$(OUTDIR)\konoha_libknh.obj\
	$(OUTDIR)\konoha_locale.obj\
	$(OUTDIR)\konoha_memory.obj\
	$(OUTDIR)\konoha_metadata.obj\
	$(OUTDIR)\konoha_mutex.obj\
	$(OUTDIR)\konoha_pkgapi.obj\
	$(OUTDIR)\konoha_print.obj\
	$(OUTDIR)\konoha_shell.obj\
	$(OUTDIR)\konoha_stack.obj\
	$(OUTDIR)\konoha_table.obj\
	$(OUTDIR)\konoha_typesystem.obj

$(OUTDIR)\anyapi.obj : "..\src\api\anyapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\anyapi.obj" "..\src\api\anyapi.c" 


$(OUTDIR)\arrayapi.obj : "..\src\api\arrayapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\arrayapi.obj" "..\src\api\arrayapi.c" 


$(OUTDIR)\bytes.obj : "..\src\api\bytes.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\bytes.obj" "..\src\api\bytes.c" 


$(OUTDIR)\dictapi.obj : "..\src\api\dictapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\dictapi.obj" "..\src\api\dictapi.c" 


$(OUTDIR)\exception.obj : "..\src\api\exception.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\exception.obj" "..\src\api\exception.c" 


$(OUTDIR)\hashapi.obj : "..\src\api\hashapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\hashapi.obj" "..\src\api\hashapi.c" 


$(OUTDIR)\iterator.obj : "..\src\api\iterator.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\iterator.obj" "..\src\api\iterator.c" 


$(OUTDIR)\kdbcapi.obj : "..\src\api\kdbcapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\kdbcapi.obj" "..\src\api\kdbcapi.c" 


$(OUTDIR)\numberapi.obj : "..\src\api\numberapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\numberapi.obj" "..\src\api\numberapi.c" 


$(OUTDIR)\objectapi.obj : "..\src\api\objectapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\objectapi.obj" "..\src\api\objectapi.c" 


$(OUTDIR)\streamapi.obj : "..\src\api\streamapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\streamapi.obj" "..\src\api\streamapi.c" 


$(OUTDIR)\stringapi.obj : "..\src\api\stringapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\stringapi.obj" "..\src\api\stringapi.c" 


$(OUTDIR)\systemapi.obj : "..\src\api\systemapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\systemapi.obj" "..\src\api\systemapi.c" 


$(OUTDIR)\knh_AffineConv.obj : "..\src\class\knh_AffineConv.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_AffineConv.obj" "..\src\class\knh_AffineConv.c" 


$(OUTDIR)\knh_Array.obj : "..\src\class\knh_Array.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Array.obj" "..\src\class\knh_Array.c" 


$(OUTDIR)\knh_array_t.obj : "..\src\class\knh_array_t.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_array_t.obj" "..\src\class\knh_array_t.c" 


$(OUTDIR)\knh_Bytes.obj : "..\src\class\knh_Bytes.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Bytes.obj" "..\src\class\knh_Bytes.c" 


$(OUTDIR)\knh_BytesConv.obj : "..\src\class\knh_BytesConv.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_BytesConv.obj" "..\src\class\knh_BytesConv.c" 


$(OUTDIR)\knh_bytes_t.obj : "..\src\class\knh_bytes_t.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_bytes_t.obj" "..\src\class\knh_bytes_t.c" 


$(OUTDIR)\knh_Class.obj : "..\src\class\knh_Class.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Class.obj" "..\src\class\knh_Class.c" 


$(OUTDIR)\knh_Class_type_t.obj : "..\src\class\knh_Class_type_t.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Class_type_t.obj" "..\src\class\knh_Class_type_t.c" 


$(OUTDIR)\knh_Closure.obj : "..\src\class\knh_Closure.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Closure.obj" "..\src\class\knh_Closure.c" 


$(OUTDIR)\knh_Connection.obj : "..\src\class\knh_Connection.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Connection.obj" "..\src\class\knh_Connection.c" 


$(OUTDIR)\knh_Context.obj : "..\src\class\knh_Context.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Context.obj" "..\src\class\knh_Context.c" 


$(OUTDIR)\knh_Context_wbuf.obj : "..\src\class\knh_Context_wbuf.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Context_wbuf.obj" "..\src\class\knh_Context_wbuf.c" 


$(OUTDIR)\knh_DictIdx.obj : "..\src\class\knh_DictIdx.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_DictIdx.obj" "..\src\class\knh_DictIdx.c" 


$(OUTDIR)\knh_DictMapSet.obj : "..\src\class\knh_DictMapSet.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_DictMapSet.obj" "..\src\class\knh_DictMapSet.c" 


$(OUTDIR)\knh_Exception.obj : "..\src\class\knh_Exception.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Exception.obj" "..\src\class\knh_Exception.c" 


$(OUTDIR)\knh_ExceptionHandler.obj : "..\src\class\knh_ExceptionHandler.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_ExceptionHandler.obj" "..\src\class\knh_ExceptionHandler.c" 


$(OUTDIR)\knh_Float.obj : "..\src\class\knh_Float.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Float.obj" "..\src\class\knh_Float.c" 


$(OUTDIR)\knh_HashMap.obj : "..\src\class\knh_HashMap.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_HashMap.obj" "..\src\class\knh_HashMap.c" 


$(OUTDIR)\knh_HashSet.obj : "..\src\class\knh_HashSet.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_HashSet.obj" "..\src\class\knh_HashSet.c" 


$(OUTDIR)\knh_InputStream.obj : "..\src\class\knh_InputStream.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_InputStream.obj" "..\src\class\knh_InputStream.c" 


$(OUTDIR)\knh_Int.obj : "..\src\class\knh_Int.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Int.obj" "..\src\class\knh_Int.c" 


$(OUTDIR)\knh_IntUnit.obj : "..\src\class\knh_IntUnit.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_IntUnit.obj" "..\src\class\knh_IntUnit.c" 


$(OUTDIR)\knh_Iterator.obj : "..\src\class\knh_Iterator.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Iterator.obj" "..\src\class\knh_Iterator.c" 


$(OUTDIR)\knh_LRUHashMap.obj : "..\src\class\knh_LRUHashMap.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_LRUHashMap.obj" "..\src\class\knh_LRUHashMap.c" 


$(OUTDIR)\knh_Mapper.obj : "..\src\class\knh_Mapper.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Mapper.obj" "..\src\class\knh_Mapper.c" 


$(OUTDIR)\knh_Method.obj : "..\src\class\knh_Method.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Method.obj" "..\src\class\knh_Method.c" 


$(OUTDIR)\knh_NameSpace.obj : "..\src\class\knh_NameSpace.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_NameSpace.obj" "..\src\class\knh_NameSpace.c" 


$(OUTDIR)\knh_Number.obj : "..\src\class\knh_Number.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Number.obj" "..\src\class\knh_Number.c" 


$(OUTDIR)\knh_Object.obj : "..\src\class\knh_Object.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Object.obj" "..\src\class\knh_Object.c" 


$(OUTDIR)\knh_OutputStream.obj : "..\src\class\knh_OutputStream.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_OutputStream.obj" "..\src\class\knh_OutputStream.c" 


$(OUTDIR)\knh_OutputStream_write.obj : "..\src\class\knh_OutputStream_write.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_OutputStream_write.obj" "..\src\class\knh_OutputStream_write.c" 


$(OUTDIR)\knh_Range.obj : "..\src\class\knh_Range.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Range.obj" "..\src\class\knh_Range.c" 


$(OUTDIR)\knh_Regex.obj : "..\src\class\knh_Regex.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Regex.obj" "..\src\class\knh_Regex.c" 


$(OUTDIR)\knh_ResultSet.obj : "..\src\class\knh_ResultSet.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_ResultSet.obj" "..\src\class\knh_ResultSet.c" 


$(OUTDIR)\knh_Runtime.obj : "..\src\class\knh_Runtime.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Runtime.obj" "..\src\class\knh_Runtime.c" 


$(OUTDIR)\knh_Script.obj : "..\src\class\knh_Script.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Script.obj" "..\src\class\knh_Script.c" 


$(OUTDIR)\knh_String.obj : "..\src\class\knh_String.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_String.obj" "..\src\class\knh_String.c" 


$(OUTDIR)\knh_StringParser.obj : "..\src\class\knh_StringParser.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_StringParser.obj" "..\src\class\knh_StringParser.c" 


$(OUTDIR)\knh_StringUnit.obj : "..\src\class\knh_StringUnit.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_StringUnit.obj" "..\src\class\knh_StringUnit.c" 


$(OUTDIR)\knh_String_mbytes.obj : "..\src\class\knh_String_mbytes.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_String_mbytes.obj" "..\src\class\knh_String_mbytes.c" 


$(OUTDIR)\knh_System.obj : "..\src\class\knh_System.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_System.obj" "..\src\class\knh_System.c" 


$(OUTDIR)\knh_Tuple2.obj : "..\src\class\knh_Tuple2.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Tuple2.obj" "..\src\class\knh_Tuple2.c" 


$(OUTDIR)\OLD1.obj : "..\src\class\OLD1.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\OLD1.obj" "..\src\class\OLD1.c" 


$(OUTDIR)\OLD2.obj : "..\src\class\OLD2.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\OLD2.obj" "..\src\class\OLD2.c" 


$(OUTDIR)\OLD3.obj : "..\src\class\OLD3.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\OLD3.obj" "..\src\class\OLD3.c" 


$(OUTDIR)\OLD4.obj : "..\src\class\OLD4.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\OLD4.obj" "..\src\class\OLD4.c" 


$(OUTDIR)\asm.obj : "..\src\compiler\asm.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\asm.obj" "..\src\compiler\asm.c" 


$(OUTDIR)\kcode.obj : "..\src\compiler\kcode.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\kcode.obj" "..\src\compiler\kcode.c" 


$(OUTDIR)\konohac.obj : "..\src\compiler\konohac.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konohac.obj" "..\src\compiler\konohac.c" 


$(OUTDIR)\parser.obj : "..\src\compiler\parser.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\parser.obj" "..\src\compiler\parser.c" 


$(OUTDIR)\perror.obj : "..\src\compiler\perror.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\perror.obj" "..\src\compiler\perror.c" 


$(OUTDIR)\stmt.obj : "..\src\compiler\stmt.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\stmt.obj" "..\src\compiler\stmt.c" 


$(OUTDIR)\token.obj : "..\src\compiler\token.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\token.obj" "..\src\compiler\token.c" 


$(OUTDIR)\tokenizer.obj : "..\src\compiler\tokenizer.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\tokenizer.obj" "..\src\compiler\tokenizer.c" 


$(OUTDIR)\typing.obj : "..\src\compiler\typing.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\typing.obj" "..\src\compiler\typing.c" 


$(OUTDIR)\driver_db.obj : "..\src\deps\driver_db.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\driver_db.obj" "..\src\deps\driver_db.c" 


$(OUTDIR)\driver_io.obj : "..\src\deps\driver_io.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\driver_io.obj" "..\src\deps\driver_io.c" 


$(OUTDIR)\driver_regex.obj : "..\src\deps\driver_regex.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\driver_regex.obj" "..\src\deps\driver_regex.c" 


$(OUTDIR)\posix.obj : "..\src\deps\posix.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\posix.obj" "..\src\deps\posix.c" 


$(OUTDIR)\tbmx1.obj : "..\src\deps\tbmx1.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\tbmx1.obj" "..\src\deps\tbmx1.c" 


$(OUTDIR)\win32.obj : "..\src\deps\win32.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\win32.obj" "..\src\deps\win32.c" 


$(OUTDIR)\mt19937-64.obj : "..\src\ext\mt19937-64.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\mt19937-64.obj" "..\src\ext\mt19937-64.c" 


$(OUTDIR)\mt19937ar.obj : "..\src\ext\mt19937ar.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\mt19937ar.obj" "..\src\ext\mt19937ar.c" 


$(OUTDIR)\codetemplate.obj : "..\src\gen\codetemplate.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\codetemplate.obj" "..\src\gen\codetemplate.c" 


$(OUTDIR)\konohac_.obj : "..\src\gen\konohac_.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konohac_.obj" "..\src\gen\konohac_.c" 


$(OUTDIR)\konoha_klr_.obj : "..\src\gen\konoha_klr_.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_klr_.obj" "..\src\gen\konoha_klr_.c" 


$(OUTDIR)\konoha_message_.obj : "..\src\gen\konoha_message_.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_message_.obj" "..\src\gen\konoha_message_.c" 


$(OUTDIR)\method_.obj : "..\src\gen\method_.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\method_.obj" "..\src\gen\method_.c" 


$(OUTDIR)\konoha.obj : "..\src\konoha.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha.obj" "..\src\konoha.c" 


$(OUTDIR)\knh_tClass.obj : "..\src\main\knh_tClass.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tClass.obj" "..\src\main\knh_tClass.c" 


$(OUTDIR)\knh_tConst.obj : "..\src\main\knh_tConst.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tConst.obj" "..\src\main\knh_tConst.c" 


$(OUTDIR)\knh_tExpt.obj : "..\src\main\knh_tExpt.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tExpt.obj" "..\src\main\knh_tExpt.c" 


$(OUTDIR)\knh_tMapper.obj : "..\src\main\knh_tMapper.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tMapper.obj" "..\src\main\knh_tMapper.c" 


$(OUTDIR)\knh_tMethod.obj : "..\src\main\knh_tMethod.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tMethod.obj" "..\src\main\knh_tMethod.c" 


$(OUTDIR)\knh_tName.obj : "..\src\main\knh_tName.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tName.obj" "..\src\main\knh_tName.c" 


$(OUTDIR)\knh_tPackage.obj : "..\src\main\knh_tPackage.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_tPackage.obj" "..\src\main\knh_tPackage.c" 


$(OUTDIR)\konoha_api.obj : "..\src\main\konoha_api.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_api.obj" "..\src\main\konoha_api.c" 


$(OUTDIR)\konoha_data.obj : "..\src\main\konoha_data.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_data.obj" "..\src\main\konoha_data.c" 


$(OUTDIR)\konoha_ext.obj : "..\src\main\konoha_ext.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_ext.obj" "..\src\main\konoha_ext.c" 


$(OUTDIR)\konoha_file.obj : "..\src\main\konoha_file.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_file.obj" "..\src\main\konoha_file.c" 


$(OUTDIR)\konoha_init.obj : "..\src\main\konoha_init.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_init.obj" "..\src\main\konoha_init.c" 


$(OUTDIR)\konoha_libknh.obj : "..\src\main\konoha_libknh.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_libknh.obj" "..\src\main\konoha_libknh.c" 


$(OUTDIR)\konoha_locale.obj : "..\src\main\konoha_locale.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_locale.obj" "..\src\main\konoha_locale.c" 


$(OUTDIR)\konoha_memory.obj : "..\src\main\konoha_memory.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_memory.obj" "..\src\main\konoha_memory.c" 


$(OUTDIR)\konoha_metadata.obj : "..\src\main\konoha_metadata.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_metadata.obj" "..\src\main\konoha_metadata.c" 


$(OUTDIR)\konoha_mutex.obj : "..\src\main\konoha_mutex.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_mutex.obj" "..\src\main\konoha_mutex.c" 


$(OUTDIR)\konoha_pkgapi.obj : "..\src\main\konoha_pkgapi.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_pkgapi.obj" "..\src\main\konoha_pkgapi.c" 


$(OUTDIR)\konoha_print.obj : "..\src\main\konoha_print.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_print.obj" "..\src\main\konoha_print.c" 


$(OUTDIR)\konoha_shell.obj : "..\src\main\konoha_shell.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_shell.obj" "..\src\main\konoha_shell.c" 


$(OUTDIR)\konoha_stack.obj : "..\src\main\konoha_stack.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_stack.obj" "..\src\main\konoha_stack.c" 


$(OUTDIR)\konoha_table.obj : "..\src\main\konoha_table.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_table.obj" "..\src\main\konoha_table.c" 


$(OUTDIR)\konoha_typesystem.obj : "..\src\main\konoha_typesystem.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\konoha_typesystem.obj" "..\src\main\konoha_typesystem.c" 


$(OUTDIR)\$(KONOHA).dll : $(OUTDIR) $(LINK32DLL_OBJS)
	$(LINK32) $(LINK32DLL_FLAGS)  "$(OUTDIR)\ext\iconv.lib" $(LINK32DLL_OBJS)

$(OUTDIR)\$(KONOHA).exe : $(OUTDIR) $(OUTDIR)\$(KONOHA).dll "$(OUTDIR)\konoha.obj"
	$(LINK32) $(LINK32_FLAGS) "$(OUTDIR)\$(KONOHA).lib" "$(OUTDIR)\$(KONOHA).obj"



LINK32DLL_MATHFLAGS=\
 /nologo /dll /LTCG /incremental:no\
 /pdb:"$(OUTDIR)\$(KONOHA).pdb" /machine:I386 /out:"$(OUTDIR)\libknhmath.dll"\
 /implib:"$(OUTDIR)\libknhmath.lib"

$(OUTDIR)\knh_Math.obj : "..\package\math\knh_Math.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\knh_Math.obj" "..\package\math\knh_Math.c" 

$(OUTDIR)\libknhmath.dll : $(OUTDIR)\knh_Math.obj
	$(LINK32) $(LINK32DLL_MATHFLAGS) $(OUTDIR)\konoha.lib $(OUTDIR)\knh_Math.obj

PACKAGE : $(OUTDIR)\libknhmath.dll
	
