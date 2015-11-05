#include "action_planner/service_manager.h"
#include "bbros_bridge/Default_ROS_BB_Bridge.h"

/*
* Implements a call to the prsfnd BB module to perform the pf_find (find a human) command
* Receives:
*	bbParameters	:	a string containing the name of the human to find
*	timeout	:	timeout for the bb command
*/
bool ServiceManager::prsfndFind(std::string bbParameters, int timeout)
{
	std::string service_name ("/pf_find");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<bbros_bridge::Default_ROS_BB_Bridge>(service_name);	//create the service caller

	bbros_bridge::Default_ROS_BB_Bridge srv;	//create the service and fill it with the parameters
	srv.request.parameters = bbParameters;
	srv.request.timeout = timeout;

	if(client.call(srv))	//call the service with the parameters contained in srv
	{
		ROS_DEBUG_STREAM_NAMED("action_planner", service_name << " service called successfully with parameters " << srv.request);
		return srv.response.success;
	}
	else
	{
		ROS_ERROR_STREAM_NAMED("action_planner", "an error acurred when trying to call the " << service_name << " service with parameters" << srv.request);
	}
	return false;
}
//bool prsfndRemember(std::String)
//{
//}
//bool prsfndAmnesia(std::String);
//bool prsfndForget(std::String);
