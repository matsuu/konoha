#Makefiile by gen_konoha.py
#CC = gcc

include ../../etc/makerules
VPATH = "./ $(shell find ../ -type d) ./"

CFLAGS += -O2 -Wall -fmessage-length=0 -I/usr/local/te/include -I"../include" -DKONOHA_OS__TB -DKONOHA_MONOLITHIC
#LDLIBS = -m

program = konoha
library =

.PHONY: all
all: $(program)


objs = \
	anyapi.o\
	arrayapi.o\
	bytes.o\
	dictapi.o\
	exception.o\
	hashapi.o\
	iterator.o\
	kdbcapi.o\
	numberapi.o\
	objectapi.o\
	streamapi.o\
	stringapi.o\
	systemapi.o\
	knh_AffineConv.o\
	knh_Array.o\
	knh_array_t.o\
	knh_Boolean.o\
	knh_Bytes.o\
	knh_Bytes_byte_t.o\
	knh_BytesConv.o\
	knh_Class.o\
	knh_Class_spec_t.o\
	knh_Class_type_t.o\
	knh_ClassMap.o\
	knh_ClassStruct.o\
	knh_Closure.o\
	knh_Connection.o\
	knh_Context.o\
	knh_Context_wbuf.o\
	knh_DictIdx.o\
	knh_DictMapSet.o\
	knh_Exception.o\
	knh_ExceptionHandler.o\
	knh_Float.o\
	knh_FloatUnit.o\
	knh_HashMap.o\
	knh_HashSet.o\
	knh_InputStream.o\
	knh_Int.o\
	knh_IntUnit.o\
	knh_Iterator.o\
	knh_LRUHashMap.o\
	knh_Mapper.o\
	knh_Method.o\
	knh_MethodField.o\
	knh_Mutex__pthread.o\
	knh_NameSpace.o\
	knh_Nue.o\
	knh_Number.o\
	knh_Object.o\
	knh_OutputStream.o\
	knh_OutputStream_write.o\
	knh_Range.o\
	knh_Regex.o\
	knh_ResultSet.o\
	knh_Runtime.o\
	knh_Script.o\
	knh_String.o\
	knh_String_mbytes.o\
	knh_StringParser.o\
	knh_StringUnit.o\
	knh_System.o\
	knh_Tuple2.o\
	knh_Asm.o\
	knh_KLRCode.o\
	knh_perror.o\
	knh_Stmt.o\
	knh_StmtMETA.o\
	knh_Token.o\
	konohac.o\
	parser.o\
	tokenizer.o\
	typing.o\
	filesystem__cygwin.o\
	knh_driver_db.o\
	knh_driver_io.o\
	knh_driver_regex.o\
	filesystem__linux.o\
	filesystem__macosx.o\
	filesystem__tb.o\
	system__bt.o\
	filesystem__win32.o\
	system__win32.o\
	mt19937-64.o\
	mt19937ar.o\
	codetemplate.o\
	konoha_init_.o\
	konoha_klr_.o\
	konoha_message_.o\
	konohac_.o\
	knh_tClass.o\
	knh_tConst.o\
	knh_tContext.o\
	knh_tExpt.o\
	knh_tMapper.o\
	knh_tMethod.o\
	knh_tName.o\
	knh_tObject.o\
	knh_tPackage.o\
	knh_tStruct.o\
	konoha_api.o\
	konoha_ext.o\
	konoha_file.o\
	konoha_init.o\
	konoha_libknh.o\
	konoha_locale.o\
	konoha_metadata.o\
	konoha_pkgapi.o\
	konoha_print.o\
	konoha_shell.o\
	konoha_stack.o\
	konoha_sync.o\
	konoha_throwcatch.o\
	konoha_time.o\
	konoha_typesystem.o\
	knh_cgi.o\
	demo.o\
	knh_iroha.o\
	knh_Math.o\
	knh_Amazon.o\
	knh_Counter.o\
	knh_naruto.o\
	knh_socket.o\
	knh_Socket_utils.o\
	knh_unix.o

anyapi.o : ../src/api/anyapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oanyapi.o -c "../src/api/anyapi.c" 


