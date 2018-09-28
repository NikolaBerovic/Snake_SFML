# Snake_SFML
Object oriented snake game written in C++ with SFML.
Code written in game engine pattern.

![alt text](http://www.mediafire.com/convkey/2f39/j2b6xgxdq40zudvzg.jpg)

## Prerequisites
- SFML 2.5+ https://www.sfml-dev.org/download/sfml/2.5.0/
- Visual Studio 2017 https://visualstudio.microsoft.com/downloads/

## Installation
- Clone this repo
```
  git clone https://github.com/NikolaBerovic/Snake_SFML.git
```
- Open Snake.sln with Visual Studio 2017
- Configure Visual Studio with libraries downloaded from SFML site
- Copy and paste SFML .dll in Snake folder
- Run in Visual Studio (X64 or X86 depending of downloaded SFML)

## Usage
Default parameters already set, if custom needed:
1. In GameData.h set preferred tile size and number of tiles depending of axis
```
static const int DEF_TILE_SIZE = 32;
static const int DEF_TILE_X = 16;
static const int DEF_TILE_Y = 12;
```
2. For any new ingame entity use Entity class as parent
3. For any new Entity derved class add it to list in World class
```
list<Entity*>  _entities;
```

## Licence
- Free to Use
