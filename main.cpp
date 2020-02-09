#pragma once
#include "Application.h"
#include "Sphere.h"
#include "Split.h"
#include "Cube.h"
#include <iostream>

int main(int argc, char *argv[])
{
	Application app;
	app.registerCommand(std::make_unique<Sphere>());
	app.registerCommand(std::make_unique<Split>());
	app.registerCommand(std::make_unique<Cube>());
	return app.execute(argc, argv);
	//Cube L = 1.0, origin = (0,0,0), filepath = "C:\\Users\Dima\Desktop\cube.stl" 
	//Split input = "C:\\Users\Dima\Desktop\sphere.stl", origin = (15.0,25.2,1.0), direction = (6.0,-1.0,-1.0), output1 = "C:\\Users\Dima\Desktop\a.stl", output2 = "C:\\Users\Dima\Desktop\b.stl"
	//Sphere R = 20.0, origin = (4.5,3.4,2.1), slices = 5, rings = 5, filename = "C:\\Users\Dima\Desktop\sphere.stl"
}