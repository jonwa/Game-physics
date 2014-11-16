#pragma once

#include "SF_src\Demo.h"
#include <vector>
#include "Timer.h"
#include <functional>
#include <map>

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
	int add(std::string id, Args&&... args)
	{
		T::ptr_t o = T::make(args...);
		pool_.push_back(o);
		pool_ids_.insert(std::make_pair(id, o));
		return pool_.size() - 1;
	}

	template<typename T>
	auto get(int id)-> typename T::ptr_t
	{
		return pool_[id]->as<T>();
	}

	template<typename T>
	auto get(const std::string& id)-> typename T::ptr_t
	{
		return pool_ids_[id]->as<T>();
	}

	void update(DemoHandler* draw)
	{			
		if (!first_update_)
		{
			for (auto& c: callbacks_)
			{
				c(*draw);
			}

			auto elapsed = static_cast<float>(timer_.elapsed_milliseconds());
			float dt = elapsed / 1000.f;

			timer_.start();
			time_step_(dt, [this](float dt){
				for (auto &&obj: pool_)
				{
					if (obj->enabled)
					{
						obj->update(dt);
					
						for (auto &&other : pool_)
						{
							if (obj != other && other->enabled)
							{
								obj->try_collision(other);
							}
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
		return "Assignment 1: Spring";
	}

	const string getInfo() override
	{
		return "Use advanced_config.json to configurate the environment.\nRead the READ_ME.txt for instructions!\nPress 'a' to release the spring!!";
	}

	void add_update_callback(std::function<void(DemoHandler&)> c_b)
	{
		callbacks_.push_back(c_b);
	}
private:
	ObjectPool_t pool_;
	std::map<std::string, Object::base_ptr_t> pool_ids_;
	Timer timer_;
	bool first_update_;
	TimeStepStategy time_step_;
	std::vector<std::function<void(DemoHandler&)>> callbacks_;
};