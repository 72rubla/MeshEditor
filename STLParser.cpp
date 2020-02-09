#pragma once
#include "STLParser.h"
#include <algorithm>

TriangleSoup STLParser::read(const std::string & filename)
{
	Point p;
	Triangle loc;
	TriangleSoup trianglesFromFile;
	std::vector<std::string> tmp;
	std::ifstream fin;
	try {
		fin.open(filename);
		std::string str;
		while (!fin.eof())
		{
			str = "";	
			std::getline(fin, str);
			if (!str.find("vertex"))
			{
				tmp = SplitByDelim(str, " ");
				p.X = std::stod(tmp[1]);
				p.Y = std::stod(tmp[2]);
				p.Z = std::stod(tmp[3]);
				loc.p1 = p;

				str = "";
				std::getline(fin, str);
				if (!str.find("vertex"))
				{
					tmp = SplitByDelim(str, " ");
					p.X = std::stod(tmp[1]);
					p.Y = std::stod(tmp[2]);
					p.Z = std::stod(tmp[3]);
					loc.p2 = p;
				}

				str = "";
				std::getline(fin, str);
				if (!str.find("vertex"))
				{
					tmp = SplitByDelim(str, " ");
					p.X = std::stod(tmp[1]);
					p.Y = std::stod(tmp[2]);
					p.Z = std::stod(tmp[3]);
					loc.p3 = p;
				}
				str = "";
				std::getline(fin, str);
				//if (!str.find("endloop"))
				{
					trianglesFromFile.push_back(loc);
				}				
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "FileReadError " << ex.what() << std::endl;
	}
	fin.close();	

	return trianglesFromFile;
}

void STLParser::write(const TriangleSoup & triangleSoup, const std::string & filename)
{
	std::ofstream fs(filename);	
	try {
		fs << "solid " << "\n";
		for (std::vector<Triangle>::const_iterator i = triangleSoup.begin(); i != triangleSoup.end(); i++)
		{
			fs << "facet normal " << i->vec.X << " " << i->vec.Y << " " << i->vec.Z << "\n";
			fs << "outer loop" << "\n";
			fs << "vertex " << i->p1.X << " " << i->p1.Y << " " << i->p1.Z << "\n";
			fs << "vertex " << i->p2.X << " " << i->p2.Y << " " << i->p2.Z << "\n";
			fs << "vertex " << i->p3.X << " " << i->p3.Y << " " << i->p3.Z << "\n";
			fs << "endloop" << "\n";
			fs << "endfacet" << "\n";
			fs << "\n";
		}
		fs << "endsolid";
	}
	catch (const std::exception& ex) 
	{
		std::cout << "FileWriteError " << ex.what() << std::endl;
	}
	fs.close();
}

bool STLParser::CheckIncorrectRead(std::string path)
{
	bool b = false;	
	try
	{
		std::ifstream fin;
		fin.open(path);
		b = fin.is_open() ? true : false;
		fin.close();
	}
	catch (const std::exception&)
	{
		exit(99);
	}	
	return b;
}

bool STLParser::CheckIncorrectWrite(std::string path)
{
	bool b = false;
	
	try
	{
		std::ofstream fs(path);
		b = fs.is_open() ? true : false;
		fs.close();
	}
	catch (const std::exception&)
	{
		exit(99);
	}	
	return b;
}

std::vector<std::string> STLParser::SplitByDelim(std::string str, std::string delim)
{
	std::vector<std::string> arr;
	std::string newStr;
	//std::remove_copy(str.begin(), str.end(), back_inserter(newStr), ')','(');
	//std::remove_copy(str.begin(), str.end(), ')', back_inserter(newStr));
	char temp;
	int size = str.length();		
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();
	if (!str.find(')')) {
		
	}
	if (!str.find('(')) {
		str.erase(str.find(')'), 1);
		str.erase(str.find('('), 1);
	}
	//str.erase(str.find(')'), 1);
	//str.erase(str.find('('), 1);
	while ((next = str.find(delim, prev)) != std::string::npos)
	{
		arr.push_back(str.substr(prev, next - prev));
		prev = next + delta;
	}
	arr.push_back(str.substr(prev));
	return arr;
}