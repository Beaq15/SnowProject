#pragma once
#include <SDL.h>
#include "surface.h"
namespace Tmpl8 {


	class HPBar
	{
	public:
		int x, y;
		int hp, hpMax;

		HPBar();
		void setup(int x, int y);
		void draw(Surface* renderer);
	};
};

