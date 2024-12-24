#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

void CutTile(SDL_Surface * src, int x, int y, int w, int h, u32 * data);

int main()
{
	// Inicializar SDL y SDL_image
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error al inicializar SDL: %s\n", SDL_GetError());
		return 1;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("Error al inicializar SDL_image: %s\n", IMG_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Surface *s = SDL_SetVideoMode(320, 240, 32, 0);
	u32 *p = (u32 *) s->pixels;

	// Crear el archivo mapa.dat
	FILE *fd = fopen("mapa.dat", "wb");
	if (!fd)
	{
		printf("Error al abrir el archivo para escritura\n");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Configuración del mapa y tiles
	int w = 640;
	int h = 480;
	int w_tile = 40;
	int h_tile = 40;
	int ntiles = 2;
	int x = 772; // Cambiar posición de recorte por cada
	int y = 36;// Fijo para este ejemplo

	fwrite(&w, 1, sizeof(int), fd);
	fwrite(&h, 1, sizeof(int), fd);
	fwrite(&ntiles, 1, sizeof(int), fd);

	// Cargar la imagen de los tiles
	SDL_Surface *img = IMG_Load("tiles.png");
	if (!img)
	{
		printf("Error al cargar la imagen: %s\n", IMG_GetError());
		fclose(fd);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Asignar memoria para almacenar los datos de un tile
	u32 *data = (u32 *) malloc(sizeof(u32) * w_tile*h_tile);
	if (!data)
	{
		printf("Error al asignar memoria para los datos del tile\n");
		SDL_FreeSurface(img);
		fclose(fd);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Procesar y guardar los tiles
	for (int i = 0; i < ntiles; i++)
	{

		fwrite(&w_tile, 1, sizeof(int), fd);
		fwrite(&h_tile, 1, sizeof(int), fd);

		u32 *pixel = (u32 *) img->pixels;

		// Recortar y guardar los datos del tile
		for (int p = 0; p < h_tile; p++)
		{
			for (int q = 0; q < w_tile; q++)
			{
				data[p * w_tile + q] = pixel[(p + y) * img->w + (x + q)];
			}
		}
		fwrite(data, 1, sizeof(u32) * 50 * 50, fd);
	}
	
	SDL_FillRect(s,0,0xffffffff);

	for (int i = 0; i < w_tile; i++)
	{
		for (int j = 0; j < h_tile; j++)
		{
			p[i * 320 + j] = data[i * w_tile + j];
		}
	}

	// while (1)
	// {
	// SDL_Rect rect={770,32,50,50};
	// SDL_BlitSurface(img,&rect,s,NULL);
	SDL_Flip(s);
	SDL_Delay(9000);

	// }

	// Liberar recursos
	free(data);
	SDL_FreeSurface(img);
	fclose(fd);
	IMG_Quit();
	SDL_Quit();

	printf("Archivo mapa.dat creado correctamente\n");
	return 0;
}

// Implementación de CutTile
void CutTile(SDL_Surface * src, int x, int y, int w, int h, u32 * data)
{
	SDL_Surface *temp =
		SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	if (!temp)
	{
		printf("Error al crear superficie temporal: %s\n", SDL_GetError());
		return;
	}

	SDL_Rect rect = { x, y, w, h };
	if (SDL_BlitSurface(src, &rect, temp, NULL) != 0)
	{
		printf("Error al recortar la superficie: %s\n", SDL_GetError());
		SDL_FreeSurface(temp);
		return;
	}

	u32 *pixels = (u32 *) temp->pixels;
	int len = w * h;
	for (int i = 0; i < len; i++)
	{
		data[i] = pixels[i];
		// data[i]=0xffffffff;
	}

	SDL_FreeSurface(temp);
}
