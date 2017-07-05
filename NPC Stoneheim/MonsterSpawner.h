#include "SimpleMonster.h"

#ifndef __MONSTERSPAWNER_H
#define __MONSTERSPAWNER_H

class MonsterSpawner : public SimpleMonster{
public:   
    MonsterSpawner();
   ~MonsterSpawner();
    void Create( void );
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
};

#endif
