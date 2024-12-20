#include  <graphic.h>

const int w = 320;
const int h = 240;

int main()
{
	Graphic g;
	g.Init(w, h, "game");

	while (1)
	{
		g.cls(0, 0, 255);
		g.pixel(10, 10, 255, 0, 0);
		g.draw_line(1,1,50,50,255,255,255);
		g.draw_rect(10,10,20,20,244,77,99);
		g.Update_screen();

	}
	g.Quit();
	return 0;
}
