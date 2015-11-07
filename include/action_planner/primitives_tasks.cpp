#include "action_planner/primitives_tasks.h"

/*
* Transform a robot coordinate to a point coordinate
*	Receives:
*		robotPoint	:	the (x,y,z) robot-coord-system 
*	Returns:
*		the (x,y,z) arm-coord-system
*/
geometry_msgs::Point PrimitivesTasks::transRobotToArm(geometry_msgs::Point robotPoint)
{
	geometry_msgs::Point armPoint;
	armPoint.x = 1.19 - robotPoint.z;
	armPoint.y = robotPoint.x;
	armPoint.z = 0.21 - robotPoint.y;

	return armPoint;
}

/*
* Implements the remember human task, captures tree patters of a human face and gives it a name
* 	Receives:
*		humanName	:	the name of the human to remember
*/
bool PrimitivesTasks::rememberHuman(std::string humanName)
{
	ServiceManager srv_man;
	bool patternStored=false;
	//get the human normal face
	srv_man.spgenSay("Please look straightforward to my web camera.", 5000);
	patternStored = srv_man.prsfndRemember(humanName, 5000);
	//get the human happy face
	srv_man.spgenSay("Human smile.", 5000);
	patternStored = patternStored && srv_man.prsfndRemember(humanName, 5000);
	//get the human serious face 
	srv_man.spgenSay("Now, a serious face.", 5000);
	patternStored = patternStored && srv_man.prsfndRemember(humanName, 5000);

	if(!patternStored)
	{
		srv_man.spgenSay("Please relax your face and look to my webcamera.", 5000);
		ros::Duration(1).sleep();
		patternStored = srv_man.prsfndRemember(humanName, 5000);
	}

	srv_man.spgenSay("I have remembered your face.", 5000);

	return patternStored;
}

/*
*	Implements the take specific object subtask 
*	Receives:
*		objectName	:	the name of the object to find
*		armSide			:	the arm side to use to take the object
*/
bool PrimitivesTasks::shearchAndTakeObject(std::string objectName, RobotKnowledge::ARM_SIDE armSide)
{
	ServiceManager srv_man;
	//move the head to -1
	std_msgs::Float32 tilt, pan, cTilt, cPan;
	tilt.data = -1, pan.data = 0.0;
	srv_man.hdLookAt(pan, tilt, cPan, cTilt);

	//use vision to find the object on the plane
	std_msgs::String std_objectName;
	std_objectName.data = objectName;
	visualization_msgs::MarkerArray recognizedObjects;

	if(!srv_man.vsnFindOnPlanes(std_objectName, recognizedObjects))
	{
		//findonplanes wasn't executed
		return false;
	}

	if(recognizedObjects.markers.size() == 0)
	{
		//no object found
		return false;
	}

	//get the closer object to the robot (relative to the arm)
	geometry_msgs::Point closestObjectArmCoord;
	double minDistance = 99999;
	
	for(int i=0; i<recognizedObjects.markers.size(); i++)
	{
		//transform the returned point to arm coordinate
		geometry_msgs::Point objectArmCoord = transRobotToArm(recognizedObjects.markers[i].pose.position);
		//verify if this is the closer distance
		double distanceToArm = sqrt(objectArmCoord.y+objectArmCoord.y + objectArmCoord.z*objectArmCoord.z);
		if(distanceToArm < minDistance)
		{
			closestObjectArmCoord.x = objectArmCoord.x;
			closestObjectArmCoord.y = objectArmCoord.y;
			closestObjectArmCoord.z = objectArmCoord.z;
			minDistance = distanceToArm;
		}
	}

	//move the arm to the object point
	std_msgs::Float32 x, y, z, roll, pitch, yaw, elbow, torque;
	torque.data = 0.0;
	//move the arm to std_by position
	x.data = 0.2; y.data = 0.0; z.data = 0.0; roll.data = 0.0; pitch.data = 0.0; yaw.data = 1.57; elbow.data=0.0;
  srv_man.armsAbsPos(armSide, x, y, z, roll, pitch, yaw, elbow);
	//open the gripper
	srv_man.armsOpenGrip(armSide, torque);
	//move the arm to the object position
	x.data = closestObjectArmCoord.x; 
	y.data = closestObjectArmCoord.y + 0.05; 
	z.data = closestObjectArmCoord.z; 
	roll.data = 0.0; pitch.data = 0.0; yaw.data = 1.57; elbow.data=0.0;
  srv_man.armsAbsPos(armSide, x, y, z, roll, pitch, yaw, elbow);
	//close the gripper
  srv_man.armsCloseGrip(armSide, torque);
	//move the arm to std_by position
	x.data = 0.2; y.data = 0.0; z.data = 0.0; roll.data = 0.0; pitch.data = 0.0; yaw.data = 1.57; elbow.data=0.0;
  srv_man.armsAbsPos(armSide, x, y, z, roll, pitch, yaw, elbow);

	//retrun head to 0 retrun head to 0 0
	tilt.data = 0.0, pan.data = 0.0;
	srv_man.hdLookAt(pan, tilt, cPan, cTilt);
}
