#include "action_planner/robot_knowledge.h"
#include "action_planner/service_manager.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"

#include <sstream>

/*
	TODO:
	Create a command manager
	Create a topics manager
	Create a states machines api
*/
int main(int argc, char** argv)
{
	ros::init(argc, argv, "action_planner");

	ServiceManager cmd_man;
	
	std_msgs::String str;
	str.data = "hello from roscpp";

	std::cout << "find human: " << cmd_man.prsfndFind("human", 5000) << std::endl;
	std::cout << "remeber human: " << cmd_man.prsfndRemember("nonato", 5000) <<std::endl;
	std::cout << "find nonato : " << cmd_man.prsfndFind("nonato", 3000) << std::endl;
	std::cout << "amnesia: " << cmd_man.prsfndAmnesia(3000);

	//TODO: test following
	//cmd_man.mpGetClose(std_msgs::String);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32, std_msgs::Float32);
	//cmd_man.hdLookAt(distance, angle);
	//bool hdTorque(std_msgs::Bool);

	return 0;
}
