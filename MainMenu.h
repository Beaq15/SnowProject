#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <list>
#include "SnowQueen.h"
#include "Snowman.h"
#include "BigFoot.h"
#include "CharacterType.h"
#include "CharacterAnimationSet.h"
#include "HPBar.h"
#include "Button.h"
#include "BattleEffects.h"
#include "ItemMenu.h"
#include "InfoBox.h"
#include "Game.h"
#include "MapScreen.h"
#include "keys.h"

namespace Tmpl8 {

	class MainMenu
	{
	public:
		SnowQueen* snowQueen;
		int* items;

		Sprite* backgroundTexture;
		int a = 0;
		Button playButton;
		Button quitButton;

		bool quit = false;
		bool playButtonPressed = (bool) a;

		MainMenu();
		~MainMenu();

		void update(bool* keysStates);
		void draw(Surface* renderer);
	};


};