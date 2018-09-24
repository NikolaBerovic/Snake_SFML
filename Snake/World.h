#pragma once
#include "SFML/Graphics.hpp"
#include "GameData.h"
#include <list>

using namespace std;
using namespace sf;

class Player;
class Entity;
class Tile;

//Class representing game world
class World : public Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	World(int worldWidth, int worldHeight);
	~World();

	//brief: Overriden draw inherited from Drawable class
	virtual void draw(RenderTarget& target, RenderStates states) const override;

	//brief: Update call for game logic
	void Tick(Time deltaTime);
	//brief: Update call for processing input events
	void ProcessEvents(Event& event) const;
	//brief: Clears all entites and restarts the game
	void Restart();

private: 

	Tile* _grid[GameData::DEF_TILE_X][GameData::DEF_TILE_Y];
	list<Entity*>  _entities; //in case of other future entities, for now only for Food entity

	Player* player;

	float _timePassed; //delta time passed for moving player in Tick
	float _delay = 0.2f; //delay for moving player in Tick

	///Tile colors
	Color _colorOdd = Color(0, 200, 0);
	Color _colorEven = Color(0, 255, 0);

	void Start();
	void Init();
	void ClearGrid();
	//brief: Spawns food at random location
	void SpawnFood();

	int Randomize(int start, int end);

	//brief: Template class for spawning Entities
	template<typename Entity>
	Entity* Spawn(Tile* tile);
};


