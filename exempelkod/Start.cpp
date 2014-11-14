
#include <iostream>
#include <fstream>
#include <string>
#include "SF_src/OpenGLStuff.h"
#include "SF_src/DemoHandler.h"
#include "demos/Assignment1_Ball.h"
#include "demos/Assignment1_Example.h"
#include "Object.h"
#include "Ball.h"
#include "Plane.h"
#include "ObjectPool.h"
#include "Integrations.h"

using namespace std;
/*
 The entry point for the program.
 You need to add your demos before you call start.
 */
int main(int argc, char* argv[])
{
	auto pos = Assignment1::Ball::Vec_t(4, 8, 0);
	auto vel = Assignment1::Ball::Vec_t(2, 0, 0);
	float mass = 0.5f;
	float radius = 0.5f;
	float elasticy = 0.9f;

	ObjectPool<SmallerTimeStep> pool(0.001f);


	pool.add<Plane>(Plane::Vec_t(0.f, 1.f, 0.f), Plane::Vec_t(0.f, 0.f, 0.f), 0.99f); //ground
	pool.add<Plane>(Plane::Vec_t(1.f, 0.f, 0.f), Plane::Vec_t(0.f, 0.f, 0.f), 0.2f); //left
	pool.add<Plane>(Plane::Vec_t(-1.f, 0.f, 0.f), Plane::Vec_t(10.f, 0.f, 0.f), 0.97f); //right


	int ball_id = pool.add<Ball<EulerIntegration>>(pos, vel, mass, radius, elasticy, Color::BLUE);


	//pool.get<BaseBall>(ball_id);
	DemoHandler::inst().addDemo(&pool);

	start(argc,argv);//function in "OpenGLStuff"s
	
	return 0;
};

/*
 (c)2012 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
