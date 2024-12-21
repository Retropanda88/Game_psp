
#include <personaje.h>

static int key_direction(u8 *key){
	if(key[SDLK_UP])   return up;
	if(key[SDLK_DOWN]) return down;
	if(key[SDLK_LEFT]) return left;
	if(key[SDLK_RIGHT]) return right;
	return sleep;
	
}

#if PSP
static int key_direction_psp(SceCtrlData *pad){
	if(pad->Buttons & PSP_CTRL_UP) return up;
   	if(pad->Buttons & PSP_CTRL_DOWN) return down;
   	if(pad->Buttons & PSP_CTRL_LEFT) return left;
   	if(pad->Buttons & PSP_CTRL_RIGHT) return right;
	return sleep;	
}
#endif

CPersonaje::CPersonaje()
{
	x = 0;
	y = 0;
	x1 = 0;
	y1 = 0;
	dx = 0;
	dy = 0;
	nvidas = 0;
	estado_salud = 0;
	for (int i = 0; i < max_spr; i++)
	{
		spr[i] = NULL;
	}

}

CPersonaje::~CPersonaje()
{

	x = 0;
	y = 0;
	x1 = 0;
	y1 = 0;
	dx = 0;
	dy = 0;
	nvidas = 0;
	estado_salud = 0;
	for (int i = 0; i < max_spr; i++)
	{
		delete spr[i];
	}

}

int CPersonaje::Init(int x, int y, int nvidas, const char *name)
{
	this->x = x;
	this->y = y;
	this->nvidas = nvidas;

	estado_salud = 100;

	sprintf(this->name, "%s", name);
	dir = sleep;
	last_dir = right;
	dx = 1;
	dy = 1;

	return 0;
}

int CPersonaje::Load_sheet(const char *fn, int nframes_w, int nframes_h)
{
	this->nframes_w = nframes_w;
	this->nframes_h = nframes_h;
	spr[sheet] = new Sprite(fn, 1, 1);
	if (spr[sheet]->getSurface() == NULL)
	{
		printf("erro: %s\n", SDL_GetError());
		return 1;
	}

	spr[sheet]->setTransparency(255, 0, 255);
	w_frame = spr[sheet]->getSurface()->w / this->nframes_w;
	h_frame = spr[sheet]->getSurface()->h / nframes_h;
	return 0;
}

void CPersonaje::Create_sprite()
{
	int index = 0;
	for (int i = 1; i < max_spr; i++)
	{
		spr[i] =
			new Sprite(spr[sheet]->getRect(0, index, nframes_w * w_frame, h_frame), nframes_w, 60);
		spr[i]->reverseAnimation();
		index += h_frame;
	}
}

void CPersonaje::desplazar(u8 *key){
	dir = key_direction(key);
	switch(dir){
		case up:
		   y-=dy; last_dir = up;
		break;
		case down:
		   y+=dy; last_dir = down;
		break;
		case left: last_dir = left;
		  x-=dx;
		break;
		case right: last_dir = right;
		  x+=dx;
		break;
		
	}
}

#if PSP
void CPersonaje::desplazar(SceCtrlData *pad){
	dir = key_direction_psp(pad);
	switch(dir){
		case up:
		   y-=dy; last_dir = up;
		break;
		case down:
		   y+=dy; last_dir = down;
		break;
		case left: last_dir = left;
		  x-=dx;
		break;
		case right: last_dir = right;
		  x+=dx;
		break;
		
	}
}
#endif

void CPersonaje::Draw(SDL_Surface *s, Camara *c){
	
	x1 = x - c->x + 160;
	y1 = y - c->y + 120;
	
	if(dir != sleep){
		spr[dir]->animate()->draw(s,x1,y1);
	}else{
		spr[last_dir]->restart();
		spr[last_dir]->draw(s,x1,y1);
	}
}