#pragma once
#include "SF_src\DemoHandler.h"
#include <memory>
#include "Eigen/Core"

class Object
{
public:
	typedef std::shared_ptr<Object> base_ptr_t;
	typedef Eigen::Vector3f Vec_t;

	virtual ~Object() = default;

	virtual void try_collision(base_ptr_t other) = 0;
	virtual void render(DemoHandler& demo) const = 0;
	virtual void update(float dt) = 0;

	template<typename T>
	bool is() const
	{
		return dynamic_cast<T>(this) != nullptr;
	}

	Point vector_to_point(const Vec_t& vec) const
	{
		return Point(vec.x(), vec.y(), vec.z());
	}
	
protected:
	struct this_is_protected {};
};

template<typename T>
class BaseObject : public Object, std::enable_shared_from_this<BaseObject<T>>
{
public:
	typedef std::shared_ptr<T> ptr_t;
	
	virtual ~BaseObject() = default;

	ptr_t get_this() const
	{
		return get_shared_from_this();
	}
};