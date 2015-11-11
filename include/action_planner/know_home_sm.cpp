#include "action_planner/states_machines.h"

namespace KnowHomeSM
{
	/*
	*	ADD THE STATES ID YOU NEED FOR EACH STATE FUNCTION (IF YOU WANT)
	*/
	enum States
	{
		InitialState,
		DoSomethingState,
		FinalState
	};
	/********************************************************************/
	
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	int initialStateFunc()
	{
		std::cout << "executing initial state" << std::endl;
		return (int)DoSomethingState;
	}
	
	int doSomethingFunc()
	{
		std::cout << "doing something state" << std::endl;
		return (int)FinalState;
	}
	
	int finalStateFunc()
	{
		std::cout << "finalState sreached" << std::endl;
		return (int)FinalState;
	}
	
	/**********************************************************************/
};

/*
* A particular constructor for your state machine
* Initialize your state machine here (add states, define the final state, define the execution method, etc)
*/
bool StatesMachines::knowHomeSM()
{
	//reset the states of the state machine
	resetStates();

	//add states to the state machine
	addState((int)KnowHomeSM::InitialState, KnowHomeSM::initialStateFunc);
	addState((int)KnowHomeSM::DoSomethingState, KnowHomeSM::doSomethingFunc);
	addState((int)KnowHomeSM::FinalState, KnowHomeSM::finalStateFunc, true);

	//execute the state machine from the initial state until the final state
	while(runNextStep());

	return true;
}
