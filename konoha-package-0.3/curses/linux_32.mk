# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic
LDLIBS = -lkonoha
LDLIBS += -lncurses

target = linux_32
pkgname = curses

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

