
CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0
LDLIBS = -lkonoha 
library = time.so
.PHONY: all
all: $(library)

objs = time.o
file.o: time.c
	$(CC) $(CFLAGS) -o $@ -c $^
$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)
.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

.PHONY: konoha_install
konoha_install: $(library)
	mkdir -p .konoha/time
	cp $(library) .konoha/time
	cp time.k .konoha/time
