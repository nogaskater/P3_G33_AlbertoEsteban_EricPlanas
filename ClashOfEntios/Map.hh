#pragma once

#include <fstream> 
#include <iostream>
#include <string>

#include "Renderer.hh"

class Map
{
private:

	const int ROWS = 36;
	const int COLUMNS = 74;

	char ** data;

	void load();

	int coloredEntioX, coloredEntioY;

	bool leftPlayerTurn;

public:

	Map();
	
	~Map();

	char getCell(const int & row, const int & column);

	void setCell(const int & row, const int & column, char value);

	void find(char a, int & row, int & column);

	void colorMovingEntio(int _x, int _y);

	void swapPlayer();

	void draw();
};
