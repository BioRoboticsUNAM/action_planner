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
	
	//std_msgs::String str;
	//str.data = "hello from roscpp";
	//cmd_man.spgenSay(str, 20);
	std_msgs::Float32 distance,angle, ang, dist;
	distance.data=0.1;
	angle.data=0.5;
	std_msgs::String object;
	visualization_msgs::MarkerArray rec;
	object.data = "objects";

	//TODO: test following
	//cmd_man.mpGetClose(std_msgs::String);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32, std_msgs::Float32);

	//cmd_man.hdLookAt(distance, angle);
	//bool hdTorque(std_msgs::Bool);
	cmd_man.vsnFindOnPlanes(object, rec);
	std::cout << rec;
	return 0;
}
