#include "stdafx.h"
#include "Game.h"
#include <iostream>

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

	// Set the size for the player
	player.w = 10;
	player.h = 10;

	return true;
}

void Game::render()
{
	// set background color
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	
	// clear previous frame
	SDL_RenderClear(mainRenderer);

	// draw to the screen here!
	//player.x = serialInterface->getPosX();
	//player.y = serialInterface->getPosY();

	// Draw test wall object
	//Wall wall;
	//wall.draw(mainRenderer);
	
	SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(mainRenderer, &player);

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
			std::cout << "Hello?2??" << std::endl;
			break;
		default:
			break;
		}
		// Arrow keys
		if (event.type == SDL_KEYDOWN) 
		{
			auto key = event.key.keysym.sym;
			if (key == SDLK_UP)
				serialInterface->setPosY(serialInterface->getPosY() + 2);
			if (key == SDLK_DOWN)
				serialInterface->setPosY(serialInterface->getPosY() - 2);
			if (key == SDLK_LEFT)
				serialInterface->setPosX(serialInterface->getPosX() - 2);
			if (key == SDLK_RIGHT)
				serialInterface->setPosX(serialInterface->getPosX() + 2);
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

