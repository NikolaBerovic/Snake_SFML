#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"

using namespace sf;

class Game
{
public:

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(int minFPS);
	~Game();

	//brief: Runs the game, call first after initialization
	void Run();

private:

	int _minFPS;
	RenderWindow _window;
	World _world;
	Text _endText;

	void Init();
	//brief: Update call for game logic
	void Tick(sf::Time deltaTime); 
	//brief: Update call for processing input events
	void ProcessEvents();
	//brief: Update call for drawing 
	void Draw();
};

