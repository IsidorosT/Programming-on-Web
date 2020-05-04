#pragma once
#include <iostream>
<<<<<<< Updated upstream
=======
#include <list>
#include "Node.h"
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
#include <vector>
#include "Node.h"
using namespace std;
class User
{
	public:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
		vector<Node> Trajectory;
		bool infected;
	User(bool infection) {
		infected = infection;
	}
=======
=======
>>>>>>> Stashed changes
		vector <Node> Trajectory;
		int speed;
		bool infected;
		int dest_x;
		int dest_y;
		int start_x;
		int start_y;
		int start_time;
		int current_x;
		int current_y;

		int wait_time = 0;
		user(bool infection, int user_speed, int dx, int dy, int sx, int sy, int stime){
			infected = infection;
			speed = user_speed;
			dest_x = dx;
			dest_y = dy;
			start_x = sx;
			start_y = sy;
			current_x = sx;
			current_y = sy;
			start_time = stime;
		}
>>>>>>> Stashed changes
};



