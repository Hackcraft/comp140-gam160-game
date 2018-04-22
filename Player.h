#pragma once
#include "SDL.h"

class Player
{
public:
	Player();
	~Player();

	void draw(SDL_Renderer *mainRenderer);
	void setSize(unsigned int width, unsigned int height);
	void setPos(unsigned int x, unsigned int y);

	int getWidth();
	int getHeight();

	int getPosX() { return rect.x; };
	int getPosY() { return rect.y; };

private:

	SDL_Rect rect;
};

