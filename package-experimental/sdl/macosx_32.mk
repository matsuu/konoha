# SDL makefile by kindofbrown@users.sourceforge.net 

CC = gcc
CFLAGS = -O2 -Wall -fmessage-length=0 -fPIC -I/Library/Frameworks/SDL.framework/Headers
LDLIBS = -lkonoha -framework SDL -framework Cocoa

target = macosx_32
pkgname = sdl

library = "$(pkgname)_$(target).dylib"

.PHONY: all
all: $(library)

objs = $(pkgname).o sdl_event.o sdl_keyboard.o sdl_color.o sdl_mouse.o sdl_cursor.o SDLmain.o

"$(pkgname).o": $(pkgname).c
	$(CC) $(CFLAGS) -o $@ -c $^

sdl_event.o: sdl_event.c
	$(CC) $(CFLAGS) -o $@ -c $^

sdl_keyboard.o: sdl_keyboard.c
	$(CC) $(CFLAGS) -o $@ -c $^

sdl_color.o: sdl_color.c
	$(CC) $(CFLAGS) -o $@ -c $^

sdl_mouse.o: sdl_mouse.c
	$(CC) $(CFLAGS) -o $@ -c $^

sdl_cursor.o: sdl_cursor.c
	$(CC) $(CFLAGS) -o $@ -c $^

SDLmain.o: SDLmain.m
	$(CC) -x objective-c $(CFLAGS) -o $@ -c $^


$(library): $(objs)
	$(CC) -dynamiclib -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(library)

