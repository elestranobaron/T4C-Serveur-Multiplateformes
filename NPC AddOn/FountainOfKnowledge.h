#include "NPCStructure.h"

#ifndef __FOUNTAINOFKNOWLEDGE_H
#define __FOUNTAINOFKNOWLEDGE_H

class FountainOfKnowledge : public NPCstructure{
public:
	FountainOfKnowledge();
	~FountainOfKnowledge();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif