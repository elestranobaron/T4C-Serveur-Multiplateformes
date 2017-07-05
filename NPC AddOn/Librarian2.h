#include "NPCStructure.h"

#ifndef __LIBRARIAN2_H
#define __LIBRARIAN2_H

class Librarian2 : public NPCstructure{
public:
	Librarian2();
	~Librarian2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif