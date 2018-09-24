#include "pch.h"
#include "World.h"
#include "Input.h"
#include "Player.h"
#include "Food.h"
#include "Helper.h"
#include "Tile.h"
#include <iostream>
#include <cstdlib>


World::World(int worldWidth, int worldHeight)
{
	srand(time(0));
	Init();
	Start();
}

World::~World()
{
	Helper::Clear(_entities);
	Helper::Clear(player);
	ClearGrid();
}

void World::Init()
{

	int size = GameData::DEF_TILE_SIZE;

	//grid init
	for (int i = 0; i < GameData::DEF_TILE_X; i++) {
		for (int j = 0; j < GameData::DEF_TILE_Y; j++) {

			Color color = (i % 2 == 0 ^ j % 2 == 0)
				? _colorOdd : _colorEven;

			Vector2i wPos = Vector2i(size*i + size / 2, size*j + size / 2);
			Vector2i gPos(i, j);
			_grid[i][j] = new Tile(size, wPos, gPos, color);
		}
	}
}

void World::Start()
{
	int startX = (int)GameData::DEF_TILE_X / 2;
	int startY = (int)GameData::DEF_TILE_Y / 2;
	player = Spawn<Player>(_grid[startX][startY]);

	SpawnFood();
}

void World::draw(RenderTarget & target, RenderStates states) const
{
	//Draws grid
	for (int i = 0; i < GameData::DEF_TILE_X; i++) {
		for (int j = 0; j < GameData::DEF_TILE_Y; j++) {

			if (_grid[i][j]) target.draw(*_grid[i][j]->GetRect());
		}
	}

	//Draws entities
	for (Entity* entity : _entities)
	{
		if (entity) target.draw(entity->GetSprite());
	}

	//Draws player
	if (player) target.draw(player->GetSprite());
	for (Entity* t: player->GetTail())
	{
		if (t) target.draw(t->GetSprite());
	}
}

void World::Tick(Time deltaTime)
{
	_timePassed += deltaTime.asSeconds();

	//player->Tick(deltaTime); //uncomment if self update needed

	if (_timePassed >= _delay && player)
	{

		Vector2i pos = player->GetTile()->GetGridPos();
		Vector2i dir = player->GetDirection();

		int tileX = pos.x + dir.x;
		int tileY = pos.y + dir.y;

		//if inside bounds
		if (tileX >= 0 && tileX < GameData::DEF_TILE_X &&
			tileY >= 0 && tileY < GameData::DEF_TILE_Y)
		{
			Tile* tile = _grid[pos.x + dir.x][pos.y + dir.y];

			//if no self collision
			if (player->DoesOccupyTile(tile) == false)
			{
				for (auto it = _entities.begin(); it != _entities.end();)
				{
					if (Food* food = dynamic_cast<Food*>(*it))
					{
						if (food->GetTile() == tile)
						{
							delete *it;
							_entities.erase(it);
							player->SetEaten(true);	
							break;
						}
					}
					++it;
				}
				player->SetTile(tile);
				if (player->HasEaten() == true)
				{
					SpawnFood();
					player->SetEaten(false);
				}	
				_timePassed = 0;
			}
			else
			{
				player->SetTile(tile);
				cout << "Collided with self!";
				GameData::State = GameState::End;
			}

		}
		else
		{
			cout << "Out of bounds!";
			GameData::State = GameState::End;
		}
	}
}

void World::ProcessEvents(Event & event) const
{
	if (player) player->GetInput()->ProcessEvents(event);
}

/// <summary>Deletes all pointed entities, restarts game</summary>
void World::Restart()
{
	Helper::Clear(_entities);
	Helper::Clear(player);
	Start();
}

/// <summary>Deletes all pointed objects  in grid 2d array</summary>
void World::ClearGrid()
{
	for (int i = 0; i < GameData::DEF_TILE_X; i++) {
		for (int j = 0; j < GameData::DEF_TILE_Y; j++) {

			delete _grid[i][j];
		}
	}
}

template<typename Entity>
Entity * World::Spawn(Tile* tile)
{
	return new Entity(tile);
}

/// <summary>Spawns food at random location of the grid
/// <para>Adds Food entity to entity list</para>  
/// </summary>
void World::SpawnFood()
{
	Tile* tile;
	int it = -1;
	int itMax = 100;
	do {
		int xRand = Randomize(0, GameData::DEF_TILE_X);
		int yRand = Randomize(0, GameData::DEF_TILE_Y);
		tile = _grid[xRand][yRand];
		it++;
	} while (player->DoesOccupyTile(tile) || it >= itMax);

	if (it < itMax) _entities.push_back(Spawn<Food>(tile));

}

int World::Randomize(int start, int end) 
{
	int random = start + (rand() % end);
	return random;
}



