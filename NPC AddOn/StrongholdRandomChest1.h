#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST1_H
#define __STRONGHOLDRANDOMCHEST1_H

class StrongholdRandomChest1 : public NPCstructure{
public:
  StrongholdRandomChest1();
  ~StrongholdRandomChest1();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
