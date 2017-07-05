#include <NPCStructure.h>

#ifndef __CHAOSWESTTOCENTERPORTAL_H
#define __CHAOSWESTTOCENTERPORTAL_H

class ChaosWestToCenterPortal : public NPCstructure{
public:   
  ChaosWestToCenterPortal();
  ~ChaosWestToCenterPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
