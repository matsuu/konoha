#include <konoha.h>

#include <SDL/SDL.h>
#include "knh_sdl.h"

METHOD KeyBoard_getKeySym(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_KeyboardEvent *key = (SDL_KeyboardEvent *)(glue->ptr);
  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.KeySym", &key->keysym, NULL));
}

METHOD KeySym_getSym(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  SDL_keysym *sym = (SDL_keysym *)(glue->ptr);
  KNH_RETURN_Int(ctx, sfp, sym->sym);
}

