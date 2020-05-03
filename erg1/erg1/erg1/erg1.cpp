// erg1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "user.h"
#include "user.cpp"
#include "point.h"
#include "point.cpp"
#include <stdlib.h>
#include <vector>
//DxD D:διαστασεις σε km
int main()
{
	int metritis = 1;//For the creation of day pointers
	vector<int> deiktes_days;//Deiktes when day starts
	int D = 1000;//D is the dimensions of the space app checking. It can be added by admin too.
	int time_metr = 0;//Counter of time
	vector<user> COVID_VICTIMS;
	//Create patients
	int plithos_asthenon = 3;//You can manage the number with an input from the admin
	for (int i = 0; i <= plithos_asthenon; i++) 
	{
		point p((int)(rand() % D + 1), (int)(rand() % D + 1));
		//Min speed is 3km/h and max speed is 6km/h. These are equivalent to 25m/30sec and 50m/30sec
		user o((int)(rand() % 26 + 25), time_metr,);
		COVID_VICTIMS.insert = o;
	}
	//Create User
	user user;
	point p((int)rand % D + 1, (int)rand % D + 1,time_metr);
	user.User_Trajectory.insert = p;
	time_metr = time_metr + 30;
	for (int i = 0; i <= plithos_asthenon; i++) {
		point p((int)rand % D + 1, (int)rand % D + 1, time_metr);
		COVID_VICTIMS[i].User_Trajectory.insert = p;
	};

	//Trajectory progression
	while(0==0){

	}
}
bool POSSIBLE_COVID_19_INFECTION(vector<point> User_Trajectory, int day, vector<user> COVID19_patients) {

}
int FIND_CROWDED_PLACES(int day, int time, vector<point> Square_Region_of_Interest, int Minimum_Stay_Duration) {

}
vector<point> REPAIR(int day, vector<point> User_Trajectory) {

}
vector<point> SUMMARIZE_TRAJECTORY(int day, vector<int> days_before, vector<point> User_Trajectory) {

}
