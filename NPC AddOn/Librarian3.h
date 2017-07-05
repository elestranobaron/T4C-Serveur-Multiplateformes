#include "NPCStructure.h"

#ifndef __LIBRARIAN3_H
#define __LIBRARIAN3_H

class Librarian3 : public NPCstructure{
public:
	Librarian3();
	~Librarian3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif