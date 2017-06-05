#pragma once

#include <vector>
#include <unordered_map>

#include "Direction.hh"
#include "Map.hh"

class Entio
{
private:

	Map & map;

	int permaFatigue;
	int turnFatigue;
	bool moved;

	char skin;
	char temp;
	int life;
	int arrows;
	int x, y;

	

public:

	Entio();
	Entio(Map & map, char skin);

	struct coord 
	{
		int x, y;

		coord(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
	};

	char getSkin();
	int getLife();
	int getPermaFatigue();
	int getTurnFatigue();
	int getTotalFatigue();
	int getX();
	int getY();
	char getTemp();
	int getArrows();

	void addPermaFatigue();
	void addTurnFatigue();
	void consumeArrow();

	void moveTo(const int & x, const int & y);
	void moveBy(const int & x, const int & y);

	void move(Direction direction);

	void takeDamage(int damage);

	bool entioMoved();
	void resetEntioMoved();
	void resetTurnFatigue();

	

};