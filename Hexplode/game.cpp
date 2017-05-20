#include "game.h"

//initializes the window, players, and hexagon array
Game::Game() :mWindow(sf::VideoMode(600, 600), "Hexplode"), mPlayer1(), mPlayer2(), mHexBoard()
{
	mPlayer1.setPlayerColor(sf::Color::Red);//set player color
	mPlayer2.setPlayerColor(sf::Color::Blue);//set player color
	mWindow.setVerticalSyncEnabled(true);//set refresh rate to same as monitor's maximum
	mPlayer1.setTurn(true);//make it player 1's turn
	mPlayer1.setPlayerColor(sf::Color::Red);//set p1 color to red
	mPlayer2.setPlayerColor(sf::Color::Blue);//set p3 color to blue
	mPlayerColor = mPlayer1.getPlayerColor();//set game color to p1
	mTexture.loadFromFile("mainMenu.png");//set to menu
	mBackground.setTexture(mTexture);//set mBackground to menu
	initializeBoard();//does what it says
	initializeChargeLocation();
}
Game::~Game()
{
	//does nothing
}
//drives the game
void Game::run()
{
	//sets the charge sound
	mChargeSoundBuffer.loadFromFile("chargeSound.ogg");
	mChargeSound.setBuffer(mChargeSoundBuffer);
	//uncomment / comment out the music files to play different menu music
	//mBuffer.loadFromFile("musicGRIZ-Live.ogg");
	//mBuffer.loadFromFile("musicArcade.ogg");//loads the fastest, smallest file
	mBuffer.loadFromFile("musicGRIZ.ogg");
	mGameMusic.setBuffer(mBuffer);
	mGameMusic.setVolume(90);//lower volume so SF aren't drowned out
	mGameMusic.play();

	while (mWindow.isOpen())
	{
		if (mGameDisplay == true)//play game
		{
			if (mPlayer1.getTurn() == true)//if player 1 turn
			{
				mTexture.loadFromFile("player1Background.png");
			}
			else//player 2's turn
			{
				mTexture.loadFromFile("player2Background.png");
			}
			processEvents();//handle user input
			updatePieces();
			render();//draw shapes to window and show window
		}//end game render

		else//show menu
		{
			processMenuEvents();
			renderMenu();
		}

	}//end window loop
}

