# ソースの依存関係ファイル (自動生成)
DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

# 標準ルール
include $(BD)/bappl/etc/makerules

VPATH = "./ $(shell find ../ -type d) ./"

# knh_os__tb -> konoha_on_tb , +LIBKONOHA
CFLAGS += -O2 -Wall -fmessage-length=0 -I$(BD)/include -I./support/include -I"../include" -DKONOHA_ON_TB -DKONOHA_MONOLITHIC
#LDLIBS = -m

program = konoha
library = lib$(program)

ifeq ($(mode),debug)
LDLIBS += -ltm
NOINST = $(program).trg
endif

$(program).trg: $(program).out $(program)
	cp $< $@
	$(STRIP) $@

.PHONY: all
all: $(program) $(program).map

libkonoha_la_SOURCES = ../src/api/anyapi.c ../src/api/arrayapi.c \
	../src/api/bytesapi.c ../src/api/dbapi.c ../src/api/dictapi.c \
	../src/api/hashapi.c ../src/api/numberapi.c \
	../src/api/objectapi.c ../src/api/streamapi.c \
	../src/api/stringapi.c ../src/api/systemapi.c \
	../src/class/knh_Array.c ../src/class/knh_Bytes.c \
	../src/class/knh_BytesConv.c ../src/class/knh_Class.c \
	../src/class/knh_ClassSpec.c ../src/class/knh_Closure.c \
	../src/class/knh_Connection.c ../src/class/knh_Context.c \
	../src/class/knh_DictIdx.c ../src/class/knh_DictMapSet.c \
	../src/class/knh_Exception.c ../src/class/knh_Hash.c \
	../src/class/knh_InputStream.c ../src/class/knh_Iterator.c \
	../src/class/knh_Mapper.c ../src/class/knh_Method.c \
	../src/class/knh_NameSpace.c ../src/class/knh_Number.c \
	../src/class/knh_Object.c ../src/class/knh_OutputStream.c \
	../src/class/knh_ResultSet.c ../src/class/knh_Script.c \
	../src/class/knh_String.c ../src/class/knh_String_mbytes.c \
	../src/class/knh_System.c ../src/class/knh_bytes_t.c \
	../src/class/knh_cwb_t.c ../src/class/knh_type_t.c \
	../src/class/knh_write.c ../src/compiler/asm.c \
	../src/compiler/kcode.c ../src/compiler/konohac.c \
	../src/compiler/parser.c ../src/compiler/perror.c \
	../src/compiler/stmt.c ../src/compiler/token.c \
	../src/compiler/tokenizer.c ../src/compiler/typing.c \
	../src/deps/dlopen.c ../src/deps/fileio.c \
	../src/deps/filesystem.c ../src/deps/locale.c \
	../src/deps/regex.c ../src/deps/socket.c ../src/deps/sqlite3.c \
	../src/deps/thread.c ../src/deps/time.c \
	../src/ext/mt19937-64.c ../src/ext/mt19937ar.c \
	../src/gen/codetemplate.c ../src/gen/fibo.c \
	../src/gen/konoha_klr_.c ../src/gen/konohac_.c \
	../src/gen/method_.c ../src/labs/b4.c  \
	../src/main/classapi.c ../src/main/exports.c \
	../src/main/fileutils.c ../src/main/glue.c \
	../src/main/konoha_api.c ../src/main/konoha_ext.c \
	../src/main/logging.c ../src/main/memory.c \
	../src/main/metadata.c ../src/main/objectdbms.c \
	../src/main/stack.c ../src/main/system.c \
	../src/main/systemtable.c ../src/main/typesystem.c
#../src/labs/konohaget.c

libkonoha_la_SOURCES += ../support/src/getenv.c

konoha_SOURCES = ../src/konoha.c

objs = $(addsuffix .o,$(basename $(notdir $(libkonoha_la_SOURCES) $(konoha_SOURCES))))

$(library).a: $(objs)
	$(AR) $(ARFLAGS) $@ $^

$(program).out: $(library).a konoha.o
	$(LINK.o) -o $@ konoha.o -L. -l$(program) $(LDLIBS) 

$(program).map: $(program).out
	$(NM) $(NMFLAGS) $< > $@

$(program): $(program).out
	$(CP) $< $@
	$(STRIP) $@
	$(ETCBIN)/bzcomp $(BZCOMP_FLAGS) $@

.PHONY: dist
dist:
	$(RM) $(objs) konoha.o

.PHONY: clean
clean:
	$(RM) $(objs) $(program) $(program).out $(program).map $(library).a konoha.o $(program).trg

# ソースの依存関係
ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)
