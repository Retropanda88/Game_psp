#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#if PSP
#include <pspctrl.h>
#endif

#include "Sprite.h"
#include "camara.h"
#include "types.h"


enum{sheet=0,down,left,right,up,down_left,down_right,up_left,up_right,sleep,max_spr};

class CPersonaje{
	public:
		CPersonaje();
		~CPersonaje();
		int Init(int x, int y, int nvidas, const char *name);
		int Load_sheet(const char *fn, int nframes_w, int nframes_h);
		char *get_name(){return name;}
		Sprite *get_spr(int index){return spr[index];}
		void Create_sprite();
		//Sprite *spr[max_spr];
		void desplazar(u8 *key);
#if PSP
		void desplazar(SceCtrlData *pad);
#endif
		void Draw(SDL_Surface *s, Camara *c);
		int get_x(){return x;}
		int get_y(){return y;}
	private:
		int x;
		int y;
		int x1;
		int y1;
		int dx;
		int dy;
		int nvidas;
		int estado_salud;
		int w_frame;
		int h_frame;
		int nframes_w;
		int nframes_h;
		Sprite *spr[max_spr];
		int dir;
		int last_dir;
		char name[50];
};


#endif