#ifndef ACT_PLN_RBT_KNW
#define ACT_PLN_RBT_KNW

#include <tuple>
#include <array>
#include <string>
#include "bbros_bridge/RecognizedSpeech.h"
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

	RobotKnowledge();
	
private:
	/*
	*	Robot speech recognition info
	* recognizedSentence	:	stores the last recognized sentence (recognized sentece, confidentiality) 
	*		comming from the speech recognition module.
	*/
	static std::array<std::tuple<std::string, double>, 3> recognizedSentences;

	/*
	* Node handle and subscriber for speech reco
	*/
	ros::NodeHandle nh_reco;
	ros::Subscriber reco_sub;

	void updateRecognizedSentence(const bbros_bridge::RecognizedSpeech::ConstPtr& recognizedSentence);
};

#endif
