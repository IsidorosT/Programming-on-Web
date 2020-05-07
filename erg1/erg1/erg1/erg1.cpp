#include "Node.h"
#include "user.cpp"
#include "user.h"
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///														USER MOVE FUNCTION												 ///		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
User Move(User& user) {
	int temp;
	srand(time(0));
	temp = rand() % 2;//Check
	if (user.timelost <= 0)
	{
		if (temp == 0) {
			user.GPSSIGNAL = false;
			user.timelost = 30 * (rand() % 11 + 1);
			user.timelost -= 30;
			if (user.flag) {
				user.GPSSIGNAL = true;
				user.timelost = 0;
			}
			user.flag = true;
		}
		else
			user.GPSSIGNAL = true;
	}
	else {
		user.timelost -= 30;
	}
	if (user.current_x == user.dest_x && user.current_y == user.dest_y) {	//If the user has arrived to his destination
		if (user.GPSSIGNAL)
		{
			if (user.wait_time > 0)											//If there is still time left to wait there
				user.wait_time -= 30;
			else {															//If it is time to pick an other destination and leave
				if (!user.flag) {
					user.start_x = user.dest_x;
					user.start_y = user.dest_y;
					user.start_time = time_counter;
					user.dest_x = rand() % (D + 1) + 0;
					user.dest_y = rand() % (D + 1) + 0;
				}
				else {
					int temp1;
					int temp2;
					if (user.current_x + user.radius + 1 <= D)
						temp1 = user.current_x + user.radius + 1;
					else
						temp1 = D + 1;
					if (user.current_x - user.radius > 0) {
						temp2 = user.current_x - user.radius;
						user.start_x = rand() % temp2 + temp1;
					}
					else {
						temp2 = 0;
						user.start_x = rand() % temp1;
					}
					if (user.current_y + user.radius + 1 <= D) 
						temp1 = user.current_y + user.radius + 1;
					else
						temp1 = D + 1;
					if (user.current_y - user.radius > 0) {
						temp2 = user.current_y - user.radius;
						user.start_y = rand() % temp2 + temp1;
					}
					else{
						temp2 = 0;
						user.start_y = rand() % temp1;
					}
					user.current_x = user.start_x;
					user.current_y = user.start_y;
					user.start_time = time_counter;
					user.dest_x = rand() % (D + 1) + 0;
					user.dest_y = rand() % (D + 1) + 0;
					user.flag = false;
				}
			}
		}
		else{
			user.wait_time = 0;
			user.radius = user.radius + user.speed;
		}
	}
	else{
		if (user.GPSSIGNAL){
			int dist = sqrt(pow(abs(user.dest_x - user.current_x), 2) + pow(abs(user.dest_y - user.current_y), 2));
			if (dist > user.speed){						//If the distance cannot be covered with this speed, within 30 sec
				int dist_covered = 0;
				while (dist_covered < user.speed) {		//Move towards the destination, until you cover 'speed' meters
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
			else{										//Else if the distance can be covered within 30 sec, move to the destination
				user.current_x = user.dest_x;
				user.current_y = user.dest_y;
				user.wait_time = 30 * (rand() % 11 + 1);
			}
		}
		else{
			user.dest_x = user.current_x;
			user.dest_y = user.current_y;
			user.wait_time = 0;
			user.radius = user.radius + user.speed;
		}
	}
	return user;
}

///////////////////////////////////////////////////////
///			1) POSSIBLE_COVID_19_INFECTION			///
///////////////////////////////////////////////////////

bool POSSIBLE_COVID_19_INFECTION(User& user, int day, vector<User> COVID19_patients) {
	cout << "Enter radius 'R':" <<endl;
	int R;
	cin >> R;
	cout << "Enter minimum duration 'T1':" << endl;
	int T1;
	cin >> T1;
	cout << "Enter maximum time difference 'T2':" << endl;
	int T2;
	cin >> T2;

	int f = user.days_index[day];													//If one of the previous days is checked, stop before the first element of the next day
	if (day == user.days_index[user.days_index.size()])								//If the last day is checked, stop at the last element of the trajectory
		f = user.days_index.size();

	for (int i = user.days_index[day-1]; i < f; i++) {								//For every Node of the user's Trajectory, for the day given
		for (int j = 0; j < COVID19_patients.size(); j++) {							//For every patient in the map
			int exposure_time = 0;
			int l = COVID19_patients[j].days_index[day];							//If one of the previous days is checked, stop before the first element of the next day
			if (day == user.days_index[COVID19_patients[j].days_index.size()])		//If the last day is checked, stop at the last element of the trajectory
				l = COVID19_patients[j].days_index.size();
			for (int z = COVID19_patients[j].days_index[day - 1]; z < l; z++) {		//For every Node of the patient's Trajectory, for the day given
				int dist = sqrt(pow(abs(user.Trajectory[i].x - COVID19_patients[j].Trajectory[z].x), 2) + pow(abs(user.Trajectory[i].y - COVID19_patients[j].Trajectory[z].y), 2));	//Distance between the two coordinates
				if (dist <= R) {
					int time_dif = abs(user.Trajectory[i].time - COVID19_patients[j].Trajectory[z].time);	
					if (time_dif <= T2 && COVID19_patients[j].Trajectory[z].time <= user.Trajectory[i].time) //If time difference is not greater than the maximum given, AND the patient was at this point before the user got near him.
						exposure_time += 30;
					if (exposure_time >= T1) {
						printf("\n\nA COVID-19 patient was at %im radius %i mins ago. You stayed for %i mins inside infected area\n\n", R, time_dif / 60, exposure_time / 60);
						return true;
					}
				}
			}
		}
	}
	return false;	//If after checking every Node of the user's Trajectory for that day, the function has not returned true, then return false
}

///////////////////////////////////////////////
///			4) SUMMARIZE_TRAJECTORY			///
///////////////////////////////////////////////

vector<Node> SUMMARIZE_TRAJECTORY(int day, int days_before, User& user) {
	cout << "Enter distance 'R':" << endl;
	int R;
	cin >> R;	
	int noi = user.days_index[day - days_before - 1];						//Node of Interest is the first Node of the day we are summarizing
	vector<Node> Nodes_for_Deletion;										//In this vector, the Nodes that need to be deleted from the Trajectory are stored
	
	for (int i = noi + 1; i < user.days_index[day - days_before]; i++) {	//For every Node of the day given, starting from the one stored after the Node of interest
		int dist = sqrt(pow(abs(user.Trajectory[i].x - user.Trajectory[noi].x), 2) + pow(abs(user.Trajectory[i].y - user.Trajectory[noi].y), 2)); //Distance between the current Node and the Node of Interest
		if (dist < R)											//If the Node is inside radius R
			Nodes_for_Deletion.push_back(user.Trajectory[i]);	//Store the Node to the vector 'Nodes_for_Deletion'
		else
			noi = i;											//Else make the current Node Node of Interest
	}

	for (int i = 0; i < Nodes_for_Deletion.size(); i++) {				//For every Node stored inside the vector 'Nodes_for_Deletion
		for (int j = user.days_index[day - days_before - 1]; j < user.days_index[day - days_before]; j++) { //For every Node of the day given
			if (user.Trajectory[j].x == Nodes_for_Deletion[i].x && user.Trajectory[j].y == Nodes_for_Deletion[i].y && user.Trajectory[j].time == Nodes_for_Deletion[i].time) { //If Nodes match
				user.Trajectory.erase(user.Trajectory.begin() + j);		//Delete Node from user's Trajectory
				break;													//Break from the loop so the next Node of the vector 'Nodes_for_Deletion' is checked
			}
		}
	}

	for (int i = day - days_before; i < user.days_index.size(); i++)	//For every day in the 'days_index' vector
		user.days_index[i] -= Nodes_for_Deletion.size();				//Subtract the number of the number of the Nodes deleted from the user's Trajectory
	Nodes_for_Deletion.clear();											//Clear the 'Nodes_for_Deletion' vector
	return user.Trajectory;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///																	 MAIN		 														  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	srand(time(0));

	////////////////////////////////////////////////////////////////////////////////////
	///									  PATIENTS									 ///
	////////////////////////////////////////////////////////////////////////////////////
	
	//Ask for the number of patients
	cout << "Enter the number of COVID-19 cases:" << endl;
	int cases;
	cin >> cases;

	//Create patients
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

	////////////////////////////////////////////////////////////////////////////////////
	///										USER									 ///
	////////////////////////////////////////////////////////////////////////////////////

	//Create User
	User user(false, rand() % 26 + 25, rand() % D + 1, rand() % D + 1, rand() % D + 1, rand() % D + 1, time_counter);
	//Generate spawn point as a Node object
	Node p(user.start_x, user.start_y, time_counter);
	//Store Node in the Trajectory
	user.Trajectory.push_back(p);

	time_counter = time_counter + 30;

	////////////////////////////////////////////////////////////////////////////////////
	///									TRAJECTORY									 ///	
	////////////////////////////////////////////////////////////////////////////////////
	//Progression
	while (true) {
		//Patients Move
		for (int i = 0; i < COVID_CASES.size(); i++) {
			Move(COVID_CASES[i]);
			COVID_CASES[i].Trajectory.push_back(Node(COVID_CASES[i].current_x, COVID_CASES[i].current_y, time_counter));
		}

		//User Moves
		Move(user);
		user.Trajectory.push_back(Node(user.current_x, user.current_y, time_counter));

		time_counter += 30;

		//Day changing
		if (time_counter % 86400 == 0) {	//86400 secs are equivalent to 24h
			///	'days_index' Update	///
			//User 
			user.days_index.push_back(user.Trajectory.size());
			//Patients
			for (int i = 0; i < COVID_CASES.size(); i++) {
				COVID_CASES[i].days_index.push_back(COVID_CASES[i].Trajectory.size() - 1);
			}

			///		Tests		///

			if (user.days_index.size() == 4) {
				for (int j = 1; j < user.days_index.size(); j++) {
					printf("\n\nDay: %i, index: %i\n\n", j, user.days_index[j - 1]);
					for (int i = user.days_index[j - 1]; i < user.days_index[j]; i++)
						printf("(%i, %i) at: %i\n", user.Trajectory[i].x, user.Trajectory[i].y, user.Trajectory[i].time);
				}
				for (int j = 2; j <= user.days_index.size(); j++)
					user.Trajectory = SUMMARIZE_TRAJECTORY(j, 1, user);

				for (int j = 1; j < user.days_index.size(); j++) {
					printf("\n\nDay: %i, index: %i\n", j, user.days_index[j - 1]);
					for (int i = user.days_index[j - 1]; i < user.days_index[j]; i++)
						printf("(%i, %i) at: %i\n", user.Trajectory[i].x, user.Trajectory[i].y, user.Trajectory[i].time);
				}
			}
		}
	}
}