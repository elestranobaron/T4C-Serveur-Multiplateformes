#ifndef SHAINON_PVP_SENTENCE_H
#define SHAINON_PVP_SENTENCE_H
#include <string>
class PVPSentence
{
	struct intern{
		int sens; // 0 = killed first else killer first
		std::string sentence;
		intern(int psens,std::string psentence){
			sens = psens;
			sentence = psentence;
		}
	};
private:
public:
	PVPSentence();
	~PVPSentence();

	void SayOnDeathChannel(std::string pKiller, std::string pKilled);
};

#endif