arrayapi.o : ../src/api/arrayapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oarrayapi.o -c "../src/api/arrayapi.c" 


bytes.o : ../src/api/bytes.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -obytes.o -c "../src/api/bytes.c" 


dictapi.o : ../src/api/dictapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -odictapi.o -c "../src/api/dictapi.c" 


exception.o : ../src/api/exception.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oexception.o -c "../src/api/exception.c" 


hashapi.o : ../src/api/hashapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ohashapi.o -c "../src/api/hashapi.c" 


iterator.o : ../src/api/iterator.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oiterator.o -c "../src/api/iterator.c" 


kdbcapi.o : ../src/api/kdbcapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okdbcapi.o -c "../src/api/kdbcapi.c" 


numberapi.o : ../src/api/numberapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -onumberapi.o -c "../src/api/numberapi.c" 


objectapi.o : ../src/api/objectapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oobjectapi.o -c "../src/api/objectapi.c" 


streamapi.o : ../src/api/streamapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ostreamapi.o -c "../src/api/streamapi.c" 


stringapi.o : ../src/api/stringapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ostringapi.o -c "../src/api/stringapi.c" 


systemapi.o : ../src/api/systemapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -osystemapi.o -c "../src/api/systemapi.c" 


knh_AffineConv.o : ../src/class/knh_AffineConv.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_AffineConv.o -c "../src/class/knh_AffineConv.c" 


knh_Array.o : ../src/class/knh_Array.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Array.o -c "../src/class/knh_Array.c" 


knh_array_t.o : ../src/class/knh_array_t.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_array_t.o -c "../src/class/knh_array_t.c" 


knh_Boolean.o : ../src/class/knh_Boolean.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Boolean.o -c "../src/class/knh_Boolean.c" 


knh_Bytes.o : ../src/class/knh_Bytes.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Bytes.o -c "../src/class/knh_Bytes.c" 


knh_Bytes_byte_t.o : ../src/class/knh_Bytes_byte_t.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Bytes_byte_t.o -c "../src/class/knh_Bytes_byte_t.c" 


knh_BytesConv.o : ../src/class/knh_BytesConv.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_BytesConv.o -c "../src/class/knh_BytesConv.c" 


knh_Class.o : ../src/class/knh_Class.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Class.o -c "../src/class/knh_Class.c" 


knh_Class_spec_t.o : ../src/class/knh_Class_spec_t.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Class_spec_t.o -c "../src/class/knh_Class_spec_t.c" 


knh_Class_type_t.o : ../src/class/knh_Class_type_t.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Class_type_t.o -c "../src/class/knh_Class_type_t.c" 


knh_ClassMap.o : ../src/class/knh_ClassMap.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_ClassMap.o -c "../src/class/knh_ClassMap.c" 


knh_ClassStruct.o : ../src/class/knh_ClassStruct.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_ClassStruct.o -c "../src/class/knh_ClassStruct.c" 


knh_Closure.o : ../src/class/knh_Closure.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Closure.o -c "../src/class/knh_Closure.c" 


knh_Connection.o : ../src/class/knh_Connection.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Connection.o -c "../src/class/knh_Connection.c" 


knh_Context.o : ../src/class/knh_Context.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Context.o -c "../src/class/knh_Context.c" 


knh_Context_wbuf.o : ../src/class/knh_Context_wbuf.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Context_wbuf.o -c "../src/class/knh_Context_wbuf.c" 


knh_DictIdx.o : ../src/class/knh_DictIdx.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_DictIdx.o -c "../src/class/knh_DictIdx.c" 


knh_DictMapSet.o : ../src/class/knh_DictMapSet.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_DictMapSet.o -c "../src/class/knh_DictMapSet.c" 


knh_Exception.o : ../src/class/knh_Exception.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Exception.o -c "../src/class/knh_Exception.c" 


knh_ExceptionHandler.o : ../src/class/knh_ExceptionHandler.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_ExceptionHandler.o -c "../src/class/knh_ExceptionHandler.c" 


knh_Float.o : ../src/class/knh_Float.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Float.o -c "../src/class/knh_Float.c" 


