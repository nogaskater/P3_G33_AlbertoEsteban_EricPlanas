#include "Player.hh"

Player::Player(Map & _map, Player *& _enemy, std::vector<char> _skins) : map(_map), enemy(_enemy), currentEntio(_skins[0]), actions(10), attackedCellContent('z')
{
	attackMenuBool = false;

	hitBool = false;
	hitFailBool = false;

	shootBool = false;
	shootFailBool = false;
	shootMountainBool = false;
	enemyHitByArrow = false;
	enemyKilledBool = false;
	actualEntioWasted = false;
	damageDealt = 0;

	randomRange = 0;

	for (int i = 0; i < _skins.size(); i++)
	{
		Entio entio(map, _skins[i]);

		std::pair<char, Entio> entioToInsert(_skins[i], entio);

		entios.insert(entioToInsert);
	}
}

void Player::reset()
{
	actions = 10;
	
	for (auto it = entios.begin(); it != entios.end(); it++)
	{
		if (it->second.getTurnFatigue() != 0)
		{
			it->second.addPermaFatigue();
		}

		it->second.resetTurnFatigue();
	}
}

void Player::action()
{
	actions--;
}

void Player::lowFatigue()
{
	map.swapPlayer();

	eraseControlZ();
	eraseControlX();

	int lowerFatigue = entios[currentEntio].getPermaFatigue();
	bool actualReached = false;
	
	for (auto it = entios.begin(); it != entios.end(); ++it)
	{
		if (it->first == currentEntio)
		{
			actualReached = true;
		}
		if (actualReached)
		{
			if (it->second.getPermaFatigue() < lowerFatigue)
			{
				lowerFatigue = it->second.getPermaFatigue();
				currentEntio = it->first;
			}
		}
	}

	for (auto it = entios.begin(); it != entios.end(); ++it)
	{
		if (it->second.getPermaFatigue() < lowerFatigue)
		{
			lowerFatigue = it->second.getPermaFatigue();
			currentEntio = it->first;
		}
	}
}

void Player::change()
{
	eraseControlZ();
	eraseControlX();

	int lowerFatigue = entios[currentEntio].getTotalFatigue();
	bool lowerFound = false;
	bool actualFirstReached = false;

	for (auto it = entios.begin(); it != entios.end(); ++it)
	{
		if (it->first == currentEntio)
		{
			actualFirstReached = true;
		}

		if (actualFirstReached)
		{
			if (it->second.getTotalFatigue() < lowerFatigue)
			{
				lowerFatigue = it->second.getTotalFatigue();
				currentEntio = it->first;
				actualFirstReached = false;
				lowerFound = true;
			}
		}
	}

	for (auto it = entios.begin(); it != entios.end(); ++it)
	{
		if (it->second.getTotalFatigue() < lowerFatigue)
		{
			lowerFatigue = it->second.getTotalFatigue();
			currentEntio = it->first;
			actualFirstReached = false;
			lowerFound = true;
		}
	}

	bool finalReached = false;
	bool actualSecondReached = false;

	if (!lowerFound)
	{
		for (auto it = entios.begin(); it != entios.end(); ++it)
		{
			if (it->first == currentEntio)
			{
				actualSecondReached = true;
			}

			if (actualSecondReached)
			{
				if (it->second.getTotalFatigue() == lowerFatigue && currentEntio != it->first)
				{
					currentEntio = it->first;
					actualSecondReached = false;
					lowerFound = true;
				}
			}
		}

		
		for (auto it = entios.begin(); it != entios.end(); ++it)
		{
			if (actualSecondReached)
			{
				if (it->second.getTotalFatigue() == lowerFatigue && currentEntio != it->first)
				{
					currentEntio = it->first;
					actualSecondReached = false;
					lowerFound = true;
				}
			}
		}
	}
	if (lowerFound)
	{
		action();
	}
	else
	{
		actualEntioWasted = true;
	}
}

void Player::move(Direction direction)
{
	storeControlZ(entios[currentEntio].getX(), entios[currentEntio].getY());

	eraseControlX();

	entios[currentEntio].move(direction);

	if (entios[currentEntio].entioMoved())
	{
		action();
		entios[currentEntio].resetEntioMoved();
	}
	else
	{
		controlZ.pop();
	}
}



