#include "Map.hh"
#include "Renderer.hh"

void Map::load()
{
	std::ifstream file;

	file.open("default.cfg");

	char line[74];

	int i = 0;

	while (file.getline(line, COLUMNS))
	{
		int j = 0;

		while (j < COLUMNS)
		{
			data[i][j] = line[j];

			j++;
		}

		i++;
	}

	file.close();
}

Map::Map()
{
	data = new char*[ROWS];

	for (int i = 0; i < ROWS; i++)
	{
		data[i] = new char[COLUMNS];
	}

	load();

	coloredEntioX = 0;
	coloredEntioY = 0;

	leftPlayerTurn = true;
}

Map::~Map()
{
	for (int i = 0; i < ROWS; i++)
	{
		delete data[i];
	}
	delete data;
	data = nullptr;
		
}

char Map::getCell(const int & row, const int & column)
{
	return data[row][column];
}

void Map::setCell(const int & row, const int & column, char value)
{
	data[row][column] = value;
}

void Map::find(char a, int & row, int & column)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (data[i][j] == a)
			{
				row = i; 
				column = j;

				return;
			}
		}
	}
}

void Map::colorMovingEntio(int _x, int _y)
{
	coloredEntioX = _x;
	coloredEntioY = _y;
}

void Map::swapPlayer()
{
	bool switched = false;
	if (leftPlayerTurn && !switched)
	{
		leftPlayerTurn = false;
		switched = true;
	}
	else
	{
		leftPlayerTurn = true;
	}
}

void Map::draw()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			enti::Color color;

			switch (data[i][j])
			{
			case 'X':

				color = enti::Color::RED;

				break;

			case 'O':

				color = enti::Color::CYAN;

				break;

			case ':':

				color = enti::Color::GREEN;

				break;

			case '.':

				color = enti::Color::DARKGRAY;

				break;

			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':

				if (leftPlayerTurn)
					color = enti::Color::YELLOW;
				else
					color = enti::Color::LIGHTGRAY;

				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':

				if (leftPlayerTurn)
					color = enti::Color::LIGHTGRAY;
				else
					color = enti::Color::YELLOW;

				break;
			}

			//enti::cout << color << data[i][j];

			if (i == coloredEntioY && j == coloredEntioX)
			{
				enti::cout << enti::Color::LIGHTMAGENTA << data[i][j];
			}
			else
			{
				enti::cout << color << data[i][j];

			}
		}
		enti::cout << enti::endl;

	}

	enti::cout << enti::endl;

	//enti::cout << enti::cend;
}
