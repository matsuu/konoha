#Makefile for "macosx/math.dylib"

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fpic
LDLIBS = -lm -lkonoha
target = linux 

library = "$(target)/math.so"

.PHONY: all
all: $(library)

objs = "$(target)/math.o"

"$(target)/math.o": math.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -shared -Wl -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

