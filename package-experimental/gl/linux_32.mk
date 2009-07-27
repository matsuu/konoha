# Last modified by Kimio Kuramitsu kkuramitsu@sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -DKONOHA_OS__LINUX
LDLIBS = -lGL -lglut -lGLU -lkonoha -lpthread

target = linux_32
pkgname = gl

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = $(pkgname).o gl_vectors.o gl_textures.o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

gl_vectors.o: gl_vectors.c
	$(CC) $(CFLAGS) -o $@ -c $^

gl_textures.o: gl_textures.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

