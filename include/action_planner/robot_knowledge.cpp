#include "action_planner/robot_knowledge.h"

/*
* Constructor
*/
RobotKnowledge::RobotKnowledge()
{
	//Initialize the recognized sentences with default values
	recognizedSentences[0] = std::tuple<std::string, double> ("", 0.0);
	recognizedSentences[1] = std::tuple<std::string, double> ("", 0.0);
	recognizedSentences[2] = std::tuple<std::string, double> ("", 0.0);
	
	//subscribe to the recognizedSpeech topic
	reco_sub = nh_reco.subscribe("recognizedSpeech", 100, updateRecognizedSentence);
}

/*
*	Listen to the recognizedSentence topic to update the current recognizedSentence data structure
*/
void RobotKnowledge::updateRecognizedSentences(const bbros_bridge::RecognizedSpeech::ConstPtr& recognizedSpeech)
{
	int recoSpeechSize = recognizedSpeech->hypotesis.size();
	//fill recognizedSentences data structure with all the elements comming from recognizedSpeech topic
	for(int i=0, i<3; i++)
	{
		std::get<0>(recognizedSentences[i]) = (i<recoSpeechSize) recognizedSpeech->hypotesis[i] : "";
		std::get<1>(recognizedSentences[i]) = (i<recoSpeechSize) recognizedSpeech->confidence[i] : 0.0;
	}
	std::cout << "reco: " << recognizedSentences << std::endl;
}
