#ifndef CAMARA_H_
#define CAMARA_H_

#include "types.h"
#include "world.h"

extern const int w_screen;
extern const int h_screen;

struct Camara{
	float x;
	float y;	
};

void iniciar_camara(Camara * camara);

void mover_camara(Camara *c, int x, int y, CWorld *m);


#endif