/* PANTALLA 320 * 240 */

#if PSP
#include <psp.h>
#endif

#include <stdlib.h>
#include <SDL/SDL.h>

#include <camara.h>
#include <graphic.h>
#include <personaje.h>
#include <world.h>
#include <SDL_manager.h>

const int w_screen = 320;
const int h_screen = 240;
const int bpp = 32;

struct Mapa *m;

u8 r = 12;
u8 g = 10;
u8 b = 19;

SDL_Surface *tilesheet = NULL;
struct Tile *tile = NULL;


/*************************************************************************
                         funtion main 
***************************************************************************/
int main(int argc, char **argv)
{

#if PSP
	init_psp();
#endif

	u8 *keys;
	Camara *c;
	CWorld *w;


	CGraphic *display;
	display = new CGraphic;
	display->Init();
	display->Set_Video(w_screen, h_screen, bpp);

	m = load_mapa("data/mapa/mapa.dat");
	if(!m){
		return -1;
	}

	w = new CWorld;
	w->Init(m);

	CPersonaje *p;
	p = new CPersonaje;
	p->Init(100, 100, 4, "personaje 1");

	p->Load_sheet("data/sheet.bmp", 6, 8);
	p->Create_sprite();

	tilesheet = load_img("data/tiles.png");

	tile = CutTile(tilesheet, 770, 32, 50, 50);

	c = new Camara;
	iniciar_camara(c);


	while (1)
	{

		// recuerda que psp no tiene soporte con el subsistema
		// de joystick sdl
#if PSP
		psp_joystick_update();
#endif
		keys = SDL_GetKeyState(NULL);
#if PSP
		p->desplazar(&pad);
#else
		p->desplazar(keys);
#endif

        SDL_BlitSurface(m->capas[0],NULL,display->get_Buffer_video(),NULL);
		   
		   
		p->Draw(display->get_Buffer_video(), c);
		mover_camara(c, p->get_x(), p->get_y(), w);

		display->Update();
		display->clean(0, 0, 0);
		display->Fps_sincronizar(10);
	}

	delete display;
	display = 0;
	delete p;
	p = 0;
	delete c;
	c = 0;

#if PSP
	exit_psp();
#endif
	return 0;
}
