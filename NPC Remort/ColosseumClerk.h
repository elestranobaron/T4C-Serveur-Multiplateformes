#include "NPCStructure.h"

#ifndef __COLOSSEUMCLERK_H
#define __COLOSSEUMCLERK_H

class ColosseumClerk : public NPCstructure{
public:
	ColosseumClerk();
	~ColosseumClerk();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif