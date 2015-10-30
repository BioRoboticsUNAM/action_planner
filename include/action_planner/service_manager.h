#ifndef ACT_PLN_CMD_MAN
#define ACT_PLN_CMD_MAN

#include "std_msgs/String.h"

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
	bool armsOpenGrip();
	bool armsCloseGrip();
};

#endif
