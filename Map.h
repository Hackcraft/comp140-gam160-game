#pragma once
#include <fstream>
#include <iostream>
#include "SDL.h"

class Map
{
public:
	Map();
	~Map();

	void draw(SDL_Renderer *mainRenderer);

	// Path to the map txt file, renderer to change window size based on map
	// True if found and loaded the map, else false
	bool loadFromFile(std::string path, SDL_Renderer *mainRenderer);

};

