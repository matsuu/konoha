# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O0 -g3 -Wall -fmessage-length=0 -fPIC
LDLIBS = -framework GLUT -framework OpenGL -lkonoha -lpthread

target = macosx_32
pkgname = gl

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

