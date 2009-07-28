//
// SDL Event Sample
// 2009/7/29
//

//終了する時はescapeキーを押してください
//if you want to quit the application, please press Escape key.

using sdl.*;


Surface screen;
Surface bg_image;
SDLEvent event = new SDLEvent();

Rect r1 = new Rect(0,0,480,480);
Rect r2 = new Rect(50,0,0,0);


SDL.init(SDL.INIT_VIDEO|SDL.INIT_TIMER);
SDL.wmSetCaption("SDL Event Sample");

screen = SDL.setVideoMode(480,480,32,SDL.SWSURFACE);
bg_image = SDL.imgLoad("./bmp/sample.png");

bg_image.blitSurface(r1,screen,r2);

float next_frame = SDL.getTicks();
float wait = 1000.0/60.0;

int i=0;

OUTER:
while(true){
    INNER:
    while(event.pollEvent()>0){
	if(event.getType() == SDL.QUIT){
	    OUT << "SDL_QUIT!" << EOL;
	    break OUTER;
	}else if((event.getType() == SDL.KEYUP) && (event.getKeySym() == SDL.SDLK_ESCAPE)){
	    OUT << "ESCAPE!" << EOL;
	    break OUTER;
	}
    }

    if(SDL.getTicks() >= next_frame){
	//update
	i++;
	if(i > 480){
	    i = 0;
	}
	Rect r3 = new Rect(50,i/2,0,0);
	if(SDL.getTicks() < next_frame + wait){
	    //Draw
	    bg_image.blitSurface(r1,screen,r3);
	    screen.updateRect(0,0,0,0);
	}
	next_frame = next_frame + wait;
	SDL.delay(0);
    }
}

OUT << "quit..." << EOL;

SDL.quit();
