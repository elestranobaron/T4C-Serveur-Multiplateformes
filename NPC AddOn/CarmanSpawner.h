#include "NPCStructure.h"

#ifndef __CARMANSPAWNER_H
#define __CARMANSPAWNER_H

class CarmanSpawner : public NPCstructure{
public:
	CarmanSpawner();
	~CarmanSpawner();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );

};

#endif