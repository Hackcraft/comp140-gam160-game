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
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(mainRenderer, &rect);
}

void Wall::setSize(unsigned int width, unsigned int height)
{
	rect.w = width;
	rect.h = height;
}

void Wall::setPos(unsigned int x, unsigned int y)
{
	rect.x = x;
	rect.y = y;
}
