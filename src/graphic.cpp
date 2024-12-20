#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <graphic.h>
#include <types.h>
#include <font.h>
#include <SDL_manager.h>

Graphic::Graphic()
{
	w = 0;
	h = 0;
	videobuffer = NULL;
}

Graphic::~Graphic()
{

}

int Graphic::Init(u32 w, u32 h, const char *msg)
{
	this->w = w;
	this->h = h;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("error: %s\n", SDL_GetError());
		return -1;
	}

	videobuffer = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE);
	if (!videobuffer)
	{
		printf("error: %s\n", SDL_GetError());
		return -1;
	}

	fb = (u32 *) videobuffer->pixels;

	printf("%s\n", msg);

	SDL_ShowCursor(false);

	return 0;
}

void Graphic::Update_screen()
{
	SDL_Flip(videobuffer);
}


void Graphic::cls()
{
	for (u32 i = 0; i < (w * h); i++)
		fb[i] = 0x00000000;

}

void Graphic::cls(u8 r, u8 g, u8 b)
{
	u32 color = SDL_MapRGB(videobuffer->format, r, g, b);
	for (u32 i = 0; i < (w * h); i++)
		fb[i] = color;
}


void Graphic::pixel(u32 x, u32 y, u8 r, u8 g, u8 b)
{
	if (x > w || x < 0 || y > h || y < 0)
		return;

	u32 color = SDL_MapRGB(videobuffer->format, r, g, b);
	int index = (y * videobuffer->pitch / 4 + x);
	fb[index] = color;
}

void Graphic::Quit()
{
	SDL_Quit();
	SDL_FreeSurface(videobuffer);
	free(fb);
}

u32 Graphic::get_pixel(u32 x, u32 y)
{
	if (x > w || x < 0 || y > h || y < 0)
		return 0x00000000;

	return fb[y * (videobuffer->pitch / 4) + x];
}

static int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void Graphic::draw_line(int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b)
{
	int x, y, step;
	step = max(abs(x2 - x1), abs(y2 - y1));
	step = step ? step : 1;
	for (int i = 0; i < step; i++)
	{
		x = x1 + (x2 - x1) * i / step;
		y = y1 + (y2 - y1) * i / step;
		pixel(x, y, r, g, b);
	}
}

void Graphic::draw_rect(int x, int y, int w, int h, u8 r, u8 g, u8 b)
{
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			pixel(x + i, y + j, r, g, b);
}

void Graphic::Fps_sincronizar(int frecuencia)
{
	static int t;
	static int temp;
	static int t1 = 0;

	t = SDL_GetTicks();
	if (t - t1 >= frecuencia)
	{
		temp = (t - t1) / frecuencia;
		t1 += temp * frecuencia;
	}
	else
	{
		SDL_Delay(frecuencia - (t - t1));
		t1 += frecuencia;
	}
}

void Graphic::print_text(int x, int y, u8 r, u8 g, u8 b, const char *s, ...)
{
	u32 color = SDL_MapRGB(videobuffer->format, r, g, b);
	char buffer[256];

	va_list zeiger;
	va_start(zeiger, s);
	vsprintf(buffer, s, zeiger);
	va_end(zeiger);

	print(videobuffer, x, y, buffer, color);
}

void Graphic::draw_surface(u32 x, u32 y, SDL_Surface * src)
{
	if(!src) return;
	SDL_Rect rect={(Sint16)x,(Sint16)y,w,h};
	SDL_BlitSurface(src,0,videobuffer,&rect);
}
