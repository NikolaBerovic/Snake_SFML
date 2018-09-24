#pragma once
#define _USE_MATH_DEFINES
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>

using namespace sf;
using namespace std;

class Tile;
class Entity
{
public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(Tile* tile, string spritePath);
	virtual ~Entity();

	//brief: Self update function
	virtual void Tick(Time deltaTime);
	//brief: Sets current tile, updates Entity locations
	virtual void SetTile(Tile* tile);
	//brief: Gets current tile where Entity is located
	virtual Tile* GetTile() const;

	//brief: Gets ref to sprite of Entity
	Sprite& GetSprite();

protected:

	class Tile* _currentTile;
	string _spritePath;
	Sprite _sprite;	
};

