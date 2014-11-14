
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

	// planes
	pool.add<Plane>(Plane::Vec_t(0.f, 1.f, 0.f), Plane::Vec_t(0.f, 0.f, 0.f), 0.99f); //ground
	pool.add<Plane>(Plane::Vec_t(1.f, 0.f, 0.f), Plane::Vec_t(0.f, 0.f, 0.f), 0.2f); //left
	pool.add<Plane>(Plane::Vec_t(-1.f, 0.f, 0.f), Plane::Vec_t(10.f, 0.f, 0.f), 0.97f); //right

	// balls
	int dynamic_id = pool.add<Ball<VerletIntegration>>(pos, vel, mass, radius, elasticy);
	int static_id = pool.add<StaticBall>(StaticBall::Vec_t(5, 8, 0), radius);
	
	// springs
	auto a = pool.get<BaseBall>(dynamic_id);
	auto b = pool.get<StaticBall>(static_id);
	pool.add<Spring>(a, b, .2f);

	DemoHandler::inst().addDemo(&pool);
	start(argc,argv);//function in "OpenGLStuff"s
	return 0;
};

/*
 (c)2012 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
