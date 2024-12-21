#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL/SDL.h>
#include "types.h"

class CGraphic{
	public:
	  CGraphic();
	  ~CGraphic();
	 int Init();
	 int Set_Video(int w, int h, int bpp);
	 void Update(){SDL_Flip(Buffer_video);}
	 void clean();
	 void clean(u8 r, u8 g, u8 b);      
	 void Fps_sincronizar(int frecuencia);
	 void Fill_Rect(int x, int y, int w, int h, u32 color);
	 void Fill_Rect(int x, int y, int w, int h, u8 r, u8 g, u8 b);
	 void Line(int x, int y, int xq, int y1, u32 color);
	 void Line(int x, int y, int x1, int y1, u8 r, u8 g, u8 b);
	 void Pixel(int x, int y, u32 color);     
	 void Pixel(int x, int y, u8 r, u8 g, u8 b);
	 void Draw_s(SDL_Surface *src, int x, int y);
	 void Print_text( int x, int y, u8 r, u8 g, u8 b, const char *s, ...);
	 void Print_text( int x, int y,u32 color, const char *s, ...);
	 int get_w(){return w;}
	 int get_h(){return h;}
	 SDL_Surface *get_Buffer_video(){return Buffer_video;}
  private:
     int w;
     int h;
     int bpp;
     SDL_Surface *Buffer_video;
};

#endif