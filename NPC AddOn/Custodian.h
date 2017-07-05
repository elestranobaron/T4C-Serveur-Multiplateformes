#include "NPCStructure.h"

#ifndef __CUSTODIAN_H
#define __CUSTODIAN_H

class Custodian : public NPCstructure{
public:
	Custodian();
	~Custodian();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif