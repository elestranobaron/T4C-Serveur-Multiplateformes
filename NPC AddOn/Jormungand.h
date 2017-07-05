#include "NPCStructure.h"

#ifndef __JORMUNGAND_H
#define __JORMUNGAND_H

class Jormungand : public NPCstructure{
public:
	Jormungand();
	~Jormungand();
	void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif