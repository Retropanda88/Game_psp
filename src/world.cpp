#include <stdio.h>
#include <stdlib.h>

#include <world.h>


// funcion para cargar un mapa
#include <stdio.h>
#include <stdlib.h>

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
	w_tile = 32;
	h_tile = 32;
	COL = 16;
	FILAS = 16;
	return 0;
}
