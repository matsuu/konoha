# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic -g3

LDLIBS = -lkonoha -lcmpisfcc

target = linux_64
pkgname = sfcc

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