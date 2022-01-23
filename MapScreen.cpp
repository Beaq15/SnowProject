#include "MapScreen.h"
#include "surface.h"
#include "template.h"
#include "game.h"

namespace Tmpl8 {

	MapScreen::MapScreen(SnowQueen* snowQueen, int* items)
	{
		this->snowQueen = snowQueen;
		this->items = items;
		this->infoBox = new InfoBox();

		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 12; y++)
			{
				map[x][y] = 6;
			}
		}
		//Open map text file
		fstream mapFile("assets/mapbea.txt");
		if (mapFile.is_open())
		{
			for (int y = 0; y < 12; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					char grid;//read in a single character from where we are up to in the file
					mapFile >> grid;
					switch (grid)
					{
					case 's':
						map[x][y] = 1; 	//sky
						break;
					case 'm':
						map[x][y] = 5; 	//smallMountainUp
						break;
					case 'd':
						map[x][y] = 4; 	//smallMountainDown
						break;
					case 'M':
						map[x][y] = 2; 	//bigMountainUp	
						break;
					case 'D':
						map[x][y] = 3; 	//biglMountainDown
						break;
					case 'i':
						map[x][y] = 11; //iceStoneBigLeft
						break;
					case 'I':
						map[x][y] = 12; //iceStoneBigRight
						break;
					case 'L':
						map[x][y] = 8; //cornerLUp
						break;
					case 'l':
						map[x][y] = 7; //cornerLDown
						break;
					case 'R':
						map[x][y] = 9; //cornerRUP
						break;
					case 'r':
						map[x][y] = 0; //cornerRDown
						break;
					case 'S':
						map[x][y] = 10; //sea
						break;
					case 'p':
						map[x][y] = 13; //icestoneSmall
						break;
					default:
						map[x][y] = 6; //snow
						switch (grid)
						{
						case 'h':
						{heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
						break;
						}
						case 'u':
						{door.type = 2;
						door.x = x;
						door.y = y;
						break;
						}
						case 'c':
						{MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
						break;
						}
						case 'g':
						{MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
						break;
						}
						case 'C':
						{MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
						break;
						}
						}
						break;
					}
				}
			}
		}
		//close file
		mapFile.close();

		//LOAD UP TILE TEXTURES
		//static Sprite snowQueenTexture(new Surface("assets/elsaTile.png"), 36);
		snowQueenTexture = new Sprite(new Surface("assets/elsaTile.png"), 1);
		doorTexture = new Sprite(new Surface("assets/doorTile.png"), 1);
		snowmanTexture = new Sprite(new Surface("assets/snowmanTile.png"), 1);
		chestTexture = new Sprite(new Surface("assets/chestTile.png"), 1);
		bigfootTexture = new Sprite(new Surface("assets/bigfootTile.png"), 1);
		snowTexture = new Sprite(new Surface("assets/snow.png"), 1);
		skyTexture = new Sprite(new Surface("assets/sky.png"), 1);
		seaTexture = new Sprite(new Surface("assets/sea.png"), 1);
		cornerLDownTexture = new Sprite(new Surface("assets/cornerLDown.png"), 1);
		cornerLUPTexture = new Sprite(new Surface("assets/cornerLUP.png"), 1);
		cornerRDownTexture = new Sprite(new Surface("assets/cornerRDown.png"), 1);
		cornerRUPTexture = new Sprite(new Surface("assets/cornerRUP.png"), 1);
		icestoneBigLeftTexture = new Sprite(new Surface("assets/icestoneBigLeft.png"), 1);
		icestoneBigRightTexture = new Sprite(new Surface("assets/icestoneBigRight.png"), 1);
		icestoneSmallTexture = new Sprite(new Surface("assets/icestoneSmall.png"), 1);
		mountainBigDownTexture = new Sprite(new Surface("assets/mountainBigDown.png"), 1);
		mountainBigUPTexture = new Sprite(new Surface("assets/mountainBigUP.png"), 1);
		mountainSmallDownTexture = new Sprite(new Surface("assets/mountainSmallDown.png"), 1);
		mountainSmallUpTexture = new Sprite(new Surface("assets/mountainSmallUp.png"), 1);

		//setup info box
		infoBox->setText("Welcome to the Ice Land!");
	}

	MapScreen::~MapScreen()
	{
		delete snowQueenTexture;
		delete doorTexture;
		delete snowmanTexture;
		delete chestTexture;
		delete bigfootTexture;
		delete snowTexture;
		delete seaTexture;
		delete cornerLDownTexture;
		delete cornerLUPTexture;
		delete cornerRDownTexture;
		delete cornerRUPTexture;
		delete icestoneBigLeftTexture;
		delete icestoneBigRightTexture;
		delete icestoneSmallTexture;
		delete mountainBigDownTexture;
		delete mountainBigUPTexture;
		delete mountainSmallDownTexture;
		delete mountainSmallUpTexture;
		delete infoBox;
	}

	void MapScreen::itemFound()
	{
		//randomly pick an item (between 1-4)
		int item = rand() % 4 + 1;//rand gets next number out of random number set (value between 0-2147483647)
		//try find a free slot for this item!
		bool freeSlotFound = false;
		for (int i = 0; i < 10; i++)
		{
			//once find free slot, set it to the item and exit the loop
			if (items[i] == 0)
			{
				freeSlotFound = true;
				items[i] = item;
				break;//exits the loop
			}
		}

		if (freeSlotFound)
		{
			if (item == 1)
				infoBox->setText("Found life regen!");
			else if (item == 2)
				infoBox->setText("Found bomb!");
			else if (item == 3)
				infoBox->setText("Found Attack Boost!");
			else if (item == 4)
				infoBox->setText("Found Defence Boost!");
		}
		else
		{
			infoBox->setText("Your bag is full!");
		}
		infoBox->visible = true;
	}
	CharacterType MapScreen::EnemyType()
	{
		return enemyType;
	}

	void MapScreen::FightEnded(bool wonfight)
	{
		if (wonfight)
		{
			infoBox->setText("You have won the fight");
		}
		else
		{
			infoBox->setText("You died");
		}
		infoBox->visible = true;
	}

	void MapScreen::update(bool* keysStates)
	{
				if (keysStates[(int)Keys::escape])
				{
					quit = true;
					//exitapp = 1;
				}
				if (keysStates[(int)Keys::enter])
				{
					infoBox->visible = false;
				}
				if (infoBox->visible == false && snowQueen->getHP() > 0)
				{
					//player movement
					int hx = heroObj.x;
					int hy = heroObj.y;
					//right dpad on keyboard
					if (keysStates[(int)Keys::right])
					{
						hx++;
					}
					//left
					if (keysStates[(int)Keys::left])
					{
						hx--;
					}
					//down dpad on keyboard
					if (keysStates[(int)Keys::down])
					{
						hy++;
					}
					//left
					if (keysStates[(int)Keys::up])
					{
						hy--;
					}
					if (hx >= 0 && hx < 12 && hy >= 0 && hy < 12 && (map[hx][hy] == 6 || map[hx][hy] == 8 || map[hx][hy] == 7 || map[hx][hy] == 9 || map[hx][hy] == 0))
					{
						heroObj.x = hx;
						heroObj.y = hy;

						if (!doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
						{
							infoBox->setText("You escaped!");
							infoBox->visible = true;
							escaped = true;
						}
						else if (doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
						{
							heroObj.x--;
							infoBox->setText("Kill all monsters before escaping!");
							infoBox->visible = true;
							if (keysStates[(int)Keys::enter])
							{
								infoBox->visible = false;
							}
						}

						//see if we walked onto a map object
						//for(int i = 1; i <= 10; i++)
						for (list<MapObject>::iterator mo = mapObjects.begin(); mo != mapObjects.end(); mo++)
						{
							//iterator is a special pointer pointing to a position in a list
							//dereferencing(*) iterator gives you access to the item at that point in the list

							//only interact with active map objects
							if ((*mo).active)
							{
								//is hero's x,y overlapping this mapobjects x,y
								if (heroObj.x == mo->x && heroObj.y == mo->y)
								{
									mo->active = false;

									//check map objects type and deal with accordingly
									if (mo->type == 3)
									{
										enemyEncountered = true;
										enemyType = CharacterType::snowmanType;
										if (snowQueen->getHP() <= 0)
										{
											infoBox->setText("You died!");
											infoBox->visible = true;
										}
									}
									else if (mo->type == 4)
									{
										enemyEncountered = true;
										enemyType = CharacterType::bigFootType;
										if (snowQueen->getHP() <= 0)
										{
											infoBox->setText("You died!");
											infoBox->visible = true;
										}
									}
									else if (mo->type == 5)
									{
										//open chest get item :D
										itemFound();
									}
								}
							}
						}
					}
				}

		//check to see if map objects all inactive and if we should unlock the door
		if (!infoBox->visible && doorLocked)
		{
			bool monstersAlive = false;
			for (MapObject mo : mapObjects)
			{
				//if is a monster(glob or mimic)
				if (mo.type == 3 || mo.type == 4)
				{
					//if is active monster?
					if (mo.active)
					{
						monstersAlive = true;
						break;
					}
				}
			}
			//if all monsters are dead, unlock the door
			if (!monstersAlive)
			{
				doorLocked = false;
				infoBox->setText("The door is unlocked!");
				infoBox->visible = true;
			}
		}

		//has user closed infobox after escaping
		if (!infoBox->visible && (escaped || snowQueen->getHP() <= 0))
		{
			SDL_Event closeWindowEvent;
			closeWindowEvent.type = SDL_QUIT;
			SDL_PushEvent(&closeWindowEvent);
		}
	}

	void MapScreen::draw(Surface* renderer) {
		//MAP DRAWING
		//tile representing size of 1 grid thing from map
		SDL_Rect tileRect = { 0,0,64,64 };
		//loop through and draw each grid value from map array
		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 12; y++)
			{
				//MOVE rectangle to grid position with regards to tile width/height
				tileRect.x = x * tileRect.w;
				tileRect.y = y * tileRect.h;
				switch (map[x][y])
				{
				case 1:
					skyTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 6:
					snowTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 5:
					mountainSmallUpTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 4:
					mountainSmallDownTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 2:
					mountainBigUPTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 3:
					mountainBigDownTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 11:
					icestoneBigLeftTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 12:
					icestoneBigRightTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 8:
					cornerLUPTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 7:
					cornerLDownTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 9:
					cornerRUPTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 0:
					cornerRDownTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 10:
					seaTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 13:
					icestoneSmallTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				}
			}
		}
		//DRAW MAP OBJECTS
		//draw hero
		tileRect.x = heroObj.x * tileRect.w;
		tileRect.y = heroObj.y * tileRect.h;
		snowQueenTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
		//draw door
		tileRect.x = door.x * tileRect.w;
		tileRect.y = door.y * tileRect.h;
		doorTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
		//DRAW MAP OBJECTS IN LIST
		//loop through list and draw each object
		for (MapObject mo : mapObjects)
		{
			//NOTE: mo is a mapObject copy from mapObjects and is not a direct reference to the mapObject in the list
			if (mo.active)
			{
				tileRect.x = mo.x * tileRect.w;
				tileRect.y = mo.y * tileRect.h;
				switch (mo.type)
				{
				case 3:
					snowmanTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				case 5:
					chestTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				default:
					bigfootTexture->DrawScaled(tileRect.x, tileRect.y, tileRect.w, tileRect.h, renderer);
					break;
				}
			}
		}
		//draw info box on top
		infoBox->draw(renderer);
	}
};