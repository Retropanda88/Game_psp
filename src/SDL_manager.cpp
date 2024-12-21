#include <SDL/SDL_image.h>
#include <SDL_manager.h>
#include <pixel.h>


SDL_Surface *create_surface(SDL_Surface *src, int x, int y, int w, int h){
	SDL_Surface * temp = NULL;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,src->format->BitsPerPixel,src->format->Rmask,src->format->Gmask,src->format->Bmask,src->format->Amask);
	if(temp == NULL){
		printf("error: %s \n",SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	return temp;
}

SDL_Surface *get_rect(SDL_Surface *src, int x, int y, int w, int h){
	SDL_Surface *temp = NULL;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,src->format->BitsPerPixel,src->format->Rmask,src->format->Gmask,src->format->Bmask,src->format->Amask);
	if(temp == NULL){
		printf("error: %s \n",SDL_GetError());
		return NULL;
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			setPixel16(temp,i,j,getPixel16(src,x+i,y+j));

		}

	}

	temp = SDL_DisplayFormat(temp);

	return temp;
}

SDL_Surface *apply_transparency(SDL_Surface *src, Uint8 r, Uint8 g, Uint8 b){
 	SDL_Surface *temp = NULL;
 	temp = get_rect(src,0,0,src->w,src->h);
 	if(temp == NULL){
 		printf("error: %s\n",SDL_GetError());
 		return NULL;
 	}
 	Uint32 color = SDL_MapRGB(src->format,r,g,b);
 	SDL_SetColorKey(temp,SDL_SRCCOLORKEY|SDL_RLEACCEL,color);
 	temp = SDL_DisplayFormat(temp);
 	return temp;
}

SDL_Surface *load_img(const char *fn){
	SDL_Surface *temp = NULL;
	temp = IMG_Load(fn);
	if(temp == NULL){
		printf("error: %s\n",SDL_GetError());
		return NULL;
	}
	temp = SDL_DisplayFormat(temp);
	return temp;
}

SDL_Surface *load_img(const char *fn, Uint32 color){
	SDL_Surface *temp = NULL;
	temp = IMG_Load(fn);
	if(temp == NULL){
		printf("error: %s\n",SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(temp,SDL_SRCCOLORKEY|SDL_RLEACCEL,color);
	temp = SDL_DisplayFormat(temp);
	return temp;
}