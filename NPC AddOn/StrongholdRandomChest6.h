#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST6_H
#define __STRONGHOLDRANDOMCHEST6_H

class StrongholdRandomChest6 : public NPCstructure{
public:
  StrongholdRandomChest6();
  ~StrongholdRandomChest6();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
