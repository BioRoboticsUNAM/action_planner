#ifndef ACT_PLN_SRV_MAN
#define ACT_PLN_SRV_MAN

#include "action_planner/robot_knowledge.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
#include "visualization_msgs/MarkerArray.h"
#include "ros/console.h"
#include "ros/ros.h"
#include <string>

class ServiceManager
{
//private:
	//CommandManager() {}
public:
	//CommandManager() {}	//default public constructor
	
	/*
	* SP-GEN services callers
	*/
	bool spgenSay(std_msgs::String, int);
	void spgenAsay(std_msgs::String);

	/*
	*	ARMS services callers
	*/
	bool armsOpenGrip(RobotKnowledge::ARMS_KNOWLEDGE, std_msgs::Float32);
	bool armsCloseGrip(RobotKnowledge::ARMS_KNOWLEDGE, std_msgs::Float32);
	bool armsAbsPos(RobotKnowledge::ARMS_KNOWLEDGE, std_msgs::Float32, std_msgs::Float32, std_msgs::Float32, std_msgs::Float32, std_msgs::Float32, std_msgs::Float32, std_msgs::Float32);
	bool armsGoTo(RobotKnowledge::ARMS_KNOWLEDGE, std_msgs::String);

	/*
	*	MVNPLN services callers
	*/
	bool mpGetClose(std_msgs::String);
	bool mpGetClose(std_msgs::Float32, std_msgs::Float32);
	bool mpGetClose(std_msgs::Float32, std_msgs::Float32, std_msgs::Float32);
	bool mpMove(std_msgs::Float32, std_msgs::Float32&);
	bool mpMove(std_msgs::Float32, std_msgs::Float32, std_msgs::Float32&, std_msgs::Float32&);

	/*
	*	HEAD services callers
	*/
	bool hdLookAt(std_msgs::Float32, std_msgs::Float32);
	bool hdTorque(std_msgs::Bool);

	/*
	*	VISION services callers
	*/
	bool vsnFindOnPlanes(std_msgs::String, visualization_msgs::MarkerArray&);
};

#endif
