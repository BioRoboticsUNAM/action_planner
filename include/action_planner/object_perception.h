#include "action_planner/primitives_tasks.h"
#include "action_planner/service_manager.h"
#include "visualization_msgs/MarkerArray.h"
#include "action_planner/states_machines.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <iostream>
#include <vector>

class ObjectPerceptionSM
{
private:
	/*
	*	ADD THE STATES ID YOU NEED FOR EACH STATE FUNCTION (IF YOU WANT)
	*/
	enum States
	{
		InitialState,
		WaitForInitCommand,
		MoveHead,
		LookForObjects,
		ReportResult,
		FinalState
	};
	struct headParams
	{
		headParams(double hpan, double htilt) : tilt(htilt), pan(hpan) {}
		double tilt;
		double pan;
	};

	//for the SM api
	StatesMachines SM;
	//service manager
	static ServiceManager srv_man;
	//stpln
	static PrimitivesTasks m_tasks;
	//state func members
	static visualization_msgs::Marker objectFound;
	static int searchAttempt;
	static int maxAttempts;
	static int currentHeadPosition;
	static std::vector<headParams> headPositions;

	/********************************************************************/
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	static int initialState();
	static int waitForInitCommand();
	static int moveHead();
	static int lookForObjects();
	static int reportResult();
	static int finalState();
	/**********************************************************************/
	
public:
	ObjectPerceptionSM(PrimitivesTasks tasks);
	bool execute();
};

int ObjectPerceptionSM::maxAttempts;
visualization_msgs::Marker ObjectPerceptionSM::objectFound;
int ObjectPerceptionSM::searchAttempt;
PrimitivesTasks ObjectPerceptionSM::m_tasks;
std::vector<ObjectPerceptionSM::headParams> ObjectPerceptionSM::headPositions;
int ObjectPerceptionSM::currentHeadPosition;
ServiceManager ObjectPerceptionSM::srv_man;

/*
* A particular constructor for your state machine
* Initialize your state machine here (add states, define the final state, define the execution method, etc)
*/
ObjectPerceptionSM::ObjectPerceptionSM(PrimitivesTasks tasks)
{
	m_tasks = tasks;
	//int (ObjectPerceptionSM::*
	//add states to the state machine
	SM.addState((int)InitialState, &initialState);
	SM.addState((int)WaitForInitCommand, &waitForInitCommand);
	SM.addState((int)MoveHead, &moveHead);
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

	/*Initialize member variables*/
	searchAttempt = 0;
	currentHeadPosition = 0;
	//head positions to find the object
	headPositions.push_back(headParams(0.0,-0.8));
	headPositions.push_back(headParams(0.3,-0.8));
	headPositions.push_back(headParams(-0.3,-0.8));
	headPositions.push_back(headParams(0.0,-0.6));
	headPositions.push_back(headParams(0.3,-0.6));
	headPositions.push_back(headParams(-0.3,-0.6));

	maxAttempts =  headPositions.size();

	return (int)WaitForInitCommand;
}

int ObjectPerceptionSM::waitForInitCommand()
{
	std::cout << "waiting for init command....." << std::endl;
	std::getchar();
	searchAttempt=0;
	currentHeadPosition = 0;
	return (int)LookForObjects;
}

int ObjectPerceptionSM::moveHead()
{
	std::cout << "moving head " << std::endl;
	
	//move the head to current pos
	std_msgs::Float32 tilt, pan, cTilt, cPan;
	tilt.data = headPositions[currentHeadPosition % headPositions.size()].tilt;
	pan.data = headPositions[currentHeadPosition % headPositions.size()].pan;
	srv_man.hdLookAt(pan, tilt, cPan, cTilt);
	currentHeadPosition++;
	//currentHeadPosition = (currentHeadPosition < headPositions.size()) ? currentHeadPosition+1: 0;
	
	//std::cout << "moving head to : (" << pan.data << ", " << tilt.data << ")" << std::endl;

	return (int)LookForObjects;
}

int ObjectPerceptionSM::lookForObjects()
{
	std::cout << "looking for objects" << std::endl;
	
	objectFound.ns = "clean";
	if(m_tasks.searchSingleObject(objectFound))
	{
		//one object found, report its position
		return (int)ReportResult;
	}
	if(searchAttempt<maxAttempts)
	{
		searchAttempt++;
		if(objectFound.ns.compare("clean")==0)
		{
			//no object found
			std::cout << "ACT-PLN: no objects found, try again moving head" << std::endl;
			return (int)MoveHead;
		}
		std::cout << "more than one object found, try again on same place" << std::endl;
		return (int)MoveHead;
	}
	return (int)ReportResult;
}

int ObjectPerceptionSM::reportResult()
{
	std::cout << "Repoorting results... " << std::endl;
	std::cout << "FOUND OBJECT NAME: " << objectFound.ns <<  std::endl;
	//return (int)FinalState;
	return (int)WaitForInitCommand;
}

int ObjectPerceptionSM::finalState()
{
	std::cout << "finalState reached" << std::endl;
	return (int)FinalState;
}

/**********************************************************************/


