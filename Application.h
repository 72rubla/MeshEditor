#pragma once
#include "Command.h"

class Application
{
public:
	void registerCommand(std::unique_ptr<Command> command);
	int execute(int argc, char *argv[]);
private:
	virtual std::map<std::string, std::string> createMap(int argc, char * argv[]);	
};

