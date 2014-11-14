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
{}

void VerletIntegration::operator()(BaseBall::ptr_t ball, float delta)
{
	auto inv_mass = 1.f / ball->mass;
	
	auto new_pos = ball->position() * 2 - prev_pos_ + ball->force() * inv_mass * delta * delta;
	prev_pos_ = ball->position();
	ball->position() = new_pos;
}