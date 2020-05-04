// erg1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "user.h"
#include "user.cpp"
#include "Node.h"
#include "Node.cpp"
#include <stdlib.h>
#include <vector>
//DxD D:διαστασεις σε m
int main()
{
	int metritis = 1;//For the creation of day pointers
	vector<int> deiktes_days;//Deiktes when day starts
	int D = 1000;//D is the dimensions of the space app checking. It can be added by admin too.
	int time_metr = 0;//Time Counter
	vector<user> COVID_VICTIMS;//List of COVID19 victims
	//Create patients
	int cases = 3;//You can manage the number with an input from the admin
	for (int i = 0; i <= cases; i++) 
	{
		Node p((int)rand % D + 1, (int)rand % D + 1,time_metr);
		//Min speed is 3km/h and max speed is 6km/h. These are equivalent to 25m/30sec and 50m/30sec
		user o((int)(rand() % 26 + 25), time_metr,p);
		o.User_Trajectory.insert = p;
		COVID_VICTIMS.insert = o;
	}
	//Create User
	Node p((int)rand % D + 1, (int)rand % D + 1, time_metr);
	user user((int)rand % 26 + 25,time_metr,p);
	user.User_Trajectory.insert = p;
	for (int i = 0; i <= cases; i++) {
		Node p((int)rand % D + 1, (int)rand % D + 1, time_metr);
		COVID_VICTIMS[i].User_Trajectory.insert = p;
	};
	time_metr = time_metr + 30;
	//Trajectory progression
	while(true){
		time_metr = time_metr + 30;
	}
}
bool POSSIBLE_COVID_19_INFECTION(vector<Node> User_Trajectory, int day, vector<user> COVID19_patients) {

}
int FIND_CROWDED_PLACES(int day, int time, vector<Node> Square_Region_of_Interest, int Minimum_Stay_Duration) {

}
vector<Node> REPAIR(int day, vector<Node> User_Trajectory) {

}
vector<Node> SUMMARIZE_TRAJECTORY(int day, vector<int> days_before, vector<Node> User_Trajectory) {

}



