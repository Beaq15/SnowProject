#include "Button.h"
namespace Tmpl8 {

	Button::~Button()
	{
		if (textTexture != nullptr)
			delete textTexture;
	}

	void Button::setup(SDL_Rect buttonRect, string text)
	{
		this->buttonRect = buttonRect;
		this->textTexture = new TextTexture();
		textTexture->setcolor({ 0,0,0,0 });
		textTexture->setText(text);
		//setup name texture drawing destination rectangle
		textTexture->SetPos(buttonRect.x + 20 + 32, buttonRect.y + 2 + 32);

		selected = false;
	}

	void Button::draw(Surface* renderer)
	{
		//use different colors for buttons if selected or not
		Pixel drawColor;
		if (selected)
			drawColor = 0x0c9cbc;
		else
			drawColor = 0xb0c8d2;

		renderer->Bar(buttonRect.x, buttonRect.y, buttonRect.x+buttonRect.w, buttonRect.y+buttonRect.h, drawColor);
		renderer->Box(buttonRect.x, buttonRect.y, buttonRect.x + buttonRect.w, buttonRect.y + buttonRect.h, 0x000000);

		textTexture->draw(renderer);
	}

	void Button::drawInactive(Surface* renderer)
	{

		renderer->Bar(buttonRect.x, buttonRect.y, buttonRect.x + buttonRect.w, buttonRect.y + buttonRect.h, 0x646464);
		renderer->Box(buttonRect.x, buttonRect.y, buttonRect.x + buttonRect.w, buttonRect.y + buttonRect.h, 0x000000);
	}
};