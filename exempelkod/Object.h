#pragma once
#include "SF_src\DemoHandler.h"
#include <memory>
#include "Eigen/Core"

class Object : std::enable_shared_from_this<Object>
{
public:
	typedef std::shared_ptr<Object> base_ptr_t;
	typedef Eigen::Vector3f Vec_t;

	virtual ~Object() = default;

	virtual void try_collision(base_ptr_t other) = 0;
	virtual void render(DemoHandler& demo) const = 0;
	virtual void update(float dt) = 0;

	template<typename T>
	bool is()
	{
		return as<T>() != nullptr;
	}

	template<typename T>
	typename T::ptr_t as()
	{ 
		return std::dynamic_pointer_cast<T>(get_this());
	}

	Point vector_to_point(const Vec_t& vec) const
	{
		return Point(vec.x(), vec.y(), vec.z());
	}

protected:
	base_ptr_t get_this()
	{
		return shared_from_this();
	}

	struct this_is_protected {};
};

template<typename T>
class BaseObject : public Object
{
public:
	typedef std::shared_ptr<T> ptr_t;
	
	virtual ~BaseObject() = default;
};