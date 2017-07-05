#include "NPCStructure.h"

#ifndef __FENRIR_H
#define __FENRIR_H

class Fenrir : public NPCstructure{
public:
	Fenrir();
	~Fenrir();
	void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif