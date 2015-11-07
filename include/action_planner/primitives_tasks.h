#ifndef ACT_PLN_PRIM_TSKS
#define ACT_PLN_PRIM_TSKS

#include "ros/ros.h"
#include "action_planner/robot_knowledge.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "action_planner/service_manager.h"
#include "visualization_msgs/MarkerArray.h"
#include <string>
#include <limits>
#include <math.h>

class PrimitivesTasks
{
public:
	/*
	* Take object primitives
	*/
	//bool takeObject(std::string objectName);
	bool searchAndTakeObject(std::string, RobotKnowledge::ARM_SIDE);
	bool rememberHuman(std::string);
private:
	geometry_msgs::Point transRobotToArm(geometry_msgs::Point);
};

#endif
