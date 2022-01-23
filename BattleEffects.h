#pragma once
#include "AnimationManager.h"

namespace Tmpl8 {
	class BattleEffects
	{
	public:
		int x, y;
		Animation hit, heal, explode, atkBoost, defBoost;
		AnimationManager animationManager;

		//set true while effect is animating
		bool doAction;

		void setup(int x, int y);
		void setXY(int x, int y);
		void doHit();
		void doHeal();
		void doExplode();
		void doAtkBoost();
		void doDefBoost();

		void update(float dt);
		void draw(Surface* renderer);
	};
};
