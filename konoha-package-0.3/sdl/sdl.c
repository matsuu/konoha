#include<konoha.h>
#ifdef KONOHA_OS__MACOSX
#include <SDL.h>
#else
#include<SDL/SDL.h>
#include"knh_sdl.h"
//#include<SDL/SDL_opengl.h>
#endif
//#include<SDL/SDL_image.h>

/* General */


METHOD SDL_testColor(Ctx* ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *g = sfp[1].glue;
  knh_sdl_color_t *c = (knh_sdl_color_t*)(g->ptr);
  printf("%lld %lld %lld\n", c->r, c->g, c->b);

}


METHOD SDL_testRect(Ctx* ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *g = sfp[1].glue;
  knh_sdl_rect_t *r = (knh_sdl_rect_t*)(g->ptr);
  printf("%lld %lld %lld %lld\n", r->x, r->y, r->w, r->h);
}

/* void SDL.init(int flags) */

METHOD SDL_init(Ctx* ctx,knh_sfp_t* sfp)
{
  int flags = p_int(sfp[1]);
  if(SDL_Init((Uint32)flags) == -1){
    fprintf(stderr,"initialize error %s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.initSubSystem(int flags) */

METHOD SDL_initSubSystem(Ctx* ctx,knh_sfp_t* sfp)
{
  int flags = p_int(sfp[1]);
  if(SDL_InitSubSystem(flags)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.quit() */

METHOD SDL_quit(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_Quit();

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.quitSubSystem(int flags) */

METHOD SDL_quitSubSystem(Ctx* ctx,knh_sfp_t* sfp)
{
  int flags = p_int(sfp[1]);
  SDL_QuitSubSystem((Uint32)flags);

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.wasInit(int flags) */

METHOD SDL_wasInit(Ctx* ctx,knh_sfp_t* sfp)
{
  int flags = p_int(sfp[1]);
  if(SDL_WasInit(flags)!=0){
    printf("It is initialized\n");
  } else {
    printf("It is not initialized\n");
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.getError */

METHOD SDL_getError(Ctx* ctx,knh_sfp_t* sfp)
{
  printf("%s\n",SDL_GetError());

  KNH_RETURN_void(ctx,sfp);
}

/* Video */

/* Surface SDL.getVideoSurface() */

METHOD SDL_getVideoSurface(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_Surface* ret;
  ret = SDL_GetVideoSurface();

  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",ret,NULL));
}

/* VideoInfo SDL.getVideoInfo() */

METHOD SDL_getVideoInfo(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_VideoInfo* ret;
  ret = SDL_GetVideoInfo();

  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.VideoInfo",ret,NULL));
}


/* void SDL.videoDriveName(String namebuf, int maxlen) */

METHOD SDL_videoDriverName(Ctx* ctx,knh_sfp_t *sfp)
{
  char* ret;
  char* namebuf = p_char(sfp[1]);
  int maxlen = p_int(sfp[2]);
  ret = SDL_VideoDriverName(namebuf, maxlen);
  if(ret == NULL){
    printf("Video is initialized\n");
    KNH_RETURN_void(ctx,sfp);
  }

  KNH_RETURN(ctx,sfp,ret);
}

/* void SDL.listModes(PixelFormat fmt, int flags) */
//todo
/*
METHOD SDL_listModes(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_PixelFormat* fmt = ((sfp[1].glue)->ptr);
  int flags = p_int(sfp[2]);
  int i;
  SDL_Rect** ret = SDL_ListModes(NULL,flags);
  if(ret == (SDL_Rect**)0){
    fprintf(stderr,"%s\n", SDL_GetError());
  } else if((SDL_Rect**)-1){
    printf("Enable All\n");
  } else {
    printf("Enable Mode\n");
    for(i = 0; ret[i]; ++i){
      printf("%d x %d\n", ret[i]->w, ret[i]->h);
    } 
  }
   
  KNH_RETURN_void(ctx,sfp);
}
*/
/* void SDL.videoModeOK(int width, int height, int bpp, int flags) */

METHOD SDL_videoModeOK(Ctx* ctx,knh_sfp_t *sfp)
{
  int width = p_int(sfp[1]);
  int height = p_int(sfp[2]);
  int bpp = p_int(sfp[3]);
  int flags = p_int(sfp[4]);
  int chk = SDL_VideoModeOK(width, height, bpp, flags);
  if(chk == 0){
    printf("Unusable mode\n");
  } else {
    printf("Reccommend %dbpp\n",chk);
  }

  KNH_RETURN_void(ctx,sfp);
}

/* Suface SDL.setVideoMode(int width, int height, int bpp, int flags) */   

METHOD SDL_setVideoMode(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *ret;
  int width = p_int(sfp[1]);
  int height = p_int(sfp[2]);
  int bpp = p_int(sfp[3]);
  int flags = p_int(sfp[4]);
  ret = SDL_SetVideoMode(width, height, bpp, flags);  
  if(ret == NULL){
    fprintf(stderr,"create screen error %s\n",SDL_GetError());
    SDL_Quit();
  }

  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.Surface", ret, NULL));
}

/* void Surface.updateRect(self, int x, int y, int width, int height) */

METHOD Surface_updateRect(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *self = ((sfp[0].glue)->ptr);
  int x = p_int(sfp[1]);
  int y = p_int(sfp[2]);
  int width = p_int(sfp[3]);
  int height = p_int(sfp[4]);
  SDL_UpdateRect(self, x, y, width, height);

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.updateRects(Surface screen, int numrects, Rect rects) */
/*
METHOD SDL_updateRects(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_UpdateRects((sfp[1].glue)->ptr,sfp[2].ivalue,(sfp[3].glue)->ptr);

  KNH_RETURN_void(ctx,sfp);
}
*/
      
/* void Surface.flip(self) */ 
 
METHOD Surface_flip(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *self = ((sfp[0].glue)->ptr);
  if( SDL_Flip(self) ==-1){
    fprintf(stderr,"flip error %s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.setColors(Surface screen, Color color, int firstcolor, int ncolors) */
/*
METHOD SDL_setColos(Ctx* ctx,knh_sfp_t *sfp)
{
  if(SDL_SetColors((sfp[1].glue)->ptr,(sfp[2].glue)->ptr,sfp[3].ivalue,sfp[4].ivalue)==0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.setPalette(Surface screen, int flags, Color color, int firstcolor, int ncolors) */
 /*
METHOD SDL_setPalette(Ctx* ctx,knh_sfp_t *sfp)
{
  if(SDL_SetPalette((sfp[1].glue)->ptr,sfp[2].ivalue,(sfp[3].glue)->ptr,sfp[4].ivalue,sfp[5].ivalue)==0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}
 */

/* void SDL.setGamma(float redgamma, float greengamma, float bluegamma) */
/*
METHOD SDL_setGamma(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_GetGammaRamp(sfp[1].fvalue,sfp[2].fvalue,sfp[3].fvalue)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.getGammaRamp(int redtable, int greentable, int bluetable) */
/*
METHOD SDL_getGammaRamp(Ctx* ctx, knh_sfp_t *sfp)
{
  int redtable = p_int(sfp[1]);
  int greentable = p_int(sfp[2]);
  int bluetable = p_int(sfp[3]);
  if(SDL_GetGammaRamp(&redtable. &greentable. &bluetable)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.setGammaRamp(int redtable, int greentable, int bluetable) */
 /* 
METHOD SDL_setGammaramp(Ctx* ctx, knh_sfp_t *sfp)
{
  int redtable = p_int(sfp[1]);
  int greentable = p_int(sfp[2]);
  int bluetable = p_int(sfp[3]);
  if(SDL_SetGammaRamp(&redtable, &greentable, &bluetable)==-1)){
      fprintf(stderr,"%s\n",SDL_GetError());
    }

    KNH_RETURN_void(ctx,sfp);
}
*/

/* int Surface.mapRGB(self, int red, int green, int blue) */

METHOD Surface_mapRGB(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  Uint8 red = p_int(sfp[1]);
  Uint8 green = p_int(sfp[2]);
  Uint8 blue = p_int(sfp[3]);
  int ret;
  ret = SDL_MapRGB(self->format, red, green, blue);

  KNH_RETURN_Int(ctx, sfp, ret);
}

/* int SDL.mapRGBA(PexelFormat fmt, int red, int green, int blue, int alpha) */
 /*
METHOD SDL_mapRGBA(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret;
  SDL_pixelFormat* fmt = ((sfp[1].glue)->ptr);
  int red = p_int(sfp[2]);
  int green = p_int(sfp[3]);
  int blue = p_int(sfp[4]);
  int alpha = p_int(sfp[5]);
  pixel = SDL_MapRGBA(fmt, red, green, blue, alpha);

  KNH_RETURN_Int(ctx,sfp,ret);
}
 */

/* void SDL.getRGB(int pixel, PixelFormat fmt, int red, int green, int blue) */
/*
METHOD SDL_getRGB(Ctx* ctx, knh_sfp_t *sfp)
{
  int pixel = p_int(sfp[1]);
  SDL_PixelFormat* fmt = ((sfp[2].glue)->glue);
  int red = p_int(sfp[3]);
  int green = p_int(sfp[4]);
  int blue = p_int(sfp[5]);
  SDL_GetRGB(pixel, fmt, red, green, blue);

  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.getRGBA(int pixel, PixelFormat fmt, int red, int green, int blue, int alpha) */
 /*
METHOD SDL_getRGBA(Ctx* ctx, knh_sfp_t *sfp)
{
  int pixel = p_int(sfp[1]);
  SDL_PixelFormat* fmt = ((sfp[2].glue)->ptr);
  int red = p_int(sfp[3]);
  int green = p_int(sfp[4]);
  int blue = p_int(sfp[5]);
  int alpha = p_int(sfp[6]);
  SDL_GetRGBA(pixel, fmt, red, green, blue, alpha);

  KNH_RETURN_void(ctx,sfp);
}
 */

/* Surface SDL.createRGBSurface(int flags, int w, int h, int d, int rmask, int gmask, int bmask, int amask) */

METHOD SDL_createRGBSurface(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* ret;
  Uint32 flags = p_int(sfp[1]);
  int width = p_int(sfp[2]);
  int height = p_int(sfp[3]);
  int depth = p_int(sfp[4]);
  Uint32 rmask = p_int(sfp[5]);
  Uint32 gmask = p_int(sfp[6]);
  Uint32 bmask = p_int(sfp[7]);
  Uint32 amask = p_int(sfp[8]);
  ret = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
  if(ret == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.Surface", ret, NULL));
}

/* Surface SDL.createRGBsurfaceFrom(void[] pixels, int width, int height, int depth, int pitch, int rmask, int gmask, int bmask, int amask) */
//TODO
METHOD SDL_createRGBsurfaceFrom(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* ret;
  void* pixels = ((sfp[1].glue)->ptr);
  int width = p_int(sfp[2]);
  int height = p_int(sfp[3]);
  int depth = p_int(sfp[4]);
  int pitch = p_int(sfp[5]);
  int rmask = p_int(sfp[6]);
  int gmask = p_int(sfp[7]);
  int bmask = p_int(sfp[8]);
  int amask = p_int(sfp[9]);
  ret = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
  if(ret == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN(ctx, sfp, new_Glue(ctx, "sdl.Surface", ret, NULL));
}
 
/* void Surface.freeSurface(self) */

METHOD Surface_freeSurface(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  SDL_FreeSurface(self);

  KNH_RETURN_void(ctx,sfp);
}

/* void Surface.lockSurface(self) */

METHOD Surface_lockSurface(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  if(SDL_LockSurface(self)== -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void Surface.unLockSurface(self) */

METHOD Surface_unLockSurface(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  SDL_UnlockSurface(self);

  KNH_RETURN_void(ctx,sfp);
}

/* Surface SDL.loadBMP(String file) */ 

METHOD SDL_loadBMP(Ctx* ctx, knh_sfp_t *sfp)
{
  char* file = p_char(sfp[1]);
  SDL_Surface *image = SDL_LoadBMP(file);
  if(image == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
    SDL_Quit();
  }

  KNH_RETURN(ctx,sfp,new_Glue(ctx, "sdl.Surface",image,NULL));
}

/* void Suface.saveBMP(self, String file) */

METHOD Surface_saveBMP(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  char* file = p_char(sfp[1]);
  if(SDL_SaveBMP(self, file) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void Surface.setColorKey(self, int flag, int key) */

METHOD Surface_setColorKey(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  int flag = p_int(sfp[1]);
  if(SDL_SetColorKey(self, flag, (*(Uint8*)self->pixels) ) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void Surface.setAlpha(self, int flag, int alpha) */

METHOD Surface_setAlpha(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  Uint32 flag = p_int(sfp[1]);
  Uint8 alpha = p_int(sfp[2]);
  if(SDL_SetAlpha(self, flag, alpha) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void SDL.setClipRect(Surface screen, Rect rect) */
/*
METHOD SDL_setClipRect(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* screen = ((sfrp[1].glue)->ptr);
  SDL_Rect* rect = ((sfp[2].glue)->ptr);
  SDL_SetClipRect(screen, rect);

  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.getClipRect(Surface screen, Rect rect) */
 /*
METHOD SDL_getClipRect(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* screen = ((sfp[1].glue)->ptr);
  SDL_Rect* rect = ((sfp[2].glue)->ptr);
  SDL_GetClipRect(screen, rect);

  KNH_RETURN_void(ctx,sfp);
}
 */

/* Surface SDL.convertSurface(Surface screen, PixelFormat fmt, int flags) */
  /*
METHOD SDL_convertSurface(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* screen = ((sfp[1].glue)->ptr);
  SDL_PixelFormat* fmt = ((sfp[2].glue)->ptr);
  int flags = p_int(sfp[3]);
  SDL_Surface* ret = SDL_ConvertSurface(screen, fmt, flags);
  if(ret == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",ret,NULL));
}
  */
  
/* void Surface.blitSurface(self, Surface screen) */
 
METHOD Surface_blitSurface(Ctx* ctx,knh_sfp_t *sfp)
{

  SDL_Surface *self = (SDL_Surface*)((sfp[0].glue)->ptr);
  knh_sdl_rect_t* rect1 = (knh_sdl_rect_t*)((sfp[1].glue)->ptr);
  SDL_Surface *screen = (SDL_Surface*)((sfp[2].glue)->ptr);
  knh_sdl_rect_t* rect2 = (knh_sdl_rect_t*)((sfp[3].glue)->ptr);
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  srcrect.x = (Sint16)rect1->x;
  srcrect.y = (Sint16)rect1->y;
  srcrect.w = (Uint16)rect1->w;
  srcrect.h = (Uint16)rect1->h;
  dstrect.x = (Sint16)rect2->x;
  dstrect.y = (Sint16)rect2->y;
  dstrect.w = (Uint16)rect2->w;
  dstrect.h = (Uint16)rect2->h;
  if(SDL_BlitSurface(self, &srcrect, screen, &dstrect) != 0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* void Surface.fillRect(self, Rect dstrect, int color) */
/*
METHOD Surface_fillRect(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  SDL_Rect* rect = ((sfp[1].glue)->ptr);
  int i1 = p_int(sfp[2]);
  if(SDL_FillRect(self, rect, i1)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
*/

/* Surface Surface.displayFormat(self) */

METHOD Surface_displayFormat(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *self = ((sfp[0].glue)->ptr);
  if((SDL_DisplayFormat(self)) == NULL ){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sdl.Surface",self,NULL));
}

/* Surface Surface.displayFormatAlpha(self) */

METHOD Surface_displayFormatAlpha(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface *self = SDL_DisplayFormatAlpha((sfp[0].glue)->ptr);
  if(self == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sdl.Surface",self,NULL));
}


/* void SDL.warpMouse(int x, int y) */

METHOD SDL_warpMouse(Ctx* ctx, knh_sfp_t *sfp)
{
  int x = p_int(sfp[1]);
  int y = p_int(sfp[2]);
  SDL_WarpMouse(x, y);

  KNH_RETURN_void(ctx,sfp);
}

/* Cursor SDL.createCursor(int[] data, int[] mask, int width, int height, int hot_x, int hot_y) */
//TODO
METHOD SDL_createCursor(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Cursor* ret;
  Uint8 data = p_int(sfp[1]);
  Uint8 mask = p_int(sfp[2]);
  int width = p_int(sfp[3]);
  int height = p_int(sfp[4]);
  int hot_x = p_int(sfp[5]);
  int hot_y = p_int(sfp[6]);
  ret = SDL_CreateCursor(&data, &mask, width, height, hot_x, hot_y);

  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sdl.Cursor", ret, NULL));
}

/* void Cursor.freeCursor(self) */

METHOD Cursor_freeCursor(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Cursor* self = ((sfp[0].glue)->ptr);
  SDL_FreeCursor(self);

  KNH_RETURN_void(ctx,sfp);
}

/* void Cursor.setCursor(self) */
METHOD Cursor_setCursor(Ctx* ctx, knh_sfp_t *sfp)
 {  
   SDL_Cursor* self = ((sfp[0].glue)->ptr);
   SDL_SetCursor(self);

   KNH_RETURN_void(ctx,sfp);
 }

/* Cursor SDL.getCursor(void) */

METHOD SDL_getCursor(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Cursor* ret = SDL_GetCursor();

  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sdl.Cursor", ret, NULL));
}
  
/* int SDL.showCursor(int toggle) */   

METHOD SDL_showCursor(Ctx* ctx, knh_sfp_t *sfp)
{
  int toggle = p_int(sfp[1]);
  int ret = SDL_ShowCursor(toggle);

  KNH_RETURN_Int(ctx,sfp,ret);
}
   
/* void SDL.glLoadLibrary(String path) */

/*METHOD SDL_glLoadLibrary(Ctx* ctx, knh_sfp_t *sfp)
{
  char* path = p_char(sfp[1]);
  if(SDL_GL_LoadLibrary(path) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
*/

/* void[] SDL.glGetProcAddress(String proc) */

/*METHOD SDL_glGetprocaddress(Ctx* ctx, knh_sfp_t *sfp)
{
  char* proc = p_char(sfp[1]);
  void* ret = SDL_GL_GetProcAddress(proc);


  }*/

/* void SDL.glGetAttribute(int attr) */

 /*METHOD SDL_glGetAttribute(Ctx* ctx, knh_sfp_t *sfp)
{
  int attr = p_int(sfp[1]);
  int* ret = NULL;
  if(SDL_GL_GetAttribute(attr, ret) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
 */

/* void SDL.glSetAttribute(int attr, int value) */

  /*METHOD SDL_glSetAttribute(Ctx* ctx, knh_sfp_t *sfp)
{
  int i1 = p_int(sfp[1]);
  int i2 = p_int(sfp[2]);
  if(SDL_GL_SetAttribute(i1, i2)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
  */

/* void SDL.glSwapBuffers(void) */
 /*
METHOD SDL_glSwapBuffers(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_GL_SwapBuffers();

  KNH_RETURN_void(ctx,sfp);
}
 */

/* Overlay SDL.createYUVoverlay(int width, int height, int fmt, Surface display) */
  /*
METHOD SDL_createYUVoverlay(Ctx* ctx, knh_sfp_t *sfp)
{
  int width = p_int(sfp[1]);
  int height = p_int(sfp[2]);
  int fmt = p_int(sfp[3]);
  SDL_Surface* display = ((sfp[4].glue)->ptr);
  SDL_Overlay* ret = SDL_CreateYUVOverlay(width, height, fmt, display);

  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Overlay",ret,NULL));
}
  */

/* void SDL.lockYUVoverlay(Overlay ol) */
   /*
METHOD SDL_lockYUVoverlay(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Overlay* ol = ((sfp[1].glue)->ptr);
  if(SDL_LockYUVOverlay(ol) == -1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
   */

/* SDL.unLockYUVoverlay(Overlay ol) */
    /*
METHOD SDL_unLockYUVoverlay(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Overlay* ol = ((sfp[1].glue)->ptr);
  SDL_UnlockYUVOverlay(ol);

  KNH_RETURN_void(ctx,sfp);
}
    */

     /* void SDL.displayYUVoverlay(Overlay ol, Rect dstrect) */
     /*
METHOD SDL_displayYUVoverlay(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Overlay* ol = ((sfp[1].glue)->glue);
  SDL_Rect* dstrect = ((sfp[2].glue)->glue);
  if(SDL_DisplayYUVOverlay(ol, dstrect)!=0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}
*/

/* void SDL.freeYUVoverlay(Overlay ol) */ 
      /*
METHOD SDL_freeYUVoverlay(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Overlay* ol = ((sfp[1].glue)->ptr);
  SDL_FreeYUVOverlay(ol);

  KNH_RETURN_void(ctx,sfp);
}
*/

/* Window Management */

/* String SDL.wmSetCaption(String title) */       

METHOD SDL_wmSetCaption(Ctx* ctx, knh_sfp_t *sfp)
{
  char* title = p_char(sfp[1]);
  SDL_WM_SetCaption(title, title);
  
  KNH_RETURN(ctx, sfp, new_String(ctx, B(title), NULL));
}

/* void String.wmGetCaption(String title) */

METHOD String_wmGetCaption(Ctx* ctx, knh_sfp_t *sfp)
{
  char* title = p_char(sfp[0]);
  SDL_WM_GetCaption(&title,&title);
  if(title){
    printf("Title was set to: %s\n",title);
  } else {
    printf("No window title was set !\n");
  }

  KNH_RETURN_void(ctx, sfp);
}

/* void SDL.wmSetIcon(Surface icon, int mask) */

METHOD SDL_wmSetIcon(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* icon = ((sfp[1].glue)->ptr);
  Uint8 mask = p_int(sfp[2]);
  SDL_WM_SetIcon(icon, &mask);

  KNH_RETURN_void(ctx,sfp);
}

/* int SDL.wmIconifyWindow(void) */

METHOD SDL_wmIconifyWindow(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret = SDL_WM_IconifyWindow();
  if(ret == 0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_Int(ctx, sfp, ret);
}


/* void Surface.wmToggleFullScreen(self) */ 
//todo
METHOD Surface_wmToggleFullScreen(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Surface* self = ((sfp[0].glue)->ptr);
  if(SDL_WM_ToggleFullScreen(self)==0){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

/* Grubmode SDL.wmGrabInput(Grubmod grabmode) */

METHOD SDL_wmGrabInput(Ctx* ctx, knh_sfp_t *sfp)
{
  int grabmode = p_int(sfp[1]);
  int ret = SDL_WM_GrabInput(grabmode);

  KNH_RETURN_Int(ctx, sfp, ret);
}


/* Event */

/* void SDL.pumpEvents(void) */

METHOD SDL_pumpEvents(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_PumpEvents();

  KNH_RETURN_void(ctx,sfp);
}

/*
METHOD SDL_peepEvents(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_PeepEvents((sfp[1].glue)->ptr, sfp[2].ivalue, sfp[3].ivalue, sfp[4].ivalue)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}
   */

 /* void SDL.pollEvent(Event evt) */
METHOD SDL_pollEvent(Ctx* ctx,knh_sfp_t *sfp)
{
  SDL_Event *event = ((sfp[1].glue)->ptr);
  if(SDL_PollEvent(event)==0){
    printf("Nothing Event\n");
  }

  KNH_RETURN_void(ctx,sfp);
}

/* int SDL.waitEvent(Event evt) */
METHOD SDL_waitEvent(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret;
  SDL_Event *event = ((sfp[1].glue)->ptr);
  if((ret = SDL_WaitEvent(event)) == 0){
    fprintf(stderr,"error:%s\n",SDL_GetError());
  }
  

  printf("ret %d\nevent.type %d\n",ret,event->type);
  //KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Event",event,NULL));

  KNH_RETURN_Int(ctx, sfp, ret);
}


/* void SDL.pushEvent(Event evt) */
METHOD SDL_pushEvent(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Event *event = ((sfp[1].glue)->ptr);
  if(SDL_PushEvent(event)==-1){
    fprintf(stderr,"error:%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}

// METHOD SDL_setEventfilter(Ctx* ctx, knh_sfp_t *sfp)
// METHOD SDL_getEventfilter(Ctx* ctx, knh_sfp_t *sfp)


/* int SDL.eventState(int type, int state) */

METHOD SDL_eventState(Ctx* ctx, knh_sfp_t *sfp)
{
  Uint8 type = p_int(sfp[1]);
  int state = p_int(sfp[2]);
  int ret = SDL_EventState(type, state);

  KNH_RETURN_Int(ctx,sfp,ret);
}


 /*
METHOD SDL_getKeyState(Ctx* ctx,knh_sfp_t *sfp)
{
  int* key = SDL_GetKeyState((sfp[1].glue)->ptr);
  KNH_RETURN_void(ctx,sfp);
}
 */

/* int SDL.getModState(void) */

METHOD SDL_getModstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret = SDL_GetModState();

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* void SDL.setModState(int modstate) */

METHOD SDL_setModstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int modstate = p_int(sfp[1]);
  SDL_SetModState(modstate);

  KNH_RETURN_void(ctx,sfp);
}

/* String SDL.getKeyName(int key) */

METHOD SDL_getKeyname(Ctx* ctx, knh_sfp_t *sfp)
{
  int key = p_int(sfp[1]);
  char* ret = SDL_GetKeyName(key);

  KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}


/* int SDL.enableUNICODE(int enable) */

METHOD SDL_enableUNICODE(Ctx* ctx, knh_sfp_t *sfp)
{
  int enable = p_int(sfp[1]);
  int ret = SDL_EnableUNICODE(enable);

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* void SDL.enableKeyRepeat(int delay, int interval) */

METHOD SDL_enableKeyRepeat(Ctx* ctx, knh_sfp_t *sfp)
{
  int delay = p_int(sfp[1]);
  int interval = p_int(sfp[2]);
  if(SDL_EnableKeyRepeat(delay, interval)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }

  KNH_RETURN_void(ctx,sfp);
}

//METHOD SDL_getMousestate(Ctx* ctx, knh_sfp_t *sfp)
//METHOD SDL_getRelativemousestate(Ctx* ctx, knh_sfp_t *sfp)

/* int SDL.getAppState(void) */

METHOD SDL_getAppstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int ret = SDL_GetAppState();

  KNH_RETURN_Int(ctx,sfp,ret);
}

/* int SDL.joystickEventState(int state) */

METHOD SDL_joystickEventstate(Ctx* ctx, knh_sfp_t *sfp)
{
  int state = p_int(sfp[1]);
  int ret = SDL_JoystickEventState(state);

  KNH_RETURN_Int(ctx,sfp,ret);
}


/* Joystick */
  /*
METHOD SDL_numJoysticks(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_NumJoysticks());
}
  */
//METHOD SDL_joystickName(Ctx* ctx, knh_sfp_t *sfp)
   /*
METHOD SDL_joystickOpen(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_Joystick* joy = SDL_JoystickOpen(sfp[1].ivalue);
  if(joy==NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Joystick",joy,NULL));
}

METHOD SDL_joystickOpened(Ctx* ctx, knh_sfp_t *sfp)
{
  int state = SDL_JoystickOpened(sfp[1].ivalue);
  if(state==0){
    printf("Joystick is closed\n");
  } else {
    printf("Joystick is opened\n");
  }
  KNH_RETURN_Int(ctx,sfp,state);
}

METHOD SDL_joystickIndex(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickIndex((sfp[1].glue)->ptr));
}

METHOD SDL_joystickNumaxes(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickNumAxes((sfp[1].glue)->ptr));
}

METHOD SDL_joystickNumballs(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickNumBalls((sfp[1].glue)->ptr));
}

METHOD SDL_joystickNumhats(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickNumHats((sfp[1].glue)->ptr));
}

METHOD SDL_joystickNumbuttons(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickButtons((sfp[1].glue)->ptr));
}

METHOD SDL_joystickUpdate(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_JoystickUpdate();
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_joystickGetaxis(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickGetAxis((sfp[1].glue)->ptr,sfp[2].ivalue));
}

METHOD SDL_joystickGethat(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickGetHat((sfp[1].glue)->ptr,sfp[2].ivalue));
}

METHOD SDL_joystickGetbutton(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_JoystickGetButton((sfp[1].glue)->ptr,sfp[2].ivalue));
}

METHOD SDL_joystickGetball(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_JoystickGetBall((sfp[1].glue)->ptr,sfp[2].ivalue,(sfp[3].glue)->ptr,(sfp[4].glue)->ptr)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETRURN_void(ctx,sfp);
}

METHOD SDL_joystickClose(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_JoystickClose((sfp[1].glue)->ptr);
  KNH_RETURN_void(ctx,sfp);
}
*/

/* Audio */
/*
METHOD SDL_openAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_OpenAudio((sfp[1].glue)->ptr,(sfp[2].glue)->ptr)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_pauseAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_PauseAudio(sfp[1].ivalue);
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_getAudiostatus(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_GetAudioStatus());
}

// METHO SDL_loadWAV(Ctx* ctx, knh_sfp_t *sfp)
		      		      
METHOD SDL_freeWAV(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_FreeWAV((sfp[1].glue)->ptr);
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_buildAudioCVT(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_BuildAudioCVT((sfp[1].glue)->ptr, sfp[2].ivalue, sfp[3].ivalue, sfp[4].ivalue, sfp[5].ivalue, sfp[6].ivalue, sfp[7].ivalue)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_convertAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_ConvertAudio((sfp[1].glue)->ptr)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_mixAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_MixAudio((sfp[1].glue)->ptr,(sfp[2].glue)->ptr,sfp[3].ivalue,sfp[4].ivalue);
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_lockAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_LockAudio();
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_unLockAudio(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_UnlockAudio();
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_closeAudo(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_CloseAudio();
  KNH_RETURN_void(ctx,sfp);
}
*/

/* CD-ROM */
/*
METHOD SDL_cdNumDrives(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_CDNumDrives());
}

//METHOD SDL_cdName(Ctx* ctx, knh_sfp_t *sfp)

METHOD SDL_cdOpen(Ctx* ctx, knh_sfp_t *sfp)
{
  SDL_CD *cd;
  cd = SDL_CDOpen(sfp[1].ivalue);
  if(cd == NULL){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.CD",cd,NULL));
}

METHOD SDL_cdStatus(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,SDL_CDStatus((sfp[1].glue)->ptr));
}

METHOD SDL_cdPlay(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_CDPlay((sfp[1].glue)->ptr,sfp[2].ivalue,sfp[3].ivalue)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}

METHOD SDL_cdPlayTracks(Ctx* ctx, knh_sfp_t *sfp)
{
  if(SDL_CDPlayTracks((sfp[1].glue)->ptr,sfp[2].ivalue,sfp[3].ivalue,sfp[4].ivalue,sfp[5].ivalue)==-1){
    fprintf(stderr,"%s\n",SDL_GetError());
  }
  KNH_RETURN_void(ctx,sfp);
}
*/



/* void SDL.delay(int ms) */

METHOD SDL_delay(Ctx* ctx, knh_sfp_t *sfp)
{
  int ms = p_int(sfp[1]);
  SDL_Delay(ms);

  KNH_RETURN_void(ctx,sfp);
}

/* float SDL.getTicks(void) */

METHOD SDL_getTicks(Ctx* ctx, knh_sfp_t *sfp)
{
   SDL_GetTicks();
  
   KNH_RETURN_Float(ctx,sfp,SDL_GetTicks());
}


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

METHOD SDL_sample(Ctx* ctx, knh_sfp_t *sfp)
{
  KNH_RETURN_void(ctx,sfp);
}

/* ConstData */
 
static
knh_IntConstData_t IntConstData[] = {
  // init
  {"SDL.INIT_TIMER", SDL_INIT_TIMER},
  {"SDL.INIT_AUDIO", SDL_INIT_AUDIO},
  {"SDL.INIT_VIDEO", SDL_INIT_VIDEO},
  {"SDL.INIT_CDROM", SDL_INIT_CDROM},
  {"SDL.INIT_JOYSTICK", SDL_INIT_JOYSTICK},
  {"SDL.INIT_EVERYTHING", SDL_INIT_EVERYTHING},
  {"SDL.INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE},
  {"SDL.INIT_EVENTTHREAD", SDL_INIT_EVENTTHREAD}, 
  // 
  {"SDL.SWSURFACE", SDL_SWSURFACE},
  {"SDL.HWSURFACE", SDL_HWSURFACE},
  {"SDL.ASYNCBLIT", SDL_ASYNCBLIT},
  {"SDL.ANYFORMAT", SDL_ANYFORMAT},
  {"SDL.HWPALETTE", SDL_HWPALETTE},     
  {"SDL.DOUBLEBUF", SDL_DOUBLEBUF},     
  {"SDL.FULLSCREEN", SDL_FULLSCREEN},   
  {"SDL.OPENGL", SDL_OPENGL},           
  {"SDL.OPENGLBLIT", SDL_OPENGLBLIT},   
  {"SDL.RESIZABLE",SDL_RESIZABLE},      
  {"SDL.HWACCEL",SDL_HWACCEL},          
  {"SDL.SRCCOLORKEY", SDL_SRCCOLORKEY}, 
  {"SDL.RLEACCEL", SDL_RLEACCEL},       
  {"SDL.SRCALPHA", SDL_SRCALPHA},       
  {"SDL.PREALLOC", SDL_PREALLOC},       
  //
  {"SDL.ACTIVEEVENT", SDL_ACTIVEEVENT},       
  {"SDL.KEYDOWN", SDL_KEYDOWN},               
  {"SDL.KEYUP", SDL_KEYUP},                   
  {"SDL.MOUSEMOTION", SDL_MOUSEMOTION},       
  {"SDL.MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN}, 
  {"SDL.MOUSEBUTTONUP", SDL_MOUSEBUTTONUP},     
  {"SDL.JOYAXISMOTION", SDL_JOYAXISMOTION},   
  {"SDL.JOYBALLMOTION", SDL_JOYBALLMOTION},   
  {"SDL.JOYHATMOTION", SDL_JOYHATMOTION},     
  {"SDL.JOYBUTTONDOWN", SDL_JOYBUTTONDOWN},   
  {"SDL.JOYBUTTONUP", SDL_JOYBUTTONUP},       
  {"SDL.QUIT", SDL_QUIT},                     
  {"SDL.SYSWMEVENT", SDL_SYSWMEVENT},         
  {"SDL.VIDEORESIZE", SDL_VIDEORESIZE},       
  {"SDL.VIDEOEXPOSE", SDL_VIDEOEXPOSE},       
  {"SDL.USEREVENT",  SDL_USEREVENT},          
  //
  {"SDL.ENABLE", SDL_ENABLE},   
  {"SDL.DISABLE", SDL_DISABLE}, 
  {"SDL.QUERY", SDL_QUERY},     
  //
  {"SDL.GRAB_QUERY", SDL_GRAB_QUERY},
  {"SDL.GRAB_OFF", SDL_GRAB_OFF},
  {"SDL.GRAB_ON", SDL_GRAB_ON},
  //
  {"SDL.SDLK_BACKSPACE", SDLK_BACKSPACE},
  {"SDL.SDLK_TAB", SDLK_TAB},
  {"SDL.SDLK_CLEAR", SDLK_CLEAR},
  {"SDL.SDLK_RETURN", SDLK_RETURN},
  {"SDL.SDLK_PAUSE", SDLK_PAUSE},
  {"SDL.SDLK_ESCAPE", SDLK_ESCAPE},
  {"SDL.SDLK_SPACE", SDLK_SPACE},
  {"SDL.SDLK_EXCLAIM", SDLK_EXCLAIM},
  {"SDL.SDLK_QUOTEDBL", SDLK_QUOTEDBL},
  {"SDL.SDLK_HASH", SDLK_HASH},
  {"SDL.SDLK_DOLLAR", SDLK_DOLLAR},
  {"SDL.SDLK_AMPERSAND", SDLK_AMPERSAND},
  {"SDL.SDLK_QUOTE", SDLK_QUOTE},
  {"SDL.SDLK_LEFTPAREN", SDLK_LEFTPAREN},
  {"SDL.SDLK_RIGHTPAREN", SDLK_RIGHTPAREN},
  {"SDL.SDLK_ASTERISK", SDLK_ASTERISK},
  {"SDL.SDLK_PLUS", SDLK_PLUS},
  {"SDL.SDLK_COMMA", SDLK_COMMA},
  {"SDL.SDLK_MINUS", SDLK_MINUS},
  {"SDL.SDLK_PERIOD", SDLK_PERIOD},
  {"SDL.SDLK_SLASH", SDLK_SLASH},
  {"SDL.SDLK_0", SDLK_0},
  {"SDL.SDLK_1", SDLK_1},
  {"SDL.SDLK_2", SDLK_2},
  {"SDL.SDLK_3", SDLK_3},
  {"SDL.SDLK_4", SDLK_4},
  {"SDL.SDLK_5", SDLK_5},
  {"SDL.SDLK_6", SDLK_6},
  {"SDL.SDLK_7", SDLK_7},
  {"SDL.SDLK_8", SDLK_8},
  {"SDL.SDLK_9", SDLK_9},
  {"SDL.SDLK_COLON", SDLK_COLON},
  {"SDL.SDLK_SEMICOLON", SDLK_SEMICOLON},
  {"SDL.SDLK_LESS", SDLK_LESS},
  {"SDL.SDLK_EQUALS",SDLK_EQUALS},
  {"SDL.SDLK_GREATER", SDLK_GREATER},
  {"SDL.SDLK_QUESTION", SDLK_QUESTION},
  {"SDL.SDLK_AT", SDLK_AT},
  {"SDL.SDLK_LEFTBRACKET", SDLK_LEFTBRACKET},
  {"SDL.SDLK_BACKSLASH", SDLK_BACKSLASH},
  {"SDL.SDLK_RIGHTBRACKET", SDLK_RIGHTBRACKET},
  {"SDL.SDLK_CARET", SDLK_CARET},
  {"SDL.SDLK_UNDERSCORE", SDLK_UNDERSCORE},
  {"SDL.SDLK_BACKQUOTE", SDLK_BACKQUOTE},
  {"SDL.SDLK_A", SDLK_a},
  {"SDL.SDLK_B", SDLK_b},
  {"SDL.SDLK_C", SDLK_c},
  {"SDL.SDLK_D", SDLK_d},
  {"SDL.SDLK_E", SDLK_e},
  {"SDL.SDLK_F", SDLK_f},
  {"SDL.SDLK_G", SDLK_g},
  {"SDL.SDLK_H", SDLK_h},
  {"SDL.SDLK_I", SDLK_i},
  {"SDL.SDLK_J", SDLK_j},
  {"SDL.SDLK_K", SDLK_k},
  {"SDL.SDLK_L", SDLK_l},
  {"SDL.SDLK_M", SDLK_m},
  {"SDL.SDLK_N", SDLK_n},
  {"SDL.SDLK_O", SDLK_o},
  {"SDL.SDLK_P", SDLK_p},
  {"SDL.SDLK_Q", SDLK_q},
  {"SDL.SDLK_R", SDLK_r},
  {"SDL.SDLK_S", SDLK_s},
  {"SDL.SDLK_T", SDLK_t},
  {"SDL.SDLK_U", SDLK_u},
  {"SDL.SDLK_V", SDLK_v},
  {"SDL.SDLK_W", SDLK_w},
  {"SDL.SDLK_X", SDLK_x},
  {"SDL.SDLK_Y", SDLK_y},
  {"SDL.SDLK_Z", SDLK_z},
  {"SDL.SDLK_DELETE", SDLK_DELETE},
  {"SDL.SDLK_KP0", SDLK_KP0},
  {"SDL.SDLK_KP1", SDLK_KP1},
  {"SDL.SDLK_KP2", SDLK_KP2},
  {"SDL.SDLK_KP3", SDLK_KP3},
  {"SDL.SDLK_KP4", SDLK_KP4},
  {"SDL.SDLK_KP5", SDLK_KP5},
  {"SDL.SDLK_KP6", SDLK_KP6},
  {"SDL.SDLK_KP7", SDLK_KP7},
  {"SDL.SDLK_KP8", SDLK_KP8},
  {"SDL.SDLK_KP9", SDLK_KP9},
  {"SDL.SDLK_KP_PERIOD", SDLK_KP_PERIOD},
  {"SDL.SDLK_KP_DIVIDE", SDLK_KP_DIVIDE},
  {"SDL.SDLK_KP_MULTIPLY", SDLK_KP_MULTIPLY},
  {"SDL.SDLK_KP_MINUS", SDLK_KP_MINUS},
  {"SDL.SDLK_KP_PLUS", SDLK_KP_PLUS},
  {"SDL.SDLK_KP_ENTER", SDLK_KP_ENTER},
  {"SDL.SDLK_KP_EQUALS", SDLK_KP_EQUALS},
  {"SDL.SDLK_UP", SDLK_UP},
  {"SDL.SDLK_DOWN", SDLK_DOWN},
  {"SDL.SDLK_RIGHT", SDLK_RIGHT},
  {"SDL.SDLK_LEFT", SDLK_LEFT},
  {"SDL.SDLK_INSERT", SDLK_INSERT},
  {"SDL.SDLK_HOME", SDLK_HOME},
  {"SDL.SDLK_END", SDLK_END},
  {"SDL.SDLK_PAGEUP", SDLK_PAGEUP},
  {"SDL.SDLK_PAGEDOWN", SDLK_PAGEDOWN},
  {"SDL.SDLK_F1", SDLK_F1},
  {"SDL.SDLK_F2", SDLK_F2},
  {"SDL.SDLK_F3", SDLK_F3},
  {"SDL.SDLK_F4", SDLK_F4},
  {"SDL.SDLK_F5", SDLK_F5},
  {"SDL.SDLK_F6", SDLK_F6},
  {"SDL.SDLK_F7", SDLK_F7},
  {"SDL.SDLK_F8", SDLK_F8},
  {"SDL.SDLK_F9", SDLK_F9},
  {"SDL.SDLK_F10", SDLK_F10},
  {"SDL.SDLK_F11", SDLK_F11},
  {"SDL.SDLK_F12", SDLK_F12},
  {"SDL.SDLK_F13", SDLK_F13},
  {"SDL.SDLK_F14", SDLK_F14},
  {"SDL.SDLK_F15", SDLK_F15},
  {"SDL.SDLK_NUMLOCK", SDLK_NUMLOCK},
  {"SDL.SDLK_CAPSLOCK", SDLK_CAPSLOCK},
  {"SDL.SDLK_SCROLLOCK", SDLK_SCROLLOCK},
  {"SDL.SDLK_RSHIFT", SDLK_RSHIFT},
  {"SDL.SDLK_LSHIFT", SDLK_LSHIFT},
  {"SDL.SDLK_RCTRL", SDLK_RCTRL},
  {"SDL.SDLK_LCTRL", SDLK_LCTRL},
  {"SDL.SDLK_RALT", SDLK_RALT},
  {"SDL.SDLK_LALT", SDLK_LALT},
  {"SDL.SDLK_RMETA", SDLK_RMETA},
  {"SDL.SDLK_LMETA", SDLK_LMETA},
  {"SDL.SDLK_LSUPER", SDLK_LSUPER},
  {"SDL.SDLK_RSUPER", SDLK_RSUPER},
  {"SDL.SDLK_MODE", SDLK_MODE},
  {"SDL.SDLK_HELP", SDLK_HELP},
  {"SDL.SDLK_PRINT", SDLK_PRINT},
  {"SDL.SDLK_SYSREQ", SDLK_SYSREQ},
  {"SDL.SDLK_BREAK", SDLK_BREAK},
  {"SDL.SDLK_MENU", SDLK_MENU},
  {"SDL.SDLK_POWER", SDLK_POWER},
  {"SDL.SDLK_EURO", SDLK_EURO},
  //
  {"SDL.KMOD_NONE", KMOD_NONE},
  {"SDL.KMOD_NUM", KMOD_NUM},
  {"SDL.KMOD_CAPS", KMOD_CAPS},
  {"SDL.KMOD_LCTRL", KMOD_LCTRL},
  {"SDL.KMOD_RCTRL", KMOD_RCTRL},
  {"SDL.KMOD_RSHIFT", KMOD_RSHIFT},
  {"SDL.KMOD_LSHIFT", KMOD_LSHIFT},
  {"SDL.KMOD_RALT", KMOD_RALT},
  {"SDL.KMOD_LALT", KMOD_LALT},
  {"SDL.KMOD_CTRL", KMOD_CTRL},
  {"SDL.KMOD_SHIFT", KMOD_SHIFT},
  {"SDL.KMOD_ALT", KMOD_ALT},
  //
  {"SDL.HAT_CENTERED", SDL_HAT_CENTERED},
  {"SDL.HAT_UP", SDL_HAT_UP},
  {"SDL.HAT_RIGHT", SDL_HAT_RIGHT},
  {"SDL.HAT_DOWN", SDL_HAT_DOWN},
  {"SDL.HAT_LEFT", SDL_HAT_LEFT},
  {"SDL.HAT_RIGHTUP", SDL_HAT_RIGHTUP},
  {"SDL.HAT_RIGHTDOWN", SDL_HAT_RIGHTDOWN},
  {"SDL.HAT_LEFTUP", SDL_HAT_LEFTUP},
  {"SDL.HAT_LEFTDOWN", SDL_HAT_LEFTDOWN},
  //
  {"SDL.AUDIO_U8", AUDIO_U8},
  {"SDL.AUDIO_S8", AUDIO_S8},
  {"SDL.AUDIO_U16", AUDIO_U16},
  {"SDL.AUDIO_U16LSB", AUDIO_U16LSB},
  {"SDL.AUDIO_S16", AUDIO_S16},
  {"SDL.AUDIO_S16LSB", AUDIO_S16LSB},
  {"SDL.AUDIO_U16MSB", AUDIO_U16MSB},
  {"SDL.AUDIO_U16SYS", AUDIO_U16SYS},
  {"SDL.AUDIO_U16LSB", AUDIO_U16LSB},
  {"SDL.AUDIO_U16MSB", AUDIO_U16MSB},
  {"SDL.AUDIO_S16SYS", AUDIO_S16SYS},
  {"SDL.AUDIO_S16LSB", AUDIO_S16LSB},
  {"SDL.AUDIO_S16MSB", AUDIO_S16MSB},
  //
  {"SDL.AUDIO_STOPPED", SDL_AUDIO_STOPPED},
  {"SDL.AUDIO_PAUSED", SDL_AUDIO_PAUSED},
  {"SDL.AUDIO_PLAYING", SDL_AUDIO_PLAYING},
  //
  {"SDL.CD_TRAYEMPTY", CD_TRAYEMPTY},
  {"SDL.CD_STOPPED", CD_STOPPED},
  {"SDL.CD_PLAYING", CD_PLAYING},
  {"SDL.CD_PAUSED", CD_PAUSED},
  {"SDL.CD_ERROR", CD_ERROR},
  //
  {"SDL.GL_RED_SIZE", SDL_GL_RED_SIZE},
  {"SDL.GL_GREEN_SIZE", SDL_GL_GREEN_SIZE},
  {"SDL.GL_BLUE_SIZE", SDL_GL_BLUE_SIZE},
  {"SDL.GL_ALPHA_SIZE", SDL_GL_ALPHA_SIZE},
  {"SDL.GL_DOUBLEBUFFER", SDL_GL_DOUBLEBUFFER},
  {"SDL.GL_BUFFER_SIZE", SDL_GL_BUFFER_SIZE},
  {"SDL.GL_DEPTH_SIZE", SDL_GL_DEPTH_SIZE},
  {"SDL.GL_STENCIL_SIZE", SDL_GL_STENCIL_SIZE},
  {"SDL.GL_ACCUM_RED_SIZE", SDL_GL_ACCUM_RED_SIZE},
  {"SDL.GL_ACCUM_GREEN_SIZE", SDL_GL_ACCUM_GREEN_SIZE},
  {"SDL.GL_ACCUM_BLUE_SIZE", SDL_GL_ACCUM_BLUE_SIZE},
  {"SDL.GL_ACCUM_ALPHA_SIZE",SDL_GL_ACCUM_ALPHA_SIZE},
  {NULL}  // end of const data
};
 
KNHAPI(int) init(Ctx *ctx)
{
  KNH_NOTICE(ctx, "loading math...");
  konoha_loadIntConstData(ctx, IntConstData);
  return 1;
}