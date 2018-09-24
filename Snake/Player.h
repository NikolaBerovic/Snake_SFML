#pragma once
#include "Entity.h"
#include <list>

class Input;
class Player : public Entity
{
public:
	Player(Tile* tile);
	~Player();

	//brief: Gets Vector2i directions, normalized
	Vector2i GetDirection();
	//brief: Gets pointer to input component
	Input* GetInput();
	//brief: Gets list of Entites representing tail
	list<Entity*> GetTail() const;

	//brief: Sets current tile and pos, adds and moves tail (conditional)
	void SetTile(Tile* tile) override;
	//brief: Sets hasEaten to value
	void SetEaten(const bool value);

	bool HasEaten() const;
	//brief: Returns true if body and tail contain tile
	bool DoesOccupyTile(const Tile* tile) const;

protected:

	Input* _input;
	list<Entity*> _tail;
	Vector2i _dir = Vector2i(0, -1);
	float _angle;

	bool _isRotated = false;
	bool _hasEaten = false;

	void SetRotation(const float degrees);
	void MoveTail();
	void AddTail();
	
};

