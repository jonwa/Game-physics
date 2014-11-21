#include "Integrations.h"
#include "Ball.h"

void EulerIntegration::operator()(BaseBall::ptr_t ball, float delta)
{
	auto old_pos = ball->position();
	ball->position() += ball->velocity() * delta;
	ball->velocity() += ball->acceleration() * delta;
}

VerletIntegration::VerletIntegration(BaseBall& ball)
	: prev_pos_(ball.position())
	, step_(0.f)
	, vel_(Object::Vec_t::Zero())
{
	ball.velocity.set_setter([&](Object::Vec_t& c_v, const Object::Vec_t& i_v) -> Object::Vec_t&
	{ 
		auto old_pos = ball.position() - i_v * step_;
		return c_v = i_v; 
	});

	ball.velocity.set_getter([&](Object::Vec_t& v) -> Object::Vec_t&
	{
		vel_ = (ball.position() - prev_pos_) * (1.f / step_);
		return vel_;
	});

	ball.velocity.set_const_getter([&](const Object::Vec_t& v) -> const Object::Vec_t&
	{
		vel_ = (ball.position() - prev_pos_) * (1.f / step_);
		return vel_;
	});
}

void VerletIntegration::operator()(BaseBall::ptr_t ball, float delta)
{
	step_ = delta;

	auto inv_mass = 1.f / ball->mass;
	
	Object::Vec_t new_pos = ball->position() * 2 - prev_pos_ + ball->force() * inv_mass * step_ * step_;
	prev_pos_ = ball->position();
	ball->position = new_pos;
}