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
		DoSomethingState,
		FinalState
	};

	//for the SM api
	StatesMachines SM;
	/********************************************************************/
	
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	static int initialStateFunc()
	{
		std::cout << "executing initial state" << std::endl;
		return (int)DoSomethingState;
	}
	
	static int doSomethingFunc()
	{
		std::cout << "doing something state" << std::endl;
		return (int)FinalState;
	}
	
	static int finalStateFunc()
	{
		std::cout << "finalState sreached" << std::endl;
		return (int)FinalState;
	}
	
	/**********************************************************************/
	
	/*
	* A particular constructor for your state machine
	* Initialize your state machine here (add states, define the final state, define the execution method, etc)
	*/
	ObjectPerceptionSM(ros::NodeHandle& mainNodeHandler, ros::Subscriber& mainSubscriber)
	{
		//add states to the state machine
		SM.addState((int)InitialState, &initialStateFunc);
		SM.addState((int)DoSomethingState, &doSomethingFunc);
		SM.addState((int)FinalState, &finalStateFunc, true);
	
		//execute the state machine from the initial state until the final state
		//while(SM.runNextStep());
	
		//return true;
	}
	bool execute()
	{
		while(SM.runNextStep());
		return true;
	}
};
