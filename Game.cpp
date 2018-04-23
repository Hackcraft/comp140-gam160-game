#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <cmath>

using std::cout;

/*
* Constructor - not used in this case
*
*/
Game::Game()
{
	serialInterface = new SerialInterface();
}

/*
	Decontructor - also not used in this case
*/
Game::~Game()
{
}

/*
* init - used to initialise and setup SDL
* Return true if everything is successful
*/
bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window succesful..
		if (mainWindow != 0) {
			cout << "Window creation success \n";

			// create renderer
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

			// if renderer successful...
			if (mainRenderer != 0) {
				cout << "Renderer creation success \n";
				SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
			}
			else {
				cout << "renderer failed \n";
				return false;
			}
		}
		else {
			cout << "window failed \n";
			return false;
		}

	}
	else {
		cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	cout << "SDL init success \n";

	//Map map;

	// Set the size for the player
	player.setSize(10, 10);

	// Commented out as potentiometers have a limited range of movement so this would cause the player to get stuck (they need to be reset)
	// Set the posistion for the player
	//serialInterface->setPosX(map.getSpawnPositionX() * map.getWallScale() + (map.getWallScale() / 2 - player.getWidth() / 2));
	//serialInterface->setPosY(map.getSpawnPositionY() * map.getWallScale() + (map.getWallScale() / 2 - player.getHeight() / 2));

	// Send the current map to the collision class
	collision.setMap(&map);

	return true;
}

void Game::render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	player.setPos(500.f / 1023.f * fmax(serialInterface->getPosX() - player.getWidth(), 1), 500.f / 1023.f * fmax(serialInterface->getPosY() - player.getHeight(), 1));

	// Draw the map
	map.draw(mainRenderer);
	
	// Draw the player
	player.draw(mainRenderer);

	// render new frame
	SDL_RenderPresent(mainRenderer);
}

/*
* update - Process all variables !in charge of anything to do with rendering
*
*/
void Game::update()
{
	serialInterface->getPositions();
	if (collision.hasCollided(player) == true)
	{
		std::cout << "You lose!" << std::endl;
	}

	char square = collision.getOccupiedSquare(player);
	switch (square) {
		case 'C':
			std::cout << "Start" << std::endl;
			break;
		case 'F':
			std::cout << "Finish" << std::endl;
			break;
		default:
			break;
	}
}

/*
* handleEvents - Poll Events and uses switch case to process specific events
*
*/
void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}
	}
}

/*
* clean - Clean up SDL and close the port
*
*/
void Game::clean()
{	
	// Clean up serial stuff
	serialInterface->close();

	// Clean up rest
	cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}


