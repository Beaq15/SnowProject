#include "HPBar.h"
namespace Tmpl8 {
	HPBar::HPBar()
	{
		//default hp
		hp = hpMax = 100;
	}

	void HPBar::setup(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void HPBar::draw(Surface* renderer)
	{
		SDL_Rect back = { x,y,102,12 };//x,y,w,h
		//draw white part of bar
		renderer->Bar(x, y, x+102, y+12, 0xffffff);

		//draw black border
		renderer->Box(x, y, x + 102, y + 12, 0x000000);
		float hpF = (float)hp;//so we dont get stuck with integer division
		int hpBarWidth = (int)((hpF / hpMax) * 100);//100 is width of pixels of full health bar
		if (hpBarWidth < 0)
			hpBarWidth = 0;

		renderer->Bar(x + 1, y + 1, x + 1 + hpBarWidth, y + 11, 0x0c9cbc);
	}

};