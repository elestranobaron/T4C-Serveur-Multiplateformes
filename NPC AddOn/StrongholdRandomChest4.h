#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST4_H
#define __STRONGHOLDRANDOMCHEST4_H

class StrongholdRandomChest4 : public NPCstructure{
public:
  StrongholdRandomChest4();
  ~StrongholdRandomChest4();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
