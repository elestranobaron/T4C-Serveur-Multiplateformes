#include "NPCStructure.h"

#ifndef __GreyLeaf_H
#define __GreyLeaf_H

class GreyLeaf: public NPCstructure{
public:   
	GreyLeaf();
	~GreyLeaf();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
