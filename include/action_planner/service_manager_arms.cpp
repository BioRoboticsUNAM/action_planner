#include "action_planner/service_manager.h"
#include "arms/arm_opengrip.h"
#include "arms/arm_closegrip.h"
#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/Float32.h"
#include <string>

/*
*	Implements a synchronous call to the arms node to open a robot hand
*	Receives:
*		side : to indicate which side of the robot must perform the action
*		position : the final open position of the hand
*	Return:
*		true : if the robot hand was open
*		false : otherwise
*/
bool ServiceManager::armsOpenGrip(int side, std_msgs::Float32 position)
{
	std::string service_name;
	/*
	TODO: use the robot description class 
	*/
	if(side==0)
		service_name = "/la_opengrip";
	else
		service_name = "/ra_opengrip";

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<arms::arm_opengrip>(service_name);	//create the service caller

	arms::arm_opengrip srv;	//create the service and fill it with the parameters
	srv.request.position = position;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters: " << position);
		return true;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters: " << position);
	}
	return false;
}

/*
*	Implements a synchronous call to the arms node to close a robot hand
*	Receives:
*		side : to indicate which side of the robot must perform the action
*		position : the final closed position of the hand
*	Return:
*		true : if the robot hand was closed
*		false : otherwise
*/
bool ServiceManager::armsCloseGrip(int side, std_msgs::Float32 position)
{
	std::string service_name;
	/*
	TODO: use the robot description class 
	*/
	if(side==0)
		service_name = "/la_closegrip";
	else
		service_name = "/ra_closegrip";

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<arms::arm_closegrip>(service_name);	//create the service caller

	arms::arm_closegrip srv;	//create the service and fill it with the parameters
	srv.request.position = position;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters: " << position);
		return true;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters: " << position);
	}
	return false;
}
