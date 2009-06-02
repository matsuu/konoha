#include<konoha.h>
#include<SDL/SDL.h>
#include"knh_sdl.h"

METHOD Color_setColors(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Color *c = ((sfp[0].glue)->ptr);
  SDL_Surface *s = ((sfp[1].glue)->ptr);
  int fstcolor = p_int(sfp[2]);
  int ncolor = p_int(sfp[3]);
  if(SDL_SetColors(s,c,fstcolor,ncolor) == 0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx, sfp);
}