knh_FloatUnit.o : ../src/class/knh_FloatUnit.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_FloatUnit.o -c "../src/class/knh_FloatUnit.c" 


knh_HashMap.o : ../src/class/knh_HashMap.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_HashMap.o -c "../src/class/knh_HashMap.c" 


knh_HashSet.o : ../src/class/knh_HashSet.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_HashSet.o -c "../src/class/knh_HashSet.c" 


knh_InputStream.o : ../src/class/knh_InputStream.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_InputStream.o -c "../src/class/knh_InputStream.c" 


knh_Int.o : ../src/class/knh_Int.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Int.o -c "../src/class/knh_Int.c" 


knh_IntUnit.o : ../src/class/knh_IntUnit.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_IntUnit.o -c "../src/class/knh_IntUnit.c" 


knh_Iterator.o : ../src/class/knh_Iterator.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Iterator.o -c "../src/class/knh_Iterator.c" 


knh_LRUHashMap.o : ../src/class/knh_LRUHashMap.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_LRUHashMap.o -c "../src/class/knh_LRUHashMap.c" 


knh_Mapper.o : ../src/class/knh_Mapper.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Mapper.o -c "../src/class/knh_Mapper.c" 


knh_Method.o : ../src/class/knh_Method.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Method.o -c "../src/class/knh_Method.c" 


knh_MethodField.o : ../src/class/knh_MethodField.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_MethodField.o -c "../src/class/knh_MethodField.c" 


knh_Mutex__pthread.o : ../src/class/knh_Mutex__pthread.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Mutex__pthread.o -c "../src/class/knh_Mutex__pthread.c" 


knh_NameSpace.o : ../src/class/knh_NameSpace.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_NameSpace.o -c "../src/class/knh_NameSpace.c" 


knh_Nue.o : ../src/class/knh_Nue.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Nue.o -c "../src/class/knh_Nue.c" 


knh_Number.o : ../src/class/knh_Number.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Number.o -c "../src/class/knh_Number.c" 


knh_Object.o : ../src/class/knh_Object.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Object.o -c "../src/class/knh_Object.c" 


knh_OutputStream.o : ../src/class/knh_OutputStream.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_OutputStream.o -c "../src/class/knh_OutputStream.c" 


knh_OutputStream_write.o : ../src/class/knh_OutputStream_write.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_OutputStream_write.o -c "../src/class/knh_OutputStream_write.c" 


knh_Range.o : ../src/class/knh_Range.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Range.o -c "../src/class/knh_Range.c" 


knh_Regex.o : ../src/class/knh_Regex.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Regex.o -c "../src/class/knh_Regex.c" 


knh_ResultSet.o : ../src/class/knh_ResultSet.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_ResultSet.o -c "../src/class/knh_ResultSet.c" 


knh_Runtime.o : ../src/class/knh_Runtime.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Runtime.o -c "../src/class/knh_Runtime.c" 


knh_Script.o : ../src/class/knh_Script.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Script.o -c "../src/class/knh_Script.c" 


knh_String.o : ../src/class/knh_String.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_String.o -c "../src/class/knh_String.c" 


knh_String_mbytes.o : ../src/class/knh_String_mbytes.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_String_mbytes.o -c "../src/class/knh_String_mbytes.c" 


knh_StringParser.o : ../src/class/knh_StringParser.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_StringParser.o -c "../src/class/knh_StringParser.c" 


knh_StringUnit.o : ../src/class/knh_StringUnit.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_StringUnit.o -c "../src/class/knh_StringUnit.c" 


knh_System.o : ../src/class/knh_System.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_System.o -c "../src/class/knh_System.c" 


knh_Tuple2.o : ../src/class/knh_Tuple2.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Tuple2.o -c "../src/class/knh_Tuple2.c" 


knh_Asm.o : ../src/compiler/knh_Asm.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Asm.o -c "../src/compiler/knh_Asm.c" 


knh_KLRCode.o : ../src/compiler/knh_KLRCode.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_KLRCode.o -c "../src/compiler/knh_KLRCode.c" 


