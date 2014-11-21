#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Property.h"

class BaseBall : public BaseObject <BaseBall>
{
public:
	Property<Vec_t> position;
	Property<Vec_t> velocity;
	Property<Vec_t> force;
	Property<Vec_t> acceleration;
	Property<float> radius;
	Property<float> elasticy;
	Property<float> mass;
	Property<float> g;

protected:
	Color color_;

	BaseBall(Vec_t position_, Vec_t velocity_, float mass_, float radius_, float elasticy_, Color color, float g_, this_is_protected&)
		: color_(color)
	{
		position = position_;
		velocity = velocity_;
		acceleration = Vec_t::Zero();
		force = Vec_t::Zero();
		mass = mass_;
		radius = radius_;
		elasticy = elasticy_;
		g = g_;
	}
};

template<typename IntegrationStrategy>
class Ball : public BaseBall
{
public:

	static ptr_t make(Vec_t position_, Vec_t velocity_, float mass, float radius, float elasticy, Color color = Color::WHITE, float g = 9.8f)
	{
		return std::make_shared<Ball<IntegrationStrategy>>(position_, velocity_, mass, radius, elasticy, color, g, this_is_protected());
	}

	Ball(Vec_t position_, Vec_t velocity_, float mass, float radius, float elasticy, Color color, float g, this_is_protected&)
		: BaseBall(position_, velocity_, mass, radius, elasticy, color, g, this_is_protected())
		, integration_(*this)
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
		
	}

	void late_update(float dt) override
	{
		apply_gravity(g, dt);
		integration_(as<BaseBall>(), dt);
		force = Vec_t::Zero();
	}

private:
	void apply_gravity(float g, float dt)
	{
		force = force() + Vec_t(0.f, -g * mass, 0.f);

		float inv_mass = 1.f / mass;
		acceleration = force() * inv_mass;
	}

	IntegrationStrategy integration_;
};

class StaticBall : public Ball<StaticIntegration>
{
public:
	static ptr_t make(Vec_t position_, float radius_, Color color = Color::WHITE)
	{
		return std::make_shared<StaticBall>(position_, radius_, color, this_is_protected());
	}

	StaticBall(Vec_t position_, float radius_, Color color, this_is_protected&)
		: Ball(position_, Vec_t::Zero(), 0.f, radius_, 1.0f, color, 0.f, this_is_protected())
	{}
};
