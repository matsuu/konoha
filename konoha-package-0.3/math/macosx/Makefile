#Makefile for "macosx/math.dylib"

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC
LDLIBS = -lm -lkonoha
target = macosx

library = "$(target)/math.dylib"

.PHONY: all
all: $(library)

objs = "$(target)/math.o"

"$(target)/math.o": math.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

