#include "Cell.hh"

Cell::Cell()
{

}

Cell::Cell(char data, enti::Color color) : data(data), color(color)
{

}

char Cell::getData()
{
	return data;
}

enti::Color Cell::getColor()
{
	return color;
}

void Cell::setData(char data)
{
	this->data = data;
}

void Cell::setColor(enti::Color color)
{
	this->color = color;
}

bool Cell::isWalkable()
{
	return (data == ':' || data == '.');
}
