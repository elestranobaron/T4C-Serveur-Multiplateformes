#include "NPCStructure.h"

#ifndef __MAKRSHPTANGH2_H
#define __MAKRSHPTANGH2_H

class MakrshPtangh2 : public NPCstructure{
public:
	MakrshPtangh2();
	~MakrshPtangh2();
	void Create( void );
	void OnAttack( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};
 
#endif