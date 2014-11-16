#pragma once 

#include <memory>
#include "Eigen/Core"

class BaseBall;

struct SmallerTimeStep
{
	SmallerTimeStep(float dt)
	:buffered_delta_(0.f)
	, step_delta_(dt)
	{}

	template<typename T>
	void operator()(float delta, T step_function)
	{
		buffered_delta_ += delta;

		while (buffered_delta_ >= step_delta_)
		{
			step_function(step_delta_);
			buffered_delta_ -= step_delta_;
		}
	}

private:
	float buffered_delta_;
	float step_delta_;
};

struct SimpleTimeStep
{
	template<typename T>
	void operator()(float delta, T step_function)
	{
		step_function(pos, vel, acc, delta);
	}
};

struct StaticIntegration
{
	StaticIntegration(BaseBall& ball)
	{}

	void operator()(std::shared_ptr<BaseBall> ball, float delta)
	{
	}
};

struct EulerIntegration
{
	EulerIntegration(BaseBall& ball){}
	void operator()(std::shared_ptr<BaseBall> ball, float delta);
};

struct VerletIntegration
{
	VerletIntegration(BaseBall& ball);
	void operator()(std::shared_ptr<BaseBall> ball, float delta);

private:
	Eigen::Vector3f prev_pos_;
	float step_;
	Eigen::Vector3f vel_;
};


