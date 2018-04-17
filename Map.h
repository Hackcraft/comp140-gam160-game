#pragma once
#include <fstream>
#include <iostream>
#include "SDL.h"
#include <vector>
#include "Wall.h"

class Map
{
public:
	Map();
	~Map();

	void draw(SDL_Renderer *mainRenderer);

	// Path to the map txt file, renderer to change window size based on map
	// True if found and loaded the map, else false
	bool loadFromFile(std::string path, SDL_Renderer *mainRenderer);

	void loadDefault();

	// Returns the spawn position of the player
	int getSpawnPosition();
	// Returns the finish position of the map
	int getFinishPosition();

	int getSpawnPositionX();
	int getSpawnPositionY();

	int getWallScale();

private:
	// 2D char array for the map values
	// W Wall, S Space, C Character, F Finish
	char map[10][10] = {
		{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ 'W', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'C', 'W' },
		{ 'W', 'S', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ 'W', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'W' },
		{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'S', 'W' },
		{ 'W', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'W' },
		{ 'W', 'S', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ 'W', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'W' },
		{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'F', 'W' },
		{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	};
	int mapWidth = 10;
	int mapHeight = 10;

	std::vector<Wall*> walls;

	// The spawn position of the player
	int spawnPosX, spawnPosY = 0;
	// The finish position of the player
	int finishPosX, finishPosY = 0;

	// Size of walls
	unsigned int wallScale = 50;

};

