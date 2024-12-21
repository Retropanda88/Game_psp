/*PANTALLA 320 * 240 */

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



int m_map[20]={0,0,0,0,0};

const int w_screen = 320;
const int h_screen = 240;
const int bpp = 16;

Mapa *m;


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
  display->Set_Video(w_screen,h_screen,bpp);
  
  w = new CWorld;
  w->Init(m);

  CPersonaje *p;
  p = new CPersonaje;
  p->Init(100,100,4,"personaje 1");
 
  p->Load_sheet("data/sheet.bmp",6,8);
  p->Create_sprite();
  
  c = new Camara;
  iniciar_camara(c);
  
  m = new Mapa;
  
  m->h_tile = 32;
  m->w_tile = 32;
  
  m->columnas = 16;
  m->filas = 16;
  m->data=m_map;
  m->tile[0] = load_img("data/ttt.png");
  
  while(1){

 //recuerda que psp no tiene soporte con el subsistema
 //de joystick sdl
 #if PSP
  	psp_joystick_update();
 #endif	
   keys = SDL_GetKeyState(NULL);
#if PSP
   p->desplazar(&pad);
#else
   p->desplazar(keys);
#endif

   p->Draw(display->get_Buffer_video(), c);
   display->Print_text(15,20,124,155,133,"%s", p->get_name());
   mover_camara(c,p->get_x(),p->get_y(), w);
    
   display->Update();
   display->clean(0,0,0);
   display->Fps_sincronizar(10);
  }
  
  delete display; display = 0;
  delete p; p=0;
  delete c; c=0;

#if PSP
  exit_psp();  
#endif
  return 0;
}