knh_perror.o : ../src/compiler/knh_perror.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_perror.o -c "../src/compiler/knh_perror.c" 


knh_Stmt.o : ../src/compiler/knh_Stmt.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Stmt.o -c "../src/compiler/knh_Stmt.c" 


knh_StmtMETA.o : ../src/compiler/knh_StmtMETA.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_StmtMETA.o -c "../src/compiler/knh_StmtMETA.c" 


knh_Token.o : ../src/compiler/knh_Token.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Token.o -c "../src/compiler/knh_Token.c" 


konohac.o : ../src/compiler/konohac.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonohac.o -c "../src/compiler/konohac.c" 


parser.o : ../src/compiler/parser.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oparser.o -c "../src/compiler/parser.c" 


tokenizer.o : ../src/compiler/tokenizer.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -otokenizer.o -c "../src/compiler/tokenizer.c" 


typing.o : ../src/compiler/typing.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -otyping.o -c "../src/compiler/typing.c" 


filesystem__cygwin.o : ../src/deps/cygwin/filesystem__cygwin.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ofilesystem__cygwin.o -c "../src/deps/cygwin/filesystem__cygwin.c" 


knh_driver_db.o : ../src/deps/knh_driver_db.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_driver_db.o -c "../src/deps/knh_driver_db.c" 


knh_driver_io.o : ../src/deps/knh_driver_io.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_driver_io.o -c "../src/deps/knh_driver_io.c" 


knh_driver_regex.o : ../src/deps/knh_driver_regex.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_driver_regex.o -c "../src/deps/knh_driver_regex.c" 


filesystem__linux.o : ../src/deps/linux/filesystem__linux.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ofilesystem__linux.o -c "../src/deps/linux/filesystem__linux.c" 


filesystem__macosx.o : ../src/deps/macosx/filesystem__macosx.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ofilesystem__macosx.o -c "../src/deps/macosx/filesystem__macosx.c" 


filesystem__tb.o : ../src/deps/tb/filesystem__tb.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ofilesystem__tb.o -c "../src/deps/tb/filesystem__tb.c" 


system__bt.o : ../src/deps/tb/system__bt.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -osystem__bt.o -c "../src/deps/tb/system__bt.c" 


filesystem__win32.o : ../src/deps/win32/filesystem__win32.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ofilesystem__win32.o -c "../src/deps/win32/filesystem__win32.c" 


system__win32.o : ../src/deps/win32/system__win32.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -osystem__win32.o -c "../src/deps/win32/system__win32.c" 


mt19937-64.o : ../src/ext/mt19937-64.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -omt19937-64.o -c "../src/ext/mt19937-64.c" 


mt19937ar.o : ../src/ext/mt19937ar.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -omt19937ar.o -c "../src/ext/mt19937ar.c" 


codetemplate.o : ../src/gen/codetemplate.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -ocodetemplate.o -c "../src/gen/codetemplate.c" 


konoha_init_.o : ../src/gen/konoha_init_.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_init_.o -c "../src/gen/konoha_init_.c" 


konoha_klr_.o : ../src/gen/konoha_klr_.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_klr_.o -c "../src/gen/konoha_klr_.c" 


konoha_message_.o : ../src/gen/konoha_message_.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_message_.o -c "../src/gen/konoha_message_.c" 


konohac_.o : ../src/gen/konohac_.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonohac_.o -c "../src/gen/konohac_.c" 


konoha.o : ../src/konoha.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha.o -c "../src/konoha.c" 


knh_tClass.o : ../src/main/knh_tClass.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tClass.o -c "../src/main/knh_tClass.c" 


knh_tConst.o : ../src/main/knh_tConst.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tConst.o -c "../src/main/knh_tConst.c" 


knh_tContext.o : ../src/main/knh_tContext.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tContext.o -c "../src/main/knh_tContext.c" 


knh_tExpt.o : ../src/main/knh_tExpt.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tExpt.o -c "../src/main/knh_tExpt.c" 


knh_tMapper.o : ../src/main/knh_tMapper.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tMapper.o -c "../src/main/knh_tMapper.c" 


