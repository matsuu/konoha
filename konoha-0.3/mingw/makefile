#Makefiile by gen_konoha.py
CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -I"include" -DKONOHA_OS__MINGW
LDLIBS = lib/iconv.a -lm

program = konoha.exe
library = libkonoha.dll

.PHONY: all
all: $(program) 


objs = \
	anyapi.o\
	arrayapi.o\
	bytesapi.o\
	dbapi.o\
	dictapi.o\
	hashapi.o\
	numberapi.o\
	objectapi.o\
	streamapi.o\
	stringapi.o\
	systemapi.o\
	knh_AffineConv.o\
	knh_Array.o\
	knh_Bytes.o\
	knh_bytes_t.o\
	knh_BytesConv.o\
	knh_Class.o\
	knh_Class_type_t.o\
	knh_Closure.o\
	knh_Connection.o\
	knh_Context.o\
	knh_cwb_t.o\
	knh_DictIdx.o\
	knh_DictMapSet.o\
	knh_Exception.o\
	knh_ExceptionHandler.o\
	knh_Float.o\
	knh_Hash.o\
	knh_InputStream.o\
	knh_Int.o\
	knh_IntUnit.o\
	knh_Iterator.o\
	knh_Mapper.o\
	knh_Method.o\
	knh_NameSpace.o\
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
	asm.o\
	kcode.o\
	konohac.o\
	parser.o\
	perror.o\
	stmt.o\
	token.o\
	tokenizer.o\
	typing.o\
	driver_db.o\
	driver_io.o\
	driver_regex.o\
	posix.o\
	tbmx1.o\
	thread.o\
	win32.o\
	mt19937-64.o\
	mt19937ar.o\
	codetemplate.o\
	fibo.o\
	konoha_klr_.o\
	konoha_message_.o\
	konohac_.o\
	method_.o\
	b4.o\
	knh_tClass.o\
	knh_tExpt.o\
	knh_tMapper.o\
	konoha_api.o\
	konoha_data.o\
	konoha_ext.o\
	konoha_file.o\
	konoha_libknh.o\
	konoha_locale.o\
	konoha_print.o\
	memory.o\
	metadata.o\
	stack.o\
	system.o\
	systemtable.o\
	typesystem.o\
	unused.o\
	unused0.o\
	unused2.o\
	unused3.o\
	unused4.o

anyapi.o : ../src/api/anyapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oanyapi.o -c "../src/api/anyapi.c" 


arrayapi.o : ../src/api/arrayapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oarrayapi.o -c "../src/api/arrayapi.c" 


bytesapi.o : ../src/api/bytesapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -obytesapi.o -c "../src/api/bytesapi.c" 


dbapi.o : ../src/api/dbapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -odbapi.o -c "../src/api/dbapi.c" 


dictapi.o : ../src/api/dictapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -odictapi.o -c "../src/api/dictapi.c" 


hashapi.o : ../src/api/hashapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ohashapi.o -c "../src/api/hashapi.c" 


numberapi.o : ../src/api/numberapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -onumberapi.o -c "../src/api/numberapi.c" 


objectapi.o : ../src/api/objectapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oobjectapi.o -c "../src/api/objectapi.c" 


streamapi.o : ../src/api/streamapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ostreamapi.o -c "../src/api/streamapi.c" 


stringapi.o : ../src/api/stringapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ostringapi.o -c "../src/api/stringapi.c" 


systemapi.o : ../src/api/systemapi.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -osystemapi.o -c "../src/api/systemapi.c" 


knh_AffineConv.o : ../src/class/knh_AffineConv.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_AffineConv.o -c "../src/class/knh_AffineConv.c" 


knh_Array.o : ../src/class/knh_Array.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Array.o -c "../src/class/knh_Array.c" 


knh_Bytes.o : ../src/class/knh_Bytes.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Bytes.o -c "../src/class/knh_Bytes.c" 


knh_bytes_t.o : ../src/class/knh_bytes_t.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_bytes_t.o -c "../src/class/knh_bytes_t.c" 


knh_BytesConv.o : ../src/class/knh_BytesConv.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_BytesConv.o -c "../src/class/knh_BytesConv.c" 


knh_Class.o : ../src/class/knh_Class.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Class.o -c "../src/class/knh_Class.c" 


knh_Class_type_t.o : ../src/class/knh_Class_type_t.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Class_type_t.o -c "../src/class/knh_Class_type_t.c" 


knh_Closure.o : ../src/class/knh_Closure.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Closure.o -c "../src/class/knh_Closure.c" 


knh_Connection.o : ../src/class/knh_Connection.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Connection.o -c "../src/class/knh_Connection.c" 


