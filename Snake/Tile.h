#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

//Class representing on-screen grid tile
class Tile
{
public:
	Tile(const Tile&) = delete;
	Tile& operator=(const Tile&) = delete;

	Tile(int size, Vector2i worldPos, Vector2i gridPos, Color color);
	~Tile();

	RectangleShape* GetRect() const;
	Vector2i GetWorldPos() const;
	Vector2i GetGridPos() const;

private:

	Vector2i _worldPos;
	Vector2i _gridPos;
	RectangleShape* _rect;
};

