#ifndef WORLD_H_
#define WORLD_H_

#include <SDL/SDL.h>
#include "types.h"

#define Max_tiles (40*40)

struct Mapa{
	int w_tile;
	int h_tile;
	int columnas;
	int filas;
	int *data;
	SDL_Surface *tile[4];
};

class CWorld{
	public:
	  CWorld();
	  ~CWorld();
	  int Init(Mapa *m);
	  
	  int get_w_tile(){return w_tile;}
	  int get_h_tile(){return h_tile;}
	  int get_COL(){return COL;}
	  int get_FILAS(){return FILAS;}
	  
	  int w_tile;
	  int h_tile;
	  int COL;
	  int FILAS;
	
};


#endif