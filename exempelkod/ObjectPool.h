#pragma once

#include "SF_src\Demo.h"
#include <vector>
#include "Timer.h"

template<typename TimeStepStategy>
class ObjectPool : public Demo
{
public:
	typedef std::vector<Object::base_ptr_t> ObjectPool_t;

	ObjectPool(TimeStepStategy time_step)
		: time_step_(time_step)
		, first_update_(true)
	{
	}

	template<typename T, typename... Args> 
	int add(Args&&... args)
	{
		T::ptr_t o = T::make(args...);
		pool_.push_back(o);
		return pool_.size() - 1;
	}

	template<typename T>
	typename T::ptr_t get(int id)
	{
		return pool_[id]->as<T>();
	}

	void update(DemoHandler* draw)
	{
		if (!first_update_)
		{
			auto elapsed = static_cast<float>(timer_.elapsed_milliseconds());
			float dt = elapsed / 1000.f;

			timer_.start();
			time_step_(dt, [this](float dt){
				for (auto &&obj : pool_)
				{
					obj->update(dt);

					for (auto &&other : pool_)
					{
						if (obj != other)
						{
							obj->try_collision(other);
						}
					}
				}
			});

			for (auto &&obj : pool_)
			{
				obj->render(*draw);
			}
		}
		first_update_ = false;
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
	Timer timer_;
	bool first_update_;
	TimeStepStategy time_step_;
};