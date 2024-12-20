#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include <SDL/SDL.h>

SDL_Surface *create_surface(SDL_Surface * src, int w, int h);
SDL_Surface *get_rect(SDL_Surface * src, int x, int y, int w, int h);
SDL_Surface *load_img(const char *fn);
SDL_Surface *load_imf(const char *fn, Uint32 color);
void apply_transparency(SDL_Surface * src, Uint8 r, Uint8 g, Uint8 b);

#endif
