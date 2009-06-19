obj-m:= konohadev.o
konohadev-objs := \
./src/main/system.o \
./src/main/objectdbms.o \
./src/main/typesystem.o \
./src/main/memory.o \
./src/main/konoha_api.o \
./src/main/konoha_ext.o \
./src/main/systemtable.o \
./src/main/fileutils.o \
./src/main/classapi.o \
./src/main/glue.o \
./src/main/exports.o \
./src/main/metadata.o \
./src/main/logging.o \
./src/main/stack.o \
./src/class/knh_Mapper.o \
./src/class/knh_Array.o \
./src/class/knh_NameSpace.o \
./src/class/knh_System.o \
./src/class/knh_OutputStream.o \
./src/class/knh_Iterator.o \
./src/class/knh_Bytes.o \
./src/class/knh_write.o \
./src/class/knh_Class.o \
./src/class/knh_Script.o \
./src/class/knh_Object.o \
./src/class/knh_String_mbytes.o \
./src/class/knh_BytesConv.o \
./src/class/knh_Hash.o \
./src/class/knh_String.o \
./src/class/knh_InputStream.o \
./src/class/knh_Closure.o \
./src/class/knh_DictMapSet.o \
./src/class/knh_ResultSet.o \
./src/class/knh_DictIdx.o \
./src/class/knh_cwb_t.o \
./src/class/knh_ClassSpec.o \
./src/class/knh_Method.o \
./src/class/knh_Connection.o \
./src/class/knh_bytes_t.o \
./src/class/knh_Exception.o \
./src/class/knh_Context.o \
./src/class/knh_Number.o \
./src/class/knh_type_t.o \
./src/ext/mt19937-64.o \
./src/ext/qsort.o \
./src/ext/mt19937ar.o \
./src/api/hashapi.o \
./src/api/stringapi.o \
./src/api/systemapi.o \
./src/api/arrayapi.o \
./src/api/dictapi.o \
./src/api/objectapi.o \
./src/api/dbapi.o \
./src/api/streamapi.o \
./src/api/numberapi.o \
./src/api/bytesapi.o \
./src/api/anyapi.o \
./src/compiler/token.o \
./src/compiler/perror.o \
./src/compiler/parser.o \
./src/compiler/asm.o \
./src/compiler/kcode.o \
./src/compiler/typing.o \
./src/compiler/stmt.o \
./src/compiler/tokenizer.o \
./src/compiler/konohac.o \
./src/labs/b4.o \
./src/labs/konohaget.o \
./src/gen/konoha_klr_.o \
./src/gen/konohac_.o \
./src/gen/method_.o \
./src/deps/filesystem.o \
./src/deps/sqlite3.o \
./src/deps/socket.o \
./src/deps/konoha_locale.o \
./src/deps/fileio.o \
./src/deps/dlopen.o \
./src/deps/regex.o \
./src/deps/thread.o \
./src/deps/time.o \
./src/konoha.o \

#./src/gen/codetemplate.s \
#./src/gen/codetemplate.c \
#./src/gen/fibo.c \
#./src/gen/fibo.s \

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)
KBUILD_CFLAGS += -DKONOHA_OS__LKM
KBUILD_CFLAGS += -I$(PWD)./include/

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules KBUILD_VERBOSE=1

clean:
	rm -f *.o
	rm -f *.ko
	rm -f *.mod.c
	rm -f *~
	rm -f ./src/main/.*.o.cmd
