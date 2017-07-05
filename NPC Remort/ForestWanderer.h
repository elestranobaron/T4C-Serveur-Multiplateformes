#include "NPCStructure.h"

#ifndef __FORESTWANDERER_H
#define __FORESTWANDERER_H

class ForestWanderer : public NPCstructure{
public:
	ForestWanderer();
	~ForestWanderer();
	void Create( void );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif