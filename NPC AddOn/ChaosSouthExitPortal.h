#include <NPCStructure.h>

#ifndef __CHAOSSOUTHEXITPORTAL_H
#define __CHAOSSOUTHEXITPORTAL_H

class ChaosSouthExitPortal : public NPCstructure{
public:   
  ChaosSouthExitPortal();
  ~ChaosSouthExitPortal();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
