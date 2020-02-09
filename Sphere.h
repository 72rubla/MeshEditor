#pragma once
#include "Command.h" 
#include "STLParser.h"
#include <cmath>

class Sphere:public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;	
private:
	const std::string s = "Sphere";
	const double PI = 3.141592653589793238463;
	TriangleSoup newSphere;
	Triangle loc;
	STLParser FileManager;
	virtual void BuildSphere(double R, Point origin, int slices, int rings, double Fi, double Ou);
	virtual Point PointBuilder(double R, double Fi, double Ou, Point origin);	
};