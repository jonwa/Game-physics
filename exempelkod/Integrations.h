#pragma once 

template <typename IntegrationStrategy>
struct SmallerTimeStep
{
	SmallerTimeStep()
	:buffered_delta_(0.f)
	, step_delta_(0.001f)
	{}

	void operator()(Object::Vec_t& pos, Object::Vec_t& vel, Object::Vec_t& acc, float delta)
	{
		buffered_delta_ += delta;

		while (buffered_delta_ >= step_delta_)
		{
			integration_(pos, vel, acc, step_delta_);
			buffered_delta_ -= step_delta_;
		}
	}

private:
	float buffered_delta_;
	float step_delta_;
	IntegrationStrategy integration_;
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

template <typename IntegrationStrategy>
struct SimpleTimeStep
{
	void operator()(Object::Vec_t& pos, Object::Vec_t& vel, Object::Vec_t& acc, float delta)
	{
		integration_(pos, vel, acc, delta);
	}

private:
	IntegrationStrategy integration_;
};

struct StaticIntegration
{
	void operator()(Object::Vec_t& pos, Object::Vec_t& vel, Object::Vec_t& acc, float delta)
	{

	}
};