#Makefile

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -lcurl -lkonoha

target = macosx_32
pkgname = curl

library = "$(target)/$(pkgname).dylib"

.PHONY: all
all: $(library)

objs = "$(target)/$(pkgname).o"

"$(target)/$(pkgname).o": $(pkgname).c
	mkdir -p $(target)
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

