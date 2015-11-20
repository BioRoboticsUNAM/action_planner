#include "action_planner/robot_knowledge.h"


/*
* Constructor
*/
RobotKnowledge::RobotKnowledge()
{
	objectDictionary["large_black_mug"] = "Mugs";
	objectDictionary["small_white_mug"] = "Mugs";
	objectDictionary["coffe_mugs"] = "Mugs";
	objectDictionary["black_jug"] = "Mugs";
	objectDictionary["fork"] = "Forks and Knives";
	objectDictionary["knife"] = "Forks and Knives";
	objectDictionary["yellow"] = "Boxes";
	objectDictionary["pink"] = "Boxes";
	objectDictionary["gold_color_frame"] = "Picture Frame";
	objectDictionary["small_black_picture_frame"] = "Picture Frame";
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


