#include <SDL/SDL.h>
#include <string.h>
#include <stdio.h>
#include <graphic.h>
#include <SDL_manager.h>
#include <font.h>
#include <pixel.h>


static int max(int a, int b){
	if(a>b)return a;
	return b;
}

CGraphic::CGraphic(){
	w = 0;
	h = 0;
	bpp = 0;
	Buffer_video = 0;
}

CGraphic::~CGraphic(){
	w = 0;
	h = 0;
	bpp = 0;
	SDL_FreeSurface(Buffer_video);
	Buffer_video = 0;
}

int CGraphic::Init(){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0){
	  printf("error: %s\n",SDL_GetError());
	  return 1;
	}
	
	printf("sistem video init success..\n");
	
	return 0;
	
}

int CGraphic::Set_Video(int w, int h, int bpp){

	this->w = w;
	this->h = h;
	this->bpp = bpp;	
	Buffer_video=SDL_SetVideoMode(w,h,bpp,SDL_SWSURFACE);
	if(Buffer_video == NULL){
		printf("error: reslocion no sopprtada\n");
		return 1;
	}

	SDL_ShowCursor(false);

	fontsize( 8, 8 );
	
	printf("set video w->%d h->%d bpp->%d\n",w,h,bpp);
	return 0;
}

void CGraphic::clean(){
	memset(Buffer_video->pixels,0x00,Buffer_video->pitch*Buffer_video->h);
}

void CGraphic::clean(u8 r, u8 g, u8 b){
     u32 color = SDL_MapRGB(Buffer_video->format,r,g,b);
     SDL_FillRect(Buffer_video,0,color);
}

void CGraphic::Fill_Rect(int x, int y, int w, int h, u32 color){
	
	SDL_Rect rect={x,y,w,h};
	SDL_FillRect(Buffer_video,&rect,color);
}

void CGraphic::Fill_Rect(int x, int y, int w, int h, u8 r, u8 g, u8 b){
	SDL_Rect rect={x,y,w,h};
	u32 color = SDL_MapRGB(Buffer_video->format,r,g,b);
	SDL_FillRect(Buffer_video,&rect,color);
}

void CGraphic::Pixel(int x, int y, u32 color){
	
	switch(bpp){
		case 8:
		  setPixel8(Buffer_video,x,y,color);
	    break;
	    case 16:
	       setPixel16(Buffer_video,x,y,color);
	    break;
	    case 32 :
	      setPixel32(Buffer_video,x,y,color);
	    break;
	}
	
}

void CGraphic::Pixel(int x, int y, u8 r, u8 g, u8 b){
	u32 color = SDL_MapRGB(Buffer_video->format,r,g,b);
	switch(bpp){
		case 8:
		  setPixel8(Buffer_video,x,y,color);
	    break;
	    case 16:
	       setPixel16(Buffer_video,x,y,color);
	    break;
	    case 32 :
	      setPixel32(Buffer_video,x,y,color);
	    break;
	}
	
}

void CGraphic::Line(int x, int y,int x1, int y1, u32 color){
	int X,Y,dx, dy, step, i;
	dx = abs(x1-x);
	dy = abs(y1-y);
	step = max(dx,dy);
	step = step?step:1;
	for(i=0;i<step;i++){
		X=x+(x1-x)*i/step;
		Y=y+(y1-y)*i/step;
		Pixel(X,Y,color);
	}
}

void CGraphic::Line(int x, int y,int x1, int y1, u8 r, u8 g, u8 b){
	int X,Y,dx, dy, step, i;
	dx = abs(x1-x);
	dy = abs(y1-y);
	step = max(dx,dy);
	step = step?step:1;
	u32 color = SDL_MapRGB(Buffer_video->format,r,g,b);
	for(i=0;i<step;i++){
		X=x+(x1-x)*i/step;
		Y=y+(y1-y)*i/step;
		Pixel(X,Y,color);
	}
}

void CGraphic::Fps_sincronizar(int frecuencia){
	static int t;
	static int temp;
	static int t1 = 0;
	
	t =  SDL_GetTicks();
	if(t-t1 >= frecuencia){
		temp = (t-t1)/frecuencia;
		t1 += temp*frecuencia;
	}
	else{
		SDL_Delay(frecuencia-(t-t1));
		t1+=frecuencia;
	}
}

void CGraphic::Draw_s(SDL_Surface *src, int x, int y){
	SDL_Rect rect={x,y,0,0};
	SDL_BlitSurface(src,0,Buffer_video,&rect);
}

void CGraphic::Print_text(int x, int y, u8 r, u8 g, u8 b, const char *s, ...){
	char buffer[256];
	va_list zeiger;
	va_start(zeiger,s);
	vsprintf(buffer,s,zeiger);
	va_end(zeiger);
	u32 color = SDL_MapRGB(Buffer_video->format, r,g,b);
	print(Buffer_video,x,y,buffer,color);
}


void CGraphic::Print_text( int x, int y,u32 color, const char *s, ...){
	char buffer[256];
	va_list zeiger;
	va_start(zeiger,s);
	vsprintf(buffer,s,zeiger);
	va_end(zeiger);
	
	print(Buffer_video,x,y,buffer,color);
}