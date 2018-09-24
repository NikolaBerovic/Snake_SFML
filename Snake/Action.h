#include <SFML/Window/Event.hpp>
#include "Enum.h"
using namespace sf;

/// <summary>Wrapper class for SFML inputs </summary>
class Action
{
public:
	
	Action(const Keyboard::Key& key, const ActionType type);
	Action(const Mouse::Button& button, const ActionType type);

	//brief: Check if action is pressed
	bool IsCalled(const Event& even)const;

private:

	int _type;
	int _key;

};
