#include "action_planner/states_machines.h"

StatesMachines::SM_STATUS StatesMachines::objectPerceptionSM()
{
	//configure sm
	/*
	sm_addstate(&funcpinter_initial) //initial state must be the first added state
	sm_addstate(&funcpinter_search)
	sm_addstate(&funcpinter_finalstate)
	*/
	//execute sm 
	/*while(state!=finalstate)
		execute next step;
	*/
	return StatesMachines::Succeeded;
}
