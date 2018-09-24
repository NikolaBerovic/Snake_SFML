#pragma once
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Enum.h"
#include <string>

using namespace std;
using namespace sf;

//Class with static game data ("static" class)
class GameData
{
public:

	GameData() = delete;
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;

	///DEFAULT CONSTANTS
	static const int DEF_TILE_SIZE = 32;
	static const int DEF_TILE_X = 16;
	static const int DEF_TILE_Y = 12;

	///RESOURCES
	static Resource<Texture> Textures;
	static Resource<Font> Fonts;

	///GAME STATE
	static GameState State;
};

