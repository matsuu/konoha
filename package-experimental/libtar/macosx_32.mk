# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -g3
LDLIBS = -ltar -lkonoha

target = macosx_32
pkgname = libtar

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)
	cat ./tar.k > ./libtar.k

objs = tar.o

tar.o: tar.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library) "$(pkgname).k"

