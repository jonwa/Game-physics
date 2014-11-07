#include <fstream>

#include "Assignment1_Example.h"
#include "../picojson.h"

namespace Assignment1
{
	Example::Example(Ball::Vec_t pos, Ball::Vec_t vel, float mass, float radius, float elasticy, float ground_height, float g)
		: ball_(pos, vel, mass, radius, elasticy, ground_height)
		, pos_(pos)
		, vel_(vel)
		, mass_(mass)
		, radius_(radius)
		, elasticy_(elasticy)
		, ground_height_(ground_height)
		, g_(g)
	{
		reset();
	}

	void Example::update(DemoHandler* draw)
	{
		if (draw->keyTyped('r'))
		{
			reset();
		}

		ball_.clear_acceleration();
		ball_.add_acceleration(Ball::Vec_t(0, -g_, 0));

		ball_.update(1.f / 60.f);
		ball_.render(*draw);
	}

	const string Example::getName()
	{
		return "Assignment 1: Bounce and Friction";
	}

	const string Example::getInfo()
	{
		return "";
	}

	void Example::reset()
	{
		std::ifstream file("config.json");
		std::string err;
		picojson::value v;
		err = picojson::parse(v, file);

		auto to_vector = [](Ball::Vec_t old, picojson::value val) -> Ball::Vec_t
		{
			if (val.is<picojson::array>())
			{
				auto arr = val.get<picojson::array>();
				if (arr.size() == 3)
				{
					old[0] = arr[0].get<double>();
					old[1] = arr[1].get<double>();
					old[2] = arr[2].get<double>();
				}
			}
			return old;
		};

		auto to_float = [](float old, picojson::value val) -> float
		{
			if (val.is<double>())
			{
				old = val.get<double>();
			}
			return old;
		};

		if (err.empty())
		{
			pos_ = to_vector(pos_, v.get("pos"));
			vel_ = to_vector(vel_, v.get("vel"));
			mass_ = to_float(mass_, v.get("mass"));
			radius_ = to_float(mass_, v.get("radius"));
			elasticy_ = to_float(mass_, v.get("elasticy"));
			g_ = to_float(mass_, v.get("g"));
			
		}
		ball_ = Ball(pos_, vel_, mass_, radius_, elasticy_, ground_height_);
	}
}