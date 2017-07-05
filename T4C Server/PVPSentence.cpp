#include "Stdafx.h"
#include "PVPSentence.h"
#include "PlayerManager.h"
#include "ChatterChannels.h"

#include <string>
#include <vector>
#include "Random.h"
#include "T4CLog.h"
extern Random rnd;

PVPSentence::PVPSentence(){
}
PVPSentence::~PVPSentence(){
}

void PVPSentence::SayOnDeathChannel(std::string pKiller, std::string pKilled){
	char buffer[800];
	int n =0;
	int val=0;
	try{

		_LOG_DEBUG
			    LOG_DEBUG_LVL1,
				"PVPSentence Begin"
			LOG_

		
		std::vector<intern> _Sentences;

		// 0 = killed first else killer first

		//////////////////////////////////////////////////////////////////////////////////////////
		// steph traduction
		//////////////////////////////////////////////////////////////////////////////////////////
		_Sentences.push_back(intern(0,"%s just lost a leg and %s does not seem to be joking about it"));
		_Sentences.push_back(intern(1,"%s is about to take a bath with the blood of the deceased %s"));
		_Sentences.push_back(intern(1,"A head falls... %s is asked to leave the rest of %s's body alone."));
		_Sentences.push_back(intern(0,"Caution %s! Too late... %s just destroyed the poor man..."));
		_Sentences.push_back(intern(0,"The graveyard proudly welcome a new member, %s, thanks to %s for this gift!"));


		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout
		//////////////////////////////////////////////////////////////////////////////////////////
		_Sentences.push_back(intern(0,"Time for %s to go back to temple. At least that's what %s thinks."));
		_Sentences.push_back(intern(0,"Is there anyone one that can give a hand to %s?! Cause %s just proved he can't be alone out there."));
		_Sentences.push_back(intern(1,"Someone better stop %s, because he just made a new victim: %s."));
		_Sentences.push_back(intern(1,"Looks like %s just got some new fresh items, courtesy of %s."));



		val = rnd(0,_Sentences.size()-1);
		if(_Sentences[val].sens == 0){
			n = sprintf(buffer,_Sentences[val].sentence.c_str(),pKilled.c_str(),pKiller.c_str());
		}
		else{
			n = sprintf(buffer,_Sentences[val].sentence.c_str(),pKiller.c_str(),pKilled.c_str());
		}


		if(n > 0 && val >= 0 ){
			std::string real(buffer,n);
			ChatterChannels &cChatter = CPlayerManager::GetChatter();
			cChatter.SystemTalk("PVP","PVP",real);
		}
		else{
			_LOG_DEBUG
			    LOG_DEBUG_LVL1,
				"PVPSentence wrong value detected. val : %i",val
			LOG_	
		}
	}
	catch(...){
		_LOG_DEBUG
            LOG_DEBUG_LVL1,
            "PVPSentence Crash detected. val : %i",val
        LOG_
	}
}