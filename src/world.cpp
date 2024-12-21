#include <world.h>

CWorld::CWorld()
{
	w_tile = 0;
	h_tile = 0;
	COL = 0;
	FILAS = 0;
}

CWorld::~CWorld()
{
	w_tile = 0;
	h_tile = 0;
	COL = 0;
	FILAS = 0;
}

int CWorld::Init(Mapa *m){
	w_tile = 32;
	h_tile = 32;
	COL = 16;
	FILAS = 16;
	return 0;
}
