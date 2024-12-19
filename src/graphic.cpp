#include <graphic.h>
#include <types.h>

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
	for (int i = 0; i < (w * h); i++)
		fb[i] = 0x00000000;

}

void Graphic::cls(u8 r, u8 g, u8 b)
{
	u32 color = SDL_MapRGB(videobuffer->format, r, g, b);
	for (int i = 0; i < (w * h); i++)
		fb[i] = color;
}
