#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "surface.h"

//using std::string;
using namespace std;

namespace Tmpl8 {

	class TextTexture
	{
	public:

		TTF_Font* font;
		string text;
		SDL_Surface* textTexture = NULL;
		SDL_Rect textRect;
		SDL_Color color;
		bool visible = true;


		TextTexture();
		~TextTexture();

		void setText(string text);
		void draw(Surface* renderer);
		void SetPos(int x, int y);
		void setcolor(SDL_Color color);
	};
};
