#pragma once
#include <ctime>
#include <string>
class Node
{
	public:
		int x;
		int y;
		int time;
		string date;
	Node(int a,int b, string cdate, int atime) {
		x = a;
		y = b;
		time = atime;
		date = cdate;
	}
};

