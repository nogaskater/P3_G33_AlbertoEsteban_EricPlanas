#include "Entio.hh"

Entio::Entio() : map(* new Map), skin('A'), temp('.'), permaFatigue(0), turnFatigue(0), moved(false)
{
	x = 0;
	y = 0;

	life = 10;
	arrows = 10;
}

Entio::Entio(Map & map, char skin) : map(map), skin(skin), temp('.'), permaFatigue(0), turnFatigue(0), moved(false)
{
	map.find(skin, y, x);

	life = 10;
	arrows = 10;
}


char Entio::getSkin()
{
	return skin;
}

int Entio::getLife()
{
	return life;
}

int Entio::getPermaFatigue()
{
	return permaFatigue;
}

int Entio::getTurnFatigue()
{
	return turnFatigue;
}

int Entio::getX()
{
	return x;
}

int Entio::getY()
{
	return y;
}

char Entio::getTemp()
{
	return temp;
}

int Entio::getArrows()
{
	return arrows;
}

void Entio::addPermaFatigue()
{
	permaFatigue++;
}

void Entio::addTurnFatigue()
{
	turnFatigue++;
}

void Entio::consumeArrow()
{
	arrows--;
}

void Entio::moveTo(const int & x, const int & y)
{
	if (map.getCell(y, x) == ':' || map.getCell(y, x) == '.')
	{
		moved = true;

		addTurnFatigue();

		// Set background cell with background skin

		map.setCell(this->y, this->x, temp);

		// Update position

		this->x = x;
		this->y = y;

		// Temp

		temp = map.getCell(this->y, this->x);

		// Set new cell with player skin

		map.setCell(y, x, skin);
	}
}

void Entio::moveBy(const int & x, const int & y)
{
	moveTo(this->x + x, this->y + y);
}

void Entio::move(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:

		moveBy(0, -1);

		break;

	case Direction::DOWN:

		moveBy(0, 1);

		break;

	case Direction::LEFT:

		moveBy(-1, 0);

		break;

	case Direction::RIGHT:

		moveBy(1, 0);

		break;
	}
}

/*
void Entio::shoot(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:

		

		break;

	case Direction::DOWN:

		

		break;

	case Direction::LEFT:

		

		break;

	case Direction::RIGHT:

		

		break;
	}
}

void Entio::hit(Direction direction)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if (enemies->at(i).getX() == this->x + x && enemies->at(i).getY() == this->y + y)
		{
			enemies->at(i).takeDamage(10);
		}
	}
}
*/

void Entio::takeDamage(int damage)
{
	life -= damage;
}


// This two functions used to register if the entio moved succesfully (not against a wall)
// If true, Player::action() will get called.
bool Entio::entioMoved()
{
	return moved;
}

void Entio::resetEntioMoved()
{
	moved = false;
}

int Entio::getTotalFatigue()
{
	return permaFatigue + turnFatigue;
}

void Entio::resetTurnFatigue()
{
	turnFatigue = 0;
}

