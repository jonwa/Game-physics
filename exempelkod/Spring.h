#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Ball.h"

class Spring : public BaseObject<Spring>
{
public:
	
	static ptr_t make(BaseBall::ptr_t a, BaseBall::ptr_t b, float k, float resting_length, Color color = Color::YELLOW)
	{
		return std::make_shared<Spring>(a, b, k, resting_length, color, this_is_protected());
	}

	Spring(BaseBall::ptr_t a, BaseBall::ptr_t b, float k, float resting_length, Color color, this_is_protected&)
		: a_(a)
		, b_(b)
		, k_(k)
		, resting_length_(resting_length)
		, color_(color)
	{}

	Spring() = delete;
	Spring(const Spring&) = delete;
	Spring& operator=(const Spring&) = delete;

	void try_collision(base_ptr_t other) override
	{

	}

	void render(DemoHandler& demo) const override
	{
		demo.drawLine(vector_to_point(a_->position), vector_to_point(b_->position), color_);
	}

	void update(float dt) override
	{
		Vec_t resting_vec = resting_length_ * ((a_->position() - b_->position()).normalized());

		Vec_t spring_force = ((a_->position() - b_->position()) - resting_vec) * k_;

		a_->force = a_->force() - spring_force;

		b_->force = b_->force() + spring_force;
	}

private:
	BaseBall::ptr_t a_;
	BaseBall::ptr_t b_;
	float k_;
	float resting_length_;
	Color color_;
};


