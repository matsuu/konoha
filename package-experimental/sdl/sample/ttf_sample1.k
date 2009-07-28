using sdl.*;

//init
SDL.init(SDL.INIT_VIDEO);
Surface s = SDL.setVideoMode(640,320,32,SDL.SWSURFACE);

//ttf_init
SDLttf.init();
SDLttf font = SDLttf.openFont("sample/font/ume-pgo5.ttf",70);

//
Rect r1 = new Rect(60,60,0,0);
Rect r2 = new Rect(0,0,500,500);
SDLColor font_color = new SDLColor(255,0,0);
Surface text_surf = font.renderUTF8Solid("描画テストです",font_color);

text_surf.blitSurface(r2,s,r1);

s.updateRect(0,0,0,0);
SDL.delay(3000);

