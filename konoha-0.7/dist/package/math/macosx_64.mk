# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O2 -m64 -Wall -fmessage-length=0 -fPIC
LDLIBS = -lm -lkonoha

target = macosx_64
pkgname = math

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = "$(pkgname).o"

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -c $^ -o $@

$(library): $(objs)
	$(CC) -dynamiclib -m64 -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

