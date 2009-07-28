#modified by goccy@users.sourceforge.jjp

CC = gcc
CPPFLAGS=`pkg-config libgvc --cflags` -Wall -g3 -O0 -fmessage-length=0 -fPIC
LDFLAGS=`pkg-config libgvc --libs`

LDLIBS = -lkonoha $(LDFLAGS)

target = linux_32
pkgname = graphviz

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
