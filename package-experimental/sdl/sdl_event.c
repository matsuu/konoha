//
// SDLEvent class
//

#include"knh_sdl.h"

static
void knh_sdlevent_free(Ctx *ctx,knh_Glue_t *g)
{
	free((SDL_Event*)g->ptr);
}

/* SDLEvent SDLEvent.new(void) */
METHOD SDLEvent_new(Ctx *ctx, knh_sfp_t *sfp)
{
	SDL_Event *event = (SDL_Event*)malloc(sizeof(SDL_Event));
	knh_Glue_init(ctx, sfp[0].glue, event, knh_sdlevent_free);
	KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* int SDLEvent.getType(void) */
METHOD SDLEvent_getType(Ctx *ctx, knh_sfp_t* sfp)
{
	SDL_Event *event = ((sfp[0].glue)->ptr);
	KNH_RETURN_Int(ctx,sfp,event->type);
}

/*void new_keysym_from_sdl(SDL_keysym *sdl, knh_sdl_keysym_t *knh)
{
  knh->scancode = sdl->scancode;
  knh->sym = sdl->sym;
  knh->mod = sdl->mod;
  knh->unicode = sdl->unicode;
  }*/

/*void new_keyboard_from_sdl(SDL_KeyboardEvent *sdl, knh_sdl_keyboard_t *knh)
{
  knh->type = sdl->type;
  knh->state = sdl->state;
  knh->keysym = malloc(sizeof(knh_sdl_keysym_t));
  new_keysym_from_sdl(&(sdl->keysym), knh->keysym);
  }*/

/* KeyBoard SDLEvent.getKeyBoard(void) */
METHOD SDLEvent_getKeyBoard(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_Event *event = (SDL_Event *)(glue->ptr);
  
  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.KeyBoard", &event->key, NULL));
}

/* MouseMotion SDLEvent.getMouseMotion(void) */
METHOD SDLEvent_getMouseMotion(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_Event *event = (SDL_Event *)(glue->ptr);

  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.MouseMotion", &event->motion, NULL));
}

/* MouseButton SDLEvent.getMouseButton(void) */
METHOD SDLEvent_getMouseButton(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_Event *event = (SDL_Event *)(glue->ptr);

  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.MouseButton", &event->button, NULL));
}

/* void SDLEvent.pumpEvents(void) */
METHOD SDLEvent_pumpEvents(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_PumpEvents();

  KNH_RETURN_void(ctx,sfp);
}

/* int SDLEvent.peepEvents(Event evt, int num, int action, int mask) */
METHOD SDLEvent_peepEvents(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Event *event = (SDL_Event *)((sfp[1].glue)->ptr);
  int num = p_int(sfp[2]);
  int action = p_int(sfp[3]);
  Uint32 mask = p_int(sfp[4]);
  int ret = SDL_PeepEvents(event, num, action, mask);
  if( ret == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_Int(ctx, sfp, ret);
}

/* int SDLEvent.pollEvent(Event evt) */
METHOD SDLEvent_pollEvent(Ctx* ctx,knh_sfp_t *sfp)
{
	SDL_Event *event = ((sfp[1].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,SDL_PollEvent(event));
}

/* int SDLEvent.waitEvent(Event evt) */
METHOD SDLEvent_waitEvent(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret;
  SDL_Event *event = (SDL_Event *)((sfp[1].glue)->ptr);
  if((ret = SDL_WaitEvent(event)) == 0){
    fprintf(stderr,"error:%s\n",SDL_GetError());
  }

  KNH_RETURN_Int(ctx, sfp, ret);
}

/* void SDLEvent.pushEvent(Event evt) */
METHOD SDLEvent_pushEvent(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Event *event = ((sfp[1].glue)->ptr);
  if(SDL_PushEvent(event)==-1){
    fprintf(stderr,"error:%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx, sfp);
}

// METHOD SDLEvent_setEventFilter(Ctx* ctx, knh_sfp_t *sfp)
// METHOD SDLEvent_getEventFilter(Ctx* ctx, knh_sfp_t *sfp)


/* int SDLEvent.eventState(int type, int state) */
METHOD SDLEvent_eventState(Ctx* ctx, knh_sfp_t *sfp)
{
  Uint8 type = p_int(sfp[1]);
  int state = p_int(sfp[2]);
  int ret = SDL_EventState(type, state);

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* int[] SDLEvent.getKeyState(int[] numkeys) */
/*METHOD SDLEvent_getKeyState(Ctx* ctx,knh_sfp_t *sfp)
{
  int *key = (int*)((sfp[1].glue)->ptr);
  int *ret = SDL_GetKeyState(key);
  KNH_RETURN_void(ctx,sfp);
  }*/

/* int SDLEvent.getModState(void) */
METHOD SDLEvent_getModstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret = SDL_GetModState();

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* void SDLEvent.setModState(int modstate) */
METHOD SDLEvent_setModstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int modstate = p_int(sfp[1]);
  SDL_SetModState(modstate);

  KNH_RETURN_void(ctx,sfp);
}

/* String SDLEvent.getKeyName(int key) */
METHOD SDLEvent_getKeyname(Ctx* ctx, knh_sfp_t *sfp)
{
  int key = p_int(sfp[1]);
  char* ret = SDL_GetKeyName(key);

  KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}


/* int SDLEvent.enableUNICODE(int enable) */
METHOD SDLEvent_enableUNICODE(Ctx* ctx, knh_sfp_t *sfp)
{
  int enable = p_int(sfp[1]);
  int ret = SDL_EnableUNICODE(enable);

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* void SDLEvent.enableKeyRepeat(int delay, int interval) */
METHOD SDLEvent_enableKeyRepeat(Ctx* ctx, knh_sfp_t *sfp)
{
  int delay = p_int(sfp[1]);
  int interval = p_int(sfp[2]);
  if(SDL_EnableKeyRepeat(delay, interval) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

//METHOD SDLEvent_getMouseState(Ctx* ctx, knh_sfp_t *sfp)
//METHOD SDLEvent_getRelativemouseState(Ctx* ctx, knh_sfp_t *sfp)

/* int SDLEvent.getAppState(void) */
METHOD SDLEvent_getAppState(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret = SDL_GetAppState();

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* int SDLEvent.joystickEventState(int state) */
METHOD SDLEvent_joystickEventState(Ctx* ctx, knh_sfp_t *sfp)
{
  int state = p_int(sfp[1]);
  int ret = SDL_JoystickEventState(state);

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* SDLEvent Original */

/* int SDLEvent.getButton(); */
METHOD SDLEvent_getButton(Ctx *ctx,knh_sfp_t *sfp)
{
	SDL_Event *sdl_ev = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,sdl_ev->button.button);
}

/* int SDLEvent.getButtonX(); */
METHOD SDLEvent_getButtonX(Ctx *ctx,knh_sfp_t *sfp)
{
	SDL_Event *sdl_ev = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,sdl_ev->button.x);
}

/* int SDLEvent.getButtonY(); */
METHOD SDLEvent_getButtonY(Ctx *ctx,knh_sfp_t *sfp)
{
	SDL_Event *sdl_ev = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,sdl_ev->button.y);
}

/* int SDLEvent.getKeySym(); */
METHOD SDLEvent_getKeySym(Ctx *ctx,knh_sfp_t *sfp)
{
	SDL_Event *sdl_ev = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,sdl_ev->key.keysym.sym);
}


