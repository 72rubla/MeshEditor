#pragma once
#include "Split.h"

const std::string& Split::getName() const
{
	//TODO: вставьте здесь оператор return
	return s;
}

int Split::execute(const std::map<std::string, std::string>& args)
{	
	if (args.count("input") < 1 || args.count("origin") < 1 || args.count("direction") < 1 || args.count("output1") < 1 || args.count("output2") < 1)
	{
		exit(3);
	}

	std::vector<std::string> tmp = FileManager.SplitByDelim(args.find("input")->second, ",");
	std::string input = tmp[0];

	Point origin;
	tmp = FileManager.SplitByDelim(args.find("origin")->second, ",");
	origin.X = std::stod(tmp[0]);
	origin.Y = std::stod(tmp[1]);
	origin.Z = std::stod(tmp[2]);

	Point direction;
	tmp = FileManager.SplitByDelim(args.find("direction")->second, ",");
	direction.X = std::stod(tmp[0]);
	direction.Y = std::stod(tmp[1]);
	direction.Z = std::stod(tmp[2]);

	if (origin.X - direction.X == 0 && origin.Y - direction.Y == 0 && origin.Z - direction.Z == 0)
	{
		exit(1);
	}

	tmp = FileManager.SplitByDelim(args.find("output1")->second, ",");
	std::string output1 = tmp[0];	

	tmp = FileManager.SplitByDelim(args.find("output2")->second, ",");
	std::string output2 = tmp[0];

	if (!FileManager.CheckIncorrectWrite(output1) || !FileManager.CheckIncorrectWrite(output2) || !FileManager.CheckIncorrectRead(input))
	{
		exit(2);
	}	

	areaLoc = CreateArea(origin, direction);

	newSplit = FileManager.read(input); //read from file
	AreaCut(newSplit, direction, origin);

	FileManager.write(FirstSide, output1);
	FileManager.write(SecondSide, output2);
	
	return 0;
}

Triangle Split::CreateArea(Point p1, Point vector)
{
	Triangle loc;
	//Point vector = new Point(6.0, -1.0, -1.0);
	//Point p1 = new Point(15.0, 25.2, 1.0);//6 18 -1
	Point p2, p3;
	double D = vector.X * (-1) * p1.X + vector.Y * (-1) * p1.Y + vector.Z * (-1) * p1.Z;
	double x = 2, y = -23;//
	double z1 = (vector.X * (-1) * x + vector.Y * (-1) * y + D * (-1)) / vector.Z;
	p2.X = x; p2.Y = y; p2.Z = z1;
	x = 27; y = -10;//
	double z2 = (vector.X * (-1) * x + vector.Y * (-1) * y + D * (-1)) / vector.Z;
	p3.X = x; p3.Y = y; p3.Z = z2;

	loc.p1 = p1;
	loc.p2 = p2;
	loc.p3 = p3;	
	return loc;
}

