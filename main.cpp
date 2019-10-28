#include "main.h"

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum class Color {
	BLACK,
	GREEN,
	RED
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event gEvent;
SDL_Rect gSnakeRect;
Direction gSnakeDirection = Direction::DOWN;

int gTick = 300;
int gTimeElapsed = 0;
int gFoodAte = 0;
bool gBlockInput = false;
bool gQuit = false;

int iInitializeSDL();
int iInitializeWindow();
void mainGame(Snake &snake, Food &food);

int main(int argc, char* args[]) {

	if (iInitializeSDL() && iInitializeWindow()) {
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		Snake snake;
		Food food;
		mainGame(snake, food);
	}

	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();

	return 1;
}

int iInitializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	return 1;
}

int iInitializeWindow()
{
	gWindow = SDL_CreateWindow(
		SnakeConstants::WINDOW_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SnakeConstants::SCREEN_WIDTH,
		SnakeConstants::SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (gWindow == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	return 1;
}

void clearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

void showRectangle(Color inColor, SDL_Rect inRect)
{
	switch (inColor) {
	case Color::BLACK:
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		break;
	case Color::GREEN:
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xBB, 0x00, 0xFF);
		break;
	case Color::RED:
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	}

	SDL_RenderFillRect(gRenderer, &inRect);
	SDL_RenderPresent(gRenderer);
}

void showDeathScreen()
{
	gSnakeRect = { 0, 0, SnakeConstants::SCREEN_WIDTH, SnakeConstants::SCREEN_HEIGHT };

	showRectangle(Color::RED, gSnakeRect);
	SDL_Delay(1000);
	gQuit = true;
}

void checkCollisionWithWalls(Snake snake)
{
	if (snake.iGetPosY() + snake.iGetSnakeSize() > SnakeConstants::SCREEN_HEIGHT
		|| snake.iGetPosY() < 0
		|| snake.iGetPosX() + snake.iGetSnakeSize() > SnakeConstants::SCREEN_WIDTH
		|| snake.iGetPosX() < 0)
	{
		showDeathScreen();
	}
}

void checkCollisionWithTail(Snake snake)
{
	bool collision = false;

	if (gSnakeDirection == Direction::UP && snake.bIsThereSegment(snake.iGetPosX(), snake.iGetPosY())) {
		collision = true;
	}
	else if (gSnakeDirection == Direction::DOWN && snake.bIsThereSegment(snake.iGetPosX(), snake.iGetPosY())) {
		collision = true;
	}
	else if (gSnakeDirection == Direction::RIGHT && snake.bIsThereSegment(snake.iGetPosX(), snake.iGetPosY())) {
		collision = true;
	}
	else if (gSnakeDirection == Direction::LEFT && snake.bIsThereSegment(snake.iGetPosX(), snake.iGetPosY())) {
		collision = true;
	}

	if (collision) {
		showDeathScreen();
	}
}

void moveSnake(Snake &snake)
{
	if (SDL_GetTicks() - gTimeElapsed > gTick) {

		gTimeElapsed = SDL_GetTicks();

		if (gSnakeDirection == Direction::UP) {
			snake.setHeadPosY(snake.iGetPosY() - snake.iGetSnakeSize(), 0);
		}
		else if (gSnakeDirection == Direction::DOWN) {
			snake.setHeadPosY(snake.iGetPosY() + snake.iGetSnakeSize(), 1);
		}
		else if (gSnakeDirection == Direction::RIGHT) {
			snake.setHeadPosX(snake.iGetPosX() + snake.iGetSnakeSize(), 1);
		}
		else if (gSnakeDirection == Direction::LEFT) {
			snake.setHeadPosX(snake.iGetPosX() - snake.iGetSnakeSize(), 0);
		}

		clearScreen();

		for (int iTmpSegment = 0; iTmpSegment < snake.iGetSegmentsLenght(); iTmpSegment++) {
			for (int iTmpDimension = 0; iTmpDimension < snake.iGetDimensionsNumber(); iTmpDimension++) {
				int iTmpPosX = snake.arrSnakeSegments[iTmpSegment][iTmpDimension];
				int iTmpPosY = snake.arrSnakeSegments[iTmpSegment][iTmpDimension+1];
		
				gSnakeRect = { iTmpPosX, iTmpPosY, snake.iGetSnakeSize(), snake.iGetSnakeSize() };
				showRectangle(Color::BLACK, gSnakeRect);
			}
		}

		gBlockInput = false;
	}
}

void checkForInput()
{
	while (SDL_PollEvent(&gEvent)) {

		if (gEvent.type == SDL_QUIT) {
			gQuit = true;
		}

		if (gBlockInput) {
			return;
		}

		switch (gEvent.key.keysym.sym) {
		case SDLK_UP:
			if (gSnakeDirection != Direction::DOWN) {
				gSnakeDirection = Direction::UP;
				gBlockInput = true;
			}
			break;

		case SDLK_RIGHT:
			if (gSnakeDirection != Direction::LEFT) {
				gSnakeDirection = Direction::RIGHT;
				gBlockInput = true;
			}
			break;

		case SDLK_DOWN:
			if (gSnakeDirection != Direction::UP) {
				gSnakeDirection = Direction::DOWN;
				gBlockInput = true;
			}
			break;

		case SDLK_LEFT:
			if (gSnakeDirection != Direction::RIGHT) {
				gSnakeDirection = Direction::LEFT;
				gBlockInput = true;
			}
			break;
		}
	}
}

void showFoodOnScreen(Food food)
{
	SDL_Rect foodRect= { food.iGetPosX(), food.iGetPosY(), food.iGetFoodSize(), food.iGetFoodSize() };
	showRectangle(Color::GREEN, foodRect);
}

void spawnFood(Food &food)
{
	if (!food.alreadyExists()) {
		food.generatePosition();
		food.setExists(true);
	}
}

bool checkCollisionWithFood(Snake &snake, Food &food)
{
	if (abs(food.iGetPosX() - snake.iGetPosX()) <= 15 && abs(food.iGetPosY() - snake.iGetPosY()) <= 15) {
		return true;
	}

	return false;
}

void eatFood(Food &food, Snake &snake)
{
	snake.addSnakeSegment(food.iGetPosX(), food.iGetPosY());
	gFoodAte++;
}

void cleanFood(Food &food)
{
	food.setExists(false);
}

void speedUp()
{
	if (gTick > 80 && gFoodAte % 4 == 0) {
		gTick -= 25;
	}
}

void mainGame(Snake &snake, Food &food)
{
	spawnFood(food);

	while (!gQuit) {
		checkCollisionWithWalls(snake);
		checkCollisionWithTail(snake);
		if (checkCollisionWithFood(snake, food)) {
			speedUp();
			eatFood(food, snake);
			cleanFood(food);
			spawnFood(food);
		}
		checkForInput();
		showFoodOnScreen(food);
		moveSnake(snake);
	}
}