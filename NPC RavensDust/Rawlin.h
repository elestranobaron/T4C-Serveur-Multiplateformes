#include "NPCStructure.h"

#ifndef __RAWLIN_H
#define __RAWLIN_H

class Rawlin : public NPCstructure{
public:   
	Rawlin();
	~Rawlin();
	void Create( void );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );    
	void OnAttack( UNIT_FUNC_PROTOTYPE );    
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