void Game::processMenuEvents(void)
{

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}

		else if (event.type == sf::Keyboard::Escape)//escape has been pressed
		{
			mWindow.close();
		}
		//run game
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 105 && event.mouseButton.x < 495 && event.mouseButton.y > 280 && event.mouseButton.y < 340)
		{
			mGameMusic.stop();
			mGameDisplay = true;
			mBackground.setTexture(mTexture);
		}
		//display game rules
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 105 && event.mouseButton.x < 495 && event.mouseButton.y > 410 && event.mouseButton.y < 470)
		{
			mTexture.loadFromFile("gameRules.png");
			mBackground.setTexture(mTexture);//display rules
		}
		//return to menu
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 20 && event.mouseButton.x < 270 && event.mouseButton.y > 535 && event.mouseButton.y < 580)
		{
			mTexture.loadFromFile("mainMenu.png");//display menu
			mBackground.setTexture(mTexture);
			mGameDisplay = false;
		}
	}
}
void Game::processEvents(void)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{

		if (event.type == sf::Event::Closed)//if clicked closed
		{
			mWindow.close();
		}

		else if (event.key.code == sf::Keyboard::Escape)//escape has been pressed
		{
			mWindow.close();
		}

		//return to main menu
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 20 && event.mouseButton.x < 270 && event.mouseButton.y > 535 && event.mouseButton.y < 580)
		{
			mTexture.loadFromFile("mainMenu.png");
			mBackground.setTexture(mTexture);//display menu
			mGameDisplay = false;
			mGameMusic.play();
		}

		//hexagon selection events:
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 92 && event.mouseButton.x < 161
			&& event.mouseButton.y > 317 && event.mouseButton.y < 376)
		{
			//if player color is the same as the board or the space is vacant
			if ((mPlayerColor == mHexBoard[0].getColor()) || (mHexBoard[0].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(0);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 151 && event.mouseButton.x < 218
			&& event.mouseButton.y > 285 && event.mouseButton.y < 343)
		{
			if ((mPlayerColor == mHexBoard[1].getColor()) || (mHexBoard[1].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(1);
			}

		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 156 && event.mouseButton.x < 218
			&& event.mouseButton.y > 350 && event.mouseButton.y < 407)
		{
			if ((mPlayerColor == mHexBoard[2].getColor()) || (mHexBoard[2].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(2);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 209 && event.mouseButton.x < 277
			&& event.mouseButton.y > 254 && event.mouseButton.y < 309)
		{
			if ((mPlayerColor == mHexBoard[3].getColor()) || (mHexBoard[3].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(3);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 209 && event.mouseButton.x < 277
			&& event.mouseButton.y > 320 && event.mouseButton.y < 376)
		{
			if ((mPlayerColor == mHexBoard[4].getColor()) || (mHexBoard[4].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(4);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 209 && event.mouseButton.x < 277
			&& event.mouseButton.y > 384 && event.mouseButton.y < 444)
		{
			if ((mPlayerColor == mHexBoard[5].getColor()) || (mHexBoard[5].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(5);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 266 && event.mouseButton.x < 334
			&& event.mouseButton.y > 215 && event.mouseButton.y < 277)
		{
			if ((mPlayerColor == mHexBoard[6].getColor()) || (mHexBoard[6].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(6);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 266 && event.mouseButton.x < 334
			&& event.mouseButton.y > 284 && event.mouseButton.y < 344)
		{
			if ((mPlayerColor == mHexBoard[7].getColor()) || (mHexBoard[7].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(7);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 266 && event.mouseButton.x < 334
			&& event.mouseButton.y > 350 && event.mouseButton.y < 411)
		{
			if ((mPlayerColor == mHexBoard[8].getColor()) || (mHexBoard[8].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(8);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 266 && event.mouseButton.x < 334
			&& event.mouseButton.y > 416 && event.mouseButton.y < 476)
		{
			if ((mPlayerColor == mHexBoard[9].getColor()) || (mHexBoard[9].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(9);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 322 && event.mouseButton.x < 388
			&& event.mouseButton.y > 250 && event.mouseButton.y < 309)
		{
			if ((mPlayerColor == mHexBoard[10].getColor()) || (mHexBoard[10].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(10);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 322 && event.mouseButton.x < 388
			&& event.mouseButton.y > 319 && event.mouseButton.y < 377)
		{
			if ((mPlayerColor == mHexBoard[11].getColor()) || (mHexBoard[11].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(11);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 322 && event.mouseButton.x < 388
			&& event.mouseButton.y > 386 && event.mouseButton.y < 443)
		{
			if ((mPlayerColor == mHexBoard[12].getColor()) || (mHexBoard[12].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(12);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 380 && event.mouseButton.x < 447
			&& event.mouseButton.y > 285 && event.mouseButton.y < 341)
		{
			if ((mPlayerColor == mHexBoard[13].getColor()) || (mHexBoard[13].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(13);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 380 && event.mouseButton.x < 447
			&& event.mouseButton.y > 353 && event.mouseButton.y < 411)
		{
			if ((mPlayerColor == mHexBoard[14].getColor()) || (mHexBoard[14].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(14);
			}
		}

		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x > 439 && event.mouseButton.x < 505
			&& event.mouseButton.y > 317 && event.mouseButton.y < 407)
		{
			if ((mPlayerColor == mHexBoard[15].getColor()) || (mHexBoard[15].getColor() == sf::Color(28, 28, 28)))
			{
				updateEvents(15);
			}
		}
	}
}

void Game::renderMenu()
{
	mWindow.draw(mBackground);
	mWindow.display();
}
void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	//draw the board
	for (int i = 0; i < 16; i++)
	{
		mWindow.draw(mHexBoard[i].getShape());
		for (int g = 0; g < 6; g++)//draw charges
		{
			if (mHexBoard[i].getCharge(g).getFillColor() != sf::Color(28, 28, 28))
			{
				mWindow.draw(mHexBoard[i].getCharge(g));
			}
		}
	}

	mWindow.display();//show all that's been drawn
}

void Game::initializeBoard()//sets the positions and base charges for all hexagons
{
	mHexBoard[0].setUpperR(&(mHexBoard[1]));
	mHexBoard[0].setLowerR(&(mHexBoard[2]));
	mHexBoard[0].setPosition(115, 300);
	mHexBoard[0].setBase(4);

	mHexBoard[1].setLowerL(&(mHexBoard[0]));
	mHexBoard[1].setBottom(&(mHexBoard[2]));
	mHexBoard[1].setLowerR(&(mHexBoard[4]));
	mHexBoard[1].setUpperR(&(mHexBoard[3]));
	mHexBoard[1].setBase(2);
	mHexBoard[1].setPosition(173, 267);

	mHexBoard[2].setTop(&(mHexBoard[1]));
	mHexBoard[2].setUpperL(&(mHexBoard[0]));
	mHexBoard[2].setLowerR(&(mHexBoard[5]));
	mHexBoard[2].setUpperR(&(mHexBoard[4]));
	mHexBoard[2].setBase(2);
	mHexBoard[2].setPosition(173, 333);

	mHexBoard[3].setLowerL(&(mHexBoard[1]));
	mHexBoard[3].setBottom(&(mHexBoard[4]));
	mHexBoard[3].setLowerR(&(mHexBoard[7]));
	mHexBoard[3].setUpperR(&(mHexBoard[6]));
	mHexBoard[3].setBase(2);
	mHexBoard[3].setPosition(230, 234);

	mHexBoard[4].setTop(&(mHexBoard[3]));
	mHexBoard[4].setUpperL(&(mHexBoard[1]));
	mHexBoard[4].setLowerL(&(mHexBoard[2]));
	mHexBoard[4].setBottom(&(mHexBoard[5]));
	mHexBoard[4].setLowerR(&(mHexBoard[8]));
	mHexBoard[4].setUpperR(&(mHexBoard[7]));
	mHexBoard[4].setPosition(230, 300);

	mHexBoard[5].setTop(&(mHexBoard[4]));
	mHexBoard[5].setUpperL(&(mHexBoard[2]));
	mHexBoard[5].setLowerR(&(mHexBoard[9]));
	mHexBoard[5].setUpperR(&(mHexBoard[8]));
	mHexBoard[5].setBase(2);
	mHexBoard[5].setPosition(230, 366);

	mHexBoard[6].setLowerL(&(mHexBoard[3]));
	mHexBoard[6].setBottom(&(mHexBoard[7]));
	mHexBoard[6].setLowerR(&(mHexBoard[10]));
	mHexBoard[6].setBase(3);
	mHexBoard[6].setPosition(287, 200);

	mHexBoard[7].setTop(&(mHexBoard[6]));
	mHexBoard[7].setUpperL(&(mHexBoard[3]));
	mHexBoard[7].setLowerL(&(mHexBoard[4]));
	mHexBoard[7].setBottom(&(mHexBoard[8]));
	mHexBoard[7].setLowerR(&(mHexBoard[11]));
	mHexBoard[7].setUpperR(&(mHexBoard[10]));
	mHexBoard[7].setPosition(287, 266);

	mHexBoard[8].setTop(&(mHexBoard[7]));
	mHexBoard[8].setUpperL(&(mHexBoard[4]));
	mHexBoard[8].setLowerL(&(mHexBoard[5]));
	mHexBoard[8].setBottom(&(mHexBoard[9]));
	mHexBoard[8].setLowerR(&(mHexBoard[12]));
	mHexBoard[8].setUpperR(&(mHexBoard[11]));
	mHexBoard[8].setPosition(287, 333);

	mHexBoard[9].setTop(&(mHexBoard[5]));
	mHexBoard[9].setUpperL(&(mHexBoard[8]));
	mHexBoard[9].setUpperR(&(mHexBoard[12]));
	mHexBoard[9].setBase(3);
	mHexBoard[9].setPosition(287, 398);

	mHexBoard[10].setUpperL(&(mHexBoard[6]));
	mHexBoard[10].setLowerL(&(mHexBoard[7]));
	mHexBoard[10].setBottom(&(mHexBoard[11]));
	mHexBoard[10].setLowerR(&(mHexBoard[13]));
	mHexBoard[10].setBase(2);
	mHexBoard[10].setPosition(344, 233);

	mHexBoard[11].setTop(&(mHexBoard[10]));
	mHexBoard[11].setUpperL(&(mHexBoard[7]));
	mHexBoard[11].setLowerL(&(mHexBoard[8]));
	mHexBoard[11].setBottom(&(mHexBoard[12]));
	mHexBoard[11].setLowerR(&(mHexBoard[14]));
	mHexBoard[11].setUpperR(&(mHexBoard[13]));
	mHexBoard[11].setPosition(344, 300);

	mHexBoard[12].setTop(&(mHexBoard[11]));
	mHexBoard[12].setUpperL(&(mHexBoard[8]));
	mHexBoard[12].setLowerL(&(mHexBoard[9]));
	mHexBoard[12].setUpperR(&(mHexBoard[14]));
	mHexBoard[12].setBase(2);
	mHexBoard[12].setPosition(344, 366);

	mHexBoard[13].setUpperL(&(mHexBoard[10]));
	mHexBoard[13].setLowerL(&(mHexBoard[11]));
	mHexBoard[13].setBottom(&(mHexBoard[14]));
	mHexBoard[13].setLowerR(&(mHexBoard[15]));
	mHexBoard[13].setBase(2);
	mHexBoard[13].setPosition(402, 266);

	mHexBoard[14].setTop(&(mHexBoard[13]));
	mHexBoard[14].setUpperL(&(mHexBoard[11]));
	mHexBoard[14].setLowerL(&(mHexBoard[12]));
	mHexBoard[14].setUpperR(&(mHexBoard[15]));
	mHexBoard[14].setBase(2);
	mHexBoard[14].setPosition(402, 333);

	mHexBoard[15].setUpperL(&(mHexBoard[13]));
	mHexBoard[15].setLowerL(&(mHexBoard[14]));
	mHexBoard[15].setBase(4);
	mHexBoard[15].setPosition(459, 300);

}
void Game::initializeChargeLocation(void)//places all the charges
{


	//Charges in the first hexagon
	//place in array and new color
	mHexBoard[0].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[0].setChargePosition(0, 120, 328);

	mHexBoard[0].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[0].setChargePosition(1, 120, 348);

	//Charges in the second hexagon
	mHexBoard[1].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[1].setChargePosition(0, 178, 295);

	mHexBoard[1].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[1].setChargePosition(1, 163, 308);

	mHexBoard[1].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[1].setChargePosition(2, 178, 320);

	mHexBoard[1].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[1].setChargePosition(3, 192, 308);

	//Charges in the third hexagon
	mHexBoard[2].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[2].setChargePosition(0, 178, 360);

	mHexBoard[2].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[2].setChargePosition(1, 163, 370);

	mHexBoard[2].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[2].setChargePosition(2, 178, 381);

	mHexBoard[2].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[2].setChargePosition(3, 193, 370);

	//Charges in the 4th hex
	mHexBoard[3].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[3].setChargePosition(0, 238, 260);

	mHexBoard[3].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[3].setChargePosition(1, 223, 273);

	mHexBoard[3].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[3].setChargePosition(2, 238, 287);

	mHexBoard[3].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[3].setChargePosition(3, 253, 272);

	//Charges in the 5th hexagon
	mHexBoard[4].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(0, 238, 318);

	mHexBoard[4].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(1, 226, 328);

	mHexBoard[4].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(2, 226, 345);

	mHexBoard[4].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(3, 238, 355);

	mHexBoard[4].setCharge(4, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(4, 253, 345);

	mHexBoard[4].setCharge(5, sf::Color(68, 68, 68));
	mHexBoard[4].setChargePosition(5, 253, 328);

	//Charges in the 6th hex
	mHexBoard[5].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[5].setChargePosition(0, 238, 390);

	mHexBoard[5].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[5].setChargePosition(1, 222, 403);

	mHexBoard[5].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[5].setChargePosition(2, 238, 415);

	mHexBoard[5].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[5].setChargePosition(3, 254, 403);

	//Charges in the 7th hex
	mHexBoard[6].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[6].setChargePosition(0, 293, 223);

	mHexBoard[6].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[6].setChargePosition(1, 280, 239);

	mHexBoard[6].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[6].setChargePosition(2, 309, 239);

	//Charges in the 8th hex
	mHexBoard[7].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(0, 295, 286);

	mHexBoard[7].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(1, 282, 296);

	mHexBoard[7].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(2, 282, 312);

	mHexBoard[7].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(3, 295, 323);

	mHexBoard[7].setCharge(4, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(4, 310, 312);

	mHexBoard[7].setCharge(5, sf::Color(68, 68, 68));
	mHexBoard[7].setChargePosition(5, 310, 296);

	//Charges in the 9th hex
	mHexBoard[8].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(0, 295, 353);

	mHexBoard[8].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(1, 282, 363);

	mHexBoard[8].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(2, 282, 379);

	mHexBoard[8].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(3, 295, 390);

	mHexBoard[8].setCharge(4, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(4, 310, 379);

	mHexBoard[8].setCharge(5, sf::Color(68, 68, 68));
	mHexBoard[8].setChargePosition(5, 310, 363);

	//Charges in the 10th hex
	mHexBoard[9].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[9].setChargePosition(0, 295, 420);

	mHexBoard[9].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[9].setChargePosition(1, 282, 437);

	mHexBoard[9].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[9].setChargePosition(2, 309, 437);

	//Charges in the 11th hex
	mHexBoard[10].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[10].setChargePosition(0, 353, 260);

	mHexBoard[10].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[10].setChargePosition(1, 338, 273);

	mHexBoard[10].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[10].setChargePosition(2, 353, 287);

	mHexBoard[10].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[10].setChargePosition(3, 368, 273);

	//Charges in the 12th hex
	mHexBoard[11].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(0, 353, 318);

	mHexBoard[11].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(1, 341, 328);

	mHexBoard[11].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(2, 341, 345);

	mHexBoard[11].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(3, 353, 355);

	mHexBoard[11].setCharge(4, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(4, 368, 345);

	mHexBoard[11].setCharge(5, sf::Color(68, 68, 68));
	mHexBoard[11].setChargePosition(5, 368, 328);

	//Charges in the 13th hex
	mHexBoard[12].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[12].setChargePosition(0, 353, 390);

	mHexBoard[12].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[12].setChargePosition(1, 337, 403);

	mHexBoard[12].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[12].setChargePosition(2, 353, 415);

	mHexBoard[12].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[12].setChargePosition(3, 369, 403);

	//Charges in the 14th hex
	mHexBoard[13].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[13].setChargePosition(0, 409, 296);

	mHexBoard[13].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[13].setChargePosition(1, 394, 308);

	mHexBoard[13].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[13].setChargePosition(2, 409, 320);

	mHexBoard[13].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[13].setChargePosition(3, 424, 308);

	//Charges in the 15th hex
	mHexBoard[14].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[14].setChargePosition(0, 409, 360);

	mHexBoard[14].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[14].setChargePosition(1, 394, 370);

	mHexBoard[14].setCharge(2, sf::Color(68, 68, 68));
	mHexBoard[14].setChargePosition(2, 409, 381);

	mHexBoard[14].setCharge(3, sf::Color(68, 68, 68));
	mHexBoard[14].setChargePosition(3, 424, 370);

	//Charges in the 16th hex
	mHexBoard[15].setCharge(0, sf::Color(68, 68, 68));
	mHexBoard[15].setChargePosition(0, 466, 335);

	mHexBoard[15].setCharge(1, sf::Color(68, 68, 68));
	mHexBoard[15].setChargePosition(1, 466, 355);
}

void Game::updateEvents(int i)
{
	if (mPlayerColor == mPlayer1.getPlayerColor())
	{
		mPlayer1.setNumTurns(1);//add one to player turn (used for highscores)
	}
	else
	{
		mPlayer2.setNumTurns(1);
	}
	mHexBoard[i].setFillColor(mPlayerColor);//change current hexagon to player's color
	mHexBoard[i].plusOneExpl();//add one to each hexagon
	mPlayChargeSound(i);
	mHexBoard[i].chargeHex(&mHexBoard[i]);//display the appropriate charge
	updateBoard();//go through board and update hexagons until there are no more explosions
	updateBoard();//ensure all spaces have been exploded
	changeTurns();//switches user turns
}
void Game::updatePieces()
{
		for (int i = 0; i < 16; i++)
		{
			//if the hexagon is ready to explode:
			if (mHexBoard[i].getBaseClick() + mHexBoard[i].getExplosionCount() > 5)
			{
				mChargeSound.stop();
				mHexBoard[i].setFillColor(28, 28, 28);//reset to board color
				mHexBoard[i].setExplosionCount(0);//reset explosion count
				mHexBoard[i].updateHex(mPlayerColor);//explode hexagon
				explosionwrap(0, i);
				for (int g = 0; g < 6; g++)//reset charges
				{
					//if the current color is charge color, reset it to the default charge
					if (mHexBoard[i].getCharge(g).getFillColor() == sf::Color(255, 255, 21))
					{
						mHexBoard[i].setCharge(g, sf::Color(64, 64, 64));
					}
				}
				i = 0;
			}
		}
}
void Game::updateBoard()//checks if hexagons on the board are going to explode and if a player has won
{
	//keeps track of hexagons occupied:
	int player1 = 0;
	int player2 = 0;
	//check each hexagon to see if it needs to be updated:
		for (int i = 0; i < 16; i++)
		{
			//if the hexagon is ready to explode:
			if (mHexBoard[i].getBaseClick() + mHexBoard[i].getExplosionCount() > 5)
			{
				mChargeSound.stop();
				mHexBoard[i].setFillColor(28, 28, 28);//reset to board color
				mHexBoard[i].setExplosionCount(0);//reset explosion count
				mHexBoard[i].updateHex(mPlayerColor);//explode hexagon
				explosionwrap(0, i);
				for (int g = 0; g < 6; g++)//reset charges
				{
					//if the current color is charge color, reset it to the default charge
					if (mHexBoard[i].getCharge(g).getFillColor() == sf::Color(255, 255, 21))
					{
						mHexBoard[i].setCharge(g, sf::Color(64, 64, 64));
					}
				}
				i = 0;
				player1 = 0;//reset hexagon count
				player2 = 0;

			}
			//if occupied hexagon is player 1's
			if (mHexBoard[i].getColor() == mPlayer1.getPlayerColor())
			{
				player1++;
			}
			//if occupied hexagon is player 2's
			if (mHexBoard[i].getColor() == mPlayer2.getPlayerColor())
			{
				player2++;
			}
		}

		//if more than one turn per player has passed:
		if ((mPlayer2.getNumTurns() != 0) && (mPlayer1.getNumTurns() != 0))
		{

			//player 2 wins
			if (player1 == 0)
			{
				mGameDisplay = false;//stop the game
				resetBoard();//resets the hexagons
				mTexture.loadFromFile("winPlayer2.png");
				mBuffer.loadFromFile("winningSong.ogg");
				//mBuffer.loadFromFile("musicGRIZ-Live.ogg");
				mGameMusic.setBuffer(mBuffer);
				mGameMusic.setVolume(100);//crank it up for the victory
				mGameMusic.play();
			}
			//player 1 wins
			if (player2 == 0)
			{
				mGameDisplay = false;
				resetBoard();//resets the hexagons
				mTexture.loadFromFile("winPlayer1.png");
				mBuffer.loadFromFile("winningSong.ogg");
				mGameMusic.setBuffer(mBuffer);
				mGameMusic.setVolume(100);//crank it up for the victory
				mGameMusic.play();
			}
		}//end game over check
}

void Game::mPlayChargeSound(int i)
{
	int volume = mHexBoard[i].getBaseClick() + mHexBoard[i].getExplosionCount();
	if (volume == 1)
	{
		mChargeSound.setPitch(1);
	}
	else if (volume == 2)
	{
		mChargeSound.setPitch(1.25);
	}
	else if (volume == 3)
	{
		mChargeSound.setPitch(1.50);
	}
	else if (volume == 4)
	{
		mChargeSound.setPitch(1.75);
	}
	else if (volume == 5)
	{
		mChargeSound.setPitch(2);
	}
	mChargeSound.play();
}
void Game::explosionwrap(int iterator, int hexagonNum)//recursively steps through explosions
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile("explosionsound.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	explosion(iterator, hexagonNum, sound);
	sound.play();
}
void Game::explosion(int iterator, int hexagonNum, sf::Sound sound)//renders explosion and plays explosion sound
{

	float x, y = 0;

	switch (hexagonNum)
	{
	case 0:
		x = 78;
		y = 298;
		break;
	case 1:
		x = 137;//153
		y = 265;//280
		break;
	case 2:
		x = 137;
		y = 330;
		break;
	case 3:
		x = 197;
		y = 233;
		break;
	case 4:
		x = 197;
		y = 298;
		break;
	case 5:
		x = 197;
		y = 365;
		break;
	case 6:
		x = 251;
		y = 200;
		break;
	case 7:
		x = 251;
		y = 265;
		break;
	case 8:
		x = 251;
		y = 330;
		break;
	case 9:
		x = 251;
		y = 397;
		break;
	case 10:
		x = 309;
		y = 235;
		break;
	case 11:
		x = 309;
		y = 298;
		break;
	case 12:
		x = 309;
		y = 365;
		break;
	case 13:
		x = 367;
		y = 264;
		break;
	case 14:
		x = 366;
		y = 330;
		break;
	case 15:
		x = 424;
		y = 297;
		break;
	}
	mWindow.clear();
	render();
	sf::Sprite Explosion;
	sf::Texture texture;
	texture.loadFromFile("explosionsprite.png");
	sf::IntRect subRect;
	Explosion.setTexture(texture);

	switch (iterator)
	{
	case 0:
		subRect.left = 0;
		subRect.top = 0;
		break;
	case 1:
		subRect.left = 64;
		subRect.top = 0;
		break;
	case 2:
		subRect.left = 128;
		subRect.top = 0;
		break;
	case 3:
		subRect.left = 192;
		subRect.top = 0;
		break;
	case 4:
		subRect.left = 256;
		subRect.top = 0;
		break;
	case 5:
		subRect.left = 64;
		subRect.top = 0;
		break;
	case 6:
		subRect.left = 64;
		subRect.top = 64;
		break;
	case 7:
		subRect.left = 64;
		subRect.top = 128;
		break;
	case 8:
		subRect.left = 64;
		subRect.top = 192;
		break;
	case 9:
		subRect.left = 64;
		subRect.top = 256;
		break;
	case 10:
		subRect.left = 128;
		subRect.top = 0;
		break;
	case 11:
		subRect.left = 128;
		subRect.top = 64;
		break;
	case 12:
		subRect.left = 128;
		subRect.top = 128;
		break;
	case 13:
		subRect.left = 128;
		subRect.top = 192;
		break;
	case 14:
		subRect.left = 128;
		subRect.top = 256;
		break;
	case 15:
		subRect.left = 192;
		subRect.top = 0;
		break;
	case 16:
		subRect.left = 192;
		subRect.top = 64;
		break;
	case 17:
		subRect.left = 192;
		subRect.top = 128;
		break;
	case 18:
		subRect.left = 192;
		subRect.top = 192;
		break;
	case 19:
		subRect.left = 192;
		subRect.top = 256;
		break;
	case 20:
		subRect.left = 256;
		subRect.top = 0;
		break;
	case 21:
		subRect.left = 256;
		subRect.top = 64;
		break;
	case 22:
		subRect.left = 256;
		subRect.top = 128;
		break;
	case 23:
		subRect.left = 256;
		subRect.top = 192;
		break;
	case 24:
		subRect.left = 256;
		subRect.top = 256;
		break;
	}
	subRect.width = 64;
	subRect.height = 64;
	sf::Sprite sprite(texture, subRect);
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(x, y);

	mWindow.draw(sprite);
	mWindow.display();

	if (iterator < 10)
	{
		explosion(iterator + 1, hexagonNum, sound);
	}
}
void Game::changeTurns(void)
{
	if (mPlayer1.getTurn() == true)//change to player 2
	{
		mPlayer1.setTurn(false);
		mPlayerColor = mPlayer2.getPlayerColor();//change board master color 
	}
	else//change to player 1
	{
		mPlayer1.setTurn(true);
		mPlayerColor = mPlayer1.getPlayerColor();
	}

}
void Game::resetBoard(void)
{

	for (int i = 0; i < 16; i++)
	{
		mHexBoard[i].setFillColor(28, 28, 28);//reset to board color
		mHexBoard[i].setExplosionCount(0);//reset explosion count
		for (int g = 0; g < 6; g++)//reset charges
		{
			//if the current color is charge color, reset it to the default charge
			if (mHexBoard[i].getCharge(g).getFillColor() == sf::Color(255, 255, 21))
			{
				mHexBoard[i].setCharge(g, sf::Color(64, 64, 64));
			}
		}
	}
	mPlayer1.resetTurn();
	mPlayer2.resetTurn();
	//mPlayer1.setTurn(false);
}