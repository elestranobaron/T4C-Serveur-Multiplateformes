#include "NPCStructure.h"

#ifndef __SWEEPER_H
#define __SWEEPER_H

class Sweeper : public NPCstructure{
public:
	Sweeper();
	~Sweeper();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnPopup( UNIT_FUNC_PROTOTYPE ); 
	void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif