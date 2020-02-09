#pragma once
#include "Command.h" 
#include "STLParser.h"

class Cube :public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string s = "Cube";
	TriangleSoup newCube;
	Triangle loc;
	STLParser FileManager;
	virtual void BuildCube(double L, Point origin);
};