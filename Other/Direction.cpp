#include <iostream>
#include <math.h>

using namespace std;

int main(){
	string dir[] = {"north","northeast","east","southeast", "south", "southwest", "west", "northwest"};
	string step[] = {"Forward" , "Turn_left", "Turn_right"};

	int real_dir = 0;
	int assign_dir = 0;
	int temp_real_dir = 0;
	int temp_assign_dir = 0;
	int assign_step;
	int next_step;

	for(real_dir = 0;real_dir <= 7; real_dir++){
		for(assign_dir = 0; assign_dir <=7; assign_dir++){
			cout << "real_dir:"<<  dir[real_dir] << ", assign_dir:" <<  dir[assign_dir] << "\n";
			//cout << "real_dir:"<<  real_dir << ", assign_dir:" <<  assign_dir << "\n";
			if(real_dir != assign_dir){
				temp_real_dir = 0;
				temp_assign_dir = assign_dir - real_dir;
				if(temp_assign_dir < 0) temp_assign_dir += 8;
				temp_real_dir += 4;
				//cout << "temp_real_dir:"<<  temp_real_dir << ", temp_assign_dir:" <<  temp_assign_dir << "\n";
				if(temp_real_dir > temp_assign_dir) assign_step = 2;
				else assign_step = 1;
			}else{
				assign_step = 0;
			}
			cout << step[assign_step] << "\n";
		}
	}
	return 0;
}
