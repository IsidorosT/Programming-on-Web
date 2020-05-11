#pragma once
#include <iostream>
#include <list>
#include "Node.h"
#include <vector>
#include "Node.h"

using namespace std;
class User
{
public:
	vector<Node> Trajectory;
	bool infected;
	int speed;
	int dest_x;
	int dest_y;
	int start_x;
	int start_y;
	int start_time;
	int current_x;
	int current_y;
	int radius;//Last Update
	bool GPSSIGNAL;//Last Update
	int timelost;//Last Update
	bool flag;
	vector<int> days_index;

	int wait_time = 0;
	User(bool infection, int user_speed, int dx, int dy, int sx, int sy, int stime) {
		infected = infection;
		speed = user_speed;
		dest_x = dx;
		dest_y = dy;
		start_x = sx;
		start_y = sy;
		current_x = sx;
		current_y = sy;
		start_time = stime;
		radius = user_speed;//Last Update
		timelost = 0;//Last Update
		flag = false;
	}
};



