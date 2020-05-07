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
vector<user> COVID_CASES; //List of COVID19 cases
bool POSSIBLE_COVID_19_INFECTION(vector<Node> Trajectory, int day, vector<user> COVID19_patients) {
	int R = 2;
	int T1 = 300;
	int T2 = 14400;
	bool k = false;
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
						k = true;
					}
				}
			}
		}
	}
	return k;
}

int FIND_CROWDED_PLACES(user us, vector<int> time, vector<Node> Square_Region_of_Interest, int Minimum_Stay_Duration, user thisuser) {
	vector<user> in = COVID_CASES;
	in.push_back(thisuser);
	for (int i = us.days_index[us.days_index.size()-2] + (time[0] / 30); i <= us.days_index[us.days_index.size() - 2] + (time[1] / 30); i++) {
		for (int j = 0; j <= in.size() - 1; j++) {
			if (in[j].Trajectory[i].x < Square_Region_of_Interest[0].x || in[j].Trajectory[i].x > Square_Region_of_Interest[1].x || in[j].Trajectory[i].y <= Square_Region_of_Interest[0].y || in[j].Trajectory[i].y > Square_Region_of_Interest[1].y)
			{
				in.erase(in.begin() + j);
			}
		}
	}
	return in.size();
}

vector<Node> REPAIR(user user, vector<Node> Trajectory) {
	vector<Node> result;
	Node st(0,0,0);
	Node dest(0,0,0);
	bool flag = false;
	int l = 0;
	int t = Trajectory[user.days_index[user.days_index.size() - 2]].time;
	for (int i = 0; i <= user.days_index[user.days_index.size() - 1]; i++) {
		if (i < user.days_index[user.days_index.size() - 2]) {
			result.push_back(Trajectory[i]);
		}
		else {
			if (Trajectory[i].time == t) {
				if (!flag)
				{
					result.push_back(Trajectory[i]);
					flag = false;
				}
				else {
					int x;
					int y;
					for (int j = 0; j <= l;j++) {
						int dist = sqrt(pow(abs(Trajectory[i].x - st.x), 2) + pow(abs(Trajectory[i].y - st.y), 2));
						if (dist > user.speed) {							//If the distance cannot be covered with this speed, within 30 sec
							int dist_covered = 0;
							while (dist_covered < user.speed) {				//Move towards the destination, until you cover 'speed' meters
								if (Trajectory[i].x > st.x)
									st.x++;
								else if (Trajectory[i].x < st.x)
									st.x--;
								if (Trajectory[i].y > st.y)
									st.y++;
								else if (Trajectory[i].y < st.y)
									st.y--;
								dist_covered += sqrt(2);
							}
							st.time = Trajectory[i-1].time + (j+1) * 30;
							result.push_back(st);
						}
						else {
							st.x = Trajectory[i].x;
							st.y = Trajectory[i].y;
							st.time = Trajectory[i - 1].time + j * 30;
							result.push_back(st);
						}
					}
					flag = false;
				}
				l = 0;
			}
			else {
				if (!flag) {
					st.x = Trajectory[i-1].x;
					st.y = Trajectory[i-1].y;
					st.time = Trajectory[i-1].time;
					i = i - 1;
					flag = true;
					l++;
				}
				else {
					l++;
					i = i - 1;
				}
				
			}
			t = t + 30;
		}
	}
	user.days_index[user.days_index.size() - 1] = user.Trajectory.size() - 1;
	return result;

}
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

