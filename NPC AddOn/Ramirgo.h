#include "NPCStructure.h"

#ifndef __RAMIRGO_H
#define __RAMIRGO_H

class Ramirgo : public NPCstructure{
public:
	Ramirgo();
	~Ramirgo();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif