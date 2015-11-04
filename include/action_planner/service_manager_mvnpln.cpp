#include "action_planner/service_manager.h"
#include "mvn_pln/mp_getclose.h"
#include "mvn_pln/mp_getclose_xy.h"
#include "mvn_pln/mp_getclose_xya.h"

/*
*	Implements a synchronous call to the mvn_pln node to move the robot to a specified string location
*	Receives:
*		location : the name of the map location (goalpoint)
*	Returns:
*		true : if the robot reach the location
*		false : otherwise
*/
bool ServiceManager::mpGetClose(std_msgs::String location)
{
	std::string service_name ("/mp_getclose");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<mvn_pln::mp_getclose>(service_name);	//create the service caller

	mvn_pln::mp_getclose srv;	//create the service and fill it with the parameters
	srv.request.location = location;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters: " << location);
		return true;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters: " << location);
		ROS_ERROR_STREAM_NAMED("action_planner", "Error message received from " << service_name << " : " << srv.response.error);
	}
	return false
}

/*
*	Implements a synchronous call to the mvn_pln node to move the robot to a specified (x, y) location
*	Receives:
*		goalX : the X position of the goalpoint
*		goalY : the Y position of the goalpoint
*	Returns:
*		true : if the robot reach the location
*		false : otherwise
*/
bool ServiceManager::mpGetClose(std_msgs::Float32 goalX, std_msgs::Float32 goalY)
{
	std::string service_name ("/mp_getclose_xy");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<mvn_pln::mp_getclose_xy>(service_name);	//create the service caller

	mvn_pln::mp_getclose_xy srv;	//create the service and fill it with the parameters
	srv.request.goalX = goalX;
	srv.request.goalY = goalY;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters: " << goalX << " " << goalY);
		return true;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters: " << goalX << " " << goalY);
		ROS_ERROR_STREAM_NAMED("action_planner", "Error message received from " << service_name << " : " << srv.response.error);
	}
	return false
}

/*
*	Implements a synchronous call to the mvn_pln node to move the robot to a specified (x, y) location with a final orientation
*	Receives:
*		goalX : the X position of the goalpoint
*		goalY : the Y position of the goalpoint
*		goalAngle : the final orientation of the robot
*	Returns:
*		true : if the robot reach the location
*		false : otherwise
*/
bool ServiceManager::mpGetClose(std_msgs::Float32 goalX, std_msgs::Float32 goalY, std_msgs::Float32 goalAngle)
{
	std::string service_name ("/mp_getclose_xya");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<mvn_pln::mp_getclose_xya>(service_name);	//create the service caller

	mvn_pln::mp_getclose_xya srv;	//create the service and fill it with the parameters
	srv.request.goalX = goalX;
	srv.request.goalY = goalY;
	srv.request.goalAngle = goalAngle;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters: " << goalX << " " << goalY << " " << goalAngle);
		return true;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters: " << goalX << " " << goalY << " " << goalAngle);
		ROS_ERROR_STREAM_NAMED("action_planner", "Error message received from " << service_name << " : " << srv.response.error);
	}
	return false
}

