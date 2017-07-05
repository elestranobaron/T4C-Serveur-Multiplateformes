#include "NPCStructure.h"
#include "SimpleMonster.h"

#ifndef __GORLOKBLOODAXE_H
#define __GORLOKBLOODAXE_H

class GorlokBloodaxe : public SimpleMonster{
public:
	GorlokBloodaxe();
	~GorlokBloodaxe();
	void Create( void );
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif