#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <SDL_manager.h>

#define Max_tiles 128

enum
{
	tierra,
	pasto,
};

// pocicion de framentos de tiles
SDL_Rect c[Max_tiles]
{
	{
	6, 38, 36, 36},
	{102, 38, 36, 36},
};


// funcion para cargar un mapa
/* static SDL_Rect *pos(int x, int y, int w, int h) { SDL_Rect *temp = NULL;
   temp = (SDL_Rect *) malloc(sizeof(SDL_Rect)); if (!temp) { printf("no
   memori for rects"); return NULL; }

   temp->x = x; temp->y = y; temp->w = w; temp->h = h;

   return temp; } */

struct Mapa *load_mapa(const char *fn)
{
	struct Mapa *m = NULL;

	m = (struct Mapa *)malloc(sizeof(struct Mapa));
	if (!m)
	{
		printf("error memory fail\n");
		return NULL;
	}

	FILE *fd = fopen(fn, "rb");	// Abrir archivo en modo binario
	if (!fd)
	{
		printf("error unload file %s\n", fn);
		free(m);				// Liberar la memoria asignada antes de
		// retornar NULL
		return NULL;
	}

	// Leer las dimensiones del mapa
	if (fread(&m->w_tile, sizeof(int), 1, fd) != 1 ||
		fread(&m->h_tile, sizeof(int), 1, fd) != 1 ||
		fread(&m->columnas, sizeof(int), 1, fd) != 1 || fread(&m->filas, sizeof(int), 1, fd) != 1)
	{
		printf("error reading map dimensions\n");
		fclose(fd);
		free(m);
		return NULL;
	}

	// Asignar memoria para los datos del mapa
	m->data = (int *)malloc(sizeof(int) * m->filas * m->columnas);
	if (!m->data)
	{
		printf("error memory fail\n");
		fclose(fd);
		free(m);
		return NULL;
	}

	// Leer los datos del mapa
	if (fread(m->data, sizeof(int), m->filas * m->columnas, fd) != m->filas * m->columnas)
	{
		printf("error reading map data\n");
		fclose(fd);
		free(m->data);
		free(m);
		return NULL;
	}

	// cargamos los tiles
	m->tile[0] = load_img("data/ttt.png");
	if (!m)
	{
		printf("error unload tile sheet");
		return NULL;
	}

	// creamos las capas dependiendo la informacion del mapa


	// capa del pizo
	for (int i = 0; i < 4; i++)
	{
		m->capas[i] = create_surface(640, 480, 32);
		if (!m->capas[0])
		{
			printf("error surface %s\n", SDL_GetError());
			return NULL;
		}

	}


	SDL_Rect pos1, pos2;

	for (int j = 0; j < m->columnas; j++)
	{
		for (int i = 0; i < m->filas; i++)
		{

			pos1 = c[m->data[j * m->columnas + i]];
			pos2 ={(Sint16)(i *m->w_tile),(Sint16)( j * m->h_tile), (Uint16)m->w_tile, (Uint16)m->h_tile};
			SDL_BlitSurface(m->tile[0], &pos1, m->capas[0], &pos2);
		}
	}

	SDL_FreeSurface(m->tile[0]);

	fclose(fd);
	return m;
}



CWorld::CWorld()
{
	w_tile = 0;
	h_tile = 0;
	COL = 0;
	FILAS = 0;
}

CWorld::~CWorld()
{
	w_tile = 0;
	h_tile = 0;
	COL = 0;
	FILAS = 0;
}

int CWorld::Init(Mapa * m)
{
	w_tile = m->w_tile;
	h_tile = m->h_tile;
	COL = m->columnas;
	FILAS = m->filas;

	return 0;
}