knh_Context.o : ../src/class/knh_Context.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Context.o -c "../src/class/knh_Context.c" 


knh_cwb_t.o : ../src/class/knh_cwb_t.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_cwb_t.o -c "../src/class/knh_cwb_t.c" 


knh_DictIdx.o : ../src/class/knh_DictIdx.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_DictIdx.o -c "../src/class/knh_DictIdx.c" 


knh_DictMapSet.o : ../src/class/knh_DictMapSet.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_DictMapSet.o -c "../src/class/knh_DictMapSet.c" 


knh_Exception.o : ../src/class/knh_Exception.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Exception.o -c "../src/class/knh_Exception.c" 


knh_ExceptionHandler.o : ../src/class/knh_ExceptionHandler.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_ExceptionHandler.o -c "../src/class/knh_ExceptionHandler.c" 


knh_Float.o : ../src/class/knh_Float.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Float.o -c "../src/class/knh_Float.c" 


knh_Hash.o : ../src/class/knh_Hash.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Hash.o -c "../src/class/knh_Hash.c" 


knh_InputStream.o : ../src/class/knh_InputStream.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_InputStream.o -c "../src/class/knh_InputStream.c" 


knh_Int.o : ../src/class/knh_Int.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Int.o -c "../src/class/knh_Int.c" 


knh_IntUnit.o : ../src/class/knh_IntUnit.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_IntUnit.o -c "../src/class/knh_IntUnit.c" 


knh_Iterator.o : ../src/class/knh_Iterator.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Iterator.o -c "../src/class/knh_Iterator.c" 


knh_Mapper.o : ../src/class/knh_Mapper.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Mapper.o -c "../src/class/knh_Mapper.c" 


knh_Method.o : ../src/class/knh_Method.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Method.o -c "../src/class/knh_Method.c" 


knh_NameSpace.o : ../src/class/knh_NameSpace.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_NameSpace.o -c "../src/class/knh_NameSpace.c" 


knh_Number.o : ../src/class/knh_Number.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Number.o -c "../src/class/knh_Number.c" 


knh_Object.o : ../src/class/knh_Object.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Object.o -c "../src/class/knh_Object.c" 


knh_OutputStream.o : ../src/class/knh_OutputStream.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_OutputStream.o -c "../src/class/knh_OutputStream.c" 


knh_OutputStream_write.o : ../src/class/knh_OutputStream_write.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_OutputStream_write.o -c "../src/class/knh_OutputStream_write.c" 


knh_Range.o : ../src/class/knh_Range.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Range.o -c "../src/class/knh_Range.c" 


knh_Regex.o : ../src/class/knh_Regex.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Regex.o -c "../src/class/knh_Regex.c" 


knh_ResultSet.o : ../src/class/knh_ResultSet.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_ResultSet.o -c "../src/class/knh_ResultSet.c" 


knh_Runtime.o : ../src/class/knh_Runtime.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Runtime.o -c "../src/class/knh_Runtime.c" 


knh_Script.o : ../src/class/knh_Script.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Script.o -c "../src/class/knh_Script.c" 


knh_String.o : ../src/class/knh_String.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_String.o -c "../src/class/knh_String.c" 


knh_String_mbytes.o : ../src/class/knh_String_mbytes.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_String_mbytes.o -c "../src/class/knh_String_mbytes.c" 


knh_StringParser.o : ../src/class/knh_StringParser.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_StringParser.o -c "../src/class/knh_StringParser.c" 


knh_StringUnit.o : ../src/class/knh_StringUnit.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_StringUnit.o -c "../src/class/knh_StringUnit.c" 


knh_System.o : ../src/class/knh_System.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_System.o -c "../src/class/knh_System.c" 


knh_Tuple2.o : ../src/class/knh_Tuple2.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_Tuple2.o -c "../src/class/knh_Tuple2.c" 


asm.o : ../src/compiler/asm.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oasm.o -c "../src/compiler/asm.c" 


kcode.o : ../src/compiler/kcode.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okcode.o -c "../src/compiler/kcode.c" 


konohac.o : ../src/compiler/konohac.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonohac.o -c "../src/compiler/konohac.c" 


parser.o : ../src/compiler/parser.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oparser.o -c "../src/compiler/parser.c" 


perror.o : ../src/compiler/perror.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -operror.o -c "../src/compiler/perror.c" 


stmt.o : ../src/compiler/stmt.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ostmt.o -c "../src/compiler/stmt.c" 


token.o : ../src/compiler/token.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -otoken.o -c "../src/compiler/token.c" 


tokenizer.o : ../src/compiler/tokenizer.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -otokenizer.o -c "../src/compiler/tokenizer.c" 


