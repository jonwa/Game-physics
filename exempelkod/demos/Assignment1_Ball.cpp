#include "Assignment1_ball.h"

namespace Assignment1
{
	Ball::Ball(Vec_t pos, Vec_t vel, float mass, float radius, float elasticy, float ground_height)
		: pos_(pos)
		, vel_(vel)
		, acc_(Vec_t::Zero())
		, mass_(mass)
		, radius_(radius)
		, buffered_delta_(0.f)
		, elasticy_(elasticy)
		, ground_height_(ground_height + radius)
	{
	}

	void Ball::update(float delta)
	{
		float step_delta = 0.001f;
		buffered_delta_ += delta;

		while (buffered_delta_ >= step_delta)
		{
			step(step_delta);
			buffered_delta_ -= step_delta;
		}
	}

	void Ball::clear_acceleration()
	{
		acc_ = Vec_t::Zero();
	}

	void Ball::add_acceleration(Vec_t acc)
	{
		acc_ += acc;
	}

	void Ball::render(DemoHandler &demo) const
	{
		demo.drawPoint(Point(pos_.x(), pos_.y(), pos_.z()), Color::WHITE, radius_);
	}

	void Ball::step(float delta)
	{
		auto old_pos = pos_;
		pos_ += vel_ * delta;
		vel_ += acc_ * delta;

		handle_ground(old_pos, pos_);
	}

	void Ball::handle_ground(Vec_t pos_before, Vec_t pos_after)
	{
		float left_wall = 0.f + radius_;
		float right_wall = 10.f - radius_;

		if (pos_after.y() < ground_height_)
		{
			reflect_vector(pos_before, pos_after, Vec_t(0, ground_height_, 0), Vec_t(0, 1, 0));
		}
		if (pos_after.x() < left_wall)
		{
			reflect_vector(pos_before, pos_after, Vec_t(left_wall, 0, 0), Vec_t(1, 0, 0));
		}
		if (pos_after.x() > right_wall)
		{
			reflect_vector(pos_before, pos_after, Vec_t(right_wall, 0, 0), Vec_t(-1, 0, 0));
		}
	}


	void Ball::reflect_vector(Vec_t pos_before, Vec_t pos_after, Vec_t plane_coord, Vec_t plane_normal)
	{
		/* position */
		/* read: http://stackoverflow.com/questions/5666222/3d-line-plane-intersection */
		Vec_t u = pos_after - pos_before;
		Vec_t w = pos_before - plane_coord;
		auto dot = plane_normal.dot(u);

		if (abs(dot) > numeric_limits<float>::epsilon())
		{
			auto fac = plane_normal.dot(w) / dot;
			u *= fac;

			Vec_t intersect = pos_before + u;
			Vec_t below_ground = pos_after - intersect;
			below_ground.x() *= -plane_normal.x();
			below_ground.y() *= -plane_normal.y();
			below_ground.z() *= -plane_normal.z();
			Vec_t reflection = intersect + below_ground;
			pos_ = reflection;

			/* velocity */
			auto some_value = plane_normal.dot(vel_);
			auto new_vel = vel_ - plane_normal*(1 + elasticy_) * some_value;
			vel_ = new_vel * 0.99f;
		}
	}
}