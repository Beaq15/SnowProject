#include "Animation.h"

namespace Tmpl8 {
	void Animation::setup( char* spriteSheetFile, int numberOfFrames, float frameDuration, int offsetX, int offsetY)
	{

		this->spriteSheet = new Sprite(new Surface(spriteSheetFile), numberOfFrames);
		this->numberOfFrames = numberOfFrames;
		this->frameDuration = frameDuration;
		this->offsetX = offsetX;
		this->offsetY = offsetY;


	}

	Animation::~Animation()
	{
		if (spriteSheet != nullptr)
			delete spriteSheet;
	}

	void Animation::draw(Surface* renderer, int frame, int x, int y)
	{
		spriteSheet->SetFrame(frame);
		spriteSheet->Draw(renderer, x - offsetX, y - offsetY);
	}
}
