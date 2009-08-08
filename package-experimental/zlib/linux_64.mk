# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC 

LDLIBS = -lz -lkonoha

target = linux_64
pkgname = zlib

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = "$(pkgname).o"

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)
