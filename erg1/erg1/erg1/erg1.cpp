#include "Node.h"
#include "User.cpp"
#include "Node.h"
#include "Node.cpp"
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace::std;

/////////////////////////
//DxD D:διαστάσεις σε m//
/////////////////////////
int D = 5;					//DxD are the dimensions of the area
int time_counter = 0;		//Time Counter
vector<User> COVID_CASES;	//List of COVID19 cases
int day = 1;				//For the creation of day indexes
vector<int> day_index;		//Indexes when day starts

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///														USER MOVE FUNCTION												 ///		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
User Move(User& user) {
	srand(time(0));
	if (user.current_x == user.dest_x && user.current_y == user.dest_y) {	//If the user has arrived to his destination
		if (user.wait_time > 0)												//If there is still time left to wait there
			user.wait_time -= 30;
		else {																//If it is time to pick an other destination and leave
			user.start_x = user.dest_x;
			user.start_y = user.dest_y;
			user.start_time = time_counter;
			user.dest_x = rand() % (D + 1) + 0;
			user.dest_y = rand() % (D + 1) + 0;
		}
	}
	else {
		int dist = sqrt(pow(abs(user.dest_x - user.current_x), 2) + pow(abs(user.dest_y - user.current_y), 2));
		if (dist > user.speed) {							//If the distance cannot be covered with this speed, within 30 sec
			int dist_covered = 0;
			while (dist_covered < user.speed) {				//Move towards the destination, until you cover 'speed' meters
				if (user.dest_x > user.current_x)
					user.current_x++;
				else if (user.dest_x < user.current_x)
					user.current_x--;
				if (user.dest_y > user.current_y)
					user.current_y++;
				else if (user.dest_y < user.current_y)
					user.current_y--;
				dist_covered += sqrt(2);
			}
		}
		else {												//Else if the distance can be covered within 30 sec, move to the destination
			user.current_x = user.dest_x;
			user.current_y = user.dest_y;
			user.wait_time = 30 * (rand() % 11 + 1);
		}
	}
	return user;
}

///////////////////////////
///			1)			///
///////////////////////////

bool POSSIBLE_COVID_19_INFECTION(vector<Node> Trajectory, int day, vector<User> COVID19_patients) {
	int R = 2;
	int T1 = 300;
	int T2 = 14400;
	for (int i = (day - 1) * 2880; i < day * 2880; i++) {
		printf("User was at (%i, %i) at time:%i\n", Trajectory[i].x, Trajectory[i].y, Trajectory[i].time);
		for (int j = 0; j < COVID19_patients.size(); j++) {
			//printf("Patient no.%i:\n", j+1);
			int exposure_time = 0;
			for (int z = 0; z < COVID19_patients[j].Trajectory.size(); z++) {
				int dist = sqrt(pow(abs(Trajectory[i].x - COVID19_patients[j].Trajectory[z].x), 2) + pow(abs(Trajectory[i].y - COVID19_patients[j].Trajectory[z].y), 2));
				//printf("COVID-19 CORPSE distance from user: %im\n", dist);
				if (dist <= 2) {
					int time_dif = abs(Trajectory[i].time - COVID19_patients[j].Trajectory[z].time);
					if (time_dif <= T2 && COVID19_patients[j].Trajectory[z].time <= Trajectory[i].time)
						exposure_time += 30;
					if (exposure_time >= T1) {
						printf("\n\nYOU WILL DIE FROM CORONA VIRUS. A COVID-19 ZOMBIE WAS AT %im RADIUS %i MINS AGO. YOU STAYED FOR %i mins INSIDE INFECTED AREA\n\n", R, time_dif / 60, exposure_time / 60);
						return true;
					}
				}
			}
		}
	}
}

///////////////////////////
///			4)			///
///////////////////////////

