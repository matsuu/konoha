# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic `pkg-config --cflags gtk+-2.0`
LDLIBS = -lkonoha `pkg-config --libs gtk+-2.0`

target = linux_32
pkgname = gtk

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = "$(pkgname).o"

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wall -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