typing.o : ../src/compiler/typing.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -otyping.o -c "../src/compiler/typing.c" 


driver_db.o : ../src/deps/driver_db.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -odriver_db.o -c "../src/deps/driver_db.c" 


driver_io.o : ../src/deps/driver_io.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -odriver_io.o -c "../src/deps/driver_io.c" 


driver_regex.o : ../src/deps/driver_regex.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -odriver_regex.o -c "../src/deps/driver_regex.c" 


posix.o : ../src/deps/posix.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oposix.o -c "../src/deps/posix.c" 


tbmx1.o : ../src/deps/tbmx1.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -otbmx1.o -c "../src/deps/tbmx1.c" 


thread.o : ../src/deps/thread.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -othread.o -c "../src/deps/thread.c" 


win32.o : ../src/deps/win32.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -owin32.o -c "../src/deps/win32.c" 


mt19937-64.o : ../src/ext/mt19937-64.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -omt19937-64.o -c "../src/ext/mt19937-64.c" 


mt19937ar.o : ../src/ext/mt19937ar.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -omt19937ar.o -c "../src/ext/mt19937ar.c" 


codetemplate.o : ../src/gen/codetemplate.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ocodetemplate.o -c "../src/gen/codetemplate.c" 


fibo.o : ../src/gen/fibo.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ofibo.o -c "../src/gen/fibo.c" 


konoha_klr_.o : ../src/gen/konoha_klr_.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_klr_.o -c "../src/gen/konoha_klr_.c" 


konoha_message_.o : ../src/gen/konoha_message_.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_message_.o -c "../src/gen/konoha_message_.c" 


konohac_.o : ../src/gen/konohac_.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonohac_.o -c "../src/gen/konohac_.c" 


method_.o : ../src/gen/method_.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -omethod_.o -c "../src/gen/method_.c" 


konoha.o : ../src/konoha.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha.o -c "../src/konoha.c" 


b4.o : ../src/labs/b4.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ob4.o -c "../src/labs/b4.c" 


knh_tClass.o : ../src/main/knh_tClass.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_tClass.o -c "../src/main/knh_tClass.c" 


knh_tExpt.o : ../src/main/knh_tExpt.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_tExpt.o -c "../src/main/knh_tExpt.c" 


knh_tMapper.o : ../src/main/knh_tMapper.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -oknh_tMapper.o -c "../src/main/knh_tMapper.c" 


konoha_api.o : ../src/main/konoha_api.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_api.o -c "../src/main/konoha_api.c" 


konoha_data.o : ../src/main/konoha_data.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_data.o -c "../src/main/konoha_data.c" 


konoha_ext.o : ../src/main/konoha_ext.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_ext.o -c "../src/main/konoha_ext.c" 


konoha_file.o : ../src/main/konoha_file.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_file.o -c "../src/main/konoha_file.c" 


konoha_libknh.o : ../src/main/konoha_libknh.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_libknh.o -c "../src/main/konoha_libknh.c" 


konoha_locale.o : ../src/main/konoha_locale.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_locale.o -c "../src/main/konoha_locale.c" 


konoha_print.o : ../src/main/konoha_print.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -okonoha_print.o -c "../src/main/konoha_print.c" 


memory.o : ../src/main/memory.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -omemory.o -c "../src/main/memory.c" 


metadata.o : ../src/main/metadata.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ometadata.o -c "../src/main/metadata.c" 


stack.o : ../src/main/stack.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ostack.o -c "../src/main/stack.c" 


system.o : ../src/main/system.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -osystem.o -c "../src/main/system.c" 


systemtable.o : ../src/main/systemtable.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -osystemtable.o -c "../src/main/systemtable.c" 


typesystem.o : ../src/main/typesystem.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -otypesystem.o -c "../src/main/typesystem.c" 


unused.o : ../src/main/unused.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ounused.o -c "../src/main/unused.c" 


unused0.o : ../src/main/unused0.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ounused0.o -c "../src/main/unused0.c" 


unused2.o : ../src/main/unused2.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ounused2.o -c "../src/main/unused2.c" 


unused3.o : ../src/main/unused3.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ounused3.o -c "../src/main/unused3.c" 


unused4.o : ../src/main/unused4.c ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS)  -I"../include" -ounused4.o -c "../src/main/unused4.c" 

$(program): $(library) konoha.o
	$(CC) -o $(program) konoha.o -L"." -lkonoha

$(library) : $(objs)
	$(CC) -shared -Wl -o $(library) -L"./lib" -L"." $(objs) $(LDLIBS) 


.PHONY: dist
dist:
	$(RM) -rf $(objs) konoha.o

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(program) $(library) konoha.o 

