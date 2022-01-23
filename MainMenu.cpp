#include "MainMenu.h"
namespace Tmpl8 {
	MainMenu::MainMenu()
	{
		//load background texture
		backgroundTexture = new Sprite(new Surface("assets/mainmenuBG.jpeg"), 1);

		//setup button
		playButton.setup({ 240,450, 150,84 }, "PLAY");
		playButton.selected = false;
		quitButton.setup({ 400,450,150,84 }, "QUIT");
		quitButton.selected = false;
	}

	MainMenu::~MainMenu()
	{
		delete backgroundTexture;
	}

	void MainMenu::update(bool* keysStates)
	{

		if (keysStates[(int)Keys::escape])
			quit = true;
		else if (keysStates[(int)Keys::down])
		{
			playButton.selected = true;
		}
		if (playButton.selected && keysStates[(int)Keys::right])
		{
			quitButton.selected = true;
			playButton.selected = false;
		}
		if (quitButton.selected && keysStates[(int)Keys::left])
		{
			quitButton.selected = false;
			playButton.selected = (bool) right;
		}
		if (keysStates[(int)Keys::enter] && playButton.selected)
		{
			playButtonPressed = true;
		}
		if (keysStates[(int)Keys::enter] && quitButton.selected)
		{
			quit = true;
		}
	}

	void MainMenu::draw(Surface* renderer)
	{
		renderer->Clear(0x15d3f0);

		//draw bg
		backgroundTexture->Draw(renderer, 0, 0);

		//draw button
		playButton.draw(renderer);
		quitButton.draw(renderer);

	}
};