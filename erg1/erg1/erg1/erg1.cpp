// erg1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "user.h"
#include "point.h"
#include <stdlib.h>
//DxD D:διαστασεις σε km
int main()
{
	int D = 1000;//D is the dimensions of the space app checking. It can be added by admin too.
	int time_metr = 0;
	list<user> COVID_VICTIMS;
	//Create patients
	int plithos_asthenon = 3;//You can manage the number with an input from the admin
	for (int i = 0; i <= plithos_asthenon; i++) 
	{
		user o;
		COVID_VICTIMS.insert = o;
	}
	//Create User
	user user;
	point p((int)rand % D + 1, (int)rand % D + 1,time_metr);
	user.User_Trajectory.insert = p;
	for (int i = 0; i <= plithos_asthenon; i++) {
		COVID_VICTIMS[i]
	}
	//Trajectory progression
	while(0==0){

	}
}
bool POSSIBLE_COVID_19_INFECTION(list<point> User_Trajectory, int day, list<user> COVID19_patients) {

}
int FIND_CROWDED_PLACES(int day, int time, list<point> Square_Region_of_Interest, int Minimum_Stay_Duration) {

}
list<point> REPAIR(int day, list<point> User_Trajectory) {

}
list<point> SUMMARIZE_TRAJECTORY(int day, list<int> days_before, list<point> User_Trajectory) {

}
