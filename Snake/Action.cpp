#include "pch.h"
#include "Action.h"


Action::Action(const Keyboard::Key& key, const ActionType type)
{
	_key = key;

	switch (type)
	{
	case ActionType::Pressed:
		_type = Event::EventType::KeyPressed;
		break;
	case ActionType::Released:
		_type = Event::EventType::KeyReleased;
		break;
	}
}

Action::Action(const Mouse::Button& button, const ActionType type)
{
	_key = button;

	switch (type)
	{
	case ActionType::Pressed:
		_type = Event::EventType::MouseButtonPressed;
		break;
	case ActionType::Released:
		_type = Event::EventType::MouseButtonReleased;
		break;
	}
}

/// <summary>Check if action key is pressed
/// <para>Call in ProcessEvent with passed event</para>  
/// </summary>
bool Action::IsCalled(const Event& event)const
{
	if (event.type == _type)
	{
		if (event.key.code == _key)
		{
			return true;
		}
	}
	
	return false;
}