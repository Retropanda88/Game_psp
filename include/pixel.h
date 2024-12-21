#ifndef PIXEL_H_
#define PIXEL_H_

#include <SDL/SDL.h>
#include "types.h"

u8 getPixel8(SDL_Surface *s, int x, int y);
u16 getPixel16(SDL_Surface *s, int x, int y);
u32 getPixel32(SDL_Surface *s, int x, int y);

int setPixel8(SDL_Surface *s, int x, int y, u8 pixel);
int setPixel16(SDL_Surface *s, int x, int y, u16 pixel);
int setPixel32(SDL_Surface *s, int x, int y, u32 pixel);

#endif