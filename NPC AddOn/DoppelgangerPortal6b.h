#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL6B_H
#define __DOPPELGANGERPORTAL6B_H

class DoppelgangerPortal6b : public NPCstructure{
public:   
  DoppelgangerPortal6b();
  ~DoppelgangerPortal6b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
