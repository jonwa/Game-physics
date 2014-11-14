#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Ball.h"

class Plane : public BaseObject<Plane> 
{
public:
	static ptr_t Plane::make(Vec_t normal, Vec_t position, float friction_factor, Color color = Color::PINK)
	{
		return std::make_shared<Plane>(normal, position, friction_factor, color, this_is_protected());
	}
	
	Plane(Vec_t normal, Vec_t position, float friction_factor, Color color, this_is_protected&)
		: normal_(normal)
		, position_(position)
		, friction_factor_(friction_factor)
		, color_(color)
	{}

	Plane() = delete;
	Plane(const Plane&) = delete;
	Plane& operator=(const Plane&) = delete;

	void try_collision(base_ptr_t other) override
	{
		if (other->is<BaseBall>())
		{
			do_try_collision(other->as<BaseBall>());
		}
	}

	void render(DemoHandler& demo) const override
	{
		demo.drawPlane(vector_to_point(position_), vector_to_point(normal_), color_);
	}

	void update(float dt) override
	{
		
	}

private:
	void do_try_collision(BaseBall::ptr_t ball)
	{
		float vrel = normal_.dot(ball->velocity());

		Vec_t p_q = ball->position() - position_;
		float project = p_q.dot(normal_);

		float penetration = ball->radius - project;

		// detected collision
		if (penetration >= 0)
		{
			// moving towards the plane with vel
			if (vrel < -1)
			{
				Vec_t new_velocity = ball->velocity() - normal_ * (1 + ball->elasticy()) * vrel;
				ball->velocity() = new_velocity;
			}
			// resting contact
			else if (vrel < 1)
			{
				Vec_t move_up = normal_ * penetration;
				ball->position() += move_up;
				ball->velocity() -= normal_ * vrel;
				
				ball->force() += (ball->velocity() * -10 * ball->mass * friction_factor_);
			}
		}
	}

private:
	Vec_t position_;
	Vec_t normal_;
	float friction_factor_; 
	Color color_;
};