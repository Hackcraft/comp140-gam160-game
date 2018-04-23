#include "stdafx.h"
#include "Wall.h"
#include "iostream"

Wall::Wall()
{
	// Default posistion
	rect.x = 0;
	rect.y = 0;
	
	// Default size
	rect.w = 50;
	rect.h = 50;
}


Wall::~Wall()
{
}

void Wall::draw(SDL_Renderer *mainRenderer)
{
	SDL_SetRenderDrawColor(mainRenderer, colour[0], colour[1], colour[2], colour[3]);
	SDL_RenderFillRect(mainRenderer, &rect);
}

void Wall::setSize(unsigned int width, unsigned int height)
{
	rect.w = width;
	rect.h = height;
}

void Wall::setPos(unsigned int x, unsigned int y)
{
	// Grid reference
	gridPosX = x;
	gridPosY = y;

	// Scale the position by the size
	rect.x = x * rect.w;
	rect.y = y * rect.h;
}

int clamp(int val, int min, int max)
{
	return fmax(min, fmin(max, val));
}

void Wall::setColour(int r, int g, int b, int a)
{
	colour[0] = clamp(r, 0, 255);
	colour[1] = clamp(g, 0, 255);
	colour[2] = clamp(b, 0, 255);
	colour[3] = clamp(a, 0, 255);
}

void Wall::setColour(int col[])
{
	colour[0] = clamp(col[0], 0, 255);
	colour[1] = clamp(col[1], 0, 255);
	colour[2] = clamp(col[2], 0, 255);
	colour[3] = clamp(col[3], 0, 255);
}
