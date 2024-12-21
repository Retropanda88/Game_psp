#ifndef WORLD_H_
#define WORLD_H_

#include <SDL/SDL.h>
#include "types.h"


struct Mapa
{
	int w_tile;
	int h_tile;
	int columnas;
	int filas;
	int *data;
	SDL_Surface *capas[4];
	SDL_Surface *sheet[6]; //ahora solo 4 para crear el mapa
};

/*esta funcion creara las capas para que se puedan rederizar
necita :
*las imagenes donde se obtendran los tiles.
*um fichero con la informacion del mapa 
     tamaño de tile ancho 
     tamaño de tile alto
     numero de tiled ancho 
     numero debtiles largo 
     armara las capas para renderizar
*/
struct Mapa *load_mapa(const char *fn);


class CWorld
{
  public:
	CWorld();
	~CWorld();
	int Init(Mapa * m);

	int get_w_tile()
	{
		return w_tile;
	}
	int get_h_tile()
	{
		return h_tile;
	}
	int get_COL()
	{
		return COL;
	}
	int get_FILAS()
	{
		return FILAS;
	}

  private:

	int w_tile;
	int h_tile;
	int COL;
	int FILAS;

};


#endif
