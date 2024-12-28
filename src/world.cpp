#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <SDL_manager.h>

#define Max_tiles 128


struct Tile *CutTile(SDL_Surface * src, int x, int y, int w, int h)
{
	struct Tile *temp = NULL;

	// Check if the source surface is valid
	if (!src)
	{
		printf("Error: source surface (src) is NULL\n");
		return NULL;
	}

	// Allocate memory for the Tile structure
	temp = (struct Tile *)malloc(sizeof(struct Tile));
	if (!temp)
	{
		printf("Error: memory allocation failed\n");
		return NULL;
	}

	// Create a new surface for the tile
	temp->tile = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	if (!temp->tile)
	{
		printf("Error: failed to create tile surface\n");
		free(temp);
		return NULL;
	}

	// Set the rectangle properties
	temp->rect.x = x;
	temp->rect.y = y;
	temp->rect.w = w;
	temp->rect.h = h;

	// Copy the specified region from src to the new surface
	if (SDL_BlitSurface(src, &temp->rect, temp->tile, NULL) < 0)
	{
		printf("Error: SDL_BlitSurface failed: %s\n", SDL_GetError());
		SDL_FreeSurface(temp->tile);
		free(temp);
		return NULL;
	}

	// Optimize the tile surface format for the current display
	SDL_Surface *optimized = SDL_DisplayFormat(temp->tile);
	if (optimized)
	{
		SDL_FreeSurface(temp->tile);
		temp->tile = optimized;
	}

	return temp;
}


void PrintTile(SDL_Surface * DST, int x, int y, struct Tile *T)
{
	// validacion de datos 
	if (!DST || !T || !T->tile)
	{
		printf("Error parametro nolo detectado en tile\n");
		return;
	}
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;


	if (SDL_BlitSurface(T->tile, NULL, DST, &rect) < 0)
	{
		printf("Error al blitear el tile %s\n", SDL_GetError());
	}
	return;

}



struct Mapa *load_mapa(const char *fn)
{
	struct Mapa *m = NULL;
	FILE *fd = fopen(fn, "rb");
	if (!fd)
	{
		printf("Error: archivo no encontrado %s\n", fn);
		return NULL;
	}

	m = (struct Mapa *)malloc(sizeof(struct Mapa));
	if (!m)
	{
		printf("Error: falla al asignar memoria para Mapa\n");
		fclose(fd);
		return NULL;
	}

	// Leer las dimensiones del mapa
	if (fread(&m->w, sizeof(int), 1, fd) != 1 ||
		fread(&m->h, sizeof(int), 1, fd) != 1 || fread(&m->ntiles, sizeof(int), 1, fd) != 1)
	{
		printf("Error: falla al leer las dimensiones del mapa\n");
		free(m);
		fclose(fd);
		return NULL;
	}

	// Asignar memoria para los tiles
	m->tile = (struct Tile *)malloc(sizeof(struct Tile) * m->ntiles);
	if (!m->tile)
	{
		printf("Error: falla al asignar memoria para los tiles\n");
		free(m);
		fclose(fd);
		return NULL;
	}

	// Leer cada tile
	for (int i = 0; i < m->ntiles; i++)
	{
		if (fread(&m->tile[i].w, sizeof(int), 1, fd) != 1 ||
			fread(&m->tile[i].h, sizeof(int), 1, fd) != 1)
		{
			printf("Error: falla al leer dimensiones del tile %d\n", i);
			// Liberar memoria asignada
			for (int j = 0; j < i; j++)
				free(m->tile[j].data);
			free(m->tile);
			free(m);
			fclose(fd);
			return NULL;
		}

		// Calcular tamaño del tile y asignar memoria
		int len = m->tile[i].w * m->tile[i].h;
		m->tile[i].data = (u32 *) malloc(sizeof(u32) * len);
		if (!m->tile[i].data)
		{
			printf("Error: falla al asignar memoria para el tile %d\n", i);
			for (int j = 0; j < i; j++)
				free(m->tile[j].data);
			free(m->tile);
			free(m);
			fclose(fd);
			return NULL;
		}

		// Leer datos del tile
		if (fread(m->tile[i].data, sizeof(u32), len, fd) != (size_t) len)
		{
			printf("Error: falla al leer datos del tile %d\n", i);
			for (int j = 0; j <= i; j++)
				free(m->tile[j].data);
			free(m->tile);
			free(m);
			fclose(fd);
			return NULL;
		}
	}

	fclose(fd);
	return m;
}


// clase world

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

int CWorld::Init()
{
	w_tile = mapa->tile[0].w;
	h_tile = mapa->tile[0].h;
	COL = mapa->w / w_tile;
	FILAS = mapa->h / h_tile;
	return 0;
}