vector<Node> SUMMARIZE_TRAJECTORY(int day, int days_before, vector<Node> Trajectory) {
	int R = 5;
	int noi = (day - days_before - 1) * 2880;					//Node of Interest
	vector<Node> Nodes_for_Deletion;
	for (int i = noi + 1; i < (day - days_before) * 2880; i++) {
		int dist = sqrt(pow(abs(Trajectory[i].x - Trajectory[noi].x), 2) + pow(abs(Trajectory[i].y - Trajectory[noi].y), 2)); //Distance of the current Node from the Node of Interest
		
		if (dist < R)
			Nodes_for_Deletion.push_back(Trajectory[i]);
		else
			noi = i;
	}

	for (int i = 0; i < Nodes_for_Deletion.size(); i++) {
		for (int j = 0; j < Trajectory.size(); j++) {
			if (Trajectory[j].x == Nodes_for_Deletion[i].x && Trajectory[j].y == Nodes_for_Deletion[i].y && Trajectory[j].time == Nodes_for_Deletion[i].time) {
				//printf("\n DELETE (%i, %i) time: %i\n", Nodes_for_Deletion[i].x, Nodes_for_Deletion[i].y, Nodes_for_Deletion[i].time);
				Trajectory.erase(Trajectory.begin() + j);
				break;
			}
		}
	}

	return Trajectory;
}

int main() {
	srand(time(0));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///															PATIENTS												 ///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Create patients
	int cases = 1;						//Can be initialised using input from the admin
	for (int i = 0; i < cases; i++)
	{
		//Create patient
		int speed = rand() % 26 + 25; //Min speed is 3km/h and max speed is 6km/h. These are equivalent to 25m/30sec and 50m/30sec
		User o(true, speed, rand() % D + 1, rand() % D + 1, rand() % D + 1, rand() % D + 1, time_counter); 
		//Generate spawn point as a Node object
		Node n(o.start_x, o.start_y, time_counter);
		//Store Node in the Trajectory
		o.Trajectory.push_back(n);
		//Add patient to the 'COVID_CASES' vector
		COVID_CASES.push_back(o);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///															USER													////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create User
	User user(false, rand() % 26 + 25, rand() % D + 1, rand() % D + 1, rand() % D + 1, rand() % D + 1, time_counter);
	//Generate spawn point as a Node object
	Node p(user.start_x, user.start_y, time_counter);
	//Store Node in the Trajectory
	user.Trajectory.push_back(p);

	time_counter = time_counter + 30;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///													TRAJECTORY													///	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Progression
	while (true) {
		for (int i = 0; i < COVID_CASES.size(); i++) {
			Move(COVID_CASES[i]);
			COVID_CASES[i].Trajectory.push_back(Node(COVID_CASES[i].current_x, COVID_CASES[i].current_y, time_counter));
			//printf("Start position: (%i, %i) \t at time: %i    \t Destination: (%i, %i)\nTrajectory:\n", COVID_CASES[i].Trajectory[0].x, COVID_CASES[i].Trajectory[0].y, COVID_CASES[i].Trajectory[0].time, COVID_CASES[i].dest_x, COVID_CASES[i].dest_y);
			//for (int j = 1; j < COVID_CASES[i].Trajectory.size(); j++) {
			//	printf("(%i, %i) at time: %i\n", COVID_CASES[i].Trajectory[j].x, COVID_CASES[i].Trajectory[j].y, COVID_CASES[i].Trajectory[j].time);
			//}
			//printf("\n");
		}
		Move(user);
		user.Trajectory.push_back(Node(user.current_x, user.current_y, time_counter));
		//}

		time_counter += 30;
		if (time_counter % 86400 == 0) {//Day changes
			day++;
			day_index.push_back(user.Trajectory.size() - 1);
			//printf("Day: %i\n", day);
			//if (POSSIBLE_COVID_19_INFECTION(user.Trajectory, day, COVID_CASES) == true)
				//exit(0);
			if (day % 2 == 0) 
				SUMMARIZE_TRAJECTORY(day, 2, user.Trajectory);			
		}
	}
}

/*
int FIND_CROWDED_PLACES(int day, int time, vector<Node> Square_Region_of_Interest, int Minimum_Stay_Duration) {
}
vector<Node> REPAIR(int day, vector<Node> User_Trajectory) {
}
*/

