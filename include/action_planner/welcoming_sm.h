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
		WaitForBellRing,
		RecognizeVisitor,
		GreetVisitor,
		PerformDrKimbleRoutine,
		PerformDeliManRoutine,
		PerformPostManRoutine,
		PerformUnknownPersonRoutine,
		MoveToInitialPosition,
		FinalState
	};

	static ros::NodeHandle* node;
	//for the SM api
	StatesMachines SM;
	//service manager
	static ServiceManager srv_man;
	//stpln
	static PrimitivesTasks m_tasks;
	//SM variables
	static std::string visitorName;
	static ros::ServiceClient srvCltEndPrepare;
	static ros::ServiceClient srvCltEndExecute;
	static ros::Subscriber subBenchmarkState;
	static ros::Publisher pubRecordData;

	/********************************************************************/
	/*
	*	ADD THE STATE FUNCTIONS YOU NEED
	*/
	static int fInitialState();
	static int fWaitForBellRing();
	static int fRecognizeVisitor();
	static int fGreetVisitor();
	static int fPerformDrKimbleRoutine();
	static int fPerformDeliManRoutine();
	static int fPerformPostManRoutine();
	static int fPerformUnknownPersonRoutine();
	static int fMoveToInitialPosition();
	static int fFinalState();
	/**********************************************************************/
	
public:
	WelcomingSM(PrimitivesTasks tasks,  ros::NodeHandle*);
	bool execute();
};

PrimitivesTasks WelcomingSM::m_tasks;
ServiceManager WelcomingSM::srv_man;
ros::NodeHandle* WelcomingSM::node;


/*
* A particular constructor for your state machine
* Initialize your state machine here (add states, define the final state, define the execution method, etc)
*/
WelcomingSM::WelcomingSM(PrimitivesTasks tasks, ros::NodeHandle* n)
{
	m_tasks = tasks;
	node = n;

	//int (WelcomingSM::*
	//add states to the state machine
	SM.addState((int)InitialState, &fInitialState);
	SM.addState((int)WaitForBellRing, &fWaitForBellRing);
	SM.addState((int)RecognizeVisitor, &fRecognizeVisitor);
	SM.addState((int)GreetVisitor, &fGreetVisitor);
	SM.addState((int)PerformDrKimbleRoutine, &fPerformDrKimbleRoutine);
	SM.addState((int)PerformDeliManRoutine, &fPerformDeliManRoutine);
	SM.addState((int)PerformPostManRoutine, &fPerformPostManRoutine);
	SM.addState((int)PerformUnknownPersonRoutine, &fPerformUnknownPersonRoutine);
	SM.addState((int)MoveToInitialPosition, &fMoveToInitialPosition);
	SM.addState((int)FinalState, &fFinalState, true);

	//srvCltEndPrepare = n->serviceClient<std_srvs::Empty>("roah_rsbb/end_prepare");
	//srvCltEndExecute = n->serviceClient<std_srvs::Empty>("roah_rsbb/end_execute");
	//subBenchmarkState = n->subscribe("/roah_rsbb/benchmark/state", 100, NavigationSM::callback_benchmark_state);
	////subGoalPose = n->subscribe("/roah_rsbb/goal", 100, NavigationSM::callback_goal_pose);
	////pubMessagesSaved = n->advertise<std_msgs::UInt32>("roah_rsbb/messages_saved", 100);
	////pubReachedWaypoint = n->advertise<std_msgs::UInt8>("roah_rsbb/reached_waypoint", 100);
	//pubRecordData = n->advertise<std_msgs::Bool>("br_record_data", 100);

}
bool WelcomingSM::execute()
{
	while(SM.runNextStep())
		ros::spinOnce();

	return true;
}

/*
*	ADD THE STATE FUNCTIONS YOU NEED
*/
 int WelcomingSM::fInitialState()
{
	std::cout << "Initializing Welcoming Visitors SM" << std::endl;
	return (int)WaitForBellRing;
}
 int WelcomingSM::fWaitForBellRing()
{
	std::cout << "Waiting for the door bell ring....." << std::endl;
	std::getchar();
	return (int)RecognizeVisitor;
}
 int WelcomingSM::fRecognizeVisitor()
{
	std::cout << "Recognizing visitor using vision..." << std::endl;
	//try to recognize Dr. Kim
	
	//if the person is not the Dr. try using clothes
	//bool vsnClothesReco(std_msgs::String&)
	//unknown person

	//TODO: Call the vision routine
	std::cout << "visitor recognized: " << std::endl;
	return (int)GreetVisitor;
}
 int WelcomingSM::fGreetVisitor()
{
	return (int)0;
}
 int WelcomingSM::fPerformDrKimbleRoutine()
{
	return (int)0;
}
 int WelcomingSM::fPerformDeliManRoutine()
{
	return (int)0;
}
 int WelcomingSM::fPerformPostManRoutine()
{
	return (int)0;
}
 int WelcomingSM::fPerformUnknownPersonRoutine()
{
	return (int)0;
}
 int WelcomingSM::fMoveToInitialPosition()
{
	return (int)0;
}
 int WelcomingSM::fFinalState()
{
	return (int)0;
}
/**********************************************************************/
