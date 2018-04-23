#pragma once
#include "Map.h"
#include "Player.h"

class Collision
{
public:
	Collision();
	~Collision();

	bool hasCollided(Player &Player);
	char getOccupiedSquare(Player &Player);

	void setMap(Map * Map);

private:
	Map *map;

	double getCurrentBoxX(double posX);
	double getCurrentBoxY(double posY);
};

