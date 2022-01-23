#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

#include "surface.h"

using std::string;

namespace Tmpl8 {
	class Animation
	{
	public:
		//basic info
		int numberOfFrames;
		int frameWidth, frameHeight;
		int offsetX, offsetY;
		float frameDuration; 
		Sprite* spriteSheet; 

		void setup(char* spriteSheetFile, int numberOfFrames, float frameDuration, int offsetX, int offsetY);
		~Animation();
		void draw(Surface* renderer, int frame, int x, int y);
	};
};
