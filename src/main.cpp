#include  <graphic.h>

const int w = 320;
const int h = 240;

int main()
{
	Graphic g;
	g.Init(w, h, "game");

	while (1)
	{
		g.cls(255,0,0);
       g.Update_screen();
       
	}
	return 0;
}
