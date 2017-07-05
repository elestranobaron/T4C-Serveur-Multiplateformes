#include "NPCStructure.h"

#ifndef __OLINHAAD3_H
#define __OLINHAAD3_H

class OlinHaad3 : public NPCstructure{
public:
	OlinHaad3();
	~OlinHaad3();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif