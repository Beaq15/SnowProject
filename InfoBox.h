#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "surface.h"
#include "TextTexture.h"

//using std::string;
using namespace std;

namespace Tmpl8 {

	class InfoBox
	{
	public:

		TextTexture* textTexture;
		SDL_Rect boxRect;

		bool visible = true;


		InfoBox();
		~InfoBox();

		void setText(string text);
		void draw(Surface* renderer);
	};
};