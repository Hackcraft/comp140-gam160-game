#pragma once
#include "SDL.h"
#include <cmath>

class Wall
{
public:
	Wall();
	~Wall();

	void draw(SDL_Renderer *mainRenderer);
	void setSize(unsigned int width, unsigned int height);
	void setPos(unsigned int x, unsigned int y);

	void setColour(int r, int g, int b, int a);
	void setColour(int col[]);
private:
	SDL_Rect rect;

	int gridPosX, gridPosY = 0;
	int colour[4] = { 0, 0, 0, 255 };
};

