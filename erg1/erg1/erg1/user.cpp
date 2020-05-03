#include "User.h"

int user_Move(User user, Node start, int x_finish, int y_finish) {
	int x_current = start.x;
	int y_current = start.y;
	//Min speed is 3km/h and max speed is 6km/h. These are equivalent to 25m/30sec and 50m/30sec 
	int speed = rand() % 26 + 25;
	int time_current = start.time;
	while (x_current != x_finish && y_current != y_finish) {
		int dist = sqrt(pow(abs(x_finish - x_current), 2) + pow(abs(y_finish - y_current), 2));
		if (dist > speed) {//If the distance cannot be covered with this speed, during 30 sec
			int dist_covered = 0;
			while (dist_covered < speed) {//Move towards the finish, till you cover 'speed' meters
				if (x_finish > x_current)
					x_current++;
				else if (x_finish < x_current)
					x_current--;
				if (y_finish > y_current)
					y_current++;
				else if (y_finish < y_current)
					y_current--;
				dist_covered += sqrt(2);
			}
		}
		else {//Else if the distance can be covered during 30 sec, move to the finish 
			x_current = x_finish;
			y_current = y_finish;
		}
		time_current += 30;//30 seconds have passed
		user.Trajectory.push_back(Node(x_current, y_current, start.date, 0));//Node is stored in the Trejectory
		//
	}
}