void Player::useControlZ()
{
	if (controlZ.size() != 0)
	{
		storeControlX(entios[currentEntio].getX(), entios[currentEntio].getY());

		entios[currentEntio].moveTo(controlZ.top().x, controlZ.top().y);

		controlZ.pop();

		actions++;
	}
}

void Player::storeControlZ(int _x, int _y)
{
	controlZ.push(Entio::coord(_x, _y));
}

void Player::eraseControlZ()
{
	while (controlZ.size() != 0)
	{
		controlZ.pop();
	}
}



void Player::useControlX()
{
	 if(controlX.size() != 0)
	 {
		 storeControlZ(entios[currentEntio].getX(), entios[currentEntio].getY());

		 entios[currentEntio].moveTo(controlX.top().x, controlX.top().y);

		 controlX.pop();

		 actions--;
	 }
}

void Player::storeControlX(int _x, int _y)
{
	controlX.push(Entio::coord(_x, _y));
}

void Player::eraseControlX()
{
	while (controlX.size() != 0)
	{
		controlX.pop();
	}
}




void Player::attackMenu()
{
	if (attackMenuBool == true)
		attackMenuBool = false;
	else
		attackMenuBool = true;
}

bool Player::isAttacking()
{
	return attackMenuBool;
}

bool Player::isOutOfAmmo()
{
	if (entios[currentEntio].getArrows() > 0)
		return false;
	else
		return true;
}

void Player::hit(Direction direction)
{
	attackMenuBool = false;

	eraseControlZ();
	eraseControlX();
	
	action();

	entios[currentEntio].addTurnFatigue();

	int x, y;
	x = entios[currentEntio].getX();
	y = entios[currentEntio].getY();

	char enemyKilledSkin = 'z';

	switch (direction)
	{
	case Direction::UP:

		attackedCellContent = map.getCell(y - 1,x);
		
		break;

	case Direction::LEFT:

		attackedCellContent = map.getCell(y, x - 1);

		break;

	case Direction::DOWN:

		attackedCellContent = map.getCell(y + 1, x);

		break;

	case Direction::RIGHT:

		attackedCellContent = map.getCell(y, x + 1);

		break;
	}


	for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
	{
		if (attackedCellContent == it->first)
		{

			it->second.takeDamage(10);
			if (it->second.getLife() <= 0)
			{
				enemyKilledBool = true;
				enemyKilledSkin = it->first;
			}

		}
	}
	if (enemyKilledBool)
	{
		deleteEnemy(enemyKilledSkin);
		hitBool = true;
	}
	else
	{
		hitFailBool = true;
	}
}

