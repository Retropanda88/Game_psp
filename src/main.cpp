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
		g.Update_screen();

	}
	g.Quit();
	return 0;
}
