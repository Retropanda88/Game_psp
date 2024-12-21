#include <pixel.h>

//y * screen->pitch / 4 + x

u8 getPixel8(SDL_Surface *s, int x, int y){
	u8 *pixels = (u8*)s->pixels;
	return pixels[y*s->pitch+x];
}

u16 getPixel16(SDL_Surface *s, int x, int y){
	u16 *pixels = (u16*)s->pixels;
	return pixels[y*s->pitch/2+x];
}

u32 getPixel(SDL_Surface *s, int x, int y){
	u32 *pixels = (u32*)s->pixels;
	return pixels[y*s->pitch/4+x];
}

int setPixel8(SDL_Surface *s, int x, int y, u8 pixel){
	u8 *pixels = (u8*)s->pixels;
	pixels[y*s->pitch+x] = pixel;
	return 0;
}

int setPixel16(SDL_Surface *s, int x, int y, u16 pixel){
	u16 *pixels = (u16*)s->pixels;
	pixels[y*s->pitch/2+x]=pixel;
	return 0;
}

int setPixel32(SDL_Surface *s, int x, int y, u32 pixel){
	u32 *pixels = (u32*)s->pixels;
	pixels[y*s->pitch/4+x]=pixel;
	return 0;
}