using sdl.*

Surface s = SDL.setVideoMode(333,333,32,SDL.SWSURFACE);
Event evt = new Event();

while(SDL.waitEvent(evt) >= 0){
		if (evt.getType() == SDL.QUIT) {
//		 if(evt.type == SDL.QUIT){
		  print "ok";
			     SDL.quit();
			     break
		} else if(evt.getType() == SDL.KEYDOWN) {
		  KeyBoard key = evt.getKeyBoard();
		  KeySym keysym = key.getKeySym();
		  if (keysym.getSym() == SDL.SDLK_SPACE) {
		    print "helllO"
		    }
		}

}

				     