#pragma once
#include "AnimationManager.h"
#include "CharacterType.h"
#include "surface.h"

namespace Tmpl8 {

	class CharacterAnimationSet
	{
	public:
		int x, y;
		Surface* renderer;
		Animation idle, attack, hit;
		AnimationManager animationManager;

		//for animations that play once then return to idle
		bool doAction;

		void setup(int x, int y, CharacterType type);
		void doIdle();
		void doAttack();
		void doHit();

		void update(float dt);
		void draw(Surface* renderer);
	};

};