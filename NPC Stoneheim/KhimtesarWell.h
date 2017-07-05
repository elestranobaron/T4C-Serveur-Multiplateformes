#include "NPCStructure.h"

#ifndef __KHIMTESARWELL_H
#define __KHIMTESARWELL_H

class KhimtesarWell : public NPCstructure{
public:
	KhimtesarWell();
	~KhimtesarWell();
	void Create( void );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
