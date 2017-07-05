#include "NPCStructure.h"

#ifndef __LOTHAR_H
#define __LOTHAR_H

class Lothar : public NPCstructure{
public:
	Lothar();
	~Lothar();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif