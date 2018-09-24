#pragma once
#include "Action.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;
using Function = function<void()>;

/// <summary>Class for input binding, unbinding
/// <para>Call <see cref="Input::ProcessEvents"/> for checks</para>  
/// </summary> 
class Input
{
public:

	Input();
	~Input();

	//brief: Binds callback to action under specified name
	void Bind(const string name, const Action& action, const Function& callback);

	//brief: Unbinds callback to action under specified name
	void Unbind(const string name);

	//brief: Check for action and executes needed callback
	void ProcessEvents(Event& event) const;

private:

	unordered_map<string, Action> _actionMap;
	unordered_map<string, Function> _functionMap;
};