void Split::AreaCut(TriangleSoup inputTriangles, Point vector, Point p1)
{
	//FirstSide.push_back(CreateArea(p1, vector));
	double t, t1, t2, t3, D;
	Triangle loc;
	int count = 0;
	for (auto it = inputTriangles.begin(); it < inputTriangles.end(); it++)
	{
		t1 = AreaCrossPointRange(vector, p1, it->p1, it->p2);
		t2 = AreaCrossPointRange(vector, p1, it->p1, it->p3);
		//t3 = AreaPointRangeFormula(vector, p1, it->p3, it->p2);
		if ((t1 >= 0.0 && t1 <= 1.0) || (t2 >= 0.0 && t2 <= 1.0))
		{
			loc = *it;
			Cuted.push_back(loc);
		}
		else
		{
			count++;
			loc = *it;
			Temp.push_back(loc);
		}
	}
	if (inputTriangles.size() == count)
	{		
		exit(4);
	}
	/*for (auto it = Temp.begin(); it < Temp.end(); it++)
	{
		D = ((vector.X * p1.X)* (-1)) + ((vector.Y * p1.Y) * (-1)) + ((vector.Z * p1.Z) * (-1));
		t3 = (vector.X * it->p1.X) + (vector.Y * it->p1.Y) + (vector.Z * it->p1.Z) + D;
		loc = *it;
		if (t3 < 0)
		{
			FirstSide.push_back(loc);
		}
		else if (t3 > 1)
		{
			SecondSide.push_back(loc);
		}
	}*/
	for (auto it = Cuted.begin(); it < Cuted.end(); it++)
	{
		Point startP1, startP2, startP3;
		Triangle lc;

		t1 = AreaCrossPointRange(vector, p1, it->p1, it->p2); //12 13 23
		t2 = AreaCrossPointRange(vector, p1, it->p1, it->p3);
		t3 = AreaCrossPointRange(vector, p1, it->p2, it->p3);
		if (t1 > 0.0 && t1 < 1.0)
		{
			if (t2 > 0.0 && t2 < 1.0)
			{
				startP1 = SphereCrossPoint(it->p1, it->p2, t1);
				startP2 = SphereCrossPoint(it->p1, it->p3, t2);
				startP3 = it->p1;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
				startP3 = it->p2;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
				startP1 = it->p2;
				startP2 = it->p3;
				startP3 = SphereCrossPoint(it->p1, it->p3, t2);
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
			}
			else if (t3 >= 0.0 && t3 <= 1.0)
			{
				startP1 = SphereCrossPoint(it->p1, it->p2, t1);
				startP2 = SphereCrossPoint(it->p2, it->p3, t3);
				startP3 = it->p2;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
				startP3 = it->p1;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
				startP1 = it->p1;
				startP2 = it->p3;
				startP3 = SphereCrossPoint(it->p2, it->p3, t3);
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
			}
		}
		else if (t2 >= 0.0 && t2 <= 1.0)
		{
			if (t3 >= 0.0 && t3 <= 1.0)
			{
				startP1 = SphereCrossPoint(it->p1, it->p3, t2);
				startP2 = SphereCrossPoint(it->p2, it->p3, t3);
				startP3 = it->p3;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);

				startP3 = it->p1;
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);

				startP1 = it->p1;
				startP2 = it->p2;
				startP3 = SphereCrossPoint(it->p2, it->p3, t3);
				lc.p1 = startP1;
				lc.p2 = startP2;
				lc.p3 = startP3;
				Temp.push_back(lc);
			}
		}
	}
	for (auto it = Temp.begin(); it < Temp.end(); it++)
	{
		D = vector.X * p1.X * -1 + vector.Y * p1.Y * -1 + vector.Z * p1.Z * -1;
		t1 = vector.X * it->p1.X + vector.Y * it->p1.Y + vector.Z * it->p1.Z + D;
		t2 = vector.X * it->p2.X + vector.Y * it->p2.Y + vector.Z * it->p2.Z + D;
		t3 = vector.X * it->p3.X + vector.Y * it->p3.Y + vector.Z * it->p3.Z + D;
		loc = *it;
		if (t1 > 1 || t2 > 1 || t3 > 1)
		{
			SecondSide.push_back(loc);
		}
		else if (t1 < 0 || t2 < 0 || t3 < 0)
		{
			FirstSide.push_back(loc);
		}
		if (t1 >= 0 && t1 <= 1 && t3 >= 0 && t3 <= 1) { std::cout << "ZERO t1" << std::endl; }
	}
	
	Point ppp;
	for (auto it = SecondSide.begin(); it < SecondSide.end(); it++)
	{
		D = vector.X * p1.X * -1 + vector.Y * p1.Y * -1 + vector.Z * p1.Z * -1;
		t1 = vector.X * it->p1.X + vector.Y * it->p1.Y + vector.Z * it->p1.Z + D;
		t2 = vector.X * it->p2.X + vector.Y * it->p2.Y + vector.Z * it->p2.Z + D;
		t3 = vector.X * it->p3.X + vector.Y * it->p3.Y + vector.Z * it->p3.Z + D;
		Point startP1, startP2, startP3;
		if (t1 < 1)
		{
			startP1 = it->p1;
			if (t2 < 1)
			{
				startP2 = it->p2;
			}
			else if (t3 < 1)
			{
				startP2 = it->p3;
			}
		}
		else if (t2 < 1)
		{
			startP1 = it->p2;
			if (t3 < 1)
			{
				startP2 = it->p3;
			}
		}
		if ((t1 == 0 && t2 == 0) || (t1 == 0 && t3 == 0) || t2 == 0 && t3 == 0)
		{
			for (auto it = SecondSide.begin(); it < SecondSide.end(); it++)
			{
				D = vector.X * p1.X * -1 + vector.Y * p1.Y * -1 + vector.Z * p1.Z * -1;
				t1 = vector.X * it->p1.X + vector.Y * it->p1.Y + vector.Z * it->p1.Z + D;
				t2 = vector.X * it->p2.X + vector.Y * it->p2.Y + vector.Z * it->p2.Z + D;
				t3 = vector.X * it->p3.X + vector.Y * it->p3.Y + vector.Z * it->p3.Z + D;
				if (it->p1.X == startP1.X && it->p1.Y == startP1.Y && it->p1.Z == startP1.Z)
				{
					if (t2 < 1)
					{
						startP3 = it->p2;
					}
					else if (t3 < 1)
					{
						startP3 = it->p3;
					}
					break;
				}
				else if (it->p2.X == startP1.X && it->p2.Y == startP1.Y && it->p2.Z == startP1.Z)
				{
					if (t1 < 1)
					{
						startP3 = it->p1;
					}
					else if (t3 < 1)
					{
						startP3 = it->p3;
					}
					break;
				}
				else if (it->p3.X == startP1.X && it->p3.Y == startP1.Y && it->p3.Z == startP1.Z)
				{
					if (t1 < 1)
					{
						startP3 = it->p1;
					}
					else if (t2 < 1)
					{
						startP3 = it->p2;
					}
					break;
				}
			}
			ppp.X = (startP2.X + startP3.X) / 2;
			ppp.Y = (startP2.Y + startP3.Y) / 2;
			ppp.Z = (startP2.Z + startP3.Z) / 2;
			break;
		}
	}
	Temp.clear();
	Temp = SecondSide;
	for (auto it = Temp.begin(); it < Temp.end(); it++)
	{
		D = vector.X * p1.X * -1 + vector.Y * p1.Y * -1 + vector.Z * p1.Z * -1;
		t1 = vector.X * it->p1.X + vector.Y * it->p1.Y + vector.Z * it->p1.Z + D;
		t2 = vector.X * it->p2.X + vector.Y * it->p2.Y + vector.Z * it->p2.Z + D;
		t3 = vector.X * it->p3.X + vector.Y * it->p3.Y + vector.Z * it->p3.Z + D;
		Point startP1, startP2, startP3;
		//startP3 = ppp;
		startP3.X = 0;
		startP3.Y = 0;
		startP3.Z = 0;
		if (t1 < 1)//t1 >= 0 && t1 <= 1
		{
			loc.p1 = it->p1;
			if (t2 < 1)
			{
				loc.p2 = it->p2;
			}
			else if (t3 < 1)
			{
				loc.p2 = it->p3;
			}
			loc.p3 = startP3;
			FirstSide.push_back(loc);
			SecondSide.push_back(loc);
		}
		else if (t2 < 1)
		{
			loc.p1 = it->p2;
			if (t3 < 1);
			{
				loc.p3 = it->p3;
			}
			loc.p3 = startP3;
			FirstSide.push_back(loc);
			SecondSide.push_back(loc);
		}		
	}
}

double Split::AreaCrossPointRange(Point vector, Point p, Point P1, Point P2)
{
	double t = (((p.X - P1.X) * vector.X) + ((p.Y - P1.Y) * vector.Y) + ((p.Z - P1.Z) * vector.Z)) / (((P2.X - P1.X) * vector.X) + ((P2.Y - P1.Y) * vector.Y) + ((P2.Z - P1.Z) * vector.Z));
	return t;
}

Point Split::SphereCrossPoint(Point p1, Point p2, double t)
{	//x=x1+(x2-x1)*t
    //y=y1+(y2-y1)*t
    //z=z1+(z2-z1)*t
	Point p;
	double x, y, z;
	x = ((p2.X - p1.X) * t) + p1.X;
	y = ((p2.Y - p1.Y) * t) + p1.Y;
	z = ((p2.Z - p1.Z) * t) + p1.Z;
	p.X = x;
	p.Y = y;
	p.Z = z;
	return p;
}