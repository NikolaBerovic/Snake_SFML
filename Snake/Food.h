#pragma once
#include "Entity.h"

class Food : public Entity
{
public:

	Food(const Food&) = delete;
	Food& operator=(const Food&) = delete;

	Food(Tile* tile);
	~Food();

};

