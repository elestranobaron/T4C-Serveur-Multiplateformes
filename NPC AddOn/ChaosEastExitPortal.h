#include <NPCStructure.h>

#ifndef __CHAOSEASTEXITPORTAL_H
#define __CHAOSEASTEXITPORTAL_H

class ChaosEastExitPortal : public NPCstructure{
public:   
  ChaosEastExitPortal();
  ~ChaosEastExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
