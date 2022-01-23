#include "BattleEffects.h"


namespace Tmpl8 {
	void BattleEffects::setup(int x, int y)
	{
		this->x = x;
		this->y = y;

		hit.setup("assets/hit.png", 4, 0.083f, 54, 107);
		heal.setup("assets/heal.png", 4, 0.083f, 54, 107);
		explode.setup("assets/explode.png", 4, 0.083f, 54, 107);
		atkBoost.setup("assets/atkBoost.png", 4, 0.083f, 31, 134);
		defBoost.setup("assets/defBoost.png", 4, 0.083f, 31, 134);
	}

	void BattleEffects::setXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void BattleEffects::doHit()
	{
		animationManager.changeAnimation(&hit);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void BattleEffects::doHeal()
	{
		animationManager.changeAnimation(&heal);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void BattleEffects::doExplode()
	{
		animationManager.changeAnimation(&explode);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void BattleEffects::doAtkBoost()
	{
		animationManager.changeAnimation(&atkBoost);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void BattleEffects::doDefBoost()
	{
		animationManager.changeAnimation(&defBoost);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void BattleEffects::update(float dt)
	{
		if (doAction)
		{
			animationManager.update(dt);
			if (animationManager.animationEnded)
				doAction = false;
		}
	}

	void BattleEffects::draw(Surface* renderer)
	{
		if (doAction)
			animationManager.draw(renderer, x, y);
	}
};