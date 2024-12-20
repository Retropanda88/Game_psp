#include <SDL/SDL_image.h>
#include <SDL_manager.h>
#include <types.h>

// y * screen->pitch / 4 + x

u8 getPixel8(SDL_Surface * s, int x, int y)
{
	u8 *pixels = (u8 *) s->pixels;
	return pixels[y * s->pitch + x];
}

u16 getPixel16(SDL_Surface * s, int x, int y)
{
	u16 *pixels = (u16 *) s->pixels;
	return pixels[y * s->pitch / 2 + x];
}

u32 getPixel(SDL_Surface * s, int x, int y)
{
	u32 *pixels = (u32 *) s->pixels;
	return pixels[y * s->pitch / 4 + x];
}

int setPixel8(SDL_Surface * s, int x, int y, u8 pixel)
{
	u8 *pixels = (u8 *) s->pixels;
	pixels[y * s->pitch + x] = pixel;
	return 0;
}

int setPixel16(SDL_Surface * s, int x, int y, u16 pixel)
{
	u16 *pixels = (u16 *) s->pixels;
	pixels[y * s->pitch / 2 + x] = pixel;
	return 0;
}

int setPixel32(SDL_Surface * s, int x, int y, u32 pixel)
{
	u32 *pixels = (u32 *) s->pixels;
	pixels[y * s->pitch / 4 + x] = pixel;
	return 0;

}


SDL_Surface *create_surface(SDL_Surface * src, int x, int y, int w, int h)
{
	SDL_Surface *temp = NULL;
	temp =
		SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, src->format->BitsPerPixel, src->format->Rmask,
							 src->format->Gmask, src->format->Bmask, src->format->Amask);
	if (temp == NULL)
	{
		printf("error: %s \n", SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	return temp;
}

SDL_Surface *get_rect(SDL_Surface * src, int x, int y, int w, int h)
{
	SDL_Surface *temp = NULL;
	temp =
		SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, src->format->BitsPerPixel, src->format->Rmask,
							 src->format->Gmask, src->format->Bmask, src->format->Amask);
	if (temp == NULL)
	{
		printf("error: %s \n", SDL_GetError());
		return NULL;
	}


	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			setPixel32(temp, i, j, getPixel16(src, x + i, y + j));

		}

	}

	temp = SDL_DisplayFormat(temp);

	return temp;
}

void apply_transparency(SDL_Surface * src, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color = SDL_MapRGB(src->format, r, g, b);
	SDL_SetColorKey(src, SDL_SRCCOLORKEY | SDL_RLEACCEL, color);
	src = SDL_DisplayFormat(src);
}

SDL_Surface *load_img(const char *fn)
{
	SDL_Surface *temp = NULL;
	temp = IMG_Load(fn);
	if (temp == NULL)
	{
		printf("error: %s\n", SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	return temp;
}

SDL_Surface *load_img(const char *fn, Uint32 color)
{
	SDL_Surface *temp = NULL;
	temp = IMG_Load(fn);
	if (temp == NULL)
	{
		printf("error: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY | SDL_RLEACCEL, color);
	temp = SDL_DisplayFormat(temp);
	return temp;
}
