#include <NPCStructure.h>

#ifndef __CHAOSWESTEXITPORTAL_H
#define __CHAOSWESTEXITPORTAL_H

class ChaosWestExitPortal : public NPCstructure{
public:   
  ChaosWestExitPortal();
  ~ChaosWestExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
