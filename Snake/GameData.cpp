#include "pch.h"
#include "GameData.h"

Resource<Texture> GameData::Textures;
Resource<Font> GameData::Fonts;
GameState GameData::State = GameState::Idle;