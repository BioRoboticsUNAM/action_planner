#include "action_planner/robot_knowledge.h"
#include "action_planner/service_manager.h"
#include "action_planner/primitives_tasks.h"
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

	ServiceManager srv_man;
	PrimitivesTasks pt;
	RobotKnowledge brain;

	ros::spin();
	//std::cout << "take: " << pt.takeObject("objects", RobotKnowledge::LeftArm) << std::endl;
	//bool rememberHuman(std::string);

	//TODO: test following
	//cmd_man.mpGetClose(std_msgs::String);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32);
	//cmd_man.mpGetClose(std_msgs::Float32, std_msgs::Float32, std_msgs::Float32);
	//cmd_man.hdLookAt(distance, angle);
	//bool hdTorque(std_msgs::Bool);

	return 0;
}
