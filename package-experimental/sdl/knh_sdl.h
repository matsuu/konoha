#include <konoha.h>
#ifdef KONOHA_OS__MACOSX
#include <SDL.h>
#else
#include<SDL/SDL.h>
#endif

typedef struct knh_sdl_rect_t {
  knh_int_t x;
  knh_int_t y;
  knh_int_t w;
  knh_int_t h;
} knh_sdl_rect_t;

typedef struct knh_sdl_color_t {
  knh_int_t r;
  knh_int_t g;
  knh_int_t b;
} knh_sdl_color_t;

typedef struct knh_sdl_active_t {
  knh_int_t type;
  knh_int_t gain;
  knh_int_t state;
} knh_sdl_active_t;

typedef struct knh_sdl_keysym_t {
  knh_int_t scancode;
  knh_int_t sym;
  knh_int_t mod;
  knh_int_t unicode;
} knh_sdl_keysym_t;

typedef struct knh_sdl_keyboard_t {
  knh_int_t type;
  knh_int_t state;
  knh_sdl_keysym_t* keysym;
} knh_sdl_keyboard_t;

typedef struct knh_sdl_mousemotion_t {
  knh_int_t type;
  knh_int_t state;
  knh_int_t x;
  knh_int_t y;
  knh_int_t xrel;
  knh_int_t yrel;
} knh_sdl_mousemotion_t;

typedef struct knh_sdl_mousebutton_t {
  knh_int_t type;
  knh_int_t button;
  knh_int_t state;
  knh_int_t x;
  knh_int_t y;
} knh_sdl_mousebutton_t;

typedef struct knh_sdl_resize_t {
  knh_int_t type;
  knh_int_t w;
  knh_int_t h;
} knh_sdl_resize_t;

typedef struct knh_sdl_expose_t {
  knh_int_t type;
} knh_sdl_expose_t;

typedef struct knh_sdl_quit_t {
  knh_int_t type;
} knh_sdl_quit_t;

typedef struct knh_sdl_event_t {
  knh_int_t type;
  knh_sdl_active_t active;
  knh_sdl_keyboard_t key;
  knh_sdl_mousemotion_t motion;
  knh_sdl_mousebutton_t button;
  knh_sdl_resize_t resize;
  knh_sdl_expose_t expose;
  knh_sdl_quit_t quit;
} knh_sdl_event_t;


/*
class KeySym
{
	int scancode;
	int sym;
	int mode;
	int unicode;
	KeySym(int scancode, int sym, int mode, int unicode){
		   _scancode = scancode; _sym = sym; _mode = mode; _unicode = unicode;
	}
};

class KeyBoard
{
	int type;
	int state;
	KeySym keysym;
	KeyBoard(int type, int state, KeySym keysym){
		     _type = type; _state = state; _keysym = keysym;
	}
}

class MouseMotion
{
	int type;
	int state;
	int x;
	int y;
	int xrel;
	int yrel;
	MouseMotion(int type, int state, int x, int y, int xrel, int yrel){
			_type = type; _state = state;
			_x = x;
			_y = y;
			_xrel = xrel;
			_yrel = yrel;
	}
};

class MouseButton
{
	int type;
	int button;
	int state;
	int x;
	int y;
	MouseButton(int type, int button, int state, int x, int y){
			_type = type;
			_button = button;
			_state = state;
			_x = x;
			_y = y;
	}
};

class Active
{
	int type;
	int gain;
	int state;
	Active(int type, int gain, int state){
		   _type = type;
		   _gain = gain;
		   _state = state;
	}
};

class Resize
{
	int type;
	int w;
	int h;
	Resize(int type, int w, int h){
		   _type = type;
		   _w = w;
		   _h = h;
	}
};

class Expose
{
	int type;
	Expose(int type){
		   _type = type;
	}
};

class Quit
{
	int type;
	Quit(int type){
		 _type = type;
	}
};

class Event
{
	int type;
	Active active;
	KeyBoard key;
	MouseMotion motion;
	MouseButton button;
	Resize resize;
	Expose expose;
	Quit quit;
	Event(int type, Active active, KeyBoard key, MouseMotion motion, MouseButton button, Resize resize, Expose expose, Quit quit){
		  _type = type; _active = active; _key = key; _motion = motion; _button = button; _resize = resize; _expose = expose; _quit = quit;
	}

}

*/
