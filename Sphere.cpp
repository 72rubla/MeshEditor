#pragma once
#include "Sphere.h"

const std::string& Sphere::getName() const
{	
	return s; //"Sphere"
}

int Sphere::execute(const std::map<std::string, std::string>& args)
{
	if (args.count("R") < 1 || args.count("slices") < 1 || args.count("rings") < 1 || args.count("filename") < 1 || args.count("origin") < 1)
	{
		exit(4);
	}

	double R = std::stod(args.find("R")->second);
	if (R <= 0) exit(1);

	int slices = std::stoi(args.find("slices")->second) + 1;
	int rings = std::stoi(args.find("rings")->second);
	if (slices <= 2 || rings <= 1) exit(2);

	std::vector<std::string> tmp = FileManager.SplitByDelim(args.find("filename")->second, ",");
	std::string path = tmp[0];
	if (!FileManager.CheckIncorrectWrite(path))
	{		
		exit(3);
	}

	tmp = FileManager.SplitByDelim(args.find("origin")->second, ",");
	Point origin; 
	origin.X = std::stod(tmp[0]);
	origin.Y = std::stod(tmp[1]);
	origin.Z = std::stod(tmp[2]);	

	BuildSphere(R, origin, slices, rings, 0.0, 180.0);
	FileManager.write(newSphere, path);
		
	return 0;
}

Point Sphere::PointBuilder(double R, double Fi, double Ou, Point origin)
{
	Point point;
	double x = R * cos((Fi * PI) / 180.0) * sin((Ou * PI) / 180.0);
	double y = R * sin((Fi * PI) / 180.0) * sin((Ou * PI) / 180.0);
	double z = R * cos((Ou * PI) / 180.0);
	point.X = x + origin.X;
	point.Y = y + origin.Y;
	point.Z = z + origin.Z;
	return point;
}

void Sphere::BuildSphere(double R, Point origin, int slices, int rings, double Fi, double Ou)
{
	Point point;
	double AngleFi = 360.0 / (double)slices;
	double AngleOu = 180.0 / (double)rings;
	for (int j = 0; j < slices; j++)
	{
		for (int i = 0; i < rings; i++)
		{
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p1 = point;
			Fi += AngleFi;
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p2 = point;
			Ou -= AngleOu;
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p3 = point;
			Fi -= AngleFi;			
			newSphere.push_back(loc);
		}
		Ou = 180.0;
		Fi += AngleFi;
	}
	Fi = 0.0;
	Ou = 0.0;
	for (int j = 0; j < slices; j++)
	{
		for (int i = 0; i < rings; i++)
		{
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p1 = point;
			Fi += AngleFi;
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p2 = point;
			Fi -= AngleFi;
			Ou += AngleOu;
			point = PointBuilder(R, Fi, Ou, origin);
			loc.p3 = point;			
			newSphere.push_back(loc);
		}
		Ou = 0;
		Fi += AngleFi;
	}	
}