#include  <graphic.h>

const int w = 320;
const int h = 240;

SDL_Surface *img = NULL;
Sprite *spr[4];

int main()
{
	Graphic g;
	g.Init(w, h, "game");

	img = load_img("data/sheet.bmp");
	apply_transparency(img, 255, 0, 255);
	
	spr[0] = new Sprite("data/sheet.bmp",1,1);
	spr[0]->setTransparency(255,0,255);
	
	spr[1] = new Sprite(spr[0]->getRect(0,0,32*6,32),6,60);


	while (1)
	{
		g.cls(0, 0, 255);
		g.draw_surface(10, 10, img);
		g.pixel(10, 10, 255, 0, 0);
		g.draw_line(1, 1, 50, 50, 255, 255, 255);
		g.draw_rect(10, 10, 20, 20, 244, 77, 99);
		g.print_text(20, 10, 255, 0, 0, "hello %d", 33);
		spr[1]->animate()->draw(g.videobuffer,50,50);
		g.Update_screen();
		g.Fps_sincronizar(10);

	}
	g.Quit();
	SDL_FreeSurface(img);
	return 0;
}
