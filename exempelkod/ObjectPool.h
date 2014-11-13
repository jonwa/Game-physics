#pragma once

#include "SF_src\Demo.h"
#include <vector>

class ObjectPool : public Demo
{
public:
	typedef std::vector<Object::base_ptr_t> ObjectPool_t;

	template<typename T, typename... Args> 
	void add(Args&&... args)
	{
		T::ptr_t o = T::make(args...);
		pool_.push_back(o);
	}

	void update(DemoHandler* draw)
	{
		for (auto &&obj : pool_)
		{
			obj->update(1 / 60);
			obj->render(*draw);
		}
	}

	const string getName() override
	{
		return "this is the name yo";
	}

	const string getInfo() override
	{
		return "this is the information yo";
	}

private:
	ObjectPool_t pool_;
};