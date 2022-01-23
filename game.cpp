#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <SDL_ttf.h>
#include "MapScreen.h"
#include "MainMenu.h"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		TTF_Init();
		
		mapScreen = new MapScreen(&snowQueen, items);
		mainMenu = new MainMenu();	
		battle = nullptr;

		string name;
		name = "Snow Queen";

		//hero stats
		int hp = 100, str = 4, def = 5, agi = 1;
		snowQueen.setName(name);
		snowQueen.setupStats(hp, str, def, agi);

		//loop through array using for loop and set each slot to = 0 (no item)
		for (int i = 0; i <= 9; i++)
		{
			//reference index using variable
			items[i] = 0;
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete mapScreen;
		delete mainMenu;
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;
			switch (currentGameState)
			{
			case GameStates::MainMenu:
				mainMenu->update(keysStates);
				mainMenu->draw(screen);
				if (mainMenu->playButtonPressed)
				{
					currentGameState = GameStates::MapScreen;
					mainMenu->playButtonPressed = false;
				}
				break;
			case GameStates::MapScreen:
				mapScreen->update(keysStates);
				mapScreen->draw(screen);
				if (mapScreen->enemyEncountered)
				{
					delete battle;
					battle = new BattleScreen(&snowQueen, items, mapScreen->EnemyType());

					currentGameState = GameStates::BattleScreen;
					mapScreen->enemyEncountered = false;

				}
				break;
			case GameStates::BattleScreen:
				battle->update(keysStates, deltaTime);
				battle->draw(screen);
				if (battle->battleFinished)
				{
					currentGameState = GameStates::MapScreen;
					mapScreen->FightEnded(battle->wonfight);
				}

				break;
			}
			for (int i = 0; i < ((int)Keys::count); i++)
			{
				keysStates[i] = false;
			}
	}
	void Game::KeyDown(int key)
	{
		switch (key)
		{
		case SDLK_ESCAPE:
			keysStates[(int)Keys::escape] = true;
			break;
		case SDL_SCANCODE_RETURN:
			keysStates[(int)Keys::enter] = true;
			break;
		case SDL_SCANCODE_RIGHT:
			keysStates[(int)Keys::right] = true;
			break;
		case SDL_SCANCODE_LEFT:
			keysStates[(int)Keys::left] = true;
			break;
		case SDL_SCANCODE_UP:
			keysStates[(int)Keys::up] = true;
			break;
		case SDL_SCANCODE_DOWN:
			keysStates[(int)Keys::down] = true;
			break;
		}
		
		
	}
};