#include "Node.h"
#include "user.cpp"
#include "Node.h"
#include "Node.cpp"
#include <stdlib.h>
#include <vector>
#include <ctime>
using namespace std;
/////////////////////////
//DxD D:διαστάσεις σε m//
/////////////////////////
int D = 1000;				//DxD are the dimensions of the area
int time_counter = 0;		//Time Counter
vector<user> COVID_CASES; //List of COVID19 cases
bool POSSIBLE_COVID_19_INFECTION(user User, int day, vector<user> COVID19_patients) {
	cout << "Enter radius 'R':" << endl;	int R;	cin >> R;
	cout << "Enter minimum duration 'T1':" << endl;	int T1;	cin >> T1;
	cout << "Enter maximum time difference 'T2':" << endl;	int T2;	cin >> T2;

	for (int i = User.days_index[(__int64)day - 1]; i < User.days_index[day]; i++) {			//For every Node of the user's Trajectory, for the day given
		for (int j = 0; j < COVID19_patients.size()-1; j++) {							//For every patient in the map
			int exposure_time = 0;
			for (int z = COVID19_patients[j].days_index[(__int64)day - 1]; z < COVID19_patients[j].days_index[day]; z++) {		//For every Node of the patient's Trajectory, for the day given
				int dist = sqrt(pow(abs(User.Trajectory[i].x - COVID19_patients[j].Trajectory[z].x), 2) + pow(abs(User.Trajectory[i].y - COVID19_patients[j].Trajectory[z].y), 2));	//Distance between the two coordinates
				if (dist <= R) {
					int time_dif = abs(User.Trajectory[i].time - COVID19_patients[j].Trajectory[z].time);
					if (time_dif <= T2) //If time difference is not greater than the maximum given, AND the patient was at this point before the user got near him.
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
int FIND_CROWDED_PLACES(user us, vector<int> time, vector<Node> Square_Region_of_Interest, int Minimum_Stay_Duration, user thisuser) {
	vector<user> in = COVID_CASES;//The full list of users and COVID VICTIMS
	vector<int> ol;//A list of representing the amount of stay in the tracking area on each of people that this app has
	for (int i = 0; i <= COVID_CASES.size(); i++)
	{
		ol.push_back(0);
	}
	in.push_back(thisuser);
	int temp = 0;
	for (int j = 0; j <= in.size() - 1; j++) {
		for (int i = in[j].days_index[in[j].days_index.size() - 2] + (time[0] / 30); i <= in[j].days_index[in[j].days_index.size() - 2] + (time[1] / 30); i++) {
			if (in[j].Trajectory[i].x >= Square_Region_of_Interest[0].x && in[j].Trajectory[i].x <= Square_Region_of_Interest[1].x && in[j].Trajectory[i].y >= Square_Region_of_Interest[0].y && in[j].Trajectory[i].y <= Square_Region_of_Interest[1].y)//if this user is in place of tracking then add 30sec on his time of stay
			{
				ol[j] = ol[j] + 30;
			}
			else {//if he is not then if he is alrady pass the minimusm stay then continue otherwise make it zero
				if (ol[j] < Minimum_Stay_Duration) {
					ol[j] = 0;
				}
			}
		}
	}
	for (int j = 0; j <= in.size() - 1; j++)//With this loop erase from list everyone that didnt stay from the minimum duration in the tracking zone
	{
		if (j == 0) {

		}
		if (ol[j] < Minimum_Stay_Duration) {
			in.erase(in.begin() + j);
			ol.erase(ol.begin() + j);
			j--;
		}
		if (in.size() == 0) {
			break;
		}
	}
	return in.size();//So print the number of the people that stay in the tracking zone
}

vector<Node> REPAIR(user user, vector<Node> Trajectory) {
	vector<Node> result;
	Node st(0,0,0);
	Node dest(0,0,0);
	bool flag = false;
	int l = 0;
	int t = Trajectory[user.days_index[user.days_index.size() - 2]].time;//t is the time of next step +30sec
	for (int i = 0; i <= user.days_index[user.days_index.size() - 1]-1; i++) {
		if (i < user.days_index[user.days_index.size() - 2]) {//until the day we are interested to repair just put the trajectory list into result
			result.push_back(Trajectory[i]);
		}
		else {
			if (Trajectory[i].time == t) {//if the time of next step is equal to time of next node of trajectory then put it in result list
				if (!flag)
				{
					result.push_back(Trajectory[i]);
					flag = false;
				}
				else {//if we found the next value that time is equal with node of trajectory then make the steps and find the nodes between and push them in result
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
			else {//if not then hold that value and check next
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
	user.days_index[user.days_index.size() - 1] = result.size() - 1;//Because we make a change on size of trajectory at the last day then change the last address for the beggining of next day
	return result;

}
vector<Node> SUMMARIZE_TRAJECTORY(int day, int days_before, user User)
{
	cout << "Enter distance 'R':" << endl;	int R;	cin >> R;
	int noi = User.days_index[(__int64)day - days_before - 1];						//Node of Interest is the first Node of the day we are summarizing
	vector<Node> Nodes_for_Deletion;										//In this vector, the Nodes that need to be deleted from the Trajectory are stored

	for (int i = noi + 1; i < User.days_index[(__int64)day - days_before]; i++) {	//For every Node of the day given, starting from the one stored after the Node of interest
		int dist = sqrt(pow(abs(User.Trajectory[i].x - User.Trajectory[noi].x), 2) + pow(abs(User.Trajectory[i].y - User.Trajectory[noi].y), 2)); //Distance between the current Node and the Node of Interest
		if (dist < R)											//If the Node is inside radius R
			Nodes_for_Deletion.push_back(User.Trajectory[i]);	//Store the Node to the vector 'Nodes_for_Deletion'
		else
			noi = i;											//Else make the current Node Node of Interest
	}

	for (int i = 0; i < Nodes_for_Deletion.size(); i++) {														//For every Node stored inside the vector 'Nodes_for_Deletion
		for (int j = User.days_index[(__int64)day - days_before - 1]; j < User.days_index[(__int64)day - days_before]; j++) {		//For every Node of the day given
			if (User.Trajectory[j].x == Nodes_for_Deletion[i].x && User.Trajectory[j].y == Nodes_for_Deletion[i].y && User.Trajectory[j].time == Nodes_for_Deletion[i].time) { //If Nodes match
				User.Trajectory.erase(User.Trajectory.begin() + j); break;		//Delete Node from user's Trajectory and break from the loop so the next Node of the vector 'Nodes_for_Deletion' is checked
			}
		}
	}

	for (int i = day - days_before; i < User.days_index.size(); i++)	//For every day in the 'days_index' vector
		User.days_index[i] -= Nodes_for_Deletion.size();				//Subtract the number of the number of the Nodes deleted from the user's Trajectory
	Nodes_for_Deletion.clear();											//Clear the 'Nodes_for_Deletion' vector
	return User.Trajectory;
}

user Move(user& user) {
	int temp;
	srand(time(0));
 	temp = rand() % 2;//Check
	if (user.timelost <= 0)
	{
		if (temp == 0) {
			user.GPSSIGNAL = false;
			user.timelost = 30 * (rand() % 3 + 1); 
			user.timelost = user.timelost - 30; 
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
					int temp = D + 1;
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
					
						user.start_x = rand() % ((temp1-temp2) +1) + temp2;
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
						user.start_y = rand() % ((temp1 - temp2) + 1) + temp2;
					}
					else {
						temp2 = 0;
						user.start_y = rand() % temp1;
					}
					user.current_x = user.start_x;
					user.current_y = user.start_y;
					user.start_time = time_counter;
					int temp = D + 1;
					user.dest_x = rand() % (D + 1) + 0;
					user.dest_y = rand() % (D + 1) + 0;
					user.flag = false;
					user.radius = 0;
				}
				
				
			}
		}
		else {
			user.wait_time = 0;
			user.radius = user.radius + user.speed;
			user.timelost = user.timelost - 30;
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
				user.wait_time = 30 * (rand() % 6 + 1);
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
	int cases = 5;						//Can be initialised using input from the admin
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
		COVID_CASES[i].days_index.push_back(0);
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
			}
		}
		Move(user);
		if (user.GPSSIGNAL) {
			user.Trajectory.push_back(Node(user.current_x, user.current_y, time_counter));
		}
		if (time_counter % 86400 == 0) {

			
			user.Trajectory = REPAIR(user,user.Trajectory);
			for (int i = 0; i < COVID_CASES.size(); i++) {
				COVID_CASES[i].days_index.push_back(COVID_CASES[i].Trajectory.size());
				COVID_CASES[i].Trajectory = REPAIR(COVID_CASES[i],COVID_CASES[i].Trajectory);
			}
			user.days_index.push_back(user.Trajectory.size());
			if (POSSIBLE_COVID_19_INFECTION(user, user.days_index[user.days_index.size()-2], COVID_CASES) == true)
			{
				printf("You are probably infected!!-Contact your doctor");
			}
			else {
				printf("You didn't come close with infected people today!!");
			}
			if (day_index.size() - 1 % 2 == 0)
			{
				SUMMARIZE_TRAJECTORY(user.days_index[user.days_index.size() - 2], 2, user);
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
					cout << "Give the starting time of tracking(00:00)-(23:59)\n";
					cin >> k;
					time.push_back((k/100)*3600+(k%100)*60);
					cout << "Give the ending time of tracking(00:00)-(23:59)\n";
					cin >> k;
					time.push_back((k / 100) * 3600 + (k % 100) * 60);
					cout << "Give the up-left spot of tracking place(0,0)-(1000,1000)\n";
					cin >> k;
					cin >> l;
					Node s(k,l,0);
					coordinates.push_back(s);
					cout << "Give the Down-Right spot of tracking place(0,0)-(1000,1000)\n";
					cin >> k;
					cin >> l;
					Node q(k, l, 0);
					coordinates.push_back(q);
					cout << "Give the minimum time amount of staying\n";
					cin >> min;
					k =FIND_CROWDED_PLACES(user,time,coordinates,min,user);
					cout << "There was " << k << " people\n";
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


