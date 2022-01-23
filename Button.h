#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "surface.h"
#include "TextTexture.h"

using std::string;

namespace Tmpl8 {

	class Button
	{
	public:
		
		SDL_Rect buttonRect;
		TextTexture* textTexture;


		bool selected;

		~Button();

		void setup(SDL_Rect buttonRect, string text);
		void draw(Surface* renderer);
		void drawInactive(Surface* renderer);//what the buttons look like when the user cannot choose options
	};

};