knh_tMethod.o : ../src/main/knh_tMethod.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tMethod.o -c "../src/main/knh_tMethod.c" 


knh_tName.o : ../src/main/knh_tName.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tName.o -c "../src/main/knh_tName.c" 


knh_tObject.o : ../src/main/knh_tObject.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tObject.o -c "../src/main/knh_tObject.c" 


knh_tPackage.o : ../src/main/knh_tPackage.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tPackage.o -c "../src/main/knh_tPackage.c" 


knh_tStruct.o : ../src/main/knh_tStruct.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_tStruct.o -c "../src/main/knh_tStruct.c" 


konoha_api.o : ../src/main/konoha_api.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_api.o -c "../src/main/konoha_api.c" 


konoha_ext.o : ../src/main/konoha_ext.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_ext.o -c "../src/main/konoha_ext.c" 


konoha_file.o : ../src/main/konoha_file.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_file.o -c "../src/main/konoha_file.c" 


konoha_init.o : ../src/main/konoha_init.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_init.o -c "../src/main/konoha_init.c" 


konoha_libknh.o : ../src/main/konoha_libknh.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_libknh.o -c "../src/main/konoha_libknh.c" 


konoha_locale.o : ../src/main/konoha_locale.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_locale.o -c "../src/main/konoha_locale.c" 


konoha_metadata.o : ../src/main/konoha_metadata.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_metadata.o -c "../src/main/konoha_metadata.c" 


konoha_pkgapi.o : ../src/main/konoha_pkgapi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_pkgapi.o -c "../src/main/konoha_pkgapi.c" 


konoha_print.o : ../src/main/konoha_print.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_print.o -c "../src/main/konoha_print.c" 


konoha_shell.o : ../src/main/konoha_shell.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_shell.o -c "../src/main/konoha_shell.c" 


konoha_stack.o : ../src/main/konoha_stack.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_stack.o -c "../src/main/konoha_stack.c" 


konoha_sync.o : ../src/main/konoha_sync.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_sync.o -c "../src/main/konoha_sync.c" 


konoha_throwcatch.o : ../src/main/konoha_throwcatch.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_throwcatch.o -c "../src/main/konoha_throwcatch.c" 


konoha_time.o : ../src/main/konoha_time.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_time.o -c "../src/main/konoha_time.c" 


konoha_typesystem.o : ../src/main/konoha_typesystem.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -okonoha_typesystem.o -c "../src/main/konoha_typesystem.c" 


knh_cgi.o : ../package/cgi/knh_cgi.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_cgi.o -c "../package/cgi/knh_cgi.c" 


demo.o : ../package/demo/demo.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -odemo.o -c "../package/demo/demo.c" 


knh_iroha.o : ../package/iroha/knh_iroha.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_iroha.o -c "../package/iroha/knh_iroha.c" 


knh_Math.o : ../package/math/knh_Math.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Math.o -c "../package/math/knh_Math.c" 


knh_Amazon.o : ../package/naruto/knh_Amazon.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Amazon.o -c "../package/naruto/knh_Amazon.c" 


knh_Counter.o : ../package/naruto/knh_Counter.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Counter.o -c "../package/naruto/knh_Counter.c" 


knh_naruto.o : ../package/naruto/knh_naruto.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_naruto.o -c "../package/naruto/knh_naruto.c" 


knh_socket.o : ../package/socket/knh_socket.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_socket.o -c "../package/socket/knh_socket.c" 


knh_Socket_utils.o : ../package/socket/knh_Socket_utils.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_Socket_utils.o -c "../package/socket/knh_Socket_utils.c" 


knh_unix.o : ../package/unix/knh_unix.c ../include/konoha/gen/konoha_class_.h
#	$(CC) $(CFLAGS)  -I"../include" -oknh_unix.o -c "../package/unix/knh_unix.c" 

$(program): $(objs) konoha.o
#	$(CC) -o $(program) $^ -L"./lib" -L"./libexec" $(LDLIBS) 
#	strip $(program)


.PHONY: dist
dist:
	$(RM) -rf $(objs) konoha.o

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(program) $(library) konoha.o 

