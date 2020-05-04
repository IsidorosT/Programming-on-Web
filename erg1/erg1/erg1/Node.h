#pragma once
#include <iostream>
#include <list>
#include "Node.h"
#include "Node.cpp"
#include <vector>
using namespace std;
class Node
{
	public:
		int x;
		int y;
		int time;
	Node(int a,int b,int atime) {
		x = a;
		y = b;
		time = atime;
	}
};



