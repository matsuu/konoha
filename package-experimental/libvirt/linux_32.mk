# Last modified by masahiro ide <imasahiro@sourceforge.jp>

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -lkonoha -lvirt
target = linux_32
pkgname = libvirt
objs = libvirt.o

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

libvirt.o : ./libvirt.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(library): $(objs)
	$(CC) -shared -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

