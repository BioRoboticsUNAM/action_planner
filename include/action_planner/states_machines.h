#ifndef ACT_PLN_SMS
#define ACT_PLN_SMS

#include <map>
#include <iostream>
class StatesMachines
{
public:
	/*
	* Constructor
	*/
	StatesMachines();

	typedef int (*fncPtr)();
	/*
	* Enum to represent the SMs status
	*
	*/
	//enum SM_STATUS
	//{
	//	Initializing,
	//	Executing,
	//	Succeeded,
	//	Failed
	//};
	//variable to know the current status of the SM
	//SM_STATUS currentSMStatus;
	
	bool objectPerceptionSM();
private:
	//dictionary to store the states of the sm to execute
	std::map<int, fncPtr> statesDictionary;
	//variable to store the final state id
	int finalStateID;
	//variable to store the next state to execute
	int stateToExecute;
	//variable to know if the final state was executed
	bool finalStateExecuted;

	void addState(int, fncPtr, bool isFinalState=false);
	void resetStates();
	bool runNextStep();
	int defaultState();
};
#endif
