#include "NPCStructure.h"

#ifndef __STRONGHOLDRANDOMCHEST5_H
#define __STRONGHOLDRANDOMCHEST5_H

class StrongholdRandomChest5 : public NPCstructure{
public:
  StrongholdRandomChest5();
  ~StrongholdRandomChest5();
	void Create( void );
	void OnAttacked (UNIT_FUNC_PROTOTYPE);
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
