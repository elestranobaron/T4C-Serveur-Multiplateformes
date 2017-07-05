#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST2_H
#define __STRONGHOLDRANDOMCHEST2_H

class StrongholdRandomChest2 : public NPCstructure{
public:
  StrongholdRandomChest2();
  ~StrongholdRandomChest2();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
