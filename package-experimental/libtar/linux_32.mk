# modified by u.hira@users.sourceforge.jp

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -g3
LDLIBS = -ltar -lkonoha
target = linux_32
pkgname = libtar
objs = tar.o

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)
	cat ./tar.k > ./libtar.k

tar.o: tar.c
	$(CC) $(CFLAGS) -o $@ -c $^
	
$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)
	
.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)
	
