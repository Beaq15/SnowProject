#include "TextTexture.h"
namespace Tmpl8 {
	TextTexture::TextTexture()
	{
		font = TTF_OpenFont("assets/openSans_BoldItalic.ttf", 16);
	}
	TextTexture::~TextTexture()
	{
		if (textTexture != NULL)
			SDL_FreeSurface(textTexture);
		TTF_CloseFont(font);
	}
	void TextTexture::SetPos(int x, int y)
	{
		textRect.x = x;
		textRect.y = y;

	}
	void TextTexture::setText(string text)
	{

		if (this->text != text && text != "")
		{
			if (textTexture != NULL)
				SDL_FreeSurface(textTexture);
			this->text = text;

			textTexture = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 0 });

			textRect.w = textTexture->w;
			textRect.h = textTexture->h;
		}
		
	}
	void TextTexture::setcolor(SDL_Color color)
	{
		this->color = color;
	}
	void TextTexture::draw(Surface* Renderer)
	{
		if (visible && textTexture != NULL && text != "")
		{
			SDL_LockSurface(textTexture);
			for (int y = 0; y < textRect.h; y++)
				for (int x = 0; x < textRect.w; x++)
				{
					Uint8 red;
					Uint8 green;
					Uint8 blue;
					Uint8* p = (Uint8*)textTexture->pixels;
					SDL_GetRGB(p[y * textTexture->pitch + x], textTexture->format, &red, &green, &blue);
					if (red == 0 && green == 0 && blue == 0)
						Renderer->GetBuffer()[(y + textRect.y) * Renderer->GetPitch() + (x + textRect.x)] = ((Pixel)color.r << 16) + ((Pixel)color.g << 8) + (Pixel)color.b;
				}
			SDL_UnlockSurface(textTexture);
		}
	}
};