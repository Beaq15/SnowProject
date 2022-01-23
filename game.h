#pragma once
#include <iostream> //input output stream
#include <string> 
#include "Character.h"
#include "SnowQueen.h"
#include "Snowman.h"
#include "BigFoot.h"
#include "Keys.h"
#include "Button.h"
#include "GameStates.h"
#include "BattleScreen.h"
//SDL Libraries
#include <SDL.h>
#include <SDL_ttf.h>

namespace Tmpl8 {

class Surface;
class MapScreen;
class MainMenu;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) { }
	void KeyDown(int key);

	SDL_Renderer* renderer;
	SnowQueen snowQueen;
	int items[10];
	CharacterType* enemyType;

	bool keysStates[(int)Keys::count];

private:
	Surface* screen;
	GameStates currentGameState = GameStates::MainMenu;
	MainMenu* mainMenu = nullptr;
	MapScreen* mapScreen = nullptr;
	BattleScreen* battle = nullptr;
};

}; // namespace Tmpl8