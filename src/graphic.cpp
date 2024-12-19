#include <graphic.h>
#include <types.h>

Graphic::Graphic(){
  w = 0;
  h = 0;
  videobuffer = NULL;
}

Graphic::~Graphic(){
	
}

int Graphic::Init(u32 w, u32 h, const char *msg){
	this->w = w;
	this->h = h;
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0)
	{
		printf("error: %s\n",SDL_GetError());
		return -1;
	}
	
	return 0;
}
