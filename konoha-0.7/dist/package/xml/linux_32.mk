# Last modified by masahiro ide <imasahiro@sourceforge.jp>

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC `xml2-config --cflags`
LDLIBS = -lkonoha `xml2-config --libs`
target = linux_32
pkgname = libxml2
objs = xml.o xmlreader.o

library = "$(pkgname)_$(target).so"

.PHONY: all
all: $(library)
	cat ./src/xml.k ./src/xmlreader.k > ./libxml2.k

xml.o : ./src/xml.c
	$(CC) $(CFLAGS) -c $^ -o $@

xmlreader.o : ./src/xmlreader.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(library): $(objs)
	$(CC) -shared -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

