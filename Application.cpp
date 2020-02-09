#pragma once
#include "Application.h"
#include "Sphere.h"
#include "Split.h"
#include <iostream>

std::map<std::string, std::unique_ptr<Command>> validCmd;
void Application::registerCommand(std::unique_ptr<Command> command)
{		
	validCmd.emplace(command->getName(), std::move(command));	
}

int Application::execute(int argc, char * argv[])
{		
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << " ";
	}
	if (validCmd.count(argv[1]) < 1)
	{
		exit(1);
	}
	validCmd.find(argv[1])->second->execute(createMap(argc, argv));
	system("pause");
	return 0;
}

std::map<std::string, std::string> Application::createMap(int argc, char * argv[])
{
	std::map<std::string, std::string> args;
	std::string tmp;
	for (int i = 3; i < argc; i++)
	{
		tmp = argv[i];
		if (tmp == "=") {
			args.emplace(argv[i - 1], argv[i + 1]);
		}
	}
	return args;
}