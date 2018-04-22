#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>

Map::Map()
{
	// Temporary map until file loading is implemented
	loadDefault();
}


Map::~Map()
{
	// Delete the wall objects
	for (auto it = begin(walls); it != end(walls); ++it) {
		delete (*it);
		(*it) = nullptr;
	}
}

void Map::draw(SDL_Renderer * mainRenderer)
{
	// Draw walls
	for (auto it = begin(walls); it != end(walls); ++it) {
		(*it)->draw(mainRenderer);
	}

	// Draw start

	// Draw finish
}

void Map::loadDefault()
{
	for (int x = 0; x < mapWidth; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			// Get the current tile
			char tile = map[x][y];

			switch (tile) {
			// Wall
			case('W'):
			{
				Wall *temp = new Wall();
				temp->setPos(x, y);
				temp->setSize(wallScale, wallScale);
				walls.push_back(temp);
			}
			// Space/empty
			case('S'):
				break;
			// Character/spawn
			case('C'):
				spawnPosX = x;
				spawnPosY = y;
				break;
			// Finish/end
			case('F'):
				finishPosX = x;
				finishPosY = y;
				break;
			default:
				break;
			}
		}
	}
}

bool Map::loadFromFile(std::string path, SDL_Renderer * mainRenderer)
{
	// Not yet implemented so use default map instead
	return false;
}

int Map::getSpawnPosition()
{
	return spawnPosX, spawnPosY;
}

int Map::getSpawnPositionX()
{
	return spawnPosX;
}

int Map::getSpawnPositionY()
{
	return spawnPosY;
}


int Map::getFinishPosition()
{
	return finishPosX, finishPosY;
}

int Map::getWallScale()
{
	return wallScale;
}

char Map::getSquare(int x, int y)
{
	if (x <= mapWidth && y <= mapHeight)
	{
		return map[x][y];
	}
}
