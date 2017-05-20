#pragma once
#include "SFML/Graphics.hpp"
class Hexagon
{
public:
	//CONSTRUCTOR
	Hexagon();
	//DESTRUCTOR
	~Hexagon();
	//SETTERS
	void setFillColor(sf::Color color);
	void setFillColor(int one, int two, int three);//accepts RGB colors as int
	void setPosition(float x, float y);
	void setTop(Hexagon *newPointer);
	void setUpperL(Hexagon *newPointer);
	void setLowerL(Hexagon *newPointer);
	void setBottom(Hexagon *newPointer);
	void setLowerR(Hexagon *newPointer);
	void setUpperR(Hexagon *newPointer);
	void setBase(int base);
	void setExplosionCount(int explode);
	void setCharge(int i, sf::Color color);//changes color (charge) at that place in the array
	void setChargePosition(int i, float x, float y);
	//GETTERS
	sf::Color getColor(void) const;
	sf::CircleShape getShape(void) const;
	sf::CircleShape getCharge(int i) const;//returns circle (charge) at that place in the array
	int getExplosionCount(void) const;
	int getBaseClick(void) const;
	//MEMBER FUNCTIONS
	void plusOneExpl();//adds one to the selected hexagon
	void chargeHex(Hexagon *pCur);//displays charges to the hexagons
	void updateHex(sf::Color mPlayerColor);//explodes a hexagon
private:
	sf::CircleShape mHexagon;//encapsulates shape and color
	sf::CircleShape mCharge[6];//holds 6 charges for each hexagon
	int explosionCount;//holds number of charges per hex
	int baseCount;//starts hexagon charges for border hex
	//pointers to adjacent hexagons
	Hexagon *mpTop;
	Hexagon *mpUpperL;
	Hexagon *mpLowerL;
	Hexagon *mpBottom;
	Hexagon *mpLowerR;
	Hexagon *mpUpperR;
};