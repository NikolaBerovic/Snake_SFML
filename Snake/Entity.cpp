#include "pch.h"
#include "Entity.h"
#include "GameData.h"
#include "Tile.h"
#include <cmath>


Entity::Entity(Tile* tile, string spritePath)
	: _spritePath(spritePath)
{
	_sprite.setTexture(GameData::Textures.Load(_spritePath), false);
	Vector2u size(_sprite.getTexture()->getSize());

	_sprite.setOrigin((float)size.x / 2, (float)size.y / 2);
	
	_sprite.setScale(
		GameData::DEF_TILE_SIZE / _sprite.getLocalBounds().width, 
		GameData::DEF_TILE_SIZE / _sprite.getLocalBounds().height);

	SetTile(tile);
}


Entity::~Entity()
{
}

/// <summary>Returns ref to sprite of Entity</summary>
Sprite& Entity::GetSprite()
{
	return _sprite;
}

/// <summary>Self update function
/// <para>Call on update for processing</para>  
/// </summary>
void Entity::Tick(Time deltaTime)
{
}

/// <summary>Sets current tile
/// <para>Updates position of Entity to location of the tile</para>  
/// </summary>
void Entity::SetTile(Tile* tile)
{
	if (tile != nullptr)
	{
		_currentTile = tile;
		_sprite.setPosition(Vector2f(_currentTile->GetWorldPos()));
	}
}

/// <summary>Returns current tile where Entity is located</summary>
Tile * Entity::GetTile() const
{
	return _currentTile;
}
