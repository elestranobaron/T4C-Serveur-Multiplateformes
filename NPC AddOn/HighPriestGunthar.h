#include "NPCStructure.h"

#ifndef __HIGHPRIESTGUNTHAR_H
#define __HIGHPRIESTGUNTHAR_H

class HighPriestGunthar : public NPCstructure{
public:
	HighPriestGunthar();
	~HighPriestGunthar();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif