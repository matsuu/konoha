# modified by goccy@users.sourceforge.jp
LIBSENT=libsent
LIBJULIUS=libjulius

CC = gcc
CPPFLAGS= -g3 -O0 -Wall -fmessage-length=0 -fPIC -I$(LIBJULIUS)/include -I$(LIBSENT)/include  `libsent-config --cflags` `libjulius-config --cflags`
LDFLAGS= -L$(LIBJULIUS) `libjulius-config --libs` -L$(LIBSENT) `libsent-config --libs`

LDLIBS = -lkonoha $(LDFLAGS)

target = linux_32
pkgname = julius

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)

objs = "$(pkgname).o"

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $^ $(LDFLAGS)

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS) $(LDFLAGS)


.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library) *~
