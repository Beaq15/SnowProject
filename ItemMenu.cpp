#include "ItemMenu.h"
namespace Tmpl8 {
	TextTexture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color colour, string text)
	{
		TextTexture* textTexture = new TextTexture();
		textTexture->setcolor(colour);
		textTexture->setText(text);
		return textTexture;
	}

	ItemMenu::~ItemMenu()
	{
		delete noItem;
		delete lifeRegen;
		delete bomb;
		delete attackBoost;
		delete defenceBoost;
		delete cancel;
	}

	void ItemMenu::setup(int* items, int x, int y)
	{
		this->items = items;
		this->x = x;
		this->y = y;

		TTF_Font* font = TTF_OpenFont("assets/openSans_BoldItalic.ttf", 16);
		SDL_Color textColor = { 0,0,0,0 };

		//generate all text textures
		noItem = generateTextTexture(font, textColor, "--");
		lifeRegen = generateTextTexture(font, textColor, "Life Regen");
		bomb = generateTextTexture(font, textColor, "Bomb");
		attackBoost = generateTextTexture(font, textColor, "Atk Boost");
		defenceBoost = generateTextTexture(font, textColor, "Def Boost");
		cancel = generateTextTexture(font, textColor, "Cancel");

		TTF_CloseFont(font);

	}

	void ItemMenu::moveUp()
	{
		selectedItemIndex--;
		//smallest index is 0 in items array, so lets not go negative
		if (selectedItemIndex < 0)
			selectedItemIndex = 0;
	}

	void ItemMenu::moveDown()
	{
		selectedItemIndex++;
		//items array index 0-9, but also we have cancel button as slot 10 in our menu
		if (selectedItemIndex > 10)
			selectedItemIndex = 10;
	}

	void ItemMenu::draw(Surface* renderer)
	{
		if (!visible)
			return; //skips rest of this function

		SDL_Rect itemButton = { x, y, 100, 20 };

		//loop through 10 items for drawing to screen
		for (int i = 0; i < 10; i++)
		{
			//put button beneath previous button
			itemButton.y = y + (i * itemButton.h);

			//set item buttons background colour based on if its selected or not
			Pixel drawColor;
			if (selectedItemIndex == i)
				drawColor = 0xd82b59;
			else
				drawColor = 0xffffff;
			renderer->Bar(itemButton.x, itemButton.y, itemButton.x + itemButton.w, itemButton.y + itemButton.h, drawColor);

			//setup Texture pointer and work out which text texture we need for this item we are rendering
			TextTexture* tmpTexture = noItem;
			if (items[i] == 1)
				tmpTexture = lifeRegen;
			else if (items[i] == 2)
				tmpTexture = bomb;
			else if (items[i] == 3)
				tmpTexture = attackBoost;
			else if (items[i] == 4)
				tmpTexture = defenceBoost;

			tmpTexture->SetPos(itemButton.x + 2, itemButton.y + 2);
			tmpTexture->draw(renderer);
		}

		//and also do cancel button too
		Pixel drawColor;
		if (selectedItemIndex == 10)
			drawColor = 0xd82b59;
		else
			drawColor = 0xffffff;

		//put button beneath previous button
		itemButton.y = y + (10 * itemButton.h);
		renderer->Bar(itemButton.x, itemButton.y, itemButton.x + itemButton.w, itemButton.y + itemButton.h, drawColor);

		cancel->SetPos(itemButton.x + 2, itemButton.y + 2);
		cancel->draw(renderer);
	}
};