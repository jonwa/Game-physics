#pragma once

#include "picojson.h"
#include "ObjectPool.h"
#include "Object.h"
#include "Ball.h"
#include "Integrations.h"
#include "Plane.h"
#include "Spring.h"
#include <algorithm>
#include <ostream>

class ConfigLoader
{
public:
	template<typename T>
	static void load_content(const std::string& file_name, const std::string& config_exampe_object, ObjectPool<T>& pool)
	{
		std::ifstream file(file_name);
		std::string err;
		picojson::value loaded;
		err = picojson::parse(loaded, file);

		picojson::value v = loaded.get(config_exampe_object);

		std::cout << err << std::endl;

		for (auto&& key : v.get<picojson::object>())
		{
			load_object<T>(key.first, key.second, pool);
		}
	}

private:

	template<typename T>
	static int load_object(const std::string& id, const picojson::value& info, ObjectPool<T>& pool)
	{
		auto position = to_vector(info.get("position"));
		auto velocity = to_vector(info.get("velocity"));
		auto acceleration = to_vector(info.get("acceleration"));
		auto force = to_vector(info.get("force"));
		auto mass = to_float(info.get("mass"));
		auto radius = to_float(info.get("radius"));
		auto elasticity = to_float(info.get("elasticity"));
		auto color = to_color(info.get("color"));
		auto k = to_float(info.get("spring_constant"));
		auto g = to_float(info.get("g"), 9.8f);
		auto normal = to_vector(info.get("normal"));
		auto friction_factor = to_float(info.get("friction_factor"));
		auto resting_length = to_float(info.get("resting_length"));

		auto type = to_string(info.get("type"));

		if (type == "ball")
		{
			return pool.add<Ball<EulerIntegration>>(id, position, velocity, mass, radius, elasticity, color, g);
		}
		if (type == "static_ball")
		{
			return pool.add<StaticBall>(id, position, radius, color);
		}
		if (type == "spring")
		{
			auto obj_1 = info.get("ball_1");
			auto obj_2 = info.get("ball_2");

			auto ball_1_ptr = load_object(id + "::__ball_1", obj_1, pool);
			auto ball_2_ptr = load_object(id + "::__ball_2", obj_2, pool);
			return pool.add<Spring>(id, pool.get<BaseBall>(ball_1_ptr), pool.get<BaseBall>(ball_2_ptr), k, resting_length, color);
		}
		if (type == "plane")
		{
			return pool.add<Plane>(id, normal, position, friction_factor, color);
		}
		return -1;
	}

private: // converters
	static Object::Vec_t to_vector(picojson::value val)
	{
		Object::Vec_t old = Object::Vec_t::Zero();

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

	static Color to_color(picojson::value val)
	{
		Color old = Color::WHITE;
		
		if (val.is<std::string>())
		{
			auto str = val.get<std::string>();
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			if (str == "white")
			{
				old = Color::WHITE;
			}
			else if (str == "red")
			{
				old = Color::RED;
			}
			else if (str == "blue")
			{
				old = Color::BLUE;
			}
			else if (str == "black")
			{
				old = Color::BLACK;
			}
			else if (str == "green")
			{
				old = Color::GREEN;
			}
			else if (str == "gray")
			{
				old = Color::GRAY;
			}
			else if (str == "yellow")
			{
				old = Color::YELLOW;
			}
			else if (str == "cyan")
			{
				old = Color::CYAN;
			}
			else if (str == "pink")
			{
				old = Color::PINK;
			}
		}
		return old;
	}

	static float to_float(picojson::value val, float def = 0.f)
	{
		if (val.is<double>())
		{
			def = val.get<double>();
		}
		return def;
	}

	static int to_int(picojson::value val, int def = 0)
	{
		if (val.is<int>())
		{
			def = val.get<int>();
		}
		return def;
	}

	static std::string to_string(picojson::value val, std::string def = std::string())
	{
		if (val.is<std::string>())
		{
			def = val.get<std::string>();
		}
		return def;
	}
};