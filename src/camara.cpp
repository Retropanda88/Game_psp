#include <camara.h>

extern const int w_screen;
extern const int h_screen;


void iniciar_camara(Camara * camara)
{
	camara->x = 100;
	camara->y = 0;
}

void mover_camara(Camara *c, int x, int y, CWorld *m){
	int limite_derecho, limite_inferior;
	
	limite_derecho = (m->get_COL()) * m->get_w_tile() - w_screen;
	
	limite_inferior = (m->get_FILAS()) *m->get_h_tile() - h_screen;
	
	c->x += (x - c->x) / 20;
	c->y += (y - c->y) / 20;
	
	if(c->x < 0) c->x = 0;
	if(c->y < 0) c->y = 0;
	
	if(c->x > limite_derecho){
		c->x = limite_derecho;
	}
	
	if(c->y > limite_inferior){
		c->y = limite_inferior;
	}
	
}
