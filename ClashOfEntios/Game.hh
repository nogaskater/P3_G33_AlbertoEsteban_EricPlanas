#pragma once

#include <vector>

#include "Input.inl.hh"
#include "Map.hh"
#include "Player.hh"

class Game
{
private:

	std::vector<char> skinsLeft = { 'A', 'B', 'C', 'D', 'E', 'F' };
	std::vector<char> skinsRight = { '1', '2', '3', '4', '5', '6' };

	Map map;

	Player * leftPlayer;
	Player * rightPlayer;
	Player * currentPlayer;

	int turnCounter;
	bool leftPlayerWon;
	bool winnerMessageBool;

public:

	Game();

	void start();
	void update();
};