#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct Point
{
	double X, Y, Z;
};
struct Triangle
{
	Point p1, p2, p3;
	Point vec;	
};

using TriangleSoup = std::vector<Triangle>;

class STLParser
{
public:	
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& triangleSoup, const std::string& filename);
	bool CheckIncorrectRead(std::string path);
	bool CheckIncorrectWrite(std::string path);
	virtual std::vector<std::string> SplitByDelim(std::string str, std::string delim);
private:
};

