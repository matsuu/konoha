#include <konoha.h>

#include <SDL/SDL.h>
#include "knh_sdl.h"

METHOD Event_new(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = (void *)malloc(sizeof(SDL_Event));
  KNH_RETURN(ctx, sfp, sfp[0].o);

}

METHOD Event_getType(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_Event *event = (SDL_Event *)(glue->ptr);
  KNH_RETURN_Int(ctx, sfp, event->type);
}

void new_keysym_from_sdl(SDL_keysym *sdl, knh_sdl_keysym_t *knh)
{
  knh->scancode = sdl->scancode;
  knh->sym = sdl->sym;
  knh->mod = sdl->mod;
  knh->unicode = sdl->unicode;
}

void new_keyboard_from_sdl(SDL_KeyboardEvent *kb, knh_sdl_keyboard_t *kkb)
{
  kkb->type = kb->type;
  kkb->state = kb->state;
  kkb->keysym = malloc(sizeof(knh_sdl_keysym_t));
  new_keysym_from_sdl(&(kb->keysym), kkb->keysym);
}

METHOD Event_getKeyBoard(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_Event *event = (SDL_Event *)(glue->ptr);
  //  knh_sdl_keyboard_t *keyboard = malloc(sizeof(knh_sdl_keyboard_t));
  //  new_keyboard_from_sdl(&(event->key), keyboard);
  
  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.KeyBoard", &event->key, NULL));
}
