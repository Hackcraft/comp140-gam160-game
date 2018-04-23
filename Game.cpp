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
	Decontructor
*/
Game::~Game()
{
	//// Surfaces
	//if (goToStartSurface)
	//{
	//	delete goToStartSurface;
	//	goToStartSurface = nullptr;
	//}

	//if (startSurface)
	//{
	//	delete startSurface;
	//	startSurface = nullptr;
	//}

	//if (finishSurface)
	//{
	//	delete finishSurface;
	//	finishSurface = nullptr;
	//}

	//// Textures
	//if (goToStartTexture)
	//{
	//	delete goToStartTexture;
	//	goToStartTexture = nullptr;
	//}

	//if (startTexture)
	//{
	//	delete startTexture;
	//	startTexture = nullptr;
	//}

	//if (finishTexture)
	//{
	//	delete finishTexture;
	//	finishTexture = nullptr;
	//}
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

	// Load SDL image for PNG
	//IMG_Init(IMG_INIT_PNG);

	// Set the size for the player
	player.setSize(10, 10);

	// Send the current map to the collision class
	collision.setMap(&map);

	return true;
}

void Game::render()
{
	switch (gameMode) 
	{
	case GoToStart:
		// set background color
		SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

		// clear previous frame
		SDL_RenderClear(mainRenderer);

		// draw to the screen here!
		player.setPos(500.f / 1023.f * fmax(serialInterface->getPosX() - player.getWidth(), 1), 500.f / 1023.f * fmax(serialInterface->getPosY() - player.getHeight(), 1));

		// Draw the map
		map.draw(mainRenderer);

		// Draw the player
		player.draw(mainRenderer);

		//SDL_RenderCopy(mainRenderer, goToStartTexture, NULL, NULL);
		std::cout << "Go to start" << std::endl;

		// render new frame
		SDL_RenderPresent(mainRenderer);

		break;
	case Playing:
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

		std::cout << "Playing" << std::endl;

		// render new frame
		SDL_RenderPresent(mainRenderer);
		break;
	case Won:
		std::cout << "You have won!" << std::endl;
		break;
	case Lost:
		std::cout << "You have lost." << std::endl;
		break;
	default:
		break;
	}
}

/*
* update - Process all variables !in charge of anything to do with rendering
*
*/
void Game::update()
{
	serialInterface->getPositions();
	switch (gameMode)
	{
	case GoToStart:
	{
		char square = collision.getOccupiedSquare(player);

		if (square == 'C')
		{
			gameMode = Playing;
			modeEnded = SDL_GetTicks();
		}
		break;
	}
	case Playing:
	{
		if (collision.hasCollided(player) == true)
		{
			gameMode = Lost;
			modeEnded = SDL_GetTicks();
		}
		else
		{
			char square = collision.getOccupiedSquare(player);

			if (square == 'F')
			{
				gameMode = Won;
				modeEnded = SDL_GetTicks();
			}
		}
		break;
	}
	case Won:
	{
		if (SDL_GetTicks() - modeEnded >= modeTimeout)
		{
			gameMode = GoToStart;
		}
		break;
	}
	case Lost:
	{
		if (SDL_GetTicks() - modeEnded >= modeTimeout)
		{
			gameMode = GoToStart;
		}
		break;
	default:
		break;
	}
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
	//IMG_Quit();
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}


