#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL2A_H
#define __DOPPELGANGERPORTAL2A_H

class DoppelgangerPortal2a : public NPCstructure{
public:   
  DoppelgangerPortal2a();
  ~DoppelgangerPortal2a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
