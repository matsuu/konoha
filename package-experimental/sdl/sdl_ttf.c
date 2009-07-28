//
// SDLttf class
//

#include "knh_sdl.h"

//General

/* @method int SDLttf.init() */
METHOD SDLttf_init(Ctx *ctx,knh_sfp_t *sfp)
{
  KNH_RETURN_Int(ctx,sfp,TTF_Init());
}

/* @method Boolean SDLttf.wasInit() */
METHOD SDLttf_wasInit(Ctx *ctx,knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx,sfp,TTF_WasInit());
}

/* @method void SDLttf.quit() */
METHOD SDLttf_quit(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Quit();
	KNH_RETURN_void(ctx,sfp);
}

/* @method void SDLttf.setError() */

/* @method String SDLttf.getError() */
METHOD SDLttf_getError(Ctx *ctx,knh_sfp_t *sfp)
{
	KNH_RETURN(ctx,sfp,new_String(ctx,B(TTF_GetError()),NULL));
}

//management

static
void knh_sdlttf_free(Ctx *ctx,knh_Glue_t *g)
{
	TTF_CloseFont((TTF_Font*)g->ptr);
}

/* @method SDLttf? SDLttf.openFont(String path,int font_size); */
METHOD SDLttf_openFont(Ctx *ctx,knh_sfp_t *sfp)
{
	char *path = p_char(sfp[1]);
	int font_size = p_int(sfp[2]);

	TTF_Font *t_font = TTF_OpenFont(path,font_size);
	knh_Glue_init(ctx,sfp[0].glue, t_font,knh_sdlttf_free);
	KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* @method SDLttf? SDLttf.new(String path,int font_size); */
METHOD SDLttf_new(Ctx *ctx,knh_sfp_t *sfp)
{
	char *path = p_char(sfp[1]);
	int font_size = p_int(sfp[2]);

	TTF_Font *t_font = TTF_OpenFont(path,font_size);
	knh_Glue_init(ctx,sfp[0].glue, t_font,knh_sdlttf_free);
	KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* @method SDLttf? SDLttf.openFontIndex(String path,int font_size,int index) */
METHOD SDLttf_openFontIndex(Ctx *ctx,knh_sfp_t *sfp)
{
	char *path = p_char(sfp[1]);
	int font_size = p_int(sfp[2]);
	int index = p_int(sfp[3]);
	
	TTF_Font *t_font = TTF_OpenFontIndex(path,font_size,index);
	knh_Glue_init(ctx,sfp[0].glue, t_font,knh_sdlttf_free);
	KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* @method void SDLttf.closeFont() */
METHOD SDLttf_closeFont(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	TTF_CloseFont(t_font);

	KNH_RETURN_void(ctx,sfp);
}

//attributes

/* @method int SDLttf.getFontStyle() */
METHOD SDLttf_getFontStyle(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_GetFontStyle(t_font));
}

/* @method void SDLttf.setFontStyle(int style) */
METHOD SDLttf_setFontStyle(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	int style = p_int(sfp[1]);
	
	TTF_SetFontStyle(t_font,style);
	KNH_RETURN_void(ctx,sfp);
}


/* int SDLttf.fontHeight(); */
METHOD SDLttf_fontHeight(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_FontHeight(t_font));
}

/* int SDLttf.fontAscent(); */
METHOD SDLttf_fontAscent(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_FontAscent(t_font));
}

/* int SDLttf.fontDescent(); */
METHOD SDLttf_fontDescent(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_FontDescent(t_font));
}

/* int SDLttf.fontLineSkip(); */
METHOD SDLttf_fontLineSkip(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_FontLineSkip(t_font));
}

/* int SDLttf.fontFaces(); */
METHOD SDLttf_fontFaces(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Int(ctx,sfp,TTF_FontFaces(t_font));
}

/* Boolean SDLttf.fontFaceIsFixedWidth(); */
METHOD SDLttf_fontFaceIsFixedWidth(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	
	KNH_RETURN_Boolean(ctx,sfp,TTF_FontFaceIsFixedWidth(t_font));
}

/* String SDLttf.fontFaceFamilyName(); */
METHOD SDLttf_fontFaceFamilyName(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);

	KNH_RETURN(ctx,sfp,new_String(ctx,B(TTF_FontFaceFamilyName(t_font)),NULL));
}

/* String SDLttf.fontFaceStyleName(); */
METHOD SDLttf_fontFaceStyleName(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);

	KNH_RETURN(ctx,sfp,new_String(ctx,B(TTF_FontFaceStyleName(t_font)),NULL));
}

//Render
/* Surface SDLttf.renderTextSolid(String text,SDLColor fg) */
METHOD SDLttf_renderTextSolid(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderText_Solid(t_font,text,*fg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* Surface SDLttf.renderUTF8Solid(String text,SDLColor fg) */
METHOD SDLttf_renderUTF8Solid(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderUTF8_Solid(t_font,text,*fg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* Surface SDLttf.renderTextShaded(String text,SDLColor fg,SDLColor bg); */
METHOD SDLttf_renderTextShaded(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	SDL_Color *bg = ((sfp[3].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderText_Shaded(t_font,text,*fg,*bg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* Surface SDLttf.renderUTF8Shaded(String text,SDLColor fg,SDLColor bg); */
METHOD SDLttf_renderUTF8Shaded(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	SDL_Color *bg = ((sfp[3].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderUTF8_Shaded(t_font,text,*fg,*bg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* Surface SDLttf.renderTextBlended(String text,SDLColor fg) */
METHOD SDLttf_renderTextBlended(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderText_Blended(t_font,text,*fg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* Surface SDLttf.renderUTF8Blended(String text,SDLColor fg) */
METHOD SDLttf_renderUTF8Blended(Ctx *ctx,knh_sfp_t *sfp)
{
	TTF_Font* t_font = ((sfp[0].glue)->ptr);
	char* text = p_char(sfp[1]);
	SDL_Color *fg = ((sfp[2].glue)->ptr);
	
	SDL_Surface *surf = TTF_RenderUTF8_Blended(t_font,text,*fg);
	KNH_RETURN(ctx,sfp,new_Glue(ctx,"sdl.Surface",surf,NULL));
}

/* SDLttf end */
