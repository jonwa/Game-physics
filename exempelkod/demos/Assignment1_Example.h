#pragma once

#include "Assignment1_Ball.h"

namespace Assignment1
{
	class Example : public Demo
	{
	public:
		Example(Ball::Vec_t pos, Ball::Vec_t vel, float mass, float radius, float elasticy, float ground_height, float g);

		void update(DemoHandler* draw);
		const string getName() override;
		const string getInfo() override;
	private:
		void reset();

		Ball ball_;
		Ball::Vec_t pos_, vel_;
		float mass_, radius_, elasticy_, ground_height_, g_;

	};
}