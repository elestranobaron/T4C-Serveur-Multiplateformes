#include "NPCStructure.h"

#ifndef __DAFYD_H
#define __DAFYD_H

class Dafyd : public NPCstructure{
public:   
	Dafyd();
	~Dafyd();
	void Create( void );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );    
	void OnAttack( UNIT_FUNC_PROTOTYPE );    
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
