#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Tile.h"
#include "Helper.h"

Player::Player(Tile* tile)
	: Entity(tile, "Resources/Textures/Head.png")
{
	_input = new Input();
	_input->Bind("SnakeRight", Action(Keyboard::D, ActionType::Released), [this]() {
		SetRotation(90);
	});
	_input->Bind("SnakeLeft", Action(Keyboard::A, ActionType::Released), [this]() {
		SetRotation(-90);
	});
}


Player::~Player()
{
	Helper::Clear(_tail);
	Helper::Clear(_input);
}

Vector2i Player::GetDirection()
{
	return _dir;
}

Input * Player::GetInput()
{
	return _input;
}

list<Entity*> Player::GetTail() const
{
	return _tail;
}

/// <summary>Sets curren tile and position to current tile
/// <para>If hasEaten true, adds tail part, otherwise moves the tail</para>  
/// <para>Rotation updated if isRotated true</para>  
/// </summary>
void Player::SetTile(Tile * tile)
{
	_hasEaten ? AddTail() : MoveTail();	

	Entity::SetTile(tile);
	if (_isRotated)
	{
		_sprite.rotate(_angle);
		_isRotated = false;
	}
}

void Player::SetEaten(const bool value)
{
	_hasEaten = value;
}

bool Player::HasEaten() const
{
	return _hasEaten;
}

/// <summary>Sets rotation angle, updates direction
/// <para>Sets isRotated to true, rotation updated in next SetTile call</para>  
/// </summary>
void Player::SetRotation(const float degrees)
{
	_angle = degrees;

	float angle = (_sprite.getRotation() + degrees) / 180 * M_PI - M_PI / 2;
	_dir = sf::Vector2i((int)std::cos(angle), (int)std::sin(angle));
	_isRotated = true;
}

/// <summary>Updates tail tile from the end to the beginning of the list
/// <para>Sets isRotated to true, rotation updated in next SetTile call</para>  
/// </summary>
void Player::MoveTail()
{
	if (_tail.empty() == false)
	{
		list<Entity*>::iterator it;
		auto end = std::prev(_tail.end());
		for (it = end; it != _tail.begin(); --it) {
			Entity* prevInList = *std::prev(it);
			(*it)->SetTile(prevInList->GetTile());
		}

		_tail.front()->SetTile(_currentTile);
	}
}

void Player::AddTail()
{
	_tail.push_front(new Entity(_currentTile, "Resources/Textures/Body.png"));
}

/// <summary>Checks if body and tail occupies tile</summary>
bool Player::DoesOccupyTile(const Tile* tile) const
{
	if (_currentTile == tile) return true;
	for (auto it = _tail.begin(); it != _tail.end(); ++it)
	{
		if ((*it)->GetTile() == tile)
		{
			return true;
		}
	}
	return false;
}
