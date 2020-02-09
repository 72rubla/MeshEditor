#pragma once
#include "Command.h"
#include "STLParser.h"

class Split :public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string s = "Split";
	STLParser FileManager;
	TriangleSoup newSplit, FirstSide, SecondSide, Cuted, Temp;
	Triangle areaLoc;
	virtual Triangle CreateArea(Point p1, Point vector);
	virtual void AreaCut(TriangleSoup inputTriangles, Point vector, Point p1);
	virtual double AreaCrossPointRange(Point vector, Point p, Point P1, Point P2);
	virtual Point SphereCrossPoint(Point p1, Point p2, double t);
};

