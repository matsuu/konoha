# Last modified by kindofbrown kindofbrown@users.sourceforge.jp

CC = gcc
CFLAGS = -O0 -g3 -Wall -fmessage-length=0 -fPIC
LDLIBS = -framework GLUT -framework OpenGL -lkonoha -lpthread

target = macosx_32
pkgname = opengl

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = $(pkgname).o gl_vectors.o gl_textures.c

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

gl_vectors.o: gl_vectors.c
	$(CC) $(CFLAGS) -o $@ -c $^

gl_textures.o: gl_textures.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

