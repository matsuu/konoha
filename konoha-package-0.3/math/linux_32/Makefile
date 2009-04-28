#Makefile for "macosx/math.dylib"

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic
LDLIBS = -lm -lkonoha

target = linux_32
pkgname = math

library = "$(target)/$(pkgname).so"

.PHONY: all
all: $(library)

objs = "$(target)/$(pkgname).o"

"$(target)/$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

