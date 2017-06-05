#pragma once

#include <vector>
#include <map>
#include <stack>
#include <ctime>


#include "Input.inl.hh"
#include "Direction.hh"
#include "Entio.hh"

class Player
{
private:

	Map & map;
	Player *& enemy;

	std::map<char, Entio> entios;
	std::stack<Entio::coord> controlZ;
	std::stack<Entio::coord> controlX;


	char currentEntio;
	int actions;

	bool attackMenuBool;
	bool hitBool;
	bool hitFailBool;
	bool shootBool;
	bool shootFailBool;
	bool shootMountainBool;
	bool actualEntioWasted;

	bool enemyHitByArrow;
	int damageDealt;

	bool enemyKilledBool;

	char attackedCellContent;

	int randomRange;

public:	

	Player(Map & _map, Player *& _enemy, std::vector<char> _skins);

	void reset();
	void action();
	void lowFatigue();
	void change();

	void move(Direction direction);

	void useControlZ();
	void storeControlZ(int _x, int _y);
	void eraseControlZ();

	void useControlX();
	void storeControlX(int _x, int _y);
	void eraseControlX();

	void attackMenu();
	bool isAttacking();
	bool isOutOfAmmo();
	
	void hit(Direction direction);
	void shoot(Direction direction);
	
	void deleteEnemy(char enemyKey);

	bool isTurn();
	
	int getEntiosSize();
	int getCurrentEntioX();
	int getCurrentEntioY();

	void drawStats();
};