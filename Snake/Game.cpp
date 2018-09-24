#include "pch.h"
#include "Game.h"

#include <iostream>



Game::Game(int minFPS)
	: _window(VideoMode(
		GameData::DEF_TILE_SIZE * GameData::DEF_TILE_X,
		GameData::DEF_TILE_SIZE * GameData::DEF_TILE_Y),
		"SnakeGame")
	, _world(
		GameData::DEF_TILE_SIZE * GameData::DEF_TILE_X,
		GameData::DEF_TILE_SIZE * GameData::DEF_TILE_Y)
	, _minFPS(minFPS)
{
	Init();
}


Game::~Game()
{
}


void Game::Init()
{
	//end text init
	_endText.setFont(GameData::Fonts.Load("Resources/Fonts/impact.ttf"));
	_endText.setCharacterSize(GameData::DEF_TILE_X * GameData::DEF_TILE_SIZE / 16);
	_endText.setString("Died! Press 'R' Key to restart");

	FloatRect size = _endText.getGlobalBounds();
	_endText.setOrigin(size.width / 2, size.height / 2);
	_endText.setPosition(GameData::DEF_TILE_SIZE * GameData::DEF_TILE_X / 2,
		GameData::DEF_TILE_SIZE * GameData::DEF_TILE_Y / 2);
}


void Game::Run()
{
	Clock clock;
	Time sinceLastUpdate;
	Time timePerFrame = seconds(1.f / _minFPS);
	GameData::State = GameState::Running;

	//Minimum time steps game loop
	while (_window.isOpen())
	{
		ProcessEvents();

		sinceLastUpdate = clock.restart();
		while (sinceLastUpdate > timePerFrame)
		{
			sinceLastUpdate -= timePerFrame;
			Tick(timePerFrame);
		}

		Tick(sinceLastUpdate);
		Draw();
	}
}

void Game::ProcessEvents()
{
	Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == Event::Closed)//Close window
			_window.close();
		else if (event.type == Event::KeyPressed) //keyboard input
		{
			if (event.key.code == Keyboard::Escape)
				_window.close();
			if (event.key.code == Keyboard::R)
			{
				_world.Restart();
				GameData::State = GameState::Running;
			}
				
		}

		_world.ProcessEvents(event); //world related inputs
	}
}

void Game::Tick(sf::Time deltaTime)
{
	if (GameData::State == GameState::Running)
	{
		_world.Tick(deltaTime);
	}
}

void Game::Draw()
{

	_window.clear();

	switch (GameData::State)
	{
	case GameState::Idle:
		break;
	case GameState::Running:
		_window.draw(_world);
		break;
	case GameState::End:
		_window.draw(_world);
		_window.draw(_endText);
		break;
	default:
		break;
	}

	_window.display();
}




