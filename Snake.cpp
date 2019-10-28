#include "main.h"

Snake::Snake()
{
	this->iPosX = 320;
	this->iPosY = 120;
	this->iSnakeSize = SnakeConstants::SQUARE_SIZE;
	this->arrSnakeSegments[0][0] = { 320 };
	this->arrSnakeSegments[0][1] = { 120 };
	this->iDimensions = 1; //0 - counts as one dimension
	this->iSegments = 1;
}

int Snake::iGetDimensionsNumber()
{
	return this->iDimensions;
}

int Snake::iGetSegmentsLenght()
{
	return this->iSegments;
}


int Snake::iGetPosX()
{
	return this->arrSnakeSegments[0][0];
}

int Snake::iGetPosY()
{
	return this->arrSnakeSegments[0][1];
}

int Snake::iGetSnakeSize()
{
	return this->iSnakeSize;
}

void Snake::setHeadPosX(int inPosX, int inOption)
{
	this->setSegments();
	if (inOption) {
		this->arrSnakeSegments[0][0] = inPosX;
	} else {
		this->arrSnakeSegments[0][0] = inPosX;
	}
}

void Snake::setHeadPosY(int inPosY, int inOption)
{
	this->setSegments();
	if (inOption) {
		this->arrSnakeSegments[0][1] = inPosY;
	}
	else {
		this->arrSnakeSegments[0][1] = inPosY;
	}
}

bool Snake::bIsThereSegment(int inPosX, int inPosY)
{
	for (int iTmpSegment = 1; iTmpSegment < this->iGetSegmentsLenght(); iTmpSegment++) {
		for (int iTmpDimension = 0; iTmpDimension < this->iGetDimensionsNumber(); iTmpDimension++) {
			if (this->arrSnakeSegments[iTmpSegment][iTmpDimension] == inPosX &&
				this->arrSnakeSegments[iTmpSegment][iTmpDimension + 1] == inPosY) 
			{
				return true;
			}
		}
	}

	return false;
}

void Snake::setSegments()
{
	int iHeadPosX = this->arrSnakeSegments[0][0];
	int iHeadPosY = this->arrSnakeSegments[0][1];

	int iLastSegmentX = -1;
	int iLastSegmentY = -1;

	int iRealLastSegmentX = -1;
	int iRealLastSegmentY = -1;

	for (int iTmpSegment = 1; iTmpSegment < this->iGetSegmentsLenght(); iTmpSegment++) {
		for (int iTmpDimension = 0; iTmpDimension < this->iGetDimensionsNumber(); iTmpDimension++) {
			if (iTmpSegment > 1) {
				iLastSegmentX = this->arrSnakeSegments[iTmpSegment][iTmpDimension];
				iLastSegmentY = this->arrSnakeSegments[iTmpSegment][iTmpDimension + 1];

				this->arrSnakeSegments[iTmpSegment][iTmpDimension] = iRealLastSegmentX;
				this->arrSnakeSegments[iTmpSegment][iTmpDimension + 1] = iRealLastSegmentY;
			} else {
				iLastSegmentX = this->arrSnakeSegments[iTmpSegment][iTmpDimension];
				iLastSegmentY = this->arrSnakeSegments[iTmpSegment][iTmpDimension + 1];

				this->arrSnakeSegments[iTmpSegment][iTmpDimension] = iHeadPosX;
				this->arrSnakeSegments[iTmpSegment][iTmpDimension + 1] = iHeadPosY;
			}

			iRealLastSegmentX = iLastSegmentX;
			iRealLastSegmentY = iLastSegmentY;
		}
	}
}

void Snake::addSnakeSegment(int inPosX, int inPosY)
{
	this->iSegments++;
	this->arrSnakeSegments[this->iSegments][0] = inPosX;
	this->arrSnakeSegments[this->iSegments][1] = inPosY;
}

void Snake::setSnakeSize(int inSize)
{
	this->iSnakeSize = inSize;
}

Snake::~Snake()
{
}