int CWorld::LoadMapa(const char *fn)
{

	mapa = NULL;
	FILE *fd = fopen(fn, "rb");
	if (!fd)
	{
		printf("Error: archivo no encontrado %s\n", fn);
		return -1;;
	}

	mapa = (struct Mapa *)malloc(sizeof(struct Mapa));
	if (!mapa)
	{
		printf("Error: falla al asignar memoria para Mapa\n");
		fclose(fd);
		return -1;
	}

	// Leer las dimensiones del mapa
	if (fread(&mapa->w, sizeof(int), 1, fd) != 1 ||
		fread(&mapa->h, sizeof(int), 1, fd) != 1 || fread(&mapa->ntiles, sizeof(int), 1, fd) != 1)
	{
		printf("Error: falla al leer las dimensiones del mapa\n");
		free(mapa);
		fclose(fd);
		return -1;
	}

	// Asignar memoria para los tiles
	mapa->tile = (struct Tile *)malloc(sizeof(struct Tile) * mapa->ntiles);
	if (!mapa->tile)
	{
		printf("Error: falla al asignar memoria para los tiles\n");
		free(mapa);
		fclose(fd);
		return -1;
	}

	// Leer cada tile
	for (int i = 0; i < mapa->ntiles; i++)
	{
		if (fread(&mapa->tile[i].w, sizeof(int), 1, fd) != 1 ||
			fread(&mapa->tile[i].h, sizeof(int), 1, fd) != 1)
		{
			printf("Error: falla al leer dimensiones del tile %d\n", i);
			// Liberar memoria asignada
			for (int j = 0; j < i; j++)
				free(mapa->tile[j].data);
			free(mapa->tile);
			free(mapa);
			fclose(fd);
			return -1;
		}

		// Calcular tamaño del tile y asignar memoria
		int len = mapa->tile[i].w * mapa->tile[i].h;
		mapa->tile[i].data = (u32 *) malloc(sizeof(u32) * len);
		if (!mapa->tile[i].data)
		{
			printf("Error: falla al asignar memoria para el tile %d\n", i);
			for (int j = 0; j < i; j++)
				free(mapa->tile[j].data);
			free(mapa->tile);
			free(mapa);
			fclose(fd);
			return -1;
		}

		// Leer datos del tile
		if (fread(mapa->tile[i].data, sizeof(u32), len, fd) != (size_t) len)
		{
			printf("Error: falla al leer datos del tile %d\n", i);
			for (int j = 0; j <= i; j++)
				free(mapa->tile[j].data);
			free(mapa->tile);
			free(mapa);
			fclose(fd);
			return -1;
		}
	}

	fclose(fd);

	// iniciamos 
	Init();
	// colocamos los tiles en su lugat
	createFloor();

	return 0;

}

int CWorld::createFloor()
{

	// Crear la superficie para la primera capa
	mapa->capas[0] = SDL_CreateRGBSurface(0, mapa->w, mapa->h, 32, 0, 0, 0, 0);

	// Validar que la superficie se haya creado correctamente
	if (!mapa->capas[0])
	{
		printf("Error al crear la superficie: %s\n", SDL_GetError());
		return -1;
	}

	u32 *p = (u32 *) mapa->capas[0]->pixels;

	// Copiar los datos de los "tiles" a la superficie
	for (int q = 0; q < FILAS; q++)
	{
		for (int k = 0; k < COL; k++)
		{
			for (int i = 0; i < h_tile; i++)
			{
				for (int j = 0; j < w_tile; j++)
				{
					// Posición en la superficie
					int surface_index = (q * h_tile + i) * mapa->w + (k * w_tile + j);
					// Posición en el "tile"
					int tile_index = i * w_tile + j;
					// Copiar el pixel
					p[surface_index] = mapa->tile[0].data[tile_index];
				}
			}
		}
	}
	return 0;
}


void CWorld::render_scene(SDL_Surface * screen, int x_cam, int y_cam)
{
	int x = x_cam;
	int y = y_cam;

	/*static int fila = 0;
	static int columna = 0;
	static int desplazamiento_x = 0;
	static int desplazamiento_y = 0;
*/

	int i;
	int j;
/*	fila = y / 32;
	columna = x / 32;
	desplazamiento_x = x % 32;
	desplazamiento_y = y % 32;*/
	SDL_Rect rect1;

	i = -x;
	j = -y;
	rect1.x = i;
	rect1.y = j;

	SDL_BlitSurface(mapa->capas[0], NULL, screen, &rect1);

}