user Move(user& user) {
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
		else { 
			user.GPSSIGNAL = true;

		}
	}
	else {
		user.timelost -= 30;
	}
	if (user.current_x == user.dest_x && user.current_y == user.dest_y) {	//If the user has arrived to his destination
		if (user.GPSSIGNAL)
		{
			if (user.wait_time > 0)												//If there is still time left to wait there
				user.wait_time -= 30;
			else {																//If it is time to pick an other destination and leave
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
					if (user.current_x + user.radius + 1 <= D) {
						temp1 = user.current_x + user.radius + 1;
					}
					else {
						temp1 = D + 1;
					}
					if (user.current_x - user.radius > 0)
					{
						temp2 = user.current_x - user.radius;
						user.start_x = rand() % temp2 + temp1;
					}
					else {
						temp2 = 0;
						user.start_x = rand() % temp1;
					}
					if (user.current_y + user.radius + 1 <= D) {
						temp1 = user.current_y + user.radius + 1;
					}
					else {
						temp1 = D + 1;
					}
					if (user.current_y - user.radius > 0)
					{
						temp2 = user.current_y - user.radius;
						user.start_y = rand() % temp2 + temp1;
					}
					else {
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
		else {
			user.wait_time = 0;
			user.radius = user.radius + user.speed;
		}
	}
	else {
		if (user.GPSSIGNAL)
		{
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
		else {
			user.dest_x = user.current_x;
			user.dest_y = user.current_y;
			user.wait_time = 0;
			user.radius = user.radius + user.speed;
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
	user.days_index.push_back(0);

	///////////////////////////
	///		TRAJECTORY		///	
	///////////////////////////
	//Progression
	while (true) {//The following loop prints the Trajectory of the first patient of the list after every movement. Remove the comments below to print movements of every patient
		for (int i = 0;i < COVID_CASES.size(); i++) {
			Move(COVID_CASES[i]);
			if (COVID_CASES[i].GPSSIGNAL)
			{
				COVID_CASES[i].Trajectory.push_back(Node(COVID_CASES[i].current_x, COVID_CASES[i].current_y, time_counter));
				/*printf("Start position: (%i, %i) \t at time: %i    \t Destination: (%i, %i)\nTrajectory:\n", COVID_CASES[i].Trajectory[0].x, COVID_CASES[i].Trajectory[0].y, COVID_CASES[i].Trajectory[0].time, COVID_CASES[i].dest_x, COVID_CASES[i].dest_y);
				for (int j = 1; j < COVID_CASES[i].Trajectory.size(); j++) {
					printf("(%i, %i) at time: %i\n", COVID_CASES[i].Trajectory[j].x, COVID_CASES[i].Trajectory[j].y, COVID_CASES[i].Trajectory[j].time);
				}
				printf("\n");*/
			}
		}
		Move(user);
		if (user.GPSSIGNAL) {
			user.Trajectory.push_back(Node(user.current_x, user.current_y, time_counter));
		}
		if (time_counter % 86400 == 0) {

			user.days_index.push_back(user.Trajectory.size()-1);
			user.Trajectory = REPAIR(user,user.Trajectory);
			for (int i = 0; i < COVID_CASES.size(); i++) {
				COVID_CASES[i].days_index.push_back(COVID_CASES[i].Trajectory.size() - 1);
				COVID_CASES[i].Trajectory = REPAIR(COVID_CASES[i],COVID_CASES[i].Trajectory);
			}
			if (POSSIBLE_COVID_19_INFECTION(user.Trajectory, day_index[day_index.size() - 1], COVID_CASES) == true)
			{
				printf("You are probably infected!!-Contact your doctor");
			}
			else {
				printf("You didn't come close with infected people today!!");
			}
			if (day_index.size() - 1 % 2 == 0)
			{
				SUMMARIZE_TRAJECTORY(user.days_index.size() - 1, 2, user.Trajectory);
				printf("Done");
			}
			string x = "";
			while (x != "N")
			{
				vector<int>time;
				vector<Node>coordinates;
				int min;
				int k;
				int l;
				if (x == "Y") {
					cout << "Give the starting time of tracking";
					cin >> k;
					time.push_back(k);
					cout << "Give the ending time of tracking";
					cin >> k;
					time.push_back(k);
					cout << "Give the up-left spot of tracking place";
					cin >> k;
					cin >> l;
					Node s(k,l,0);
					coordinates.push_back(s);
					cout << "Give the Down-Right spot of tracking place";
					cin >> k;
					cin >> l;
					Node q(k, l, 0);
					coordinates.push_back(q);
					cout << "Give the minimum time amount of staying";
					cin >> min;
					k =FIND_CROWDED_PLACES(user,time,coordinates,min,user);
					cout << "There was %i people\n",k;
				}
				else {
					x = "N";
				}
				
				cout << "If you want to track crowded places press (Y) if not press (N)\n"; // Type a number and press enter
				cin >> x;
			}
		}
		time_counter += 30;
	}
}


