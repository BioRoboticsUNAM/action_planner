#ifndef ACT_PLN_CMD_MAN
#define ACT_PLN_CMD_MAN

#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
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
};

#endif
