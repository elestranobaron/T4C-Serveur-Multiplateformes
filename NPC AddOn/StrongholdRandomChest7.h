#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST7_H
#define __STRONGHOLDRANDOMCHEST7_H

class StrongholdRandomChest7 : public NPCstructure{
public:
  StrongholdRandomChest7();
  ~StrongholdRandomChest7();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
