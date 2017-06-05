#include "Game.hh"

Game::Game()
{
	leftPlayer = new Player(map, rightPlayer, skinsLeft);
	rightPlayer = new Player(map, leftPlayer, skinsRight);

	currentPlayer = leftPlayer;

	turnCounter = 0;
	leftPlayerWon = false;
	winnerMessageBool = true;
}

void Game::start()
{
	enti::cout << enti::Color::YELLOW << "BATTLE OF ENTIOS" << enti::endl;
	enti::cout << enti::Color::WHITE << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each player has 6 entios." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Use WASD to move each entio." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Use Z to undo a movement." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each entio has 2 weapons: 1 sword and 1 bow." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Press SPACEBAR to use a weapon." << enti::endl;
	enti::cout << enti::Color::WHITE << "- The sword can instantly kill an enemy if it is placed in a cell next door." << enti::endl;
	enti::cout << enti::Color::WHITE << "- The bow can damage an enemy within a maximum distance of 10 cells." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each character has only 10 arrows." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each turn the less fatigued entio will play first." << enti::endl;
	enti::cout << enti::Color::WHITE << "- To play with the next entio press ENTER." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each player can do 10 of these actions per turn." << enti::endl;
	enti::cout << enti::Color::WHITE << enti::endl;
	enti::cout << enti::Color::LIGHTMAGENTA << "Press any key to begin the game!" << enti::cend;

	enti::InputKey key0;

	do 
	{
		key0 = enti::getInputKey();
	} 
	while (key0 == enti::InputKey::NONE);

	//system("cls");

	map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

	map.draw();

	currentPlayer->drawStats();

	enti::cout << enti::cend;

}

