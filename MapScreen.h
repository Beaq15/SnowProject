#pragma once
#include <iostream>
#include <string>

#include "surface.h"
#include "SnowQueen.h"
#include "MapObject.h"
#include <list>//is a container that can shrink and grow (others vector, map, queue, stack)

#include <fstream>//file stream
#include "InfoBox.h"

#include <stdlib.h>//useful functions including rand and srand
#include <time.h>//time in seconds since start of year

#include "BattleScreen.h"
#include "MainMenu.h"

#include "Keys.h"

using namespace std;
namespace Tmpl8 {
	class MapScreen
	{
	public:
		SnowQueen* snowQueen;
		int* items; 

		int map[14][14];
		MapObject heroObj;
		MapObject door;
		list<MapObject> mapObjects;

		Sprite* snowQueenTexture, * doorTexture, * snowmanTexture, * chestTexture, * bigfootTexture, * snowTexture, * skyTexture, * cornerLDownTexture, * cornerLUPTexture, * cornerRDownTexture, * cornerRUPTexture, * icestoneBigLeftTexture, * icestoneBigRightTexture, * icestoneSmallTexture, * mountainBigDownTexture, * mountainBigUPTexture, * mountainSmallDownTexture, * mountainSmallUpTexture, * seaTexture;

		bool quit = false;
		bool escaped = false;
		bool doorLocked = true;
		bool enemyEncountered = false;

		CharacterType enemyType;

		InfoBox* infoBox;

		MapScreen(SnowQueen* snowQueen, int* items);
		~MapScreen();
		void itemFound();
		CharacterType EnemyType();
		void FightEnded(bool wonfight);
		void update(bool* keysStates);
		void draw(Surface* renderer);
	};
};