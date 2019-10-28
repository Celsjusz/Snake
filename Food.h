class Food
{
private:
	int iPosX, iPosY, iFoodSize;
	bool bExists;
public:
	int iGetPosX();
	int iGetPosY();
	int iGetFoodSize();
	int iGetRandomMapSquareX();
	int iGetRandomMapSquareY();
	int iCalculatePositionInCenter(int inSquare);
	bool alreadyExists();
	void setExists(bool inExists);
	void setPosX(int inPosX);
	void setPosY(int inPosY);
	void setFoodSize(int inSize);
	void generatePosition();
	Food();
	~Food();
};

