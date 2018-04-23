#pragma once
#include "SDL.h"
// #include "SDL_image.h"
#include "SerialInterface.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return isRunning; };

private:
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	bool isRunning;

	enum gameModes { GoToStart = 1, Playing = 2, Won = 3, Lost = 4 };
	int gameMode = 1;

	SerialInterface* serialInterface;

	Player player;

	Map map;

	Collision collision;

	int modeEnded = 0;
	int modeTimeout = 50 * 50;

	// Images
	//SDL_Surface * goToStartSurface = IMG_Load("textures/go_to_start.png");
	//SDL_Surface * startSurface = IMG_Load("textures/you_lost.png");
	//SDL_Surface * finishSurface = IMG_Load("textures/you_win.png");

	//SDL_Texture * goToStartTexture = SDL_CreateTextureFromSurface(mainRenderer, goToStartSurface);
	//SDL_Texture * startTexture = SDL_CreateTextureFromSurface(mainRenderer, startSurface);
	//SDL_Texture * finishTexture = SDL_CreateTextureFromSurface(mainRenderer, finishSurface);
};

