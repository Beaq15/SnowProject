#include "BattleScreen.h"

namespace Tmpl8 {
	BattleScreen::BattleScreen(SnowQueen* snowQueen, int* items, CharacterType enemyType)
	{
		//if incorrect enemy type put in, default to snowman
		if (enemyType != CharacterType::snowmanType && enemyType != CharacterType::bigFootType)
			enemyType = CharacterType::snowmanType;

		this->snowQueen = snowQueen;
		this->items = items;
		this->nameTexture = new TextTexture();

		//load background texture
		backgroundTexture = new Sprite(new Surface("assets/bg.png"), 1);

		//setup name texture drawing destination rectangle
		nameTexture->SetPos(180, 620);
		nameTexture->setcolor({ 0,0,0,0 });
		nameTexture->setText(snowQueen->getName());

		//setup animations
		heroAnimationSet.setup(80, 560, CharacterType::snowQueenType);
		enemyAnimationSet.setup(600, 350, enemyType);

		if (enemyType == CharacterType::snowmanType)
			enemy = new Snowman();
		else if (enemyType == CharacterType::bigFootType)
			enemy = new BigFoot();

		//setup health bars
		heroHP.setup(180, 650);
		enemyHP.setup(615, 220);

		//setup buttons
		fightButton.setup({ 0,600,150,84 }, "Fight");
		fightButton.selected = true;
		itemButton.setup({ 0,684,150,84 }, "Item");

		//decide who goes first
		if (snowQueen->getAGI() > enemy->getAGI())
			elsaTurn = true;
		else
			elsaTurn = false;

		//setup battle effects
		battleEffects.setup(enemyAnimationSet.x, enemyAnimationSet.y);

		//setup item menu
		itemMenu.setup(items, 0, 380);

	}

	BattleScreen::~BattleScreen()
	{
		delete backgroundTexture;
		delete nameTexture;
	}

	bool BattleScreen::animationsPlaying()
	{
		bool animating = heroAnimationSet.doAction || enemyAnimationSet.doAction;
		return animating;
	}

	void BattleScreen::useItem()
	{
		switch (items[itemMenu.selectedItemIndex])
		{
		case 1:
			//was liferegen, lets heal
			battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
			battleEffects.doHeal();

			snowQueen->heal(10);
			break;
		case 2:
			//bomb
			battleEffects.setXY(enemyAnimationSet.x, enemyAnimationSet.y);
			battleEffects.doExplode();

			enemyDmg = 20;
			break;
		case 3:
			//atk boost (perma increase)
			battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
			battleEffects.doAtkBoost();

			snowQueen->atkBoost(2);
			break;
		case 4:
			//def boost (perma increase)
			battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
			battleEffects.doDefBoost();

			snowQueen->defBoost(2);
			break;
		}
		//clear item from inventory
		items[itemMenu.selectedItemIndex] = 0;

		//change turns
		elsaTurn = false;
	}

	void BattleScreen::update(bool* keysStates, float deltaTime)
	{
					if (keysStates[(int)Keys::escape])
					{
						quit = true;
					}
					else if (keysStates[(int)Keys::up])
					{
						if (elsaTurn)
						{
							if (itemMenu.visible)
							{
								itemMenu.moveUp();
							}
							else
							{
								fightButton.selected = true;
								itemButton.selected = false;
							}
						}
					}
					else if (keysStates[(int)Keys::down])
					{
						if (elsaTurn)
						{
							if (itemMenu.visible)
							{
								itemMenu.moveDown();
							}
							else
							{
								fightButton.selected = false;
								itemButton.selected = true;
							}
						}
					}
					else if (keysStates[(int)Keys::enter])
					{
						if (elsaTurn && !animationsPlaying()) 
						{
							if (itemMenu.visible)
							{
								//if selected item was cancel or a noItem, do nothing
								if (itemMenu.selectedItemIndex == 10 || items[itemMenu.selectedItemIndex] == 0)
								{
									//do nothing, just need to close the item window
								}
								else
								{
									//use item
									useItem();
								}
								itemMenu.visible = false;
							}
							else if (fightButton.selected)
							{
								//punch someone
								heroAnimationSet.doAttack();
								enemyDmg = snowQueen->getDamage();
								elsaTurn = false;
							}
							else if (itemButton.selected)
							{
								//show item menu
								itemMenu.visible = true;
							}
						}
					}

			//update character states
			if (!animationsPlaying()) {
				if (snowQueen->getHP() <= 0 || enemy->getHP() <= 0)
				{
					//if anyone is dead, battle over
					battleFinished = true;
					wonfight = snowQueen->getHP() > 0;
				}
				else if (elsaDmg > 0)
				{
					snowQueen->takeDamage(elsaDmg);
					heroAnimationSet.doHit();

					battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
					battleEffects.doHit();

					elsaDmg = 0;
				}
				else if (enemyDmg > 0)
				{
					enemy->takeDamage(enemyDmg);
					enemyAnimationSet.doHit();

					battleEffects.setXY(enemyAnimationSet.x, enemyAnimationSet.y);
					battleEffects.doHit();

					enemyDmg = 0;
				}
				else if (!elsaTurn)
				{
					//ENEMY ATTACK
					enemyAnimationSet.doAttack();
					elsaDmg = enemy->getDamage();
					elsaTurn = true;
				}
			}

			//update animations
			heroAnimationSet.update(deltaTime);
			enemyAnimationSet.update(deltaTime);

			//update health bars
			heroHP.hp = snowQueen->getHP();
			heroHP.hpMax = snowQueen->getHPMax();

			enemyHP.hp = enemy->getHP();
			enemyHP.hpMax = enemy->getHPMax();

			//update battle effect animations
			battleEffects.update(deltaTime);
	}

	void BattleScreen::draw(Surface* renderer)
	{
		//clear the screen
		renderer->Clear(0x15cff9);

		//draw bg
		backgroundTexture->Draw(renderer, 0, 0);

		//draw enemy
		enemyAnimationSet.draw(renderer);

		//draw hero
		heroAnimationSet.draw(renderer);

		//ui bottom bar
		SDL_Rect bottomUIBar = { 0,600, 768, 168 };//x,y,w,h
		renderer->Bar(bottomUIBar.x, bottomUIBar.y, bottomUIBar.x + bottomUIBar.w, bottomUIBar.y + bottomUIBar.h, 0xb0c8d2);
		//draw border too
		renderer->Box(bottomUIBar.x, bottomUIBar.y, bottomUIBar.x + bottomUIBar.w, bottomUIBar.y + bottomUIBar.h, 0x000000);

		//draw name
		nameTexture->draw(renderer);

		//draw HP bars
		heroHP.draw(renderer);
		enemyHP.draw(renderer);

		//draw buttons
		fightButton.draw(renderer);
		itemButton.draw(renderer);

		//draw item menu
		itemMenu.draw(renderer);

		//draw effects
		battleEffects.draw(renderer);

	}
};
