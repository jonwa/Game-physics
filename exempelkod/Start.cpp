
#include <iostream>
#include <fstream>
#include <string>
#include "SF_src/OpenGLStuff.h"
#include "SF_src/DemoHandler.h"
#include "demos/Assignment1_Ball.h"
#include "demos/Assignment1_Example.h"


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
	float ground_height = 0.f;
	float g = 9.82f;

	

	DemoHandler::inst().addDemo(new Assignment1::Example(pos, vel, mass, radius, elasticy, ground_height, g));
	start(argc,argv);//function in "OpenGLStuff"
	
	return 0;
};

/*
 (c)2012 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
