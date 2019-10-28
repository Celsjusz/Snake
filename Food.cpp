#include "main.h"
#include <cstdlib>

Food::Food()
{
	this->iFoodSize = 10;
	this->iPosX = 0;
	this->iPosY = 0;
	this->bExists = false;
}

int Food::iGetPosX()
{
	return this->iPosX;
}

int Food::iGetPosY()
{
	return this->iPosY;
}

int Food::iGetFoodSize()
{
	return this->iFoodSize;
}

int Food::iGetRandomMapSquareX()
{
	return rand() % (SnakeConstants::SCREEN_WIDTH / SnakeConstants::SQUARE_SIZE) + 1;
}

int Food::iGetRandomMapSquareY()
{
	return rand() % (SnakeConstants::SCREEN_HEIGHT / SnakeConstants::SQUARE_SIZE) + 1;
}

int Food::iCalculatePositionInCenter(int inSquare)
{
	return (SnakeConstants::SQUARE_SIZE * (inSquare - 1)) + ((SnakeConstants::SQUARE_SIZE - this->iGetFoodSize()) / 2);
}


void Food::setPosX(int inPosX)
{
	this->iPosX = inPosX;
}

void Food::setPosY(int inPosY)
{
	this->iPosY = inPosY;
}

void Food::setFoodSize(int inSize)
{
	this->iFoodSize = inSize;
}

void Food::generatePosition()
{
	int iXSquare, iYSquare;

	iXSquare = this->iGetRandomMapSquareX(); //map is divided into squares, so we get random square
	iYSquare = this->iGetRandomMapSquareY(); //and its top left corner position (x,y)

	this->iPosX = this->iCalculatePositionInCenter(iXSquare); //make sure that food is generated in the center
	this->iPosY = this->iCalculatePositionInCenter(iYSquare); //of that square (same margins)
}

bool Food::alreadyExists()
{
	return this->bExists;
}

void Food::setExists(bool inExists)
{
	this->bExists = inExists;
}

Food::~Food()
{
}