void Player::shoot(Direction direction)
{
	attackMenuBool = false;

	eraseControlZ();
	eraseControlX();

	action();

	entios[currentEntio].addTurnFatigue();

	srand(time(nullptr));
	randomRange = (rand() % 8) + 3;

	entios[currentEntio].consumeArrow();

	int x, y;
	x = entios[currentEntio].getX();
	y = entios[currentEntio].getY();

	char enemyKilledSkin = 'z';

	switch (direction)
	{
	case Direction::UP:

		for (int i = 1; i <= randomRange; i++)
		{
			if (enemyHitByArrow)
				break;

			attackedCellContent = map.getCell(y - i, x);
			damageDealt = 11 - i;

			if (attackedCellContent == 'X')
			{
				shootMountainBool = true;
				break;
			}
			for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
			{
				if (enemyHitByArrow)
					break;

				if (attackedCellContent == it->first)
				{
					enemyHitByArrow = true;


					it->second.takeDamage(damageDealt);


					if (it->second.getLife() <= 0)
					{
						enemyKilledBool = true;
						enemyKilledSkin = it->first;
					}
				}
			}
		}

		break;

	case Direction::LEFT:

		for (int i = 1; i <= randomRange; i++)
		{
			if (enemyHitByArrow)
				break;

			attackedCellContent = map.getCell(y, x - i);
			damageDealt = 11 - i;

			if (attackedCellContent == 'X')
			{
				shootMountainBool = true;
				break;
			}

			for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
			{
				if (enemyHitByArrow)
					break;

				if (attackedCellContent == it->first)
				{
					enemyHitByArrow = true;


					it->second.takeDamage(damageDealt);


					if (it->second.getLife() <= 0)
					{
						enemyKilledBool = true;
						enemyKilledSkin = it->first;
					}
				}
			}
		}

		break;

	case Direction::DOWN:

		for (int i = 1; i <= randomRange; i++)
		{
			if (enemyHitByArrow)
				break;

			attackedCellContent = map.getCell(y + i, x);
			damageDealt = 11 - i;

			if (attackedCellContent == 'X')
			{
				shootMountainBool = true;
				break;
			}

			for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
			{
				if (enemyHitByArrow)
					break;

				if (attackedCellContent == it->first)
				{
					enemyHitByArrow = true;


					it->second.takeDamage(damageDealt);


					if (it->second.getLife() <= 0)
					{
						enemyKilledBool = true;
						enemyKilledSkin = it->first;
					}
				}
			}
		}

		break;

	case Direction::RIGHT:

		for (int i = 1; i <= randomRange; i++)
		{
			if (enemyHitByArrow)
				break;

			attackedCellContent = map.getCell(y, x + i);
			damageDealt = 11 - i;

			if (attackedCellContent == 'X')
			{
				shootMountainBool = true;
				break;
			}

			for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
			{
				if (enemyHitByArrow)
					break;

				if (attackedCellContent == it->first)
				{
					enemyHitByArrow = true;


					it->second.takeDamage(damageDealt);


					if (it->second.getLife() <= 0)
					{
						enemyKilledBool = true;
						enemyKilledSkin = it->first;
					}
				}
			}
		}

		break;

	}

	if (!enemyHitByArrow && !shootMountainBool)
	{
		shootFailBool = true;
	}

	if (enemyKilledBool)
	{
		deleteEnemy(enemyKilledSkin);
	}

}


void Player::deleteEnemy(char enemyKey)
{
	int x = enemy->entios[enemyKey].getX();
	int y = enemy->entios[enemyKey].getY();

	map.setCell(y, x, enemy->entios[enemyKey].getTemp());

	
	if (enemy->currentEntio == enemyKey) 
	{
		bool actualReached = false;
		bool currentEntioSwaped = false;

		for (auto it = enemy->entios.begin(); it != enemy->entios.end(); ++it)
		{
			if (it->first == enemyKey)
			{
				actualReached = true;
			}
			if (actualReached && !currentEntioSwaped)
			{
				if (it->first != enemyKey)
				{
					enemy->currentEntio = it->first;
					currentEntioSwaped = true;
				}
			}
		}
		if (!currentEntioSwaped)
		{
			enemy->currentEntio = enemy->entios.begin()->first;
		}
	}
	
	enemy->entios.erase(enemyKey);

}

bool Player::isTurn()
{
	return actions > 0;
}





int Player::getEntiosSize()
{
	return entios.size();
}

int Player::getCurrentEntioX()
{
	return entios[currentEntio].getX();
}

int Player::getCurrentEntioY()
{
	return entios[currentEntio].getY();
}



