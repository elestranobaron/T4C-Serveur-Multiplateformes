#include "NPCStructure.h"

#ifndef __BLOODLUST_H
#define __BLOODLUST_H

class Bloodlust : public NPCstructure{
public:
	Bloodlust();
	~Bloodlust();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );   
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};
 
#endif