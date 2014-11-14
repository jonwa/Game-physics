#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Integrations.h"

template<typename T>
class Property
{
	T value;
public:
	T& operator = (const T &v){ return value = v; }
	operator const T& () const{ return value; }
	operator T& () { return value; }
	const T& operator()() const{ return value; }
	T& operator()() { return value; }
	Property(const T& val)
		:value(val)
	{}
};

class BaseBall : public BaseObject < BaseBall >
{
public:
	Property<Vec_t> position;
	Property<Vec_t> velocity;
	Property<Vec_t> force;
	Property<float> radius;
	Property<float> elasticy;
	Property<float> mass;

protected:
	Property<Vec_t> acceleration;

	Color color_;

	BaseBall(Vec_t position_, Vec_t velocity, float mass_, float radius_, float elasticy_, Color color, this_is_protected&)
		: position(position_)
		, velocity(velocity)
		, acceleration(Vec_t::Zero())
		, force(Vec_t::Zero())
		, mass(mass_)
		, radius(radius_)
		, elasticy(elasticy_)
		, color_(color)
	{}

};

// Regular
template<typename IntegrationStrategy>
class Ball : public BaseBall
{
public:

	static ptr_t make(Vec_t position_, Vec_t velocity_, float mass, float radius, float elasticy, Color color = Color::WHITE)
	{
		return std::make_shared<Ball<IntegrationStrategy>>(position_, velocity_, mass, radius, elasticy, color, this_is_protected());
	}

	Ball(Vec_t position_, Vec_t velocity_, float mass, float radius, float elasticy, Color color, this_is_protected&)
		: BaseBall(position_, velocity_, mass, radius, elasticy, color, this_is_protected())
	{}

	Ball() = delete;
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void try_collision(base_ptr_t other) override
	{
		
	}

	void render(DemoHandler& demo) const override
	{
		demo.drawPoint(vector_to_point(position), color_, radius);
	}

	void update(float dt) override
	{
		force = Vec_t::Zero();
		force() += Vec_t(0.f, -10.f * mass, 0.f);
		float inv_mass = 1.f / mass;
		acceleration = force() * inv_mass;
		integration_(position, velocity, acceleration, dt);
	}

private:
	IntegrationStrategy integration_;
};

// Static 
class StaticBall : public Ball<StaticIntegration>
{
public:
	static ptr_t make(Vec_t position_, float radius_, Color color = Color::GRAY)
	{
		return std::make_shared<StaticBall>(position_, radius_, color, this_is_protected());
	}

	StaticBall(Vec_t position_, float radius_, Color color, this_is_protected&)
		: Ball(position_, Vec_t::Zero(), 0.f, radius_, 1.0f, color, this_is_protected())
	{}
};
