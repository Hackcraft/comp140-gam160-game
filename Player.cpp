#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player()
{
}


Player::~Player()
{
}

void Player::draw(SDL_Renderer * mainRenderer)
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(mainRenderer, &rect);
}

void Player::setSize(unsigned int width, unsigned int height)
{
	rect.w = width;
	rect.h = height;
}

void Player::setPos(unsigned int x, unsigned int y)
{
	rect.x = x;
	rect.y = y;
}

int Player::getWidth()
{
	return rect.w;
}

int Player::getHeight()
{
	return rect.h;
}
