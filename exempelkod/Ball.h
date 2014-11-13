#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Integrations.h"

// Regular
template<typename IntegrationStrategy, template <class> class TimeStepStrategy>
class Ball : public BaseObject<Ball<IntegrationStrategy, TimeStepStrategy>>
{
public:

	static ptr_t make(Vec_t position, Vec_t velocity, float mass, float radius, float elasticy, Color color = Color::WHITE)
	{
		return std::make_shared<Ball<IntegrationStrategy, TimeStepStrategy>>(position, velocity, mass, radius, elasticy, color, this_is_protected());
	}

	Ball(Vec_t position, Vec_t velocity, float mass, float radius, float elasticy, Color color, this_is_protected&)
		: position_(position)
		, velocity_(velocity)
		, acceleration_(Vec_t())
		, mass_(mass)
		, radius_(radius)
		, elasticy_(elasticy)
		, color_(color)
	{}

	Ball() = delete;
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void try_collision(base_ptr_t other) override
	{
		
	}

	void render(DemoHandler& demo) const override
	{
		demo.drawPoint(vector_to_point(position_), color_, radius_);
	}

	void update(float dt) override
	{
		time_step_(position_, velocity_, acceleration_, dt);
	}

private:
	Vec_t position_;
	Vec_t velocity_;
	Vec_t acceleration_;
	float mass_;
	float radius_;
	float elasticy_;
	Color color_;

	TimeStepStrategy<IntegrationStrategy> time_step_;
};

// Static 
class StaticBall : public Ball<StaticIntegration, SimpleTimeStep>
{
public:
	static ptr_t make(Vec_t position, float radius, Color color = Color::GRAY)
	{
		return std::make_shared<StaticBall>(position, radius, color, this_is_protected());
	}

	StaticBall(Vec_t position, float radius, Color color, this_is_protected&)
		: Ball(position, Vec_t(), 0.f, radius, 1.0f, color, this_is_protected())
	{}
};
