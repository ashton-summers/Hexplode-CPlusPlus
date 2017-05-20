#include "player.h"

Player::Player()
{
	mNumTurns = 0;
	isTurn = false;
}

Player::~Player()
{
}

//SETTERS
void Player::setPlayerColor(sf::Color color)
{
	mPlayerColor = color;
}

void Player::setPlayerColor(int one, int two, int three)
{
	mPlayerColor = sf::Color(one, two, three);
}


void Player::setNumTurns(int turn)
{
	mNumTurns = mNumTurns + turn;
}


void Player::setTurn(bool newTurn)
{
	isTurn = newTurn;
}

//GETTERS
sf::Color Player::getPlayerColor(void) const
{
	return this->mPlayerColor;
}

int Player::getNumTurns(void) const
{
	return this->mNumTurns;
}

bool Player::getTurn(void) const
{
	return this->isTurn;
}

//MEMBER FUNCTIONS
void Player::resetTurn(void)
{
	mNumTurns = 0;
}
