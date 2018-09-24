#include "pch.h"
#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

/// <summary>Binds action and callback at specified name
/// <para>If already existent, throws exeption</para>  
/// </summary>
void Input::Bind(const string name, const Action& action, const Function& callback)
{
	if (_actionMap.count(name) > 0 || _functionMap.count(name))
		throw std::runtime_error("Error, input with the same name already exist!");

	_actionMap.emplace(name, action);
	_functionMap.emplace(name, callback);
}

/// <summary>Unbinds action and callback at specified name
/// <para>If non existent, throws exeption</para>  
/// </summary> 
void Input::Unbind(const string name)
{
	if (_actionMap.count(name) > 0 && _functionMap.count(name) > 0)
	{
		_actionMap.erase(name);
		_functionMap.erase(name);
	}
	else throw std::runtime_error("Input doesn't exist!");
}

/// <summary>Call on update for processing input detection</summary> 
void Input::ProcessEvents(Event& event) const
{
	for (auto& action : _actionMap)
	{
		if (action.second.IsCalled(event))
		{
			_functionMap.at(action.first)();
		}
	}
}