void Player::drawStats()
{
	enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
	enti::cout << enti::endl;
	enti::cout << enti::Color::DARKGRAY << "                          Entio controlled: " << enti::Color::LIGHTMAGENTA << entios[currentEntio].getSkin() << enti::endl;
	enti::cout << enti::endl;
	enti::cout << enti::Color::DARKGRAY << "                       You have " << enti::Color::LIGHTGREEN << actions << enti::Color::DARKGRAY << " movements left!" << enti::endl;
	enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;

	//std::cout << "Entio fatigue: " << entios[currentEntio].getPermaFatigue() << std::endl;
	//std::cout << entios.size() << std::endl;
	
	enti::cout << enti::Color::WHITE << enti::endl;
	

	// COUT DE LA FATIGA DE TODOS LOS ENTIOS
	/*
	for (auto it = entios.begin(); it != entios.end(); ++it)
	{
		std::cout << "Entio " << it->first << " : " << it->second.getPermaFatigue() << " - " << it->second.getTurnFatigue() << std::endl;
	}
	*/

	if (attackMenuBool)
	{
		enti::cout << enti::Color::YELLOW << "                              ATTACK MENU" << enti::endl;
		enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
		enti::cout << enti::endl;
		enti::cout << enti::Color::DARKGRAY << "                  Select the weapon you want to choose:" << enti::endl;
		enti::cout << enti::Color::WHITE << enti::endl;
		enti::cout << enti::Color::LIGHTMAGENTA << "                       1 - " << enti::Color::WHITE << "SWORD    ";
		enti::cout << enti::Color::LIGHTMAGENTA << "   2 - " << enti::Color::WHITE << "BOW";
		if (!isOutOfAmmo()) enti::cout << enti::Color::DARKGRAY << " (" << enti::Color::LIGHTGREEN << entios[currentEntio].getArrows() << enti::Color::DARKGRAY << " arrows left!)";
		else enti::cout << enti::Color::RED << "  (This Entio is OUT OF ARROWS!)";
		enti::cout << enti::Color::WHITE << enti::endl;

	}

	if (hitBool)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "                 Entio " << enti::Color::LIGHTMAGENTA << currentEntio << enti::Color::LIGHTGRAY << " slashed Entio " << enti::Color::LIGHTRED << attackedCellContent << enti::Color::LIGHTGRAY << " with his SWORD!" << enti::endl;

		hitBool = false;
	}
	if (hitFailBool)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "              Entio " << enti::Color::LIGHTMAGENTA << currentEntio << enti::Color::LIGHTGRAY << " just missed an attack with his SWORD!" << enti::endl;
		enti::cout << enti::Color::WHITE << enti::endl;
		enti::cout << enti::Color::WHITE << "                              What a noob!" << enti::endl;

		hitFailBool = false;
	}
	if (enemyHitByArrow)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "    Entio " << enti::Color::LIGHTMAGENTA << currentEntio << enti::Color::LIGHTGRAY << " landed an arrow into Entio " << enti::Color::LIGHTRED << attackedCellContent << enti::Color::LIGHTGRAY << ", dealing " << enti::Color::YELLOW << damageDealt << enti::Color::LIGHTGRAY << " points of damage." << enti::endl;
		if (!enemyKilledBool)
		{
			enti::cout << enti::endl;
			enti::cout << enti::Color::LIGHTGRAY << "                   Entio " << enti::Color::LIGHTRED << attackedCellContent << enti::Color::LIGHTGRAY << " has " << enti::Color::YELLOW << enemy->entios[attackedCellContent].getLife() << enti::Color::LIGHTGRAY << " points of health left!" << enti::endl;
		}

		enemyHitByArrow = false;
	}

	if (shootFailBool)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "                Entio " << enti::Color::LIGHTMAGENTA << currentEntio << enti::Color::LIGHTGRAY << " just missed a shot with his BOW!" << enti::endl;
		enti::cout << enti::endl;
		enti::cout << enti::Color::WHITE << "                          Is he even trying?" << enti::endl;
		shootFailBool = false;
	}

	if (shootMountainBool)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "                Entio " << enti::Color::LIGHTMAGENTA << currentEntio << enti::Color::LIGHTGRAY << " just hit a MOUNTAIN with his BOW!" << enti::endl;
		enti::cout << enti::endl;
		enti::cout << enti::Color::WHITE << "                You cant shoot through mountains, you fool!" << enti::endl;
		shootMountainBool = false;
	}

	if (enemyKilledBool)
	{
		enti::cout << enti::Color::WHITE << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "                           Entio " << enti::Color::LIGHTRED << attackedCellContent << enti::Color::LIGHTGRAY << " is DEAD!" << enti::endl;
		enemyKilledBool = false;
	}

	if (actualEntioWasted)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "               You are already on the less fatigued Entio!" << enti::endl;
		actualEntioWasted = false;
	}

	//std::cout << randomRange << std::endl;

	//CONTROL Z / X Debug
	/*
	for (int i = 0; i < controlZ.size(); i++)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::WHITE << "controlZ storage" << enti::endl;
		enti::cout << enti::Color::WHITE << controlZ.top().x << " - " << controlZ.top().y << enti::endl;
	}
	for (int i = 0; i < controlX.size(); i++)
	{
		enti::cout << enti::endl;
		enti::cout << enti::Color::WHITE << "controlX storage" << enti::endl;
		enti::cout << enti::Color::WHITE << controlX.top().x << " - " << controlX.top().y << enti::endl;
	}
	*/
}


