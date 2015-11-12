#include "action_planner/primitives_tasks.h"
#include "action_planner/states_machines.h"
#include "service_manager.h"
#include "ros/ros.h"
#include <iostream>

class NavigationSM
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
	//Service manager
	static ServiceManager srv_man;
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
	
	/*
	* A particular constructor for your state machine
	* Initialize your state machine here (add states, define the final state, define the execution method, etc)
	*/
	NavigationSM(PrimitivesTasks tasks);
	bool execute();
	
};
//
//END OF CLASS DEFINITION
//



PrimitivesTasks NavigationSM::m_tasks; 
ServiceManager NavigationSM::srv_man;

int NavigationSM::initialState()
{
	std::cout << "executing initial state" << std::endl;
	srv_man.spgenSay("I am ready for the navigation test...", 7000);
	return (int)WaitForInitCommand;
}

int NavigationSM::waitForInitCommand()
{
	std::cout << "waiting for init command....." << std::endl;
	return (int)LookForObjects;
}

int NavigationSM::lookForObjects()
{
	std::cout << "looking for objects" << std::endl;
	return (int)ReportResult;
}

int NavigationSM::reportResult()
{
	std::cout << "Repoorting results" << std::endl;
	return (int)FinalState;
}

int NavigationSM::finalState()
{
	std::cout << "finalState reached" << std::endl;
	return (int)FinalState;
}

NavigationSM::NavigationSM(PrimitivesTasks tasks)
{
	m_tasks = tasks;
	//add states to the state machine
	SM.addState((int)InitialState, &initialState);
	SM.addState((int)WaitForInitCommand, &waitForInitCommand);
	SM.addState((int)LookForObjects, &lookForObjects);
	SM.addState((int)ReportResult, &reportResult);;
	SM.addState((int)FinalState, &finalState, true);

	//execute the state machine from the initial state until the final state
	//while(SM.runNextStep());

	//return true;
}
bool NavigationSM::execute()
{
	while(SM.runNextStep());
	return true;
}
