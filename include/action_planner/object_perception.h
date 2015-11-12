#include "action_planner/primitives_tasks.h"
#include "action_planner/service_manager.h"
#include "visualization_msgs/MarkerArray.h"
#include "action_planner/states_machines.h"
#include "ros/ros.h"
#include <iostream>

class ObjectPerceptionSM
{
public:
	/*
	*	ADD THE STATES ID YOU NEED FOR EACH STATE FUNCTION (IF YOU WANT)
	*/
	enum States
	{
		InitialState,
		WaitForInitCommand,
		LookForObjects,
		ReportResult,
		FinalState
	};

	//for the SM api
	StatesMachines SM;
	//stpln
	static PrimitivesTasks m_tasks;
	//state func members
	static visualization_msgs::Marker objectFound;
	static int searchAttempt;
	static int maxAttempts;

	/********************************************************************/
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	static int initialState();
	static int waitForInitCommand();
	static int lookForObjects();
	static int reportResult();
	static int finalState();
	/**********************************************************************/
	ObjectPerceptionSM(PrimitivesTasks tasks);
	bool execute();
};

int ObjectPerceptionSM::maxAttempts;
visualization_msgs::Marker ObjectPerceptionSM::objectFound;
int ObjectPerceptionSM::searchAttempt;
PrimitivesTasks ObjectPerceptionSM::m_tasks;

/*
* A particular constructor for your state machine
* Initialize your state machine here (add states, define the final state, define the execution method, etc)
*/
ObjectPerceptionSM::ObjectPerceptionSM(PrimitivesTasks tasks)
{
	m_tasks = tasks;
	//add states to the state machine
	SM.addState((int)InitialState, &initialState);
	SM.addState((int)WaitForInitCommand, &waitForInitCommand);
	SM.addState((int)LookForObjects, &lookForObjects);
	SM.addState((int)ReportResult, &reportResult);;
	SM.addState((int)FinalState, &finalState, true);
}
bool ObjectPerceptionSM::execute()
{
	while(SM.runNextStep());
	return true;
};

/*
*	ADD THE STATE FUNCTIONS YOU NEED
*/
int ObjectPerceptionSM::initialState()
{
	std::cout << "executing initial state " << maxAttempts << std::endl;
	maxAttempts=3;
	searchAttempt=0;
	return (int)WaitForInitCommand;
}

int ObjectPerceptionSM::waitForInitCommand()
{
	ServiceManager srv_man;
	std::cout << "waiting for init command....." << std::endl;
	searchAttempt=0;
	return (int)LookForObjects;
}

int ObjectPerceptionSM::lookForObjects()
{
	std::cout << "looking for objects" << std::endl;
	
	if(m_tasks.searchSingleObject(objectFound))
	{
		//one object found, report its position
		return (int)ReportResult;
	}
	std::cout << objectFound << std::endl;
	if(objectFound.ns.compare("no_object_data")==0)
	{
		std::cout << "no objects found, try again" << std::endl;
		return (int)LookForObjects;
	}
	std::cout << "more than one object found, try again" << std::endl;
	if(searchAttempt<maxAttempts)
	{
		searchAttempt++;
		return (int)LookForObjects;
	}
	return (int)ReportResult;
}

int ObjectPerceptionSM::reportResult()
{
	std::cout << "Repoorting results: " << objectFound <<  std::endl;
	return (int)FinalState;
}

int ObjectPerceptionSM::finalState()
{
	std::cout << "finalState reached" << std::endl;
	return (int)FinalState;
}

/**********************************************************************/


