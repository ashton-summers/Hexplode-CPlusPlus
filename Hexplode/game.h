#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "hexagon.h"
#include "player.h"

class Game
{
public:
	//CONSTRUCTORS
	Game();
	//DESTRUCTORS
	~Game();
								//MEMBER FUNCTIONS
	//Game &operator = (const Game&) = delete;
	void run();
	void initializeBoard(void);//loops through the printShape to print out the board
	void initializeChargeLocation(void);
	void resetBoard(void);
	void updatePieces(void);

private:
	void processEvents(void);//manage user events
	void processMenuEvents(void);
	void updateBoard(void);//checks for exploded hexagons
	void renderMenu(void);//renders the menu
	void render(void);//displays the game to screen
	void explosion(int iterator, int hexagonNum, sf::Sound sound);
	void explosionwrap(int iterator, int hexagonNum);
	void changeTurns(void);
	void updateEvents(int i);
	bool mGameDisplay = false;	
	void mPlayChargeSound(int i);

	sf::RenderWindow mWindow;//game window
	sf::SoundBuffer mBuffer;//holds music file
	sf::Sound mGameMusic;//modifies music
	sf::SoundBuffer mChargeSoundBuffer;//holds charge sound file
	sf::Sound mChargeSound;//plays the charge sound
	sf::Sprite mBackground;//sets background
	sf::Texture mTexture;//gets background file
	sf::Color mPlayerColor;//holds current player's color
	Player mPlayer1;
	Player mPlayer2;
	Hexagon mHexBoard[16];//holds the hexagons
};