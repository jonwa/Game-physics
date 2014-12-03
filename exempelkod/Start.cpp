
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SF_src/OpenGLStuff.h"
#include "SF_src/DemoHandler.h"
#include "demos/Assignment1_Ball.h"
#include "demos/Assignment1_Example.h"
#include "Object.h"
#include "Integrations.h"
#include "Ball.h"
#include "Plane.h"
#include "Spring.h"
#include "ObjectPool.h"
#include "ConfigLoader.h"

using namespace std;

/*
 The entry point for the program.
 You need to add your demos before you call start.
 */
int main(int argc, char* argv[])
{
	std::string example_object = "1";
	auto pos = Assignment1::Ball::Vec_t(5, 8, 0);
	auto vel = Assignment1::Ball::Vec_t(0, 0, 0);
	float mass = 3.f;
	float radius = 0.5f;
	float elasticy = 0.9f;

	ObjectPool<SmallerTimeStep> pool(0.001f);
	ConfigLoader::load_content("advanced_config.json", example_object, pool);
	
	pool.add_update_callback([&pool](DemoHandler& d)
	{
		auto spring = pool.get<Spring>("spring");
		if (spring == nullptr)
		{
			return;
		}
		if (d.keyTyped('a'))
		{
			spring->enabled = !spring->enabled;
		}
	});
	
	pool.add_update_callback([&pool, &example_object](DemoHandler& d)
	{
		if (d.keyTyped('r'))
		{
			pool.clear();
			ConfigLoader::load_content("advanced_config.json", example_object, pool);
		}

		for (char i = 1; i <= 4; ++i)
		{
			/* WHADAP */
			if (d.keyTyped(i + '0'))
			{
				pool.clear();
				example_object = std::string({ static_cast<char>(i + '0') });
				ConfigLoader::load_content("advanced_config.json", example_object, pool);
			}
		}
	});

	DemoHandler::inst().addDemo(&pool);

	start(argc,argv);//function in "OpenGLStuff"s
	return 0;
};

/*
 (c)2012 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
*/