#ifndef ACT_PLN_SRV_MAN
#define ACT_PLN_SRV_MAN

#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
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
	bool armsOpenGrip(int, std_msgs::Float32);
	bool armsCloseGrip(int, std_msgs::Float32);

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
};

#endif