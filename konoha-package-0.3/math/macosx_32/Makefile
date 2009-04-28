#Makefile for "macosx/math.dylib"

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -lm -lkonoha

target = macosx_32
pkgname = math

library = "$(target)/$(pkgname).dylib"

.PHONY: all
all: $(library)

objs = "$(target)/$(pkgname).o"

"$(target)/$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