void Game::update()
{
	bool gameLoop = true;

	while (gameLoop)
	{

		// Main key
		enti::InputKey key0;

		do
		{
			key0 = enti::getInputKey();
		} 
		while (key0 == enti::InputKey::NONE);

		// Main switch

		if (!currentPlayer->isAttacking())
		{
			switch (key0)
			{
			case enti::InputKey::W:

				currentPlayer->move(Direction::UP);

				break;

			case enti::InputKey::S:

				currentPlayer->move(Direction::DOWN);

				break;

			case enti::InputKey::A:

				currentPlayer->move(Direction::LEFT);

				break;

			case enti::InputKey::D:

				currentPlayer->move(Direction::RIGHT);

				break;

			case enti::InputKey::ENTER:

				currentPlayer->change();

				break;

			case enti::InputKey::SPACEBAR:

				currentPlayer->attackMenu();

				break;

			case enti::InputKey::z:

				currentPlayer->useControlZ();

				break;

			case enti::InputKey::x:

				currentPlayer->useControlX();

				break;

			case enti::InputKey::ESC:

				gameLoop = false;

				winnerMessageBool = false;

				break;
			}
		}
		else
		{

			if (key0 == enti::InputKey::NUM1)
			{
				map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

				map.draw();

				currentPlayer->drawStats();

				enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
				enti::cout << enti::endl;
				enti::cout << enti::Color::DARKGRAY << "               Enter the " << enti::Color::LIGHTMAGENTA << "direction" << enti::Color::DARKGRAY << " to attack with the SWORD:" << enti::endl;
				enti::cout << enti::endl;
				enti::cout << enti::Color::LIGHTMAGENTA << "                              1 - " << enti::Color::LIGHTGRAY << "UP" << enti::endl;
				enti::cout << enti::endl;
				enti::cout << enti::Color::LIGHTMAGENTA << "                  2 - " << enti::Color::LIGHTGRAY << "LEFT" << enti::Color::LIGHTMAGENTA << "               4 - " << enti::Color::LIGHTGRAY << "RIGHT" << enti::endl;
				enti::cout << enti::endl;
				enti::cout << enti::Color::LIGHTMAGENTA << "                             3 - " << enti::Color::LIGHTGRAY << "DOWN" << enti::endl;

				enti::cout << enti::cend;
				
				enti::InputKey directionKey;

				do
				{

					directionKey = enti::getInputKey();
				} 
				while (directionKey == enti::InputKey::NONE);

				switch (directionKey)
				{

				case enti::InputKey::NUM1:
					currentPlayer->hit(Direction::UP);
					break;
				case enti::InputKey::NUM2:
					currentPlayer->hit(Direction::LEFT);
					break;
				case enti::InputKey::NUM3:
					currentPlayer->hit(Direction::DOWN);
					break;
				case enti::InputKey::NUM4:
					currentPlayer->hit(Direction::RIGHT);
					break;
				}
			}
			else if (key0 == enti::InputKey::NUM2)
			{
				if (currentPlayer->isOutOfAmmo())
				{
					currentPlayer->attackMenu();
				}
				else
				{
					map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

					map.draw();

					currentPlayer->drawStats();

					enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
					enti::cout << enti::endl;
					enti::cout << enti::Color::DARKGRAY << "               Enter the " << enti::Color::LIGHTMAGENTA << "direction" << enti::Color::DARKGRAY << " to attack with the BOW:" << enti::endl;
					enti::cout << enti::endl;
					enti::cout << enti::Color::LIGHTMAGENTA << "                              1 - " << enti::Color::LIGHTGRAY << "UP" << enti::endl;
					enti::cout << enti::endl;
					enti::cout << enti::Color::LIGHTMAGENTA << "                  2 - " << enti::Color::LIGHTGRAY << "LEFT" << enti::Color::LIGHTMAGENTA << "               4 - " << enti::Color::LIGHTGRAY << "RIGHT" << enti::endl;
					enti::cout << enti::endl;
					enti::cout << enti::Color::LIGHTMAGENTA << "                             3 - " << enti::Color::LIGHTGRAY << "DOWN" << enti::endl;

					enti::cout << enti::cend;

					enti::InputKey directionKey;

					do
					{
						directionKey = enti::getInputKey();
					} while (directionKey == enti::InputKey::NONE);

					switch (directionKey)
					{

					case enti::InputKey::NUM1:
						currentPlayer->shoot(Direction::UP);
						break;
					case enti::InputKey::NUM2:
						currentPlayer->shoot(Direction::LEFT);
						break;
					case enti::InputKey::NUM3:
						currentPlayer->shoot(Direction::DOWN);
						break;
					case enti::InputKey::NUM4:
						currentPlayer->shoot(Direction::RIGHT);
						break;
					}
				}
			}
			else
			{
				currentPlayer->attackMenu();
			}
		}



		// Draw

		//system("cls");

		if (currentPlayer->isTurn())
		{
			map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

			map.draw();

			currentPlayer->drawStats();

			enti::cout << enti::cend;
		}


		// Change turn
		if (!currentPlayer->isTurn())
		{
			map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

			map.draw();

			//currentPlayer->

			currentPlayer->drawStats();

			enti::cout << enti::Color::WHITE << enti::endl;
			enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
			enti::cout << enti::Color::WHITE << enti::endl;
			enti::cout << enti::Color::DARKGRAY << "                     Press " << enti::Color::LIGHTMAGENTA <<"ENTER" << enti::Color::DARKGRAY << " to end your turn!" << enti::endl;

			enti::cout << enti::cend;
			do
			{
				key0 = enti::getInputKey();
			} 
			while (key0 != enti::InputKey::ENTER);

			currentPlayer = (currentPlayer == leftPlayer) ? rightPlayer : leftPlayer;

			turnCounter++;

			currentPlayer->reset();
			currentPlayer->lowFatigue();

			map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

			map.draw();

			currentPlayer->drawStats();

			enti::cout << enti::cend;

		}

		if (leftPlayer->getEntiosSize() == 0)
		{
			gameLoop = false;
			leftPlayerWon = false;
		}
		if (rightPlayer->getEntiosSize() == 0)
		{
			gameLoop = false;
			leftPlayerWon = true;
		}
	}

	map.colorMovingEntio(currentPlayer->getCurrentEntioX(), currentPlayer->getCurrentEntioY());

	map.draw();

	currentPlayer->drawStats();

	if (winnerMessageBool)
	{
		if (leftPlayerWon)
		{
			enti::cout << enti::endl;
			enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
			enti::cout << enti::endl;
			enti::cout << enti::endl;
			enti::cout << enti::Color::LIGHTGREEN << "                    Left Player WON" << enti::Color::LIGHTGRAY << " after " << enti::Color::YELLOW << turnCounter << enti::Color::LIGHTGRAY << " turns!" << enti::endl;
		}
		else
		{
			enti::cout << enti::endl;
			enti::cout << enti::Color::WHITE << "                 _____________________________________" << enti::endl;
			enti::cout << enti::endl;
			enti::cout << enti::endl;		
			enti::cout << enti::Color::LIGHTGREEN << "                    Right Player WON" << enti::Color::LIGHTGRAY << " after " << enti::Color::YELLOW << turnCounter << enti::Color::LIGHTGRAY << " turns!" << enti::endl;

		}

		enti::cout << enti::endl;
		enti::cout << enti::endl;
		enti::cout << enti::Color::LIGHTGRAY << "                     Press " << enti::Color::LIGHTMAGENTA << "ENTER" << enti::Color::LIGHTGRAY << " or " << enti::Color::LIGHTMAGENTA << "ESC " << enti::Color::LIGHTGRAY << "to exit..." << enti::endl;

		enti::cout << enti::cend;

		enti::InputKey exitKey;
		do
		{
			exitKey = enti::getInputKey();

		} while (exitKey != enti::InputKey::ENTER && exitKey != enti::InputKey::ESC);
	}
}
