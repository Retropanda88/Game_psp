#ifndef WORLD_H_
#define WORLD_H_

#include <SDL/SDL.h>
#include <types.h>

#define floor 0


struct Tile
{
	SDL_Rect rect;				// contiene la posicion y dimencion del tilen
	SDL_Surface *tile;
	int w;
	int h;
	u32 *data;
};

struct Mapa
{
	int w;						// ancho del mapa
	int h;						// alto del mapa
	int ntiles;
	Tile *tile;
	// esto es para dibujar unicamente
	SDL_Surface *capas[4];
};

/* esta funcion creara las capas para que se puedan rederizar necita : *las
   imagenes donde se obtendran los tiles. *um fichero con la informacion del
   mapa tamaño de tile ancho tamaño de tile alto numero de tiled ancho
   numero debtiles largo armara las capas para renderizar */
struct Mapa *load_mapa(const char *fn);


/* la funcion corta el fragmento de un conjuto de tiles y guarda el tile en
   una nueva supreficie, src es la imagen que contiene los tiles x,y,w,h son
   las coordenadas donde se recortara el nuevo tile */

struct Tile *CutTile(SDL_Surface * src, int x, int y, int w, int h);


/* funcuon para pintar un tilen en posicion x,y */
void PrintTile(SDL_Surface * DST, int x, int y, struct Tile *T);


class CWorld
{
  public:
	CWorld();
	~CWorld();
	int Init();
	int LoadMapa(const char *fn);
	int createFloor();
    void render_scene(SDL_Surface * screen, int x_cam, int y_cam);
	int get_w_tile(){return w_tile;}
	int get_h_tile(){return h_tile;}
	int get_COL(){return COL;}
	int get_FILAS(){return FILAS;}

  private:
	int w_tile;
	int h_tile;
	int COL;
	int FILAS;
	struct Mapa *mapa;

};


#endif
