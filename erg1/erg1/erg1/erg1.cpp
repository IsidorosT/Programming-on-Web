// erg1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "User.h"
#include "Node.h"
#include "User.cpp"
#include <stdlib.h>
#include <vector>
#include<string>
//DxD D:διαστασεις σε km
int main()
{
	int D = 1000;
	string date = "3/5/2020";
	vector<User> COVID_Cases;
	


	//Create patients
	int cases = 3;
	for (int i = 0; i <= cases; i++)
	{
		//'Patient' objects are created
		COVID_Cases.insert = User(true);
		//Patients Spawn in a random point of map. First Node stored in the 'Trajectory' vector
		COVID_Cases[i].Trajectory.push_back(Node((int)rand % D + 1, (int)rand % D + 1, date, 0));
		//Patients start moving. Starting point is the first Node of the 'Trajectory' vector
		user_Move(COVID_Cases[i], COVID_Cases[i].Trajectory.size - 1, (int)rand % D + 1, (int)rand % D + 1);
	}


	//Create User
	User user1(false);
	//User Spawns in map
	user1.Trajectory.push_back(Node ((int)rand % D + 1, (int)rand % D + 1, date, 0));
	//User stars moving
	user_Move(user1, user1.Trajectory.size - 1, (int)rand % D + 1, (int)rand % D + 1);

}

bool POSSIBLE_COVID_19_INFECTION(list<Node> User_Trajectory, int day, list<User> COVID19_patients) {

}
int FIND_CROWDED_PLACES(int day, int time, list<Node> Square_Region_of_Interest, int Minimum_Stay_Duration) {

}
list<Node> REPAIR(int day, list<Node> User_Trajectory) {

}
list<Node> SUMMARIZE_TRAJECTORY(int day, list<int> days_before, list<Node> User_Trajectory) {

}
