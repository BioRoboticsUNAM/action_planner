#include "action_planner/primitives_tasks.h"

/*
* Transform a robot coordinate to a point coordinate
*	Receives:
*		robotPoint	:	the (x,y,z) robot-coord-system 
*	Returns:
*		the (x,y,z) arm-coord-system
*/
geometry_msgs::Point transRobotToArm(geometry_msgs::Point robotPoint)
{
}

/*
*	Implements the take specific object subtask 
*	Receives:
*		objectName	:	the name of the object to find
*		armSide			:	the arm side to use to take the object
*/
bool PrimitivesTasks::takeObject(std::string objectName, RobotKnowledge::ARM_SIDE armSide)
{
	ServiceManager srv_man;

	//use vision to find the object on the plane
	std_msgs::String std_objectNama(objectName);
	std_objectName.data = objectName;
	visualization_msgs::MarkerArray objectRobotCoord;
	srv_man.vsnFindOnPlanes(std_objectName, objectRobotCoord);
	
	//transform the returned point to arm coordinate
	//move the arm to the object point
}
