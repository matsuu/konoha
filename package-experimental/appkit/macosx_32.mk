# AppKit makefile by imasahiro@users.sourceforge.net 

CC = gcc
CFLAGS = -x objective-c -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -framework AppKit -lkonoha

target = macosx_32
pkgname = appkit

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = $(pkgname).o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

