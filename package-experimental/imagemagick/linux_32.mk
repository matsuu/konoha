# Last modified by Shinpei Nakata <kindofbrown@users.sourceforge.jp>

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 `Magick-config --cflags --cppflags`
LDLIBS = -lkonoha `Magick-config --ldflags --libs`

target = linux_32
pkgname = imagemagick

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = "$(pkgname).o" attributes.o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

attributes.o : attributes.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

