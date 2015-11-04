#include "action_planner/service_manager.h"
#include "vision/vsn_findonplanes.h"

/*
*	Implements a synchronous call to the vision node to perform the search of object on a plane
*	Receives:
*		object : the object the robot must find
*		recognized	:	the MarkerArray of the recognized object
*	Returns:
*		true : if the vision module find the object
*		false : otherwise
*/
bool ServiceManager::vsnFindOnPlanes(std_msgs::String object, visualization_msgs::MarkerArray &recognized)
{
	std::string service_name ("/vsn_findonplanes");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<vision::vsn_findonplanes>(service_name);	//create the service caller

	vision::vsn_findonplanes srv;	//create the service and fill it with the parameters
	srv.request.obj_name = object;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters " << srv.request);
		recognized = srv.response.recognized;
		return true;
	}
	else
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters " << srv.request);

	return false;
}
