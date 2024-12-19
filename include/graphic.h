#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL/SDL.h>
#include <types.h>

class Graphic{
	public:
		Graphic();
		~Graphic();
		int Init(u32 w, u32 h, const char *msg);
		void Quit();
		void Update_screen();
		void cls();
		void cls(u8 r, u8 g, u8 b);
	private:
		int w;
		int h;
		u32 *fb;
		SDL_Surface *videobuffer;
};



#endif
