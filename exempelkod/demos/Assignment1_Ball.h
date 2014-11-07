#pragma once

#include "../SF_src/Demo.h"
#include "../SF_src/DemoHandler.h"
#include "../SF_src/MyVector.h"
#include <cmath>
#include <string>
#include <sstream>

#include <Eigen\Core>


namespace Assignment1
{
	class Ball
	{
	public:
		typedef Eigen::Vector3f Vec_t;

		Ball(Vec_t pos, Vec_t vel, float mass, float radius, float elasticy, float ground_height);

		void update(float delta);
		void clear_acceleration();
		void add_acceleration(Vec_t acc);
		
		void render(DemoHandler &demo) const;

	private:
		void step(float delta);
		void handle_ground(Vec_t pos_before, Vec_t pos_after);
		void reflect_vector(Vec_t pos_before, Vec_t pos_after, Vec_t plane_coord, Vec_t plane_normal);

		Vec_t pos_, vel_, acc_;
		float mass_, radius_, buffered_delta_, ground_height_, elasticy_;
	};
}