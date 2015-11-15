#include "action_planner/primitives_tasks.h"
#include "action_planner/service_manager.h"
#include "action_planner/states_machines.h"
#include "ros/ros.h"
#include <iostream>
#include <vector>

class WelcomingSM
{
private:
	/*
	*	ADD THE STATES ID YOU NEED FOR EACH STATE FUNCTION (IF YOU WANT)
	*/
	enum States
	{
		InitialState,
		WaitForInitCommand,
		ProcessAudioFiles,
		ListenAndParse,
		ReportResult,
		FinalState
	};

	//for the SM api
	StatesMachines SM;
	//service manager
	static ServiceManager srv_man;
	//stpln
	static PrimitivesTasks m_tasks;
	//state func members
	static int listenAttempts;
	static int maxListenAttempts;
	static std::string cfrRepresentation;

	/********************************************************************/
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	static int initialState();
	static int waitForInitCommand();
	static int processAudioFiles();
	static int listenAndParse();
	static int reportResult();
	static int finalState();
	/**********************************************************************/
	
public:
	WelcomingSM(PrimitivesTasks tasks);
	bool execute();
};

PrimitivesTasks WelcomingSM::m_tasks;
ServiceManager WelcomingSM::srv_man;
int WelcomingSM::listenAttempts;
int WelcomingSM::maxListenAttempts;
std::string WelcomingSM::cfrRepresentation;


/*
* A particular constructor for your state machine
* Initialize your state machine here (add states, define the final state, define the execution method, etc)
*/
WelcomingSM::WelcomingSM(PrimitivesTasks tasks)
{
	m_tasks = tasks;
	//int (WelcomingSM::*
	//add states to the state machine
	SM.addState((int)InitialState, &initialState);
	SM.addState((int)WaitForInitCommand, &waitForInitCommand);
	SM.addState((int)ProcessAudioFiles, &processAudioFiles);
	SM.addState((int)ListenAndParse, &listenAndParse);
	SM.addState((int)ReportResult, &reportResult);;
	SM.addState((int)FinalState, &finalState, true);
}
bool WelcomingSM::execute()
{
	while(SM.runNextStep());
	return true;
};

/*
*	ADD THE STATE FUNCTIONS YOU NEED
*/
int WelcomingSM::initialState()
{
	std::cout << "executing initial state " << std::endl;

	/*Initialize member variables*/
	listenAttempts=0;
	maxListenAttempts=3;

	return (int)WaitForInitCommand;
}

int WelcomingSM::waitForInitCommand()
{
	std::cout << "waiting for init command....." << std::endl;
	std::getchar();
	return (int)ProcessAudioFiles;
}

int WelcomingSM::processAudioFiles()
{
	std::cout << "processing audio files... " << std::endl;
	
	return (int)ListenAndParse;
}

int WelcomingSM::listenAndParse()
{
	std::cout << "waiting for speech command... " << std::endl;
	std::string recoSentence;
	if(m_tasks.listen(recoSentence, 10000))
	{
		std::cout << "parsing command... " << std::endl;
		srv_man.langundProcess(recoSentence, cfrRepresentation);
	}
	else
	{
		//nothing heared, try again
		srv_man.spgenSay("Human I cannot hear you. Please get closer to my microphone", 5000);
		if(listenAttempts<maxListenAttempts)
		{
			listenAttempts++;
			return (int)ListenAndParse;
		}
		return (int)ReportResult;
	}
	
	//ros::Duration(0.5).sleep();
	return (int)ReportResult;
}

int WelcomingSM::reportResult()
{
	std::cout << "Repoorting result... " << std::endl;
	std::cout << "CFR Representation of the recognized sentence: " << cfrRepresentation << std::endl;
	//return (int)FinalState;
	return (int)ListenAndParse;
}

int WelcomingSM::finalState()
{
	std::cout << "finalState reached" << std::endl;
	return (int)FinalState;
}

/**********************************************************************/
