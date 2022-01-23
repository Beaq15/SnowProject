#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "surface.h"
#include "TextTexture.h"

using std::string;

namespace Tmpl8 {

	class ItemMenu
	{
	private:
		TextTexture* generateTextTexture(TTF_Font* font, SDL_Color colour, string text);

	public:
		int* items;//items array

		TextTexture* noItem, * lifeRegen, * bomb, * attackBoost, * defenceBoost, * cancel;
		int x, y;
		int selectedItemIndex;

		bool visible = false;



		~ItemMenu();
		void setup(int* items, int x, int y);
		void moveUp();
		void moveDown();
		void draw(Surface* renderer);
	};

};