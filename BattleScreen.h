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
#include "surface.h"
#include "Keys.h"

namespace Tmpl8 {

	class BattleScreen
	{
	public:
		Sprite* backgroundTexture;

		SnowQueen* snowQueen;
		int* items;//pointer for our items array

		Character* enemy;

		bool battleFinished = false;
		bool quit = false;
		bool elsaTurn = true;
		bool wonfight = false;

		TextTexture* nameTexture;

		CharacterAnimationSet heroAnimationSet;
		CharacterAnimationSet enemyAnimationSet;

		HPBar heroHP;
		HPBar enemyHP;

		Button fightButton;
		Button itemButton;

		int elsaDmg = 0, enemyDmg = 0;

		BattleEffects battleEffects;

		ItemMenu itemMenu;
		InfoBox infoBox;

		BattleScreen(SnowQueen* snowQueen, int* items, CharacterType enemyType);
		~BattleScreen();
		bool animationsPlaying();
		void useItem();
		void update(bool* keysStates, float deltaTime);
		void draw(Surface* renderer);
	};

};
