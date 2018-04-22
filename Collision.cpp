#include "stdafx.h"
#include "Collision.h"
#include <iostream>
#include <cmath>

Collision::Collision()
{
}


Collision::~Collision()
{
	// Remove the map pointer object
	if (map) 
	{
		delete map;
		map = nullptr;
	}
}

// Generic collision function, determins collision type based on flags
bool Collision::hasCollided(Player &Player)
{
	int x, y;

	// Top left
	x = getCurrentBoxX(Player.getPosX());
	y = getCurrentBoxY(Player.getPosY());

	//std::cout << x << " - " << y << " --> " << map->getSquare(x, y) << std::endl; // Map block Debug

	if (map->getSquare(x, y) == 'W')
		return true;

	// Top right
	x = getCurrentBoxX(Player.getPosX() + Player.getWidth());
	y = getCurrentBoxY(Player.getPosY());
	if (map->getSquare(x, y) == 'W')
		return true;

	// Bottom left
	x = getCurrentBoxX(Player.getPosX());
	y = getCurrentBoxY(Player.getPosY() + Player.getHeight());
	if (map->getSquare(x, y) == 'W')
		return true;

	// Bottom right
	x = getCurrentBoxX(Player.getPosX() + Player.getWidth());
	y = getCurrentBoxY(Player.getPosY() + Player.getHeight());
	if (map->getSquare(x, y) == 'W')
		return true;
	
	return false;
}

void Collision::setMap(Map * Map)
{
	map = Map;

	std::cout << map << std::endl;
}

// Private
double Collision::getCurrentBoxX(double posX)
{
	return floor(map->getMapWidth() / map->getWindowWidth() * posX );
}

// Private
double Collision::getCurrentBoxY(double posY)
{
	return floor(map->getMapHeight() / map->getWindowHeight() * posY);
}
