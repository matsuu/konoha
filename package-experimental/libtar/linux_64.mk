# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -ltar -lkonoha

target = linux_64
pkgname = libtar

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)
	cat ./tar.k > ./libtar.k

objs = tar.o

tar.o: tar.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library) "$(pkgname).k"

