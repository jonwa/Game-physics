#pragma once 



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

struct EulerIntegration
{
	void operator()(Object::Vec_t& pos, Object::Vec_t& vel, Object::Vec_t& acc, float delta)
	{
		auto old_pos = pos;
		pos += vel * delta;
		vel += acc * delta;
	}
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
	void operator()(Object::Vec_t& pos, Object::Vec_t& vel, Object::Vec_t& acc, float delta)
	{

	}
};