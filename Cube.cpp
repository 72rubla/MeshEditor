#pragma once
#include "Cube.h"

const std::string & Cube::getName() const
{
	// TODO: вставьте здесь оператор return
	return s;
}

int Cube::execute(const std::map<std::string, std::string>& args)
{
	if (args.count("L") < 1 || args.count("origin") < 1 || args.count("filepath") < 1)
	{
		exit(3);
	}

	double L = std::stod(args.find("L")->second);
	if (L <= 0) exit(1);	

	std::vector<std::string> tmp = FileManager.SplitByDelim(args.find("filepath")->second, ",");
	std::string path = tmp[0];
	if (!FileManager.CheckIncorrectWrite(path))
	{
		exit(2);
	}

	tmp = FileManager.SplitByDelim(args.find("origin")->second, ",");
	Point origin;
	origin.X = std::stod(tmp[0]);
	origin.Y = std::stod(tmp[1]);
	origin.Z = std::stod(tmp[2]);

	BuildCube(L, origin);
	FileManager.write(newCube, path);
	return 0;
}

void Cube::BuildCube(double L, Point origin)
{
	Point p1, p2, p3;
	
	p1 = origin;	
	p2 = p1;
	p2.X += L;
	p3 = p1;
	p3.Z += L;
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.Y += L;
	loc.p2.Y += L;
	loc.p3.Y += L;
	newCube.push_back(loc);

	p1 = p2;
	p2 = p1;
	p1.Z += L;
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.Y += L;
	loc.p2.Y += L;
	loc.p3.Y += L;
	newCube.push_back(loc);

	//
	p1 = origin;
	p2 = p1;
	p2.Z += L;
	p3 = p1;
	p3.Y += L;
	p3.Z += L;
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.X += L;
	loc.p2.X += L;
	loc.p3.X += L;
	newCube.push_back(loc);

	p1 = origin;
	p2 = p3;
	p3 = p1;
	p3.Y += L;
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.X += L;
	loc.p2.X += L;
	loc.p3.X += L;
	newCube.push_back(loc);
	//
	p1 = origin;
	p2 = p1;
	p2.X += L;
	p3 = p1;
	p3.Y += L;
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.Z += L;
	loc.p2.Z += L;
	loc.p3.Z += L;
	newCube.push_back(loc);

	p1 = p2;
	p2.Y += L;	
	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;
	newCube.push_back(loc);

	loc.p1.Z += L;
	loc.p2.Z += L;
	loc.p3.Z += L;
	newCube.push_back(loc);
}