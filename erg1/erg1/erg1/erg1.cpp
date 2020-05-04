#include "Node.h"
#include "user.cpp"
#include "Node.h"
#include "Node.cpp"
#include <stdlib.h>
#include <vector>
#include <ctime>

/////////////////////////
//DxD D:διαστάσεις σε m//
/////////////////////////
int D = 1000;				//DxD are the dimensions of the area
int time_counter = 0;		//Time Counter
vector<user> COVID_CASES;	//List of COVID19 cases

user Move(user& user) {
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
			user.wait_time = 30 * rand() % 11 + 1;
		}
	}
	return user;
}
int main() {
	srand(time(0));
	int counter = 1;		//For the creation of day indexes
	vector<int> day_index;	//Indexes when day starts


	///////////////////////
	///		PATIENTS	///
	///////////////////////
	//Create patients
	int cases = 3;						//Can be initialised using input from the admin
	for (int i = 0; i < cases; i++)
	{
		//Create patient
		user o(true, rand() % 26 + 25, rand() % D + 1, rand() % D + 1, rand() % D + 1, rand() % D + 1, time_counter);//Min speed is 3km/h and max speed is 6km/h. These are equivalent to 25m/30sec and 50m/30sec 
		//Generate spawn point as a Node object
		Node n(o.start_x, o.start_y, time_counter);
		//Store Node in the Trajectory
		o.Trajectory.push_back(n);
		//Add patient to the COVID_CASES vector
		COVID_CASES.push_back(o);
	}

	///////////////////
	///		USER	///
	///////////////////
	//Create User
	user user(false, rand() % 26 + 25, rand() % D + 1, rand() % D + 1, rand() % D + 1, rand() % D + 1, time_counter);
	//Generate spawn point as a Node object
	Node p(user.start_x, user.start_y, time_counter);
	//Store Node in the Trajectory
	user.Trajectory.push_back(p);

	time_counter = time_counter + 30;

	///////////////////////////
	///		TRAJECTORY		///	
	///////////////////////////
	//Progression
	while (true) {//The following loop prints the Trajectory of the first patient of the list after every movement. Remove the comments below to print movements of every patient
		//for (
		int i = 0; //i < COVID_CASES.size(); i++) {
		Move(COVID_CASES[i]);
		COVID_CASES[i].Trajectory.push_back(Node(COVID_CASES[i].current_x, COVID_CASES[i].current_y, time_counter));
		printf("Start position: (%i, %i) \t at time: %i    \t Destination: (%i, %i)\nTrajectory:\n", COVID_CASES[i].Trajectory[0].x, COVID_CASES[i].Trajectory[0].y, COVID_CASES[i].Trajectory[0].time, COVID_CASES[i].dest_x, COVID_CASES[i].dest_y);
		for (int j = 1; j < COVID_CASES[i].Trajectory.size(); j++) {
			printf("(%i, %i) at time: %i\n", COVID_CASES[i].Trajectory[j].x, COVID_CASES[i].Trajectory[j].y, COVID_CASES[i].Trajectory[j].time);
		}
		printf("\n");
		//}
	//}
		time_counter += 30;
	}
}

/*
bool POSSIBLE_COVID_19_INFECTION(vector<Node> User_Trajectory, int day, vector<user> COVID19_patients) {
}
int FIND_CROWDED_PLACES(int day, int time, vector<Node> Square_Region_of_Interest, int Minimum_Stay_Duration) {
}
vector<Node> REPAIR(int day, vector<Node> User_Trajectory) {
}
vector<Node> SUMMARIZE_TRAJECTORY(int day, vector<int> days_before, vector<Node> User_Trajectory) {
}
*/