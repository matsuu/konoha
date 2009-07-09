# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -g3
LDLIBS = -lz -lkonoha

target = macosx_32
pkgname = zlib

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = "$(pkgname).o"

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

