# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -DKONOHA_OS__LINUX
LDLIBS = -lGL -lglut -lGLU -lkonoha

target = linux_32
pkgname = gl

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = $(pkgname).o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

