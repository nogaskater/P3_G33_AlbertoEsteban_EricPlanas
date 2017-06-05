#pragma once

#include"Renderer.hh"

class Cell
{
private:

	char data;
	enti::Color color;

public:

	Cell();
	Cell(char data, enti::Color color);

	char getData();
	enti::Color getColor();

	void setData(char data);
	void setColor(enti::Color color);

	bool isWalkable();
};