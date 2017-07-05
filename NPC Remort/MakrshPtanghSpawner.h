#include "SimpleMonster.h"

#ifndef __MAKRSHPTANGHSPAWNER_H
#define __MAKRSHPTANGHSPAWNER_H

class MakrshPtanghSpawner : public SimpleMonster{
public:
	MakrshPtanghSpawner();
	~MakrshPtanghSpawner();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
};
 
#endif