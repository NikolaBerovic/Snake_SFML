#pragma once
#include <list>

using namespace std;

class Helper
{
public:
	Helper() = delete;
	Helper(const Helper&) = delete;
	Helper& operator=(const Helper&) = delete;

	//brief: Deletes all pointed objects, clears list of pointers
	template <typename T>
	static bool Clear(list<T*>& cleanList);

	//brief: Deletes pointed object, sets pointer to nullptr
	template <typename T>
	static bool Clear(T*& object);
};

template<typename T>
inline bool Helper::Clear(list<T*>& cleanList)
{
	while (!cleanList.empty()) delete cleanList.front(), cleanList.pop_front();
	return true;
}

template<typename T>
inline bool Helper::Clear(T *& object)
{
	delete object;
	object = nullptr;
	return true;
}
