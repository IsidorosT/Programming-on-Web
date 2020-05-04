#pragma once
#include <iostream>
#include <list>
#include "Node.h"
#include "Node.cpp"
#include <vector>
using namespace std;
class user
{
	public:
		vector <Node> User_Trajectory;
		int speed;
		int waittime;
		Node targetpoint;
		user(int sped, int waitime, Node targepoint)
		{
			speed = sped;
			waittime = waitime;
			targetpoint = targepoint;
		};
};

