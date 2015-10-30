#include "action_planner/service_manager.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

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
	cmd_man.spgenSay(str, 20);

	return 0;
}
