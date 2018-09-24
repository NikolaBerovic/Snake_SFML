#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string> 
#include <memory> 

using namespace std;

//Template class for resource management
template<typename RESOURCE>
class Resource
{
public:
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;

	Resource() = default;

	//brief: Loads resource and maps it
	const RESOURCE& Load(const string path);

private:
	unordered_map<string, unique_ptr<RESOURCE>> _map;
};

/// <summary>Loads resource, maps it and returns reference to it
/// <para>If exstant, returns mapped resource</para>  
/// </summary>
template<typename RESOURCE>
inline const RESOURCE& Resource<RESOURCE>::Load(const string path)
{
	
	if (_map.count(path) == 0)
	{
		unique_ptr<RESOURCE> ptr(new RESOURCE);

		if (not ptr->loadFromFile(path))
			throw std::runtime_error("Error, wrong path or file doesn't exist");
			
		ptr->loadFromFile(path);
		_map.emplace(path, std::move(ptr));
	}
	return *_map.at(path);
}