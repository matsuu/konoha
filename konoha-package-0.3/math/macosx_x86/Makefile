#Makefile for math.so

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic
LDLIBS = -lm -lkonoha

library = math.so
#library = math.dylib

.PHONY: all
all: $(library)

objs = math.o

math.o: math.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

.PHONY: konoha_install
konoha_install: $(library)
	mkdir -p .konoha/math
	cp $(library) .konoha/math
	cp math.k .konoha/math
