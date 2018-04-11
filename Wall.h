#pragma once
#include "SDL.h"

class Wall
{
public:
	Wall();
	~Wall();

	void draw(SDL_Renderer *mainRenderer);
	void setSize(unsigned int width, unsigned int height);
	void setPos(unsigned int x, unsigned int y);

private:
	SDL_Rect rect;
};

