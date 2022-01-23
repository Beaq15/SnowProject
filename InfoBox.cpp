#include "InfoBox.h"

namespace Tmpl8 {

	InfoBox::InfoBox()
	{
		this->textTexture = new TextTexture();
		textTexture->setcolor({ 255,255,255,255 });
	}


	InfoBox::~InfoBox()
	{
		if (textTexture != nullptr)
			delete textTexture;
	}


	void InfoBox::setText(string text)
	{
		
		//only bother changing text if its different from before and not an empty string
		if (textTexture->text != text && text != "")
		{
			textTexture->setText(text);
			textTexture->SetPos(768 / 2 - textTexture->textRect.w / 2, 768 / 2 - textTexture->textRect.h / 2);

			//work out our box rectangle with some padding
			boxRect.x = textTexture->textRect.x - 4;
			boxRect.y = textTexture->textRect.y - 4;
			boxRect.w = textTexture->textRect.w + 8;
			boxRect.h = textTexture->textRect.h + 8;

		}
	}

	void InfoBox::draw(Surface* renderer)
	{
		if (visible && textTexture != NULL && textTexture->text != "")
		{
			//draw box
			renderer->Bar(boxRect.x, boxRect.y, boxRect.w+boxRect.x, boxRect.h+boxRect.y, 0x1865f3);

			//draw border
			renderer->Box(boxRect.x, boxRect.y, boxRect.w + boxRect.x, boxRect.h + boxRect.y, 0xffffff);

			//draw text to screen
			textTexture->draw(renderer);
		}
		
	}
};