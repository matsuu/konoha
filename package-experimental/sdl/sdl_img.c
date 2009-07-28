#include"knh_sdl.h"

/*
METHOD SDL_imgLoad(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *image;
  image=IMG_Load("sample.bmp");
  if(image==NULL){
    fprintf(stderr,"%s\n",IMG_GetError());
    SDL_Quit();
  }
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",image,NULL));
}

METHOD SDL_imgLoadRW(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *image;
  image=IMG_Load_RW(SDL_RWFromFile("sample.png","rb"),1);
  if(image==NULL){
    fprintf(stderr,"%s\n",IMG_GetError());
  }
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",image,NULL));
}
*/

/* Surface SDL.imgLoad(String file_name) */
METHOD SDL_imgLoad(Ctx *ctx,knh_sfp_t *sfp)
{
	char* file_name = p_char(sfp[1]);
	SDL_Surface *image = IMG_Load(file_name);
	if(image==NULL){
		fprintf(stderr,"%s\n",IMG_GetError());
		SDL_Quit();
	}
	
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",image,NULL));
}

/* Surface SDL.imgLoadRW() */
