#pragma once

#include <iostream>
#include <string>

using std::string;

namespace Tmpl8 {


	class Character
	{
	protected: //works the same as private, but children classes can access them
		//attributes
		int hp, hpMax, str, def, agi;
	public:
		//behaviours/methods
		void setupStats(int _hp, int _str, int _def, int _agi);

		int getHP();
		int getHPMax();
		int getAGI();

		int getDamage();
		void takeDamage(int dmg);

	};
};
