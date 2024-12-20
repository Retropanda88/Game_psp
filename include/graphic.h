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
		void pixel(u32 x, u32 y, u8 r, u8 g, u8 b);
		void draw_line(int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b);
		void draw_rect(int  x, int y, int w, int h, u8 r, u8 g, u8 b);
		void fps_sincronizar(u32 fps);
		//get
		u32 get_pixel(u32 x, u32 y);
		u32 get_w(){return w;}
		u32 get_h(){return h;}
		u32 *get_fb(){return fb;}
		SDL_Surface *get_framebuffer(){return videobuffer;}
		
	private:
		u32 w;
		u32 h;
		u32 *fb;
		SDL_Surface *videobuffer;
};



#endif
