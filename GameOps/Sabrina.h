#include "NPCStructure.h"

#ifndef __SABRINA_H
#define __SABRINA_H

class Sabrina : public NPCstructure{
public:   
	Sabrina();
	~Sabrina();
	void Create( void );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );   
};

#endif
