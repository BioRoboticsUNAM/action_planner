#include "action_planner/robot_knowledge.h"


/*
* Constructor
*/
RobotKnowledge::RobotKnowledge()
{
	objectDictionary["pepsi cup"] = "Mugs";
	objectDictionary["small white mug with yellow dots"] = "Mugs";
	objectDictionary["coffee mugs"] = "Mugs";
	objectDictionary["black jug"] = "Mugs";
	objectDictionary["fork"] = "Forks and Knives";
	objectDictionary["knife"] = "Forks and Knives";
	objectDictionary["yellow box"] = "Boxes";
	objectDictionary["pink box"] = "Boxes";
	objectDictionary["gold color frame"] = "Picture Frame";
	objectDictionary["black color frame"] = "Picture Frame";
//	//Initialize the recognized sentences with default values
//	recoSentenceTuple defaultRecoValue;
//	recognizedSentences = std::vector<recoSentenceTuple>(3, defaultRecoValue);
//	//recognizedSentences.push_back(defaultRecoValue);
//	//recognizedSentences.push_back(defaultRecoValue);
//	//recognizedSentences.push_back(defaultRecoValue);
//	
//	//subscribe to the recognizedSpeech topic
//	reco_sub = nh_reco.subscribe("recognizedSpeech", 100, updateRecognizedSentences);
//
//	std::cout << "reco initial value: " << recognizedSentences[0].hypotesis << " " << recognizedSentences[0].confidence << std::endl;
//	std::cout << "reco initial value: " << recognizedSentences[1].hypotesis << " " << recognizedSentences[1].confidence << std::endl;
//	std::cout << "reco initial value: " << recognizedSentences[2].hypotesis << " " << recognizedSentences[2].confidence << std::endl;
}


