#pragma once
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player();
	~Player();

	//SETTERS
	void setPlayerColor(sf::Color color);
	void setPlayerColor(int one, int two, int three);
	void setNumTurns(int turns);
	void setTurn(bool newTurn);

	//GETTERS
	sf::Color getPlayerColor(void) const;
	int getNumTurns(void) const;
	bool getTurn(void) const;

	//MEMBER FUNCTIONS
	void resetTurn(void);
private:
	sf::Color mPlayerColor;//sets player color
	int mNumTurns;//indicates the number of turns
	bool isTurn;
};