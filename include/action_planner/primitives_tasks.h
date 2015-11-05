#ifndef ACT_PLN_PRIM_TSKS
#define ACT_PLN_PRIM_TSKS

#include "action_planner/robot_knowledge.h"
#include <string>
class PrimitivesTasks
{
public:
	/*
	* Take object primitives
	*/
	//bool takeObject(std::string objectName);
	bool takeObject(std::string, RobotKnowledge::ARM_SIDE);
};

#endif
