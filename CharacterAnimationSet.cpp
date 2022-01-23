#include "CharacterAnimationSet.h"
namespace Tmpl8 {
	void CharacterAnimationSet::setup(int x, int y, CharacterType type)
	{
		this->renderer = renderer;
		this->x = x;
		this->y = y;

		if (type == CharacterType::snowQueenType)
		{
			//load up hero animations

			idle.setup("assets/fataIdle.png", 1, 1, 69, 132);
			attack.setup("assets/elsaAttack.png", 3, 0.2f, 69, 155);
			hit.setup("assets/elsaHit.png", 2, 0.1f, 47, 145);
		}
		else if (type == CharacterType::snowmanType)
		{
			idle.setup("assets/snowmanIdle.png", 1, 1, 36, 105);
			attack.setup("assets/snowmanAttack.png", 3, 0.1f, 36, 105);
			hit.setup("assets/snowmanHit.png", 2, 0.1f, 36, 105);
		}
		else if (type == CharacterType::bigFootType)
		{
			idle.setup("assets/bigfootIdle.png", 1, 1, 53, 65);
			attack.setup("assets/bigfootAttack.png", 4, 0.2f, 45, 69);
			hit.setup("assets/bigfootHit.png", 2, 0.1f, 45, 69);
		}

		doIdle();
	}

	void CharacterAnimationSet::doIdle()
	{
		animationManager.changeAnimation(&idle);
		animationManager.setAnimationLooping(true);
		doAction = false;
	}

	void CharacterAnimationSet::doAttack()
	{
		animationManager.changeAnimation(&attack);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void CharacterAnimationSet::doHit()
	{
		animationManager.changeAnimation(&hit);
		animationManager.setAnimationLooping(false);
		doAction = true;
	}

	void CharacterAnimationSet::update(float dt)
	{
		animationManager.update(dt);
		//if running action animation and that animation is finished
		if (animationManager.animationEnded && doAction)
		{
			doIdle();//go back to idle animation state
		}
	}

	void CharacterAnimationSet::draw(Surface* renderer)
	{
		animationManager.draw(renderer, x, y);
	}
};