#include "pch.h"
#include "Tile.h"


Tile::Tile(int size, Vector2i worldPos, Vector2i gridPos, Color color)
	:_worldPos(worldPos)
	,_gridPos(gridPos)
{
	_rect = new RectangleShape(Vector2f(size, size));
	_rect->setOrigin((float)size / 2, (float)size / 2);
	_rect->setPosition(Vector2f(worldPos));
	_rect->setFillColor(color);
}

Tile::~Tile()
{
	delete _rect;
}

RectangleShape * Tile::GetRect() const
{
	return _rect;
}

Vector2i Tile::GetWorldPos() const
{
	return _worldPos;
}

Vector2i Tile::GetGridPos() const
{
	return _gridPos;
}
