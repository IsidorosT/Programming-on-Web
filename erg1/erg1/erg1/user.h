#pragma once
#include <iostream>
#include <list>
#include "point.h"
#include <vector>
using namespace std;
class user
{
	public:
		vector <point> User_Trajectory;
		int speed;
		int waittime;
		point targetpoint;
		user(int sped, int waitime, point targepoint) {
			speed = sped;
			waittime = waitime;
			targetpoint = targepoint;
		}
};

