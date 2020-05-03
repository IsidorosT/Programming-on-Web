#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;
class User
{
	public:
		vector<Node> Trajectory;
		bool infected;
	User(bool infection) {
		infected = infection;
	}
};



