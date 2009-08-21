# Last modified by Shinpei Nakata <kindofbrown@users.sourceforge.jp>

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 `MagickWand-config --cflags --cppflags`
LDLIBS = -lkonoha `MagickWand-config --ldflags --libs`

target = macosx_32
pkgname = imagemagick

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = "$(pkgname).o" attributes.o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

attributes.o : attributes.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

