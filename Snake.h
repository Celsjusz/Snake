class Snake
{
private:
	int iPosX, iPosY, iSnakeSize, iSegments, iDimensions;
public:
	int arrSnakeSegments[100][2]; //100 is max lenght, temporary solution

	int iGetPosX();
	int iGetPosY();
	int iGetSnakeSize();
	int iGetSegmentsLenght();
	int iGetDimensionsNumber();
	void setHeadPosX(int inPosX, int inOption = 0);
	void setHeadPosY(int inPosY, int inOption = 0);
	void setSnakeSize(int inSize);
	void addSnakeSegment(int inPosX, int inPosY);
	void setSegments();
	bool bIsThereSegment(int inPosX, int inPosY);
	Snake();
	~Snake();
};
