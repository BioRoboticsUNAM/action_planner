#ifndef ACT_PLN_RBT_KNW
#define ACT_PLN_RBT_KNW

#include "ros/ros.h"

class RobotKnowledge
{
public:
	/*
	* Robot ARMS Constants
	*/
	enum ARM_SIDE
	{
		LeftArm,
		RightArm
	};


	//RobotKnowledge();
private:
	/*
	* Node handle and subscriber for speech reco
	*/
	//ros::NodeHandle nh_reco;
	//ros::Subscriber reco_sub;

	//static void updateRecognizedSentences(const bbros_bridge::RecognizedSpeech::ConstPtr& recognizedSentence);
};

#endif
