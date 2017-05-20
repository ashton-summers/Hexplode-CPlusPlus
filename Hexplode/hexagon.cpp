#include "hexagon.h"

//CONSTRUCTOR
Hexagon::Hexagon()
{
	mpTop = nullptr;
	mpUpperL = nullptr;
	mpLowerL = nullptr;
	mpBottom = nullptr;
	mpLowerR = nullptr;
	mpUpperR = nullptr;
	mHexagon.setRadius(35);
	mHexagon.setPointCount(6);
	mHexagon.setRotation(30);
	mHexagon.setFillColor(sf::Color(28, 28, 28));//dark cyan
	explosionCount = 0;
	baseCount = 0;

	for (int g = 0; g < 6; g++)
	{
		mCharge[g].setRadius(7);
		mCharge[g].setFillColor(sf::Color(28, 28, 28));//make it so they don't appear if rendered.
		mCharge[g].setPointCount(6);
		mCharge[g].setRotation(30);
	}
}

//DESTRUCTOR
Hexagon::~Hexagon()
{


}
//SETTERS
void Hexagon::setFillColor(sf::Color color)
{
	this->mHexagon.setFillColor(color);//sets hexagon color
}
void Hexagon::setFillColor(int one, int two, int three)
{
	this->mHexagon.setFillColor(sf::Color(one, two, three));//sets board color
}
void Hexagon::setPosition(float x, float y)
{
	this->mHexagon.setPosition(x, y);//set hexagon position
}
void Hexagon::setTop(Hexagon *newPointer)
{
	this->mpTop = newPointer;
}
void Hexagon::setUpperL(Hexagon *newPointer)
{
	this->mpUpperL = newPointer;
}
void Hexagon::setLowerL(Hexagon *newPointer)
{
	this->mpLowerL = newPointer;
}
void Hexagon::setBottom(Hexagon *newPointer)
{
	this->mpBottom = newPointer;
}
void Hexagon::setLowerR(Hexagon *newPointer)
{
	this->mpLowerR = newPointer;
}
void Hexagon::setUpperR(Hexagon *newPointer)
{
	this->mpUpperR = newPointer;
}
void Hexagon::setBase(int base)
{
	this->baseCount = base;
}
void Hexagon::setExplosionCount(int explode)
{
	this->explosionCount = explode;
}
void Hexagon::setCharge(int i, sf::Color color)
{
	mCharge[i].setFillColor(color);
}
void Hexagon::setChargePosition(int i, float x, float y)
{
	mCharge[i].setPosition(x, y);
}

//GETTERS
sf::Color Hexagon::getColor(void) const
{
	return this->mHexagon.getFillColor();
}
sf::CircleShape Hexagon::getShape(void) const
{
	return this->mHexagon;
}
sf::CircleShape Hexagon::getCharge(int i) const
{
	return mCharge[i];
}
int Hexagon::getExplosionCount(void) const
{
	return this->explosionCount;
}
int Hexagon::getBaseClick(void) const
{
	return this->baseCount;
}
//MEMBER FUNCTIONS

void Hexagon::plusOneExpl()//adds one to the explosion counter
{
	this->explosionCount++;
}

void Hexagon::chargeHex(Hexagon *pCur)
{
	int i = 0;
	i = pCur->explosionCount;//set i to the current charge
	//charge the hexagon 'i' times
	for (; i != 0; i--)
	{
		//it's i-1 to be at the correct place in the array
		//check to make sure we're not coloring a hexagon that we don't want to:
		if (pCur->mCharge[i-1].getFillColor() != sf::Color(28, 28, 28))//if not equal to background color
		{
			pCur->mCharge[i-1].setFillColor(sf::Color(255, 255, 21));//sets charge to yellow
		}
	}
}
void Hexagon::updateHex(sf::Color mPlayerColor)//send out a +1 to each hex
{
	//if hexagon is adjacent:
	if (mpTop != nullptr)
	{
		mpTop->setFillColor(mPlayerColor);//will replace with player color later
		mpTop->plusOneExpl();
		chargeHex(mpTop);
	}
	if (mpUpperL != nullptr)
	{
		mpUpperL->setFillColor(mPlayerColor);
		mpUpperL->plusOneExpl();
		chargeHex(mpUpperL);
	}
	if (mpLowerL != nullptr)
	{
		mpLowerL->setFillColor(mPlayerColor);
		mpLowerL->plusOneExpl();
		chargeHex(mpLowerL);
	}
	if (mpBottom != nullptr)
	{
		mpBottom->setFillColor(mPlayerColor);
		mpBottom->plusOneExpl();
		chargeHex(mpBottom);
	}
	if (mpLowerR != nullptr)
	{
		mpLowerR->setFillColor(mPlayerColor);
		mpLowerR->plusOneExpl();
		chargeHex(mpLowerR);
	}
	if (mpUpperR != nullptr)
	{
		mpUpperR->setFillColor(mPlayerColor);
		mpUpperR->plusOneExpl();
		chargeHex(mpUpperR);
	}
	return;
}
