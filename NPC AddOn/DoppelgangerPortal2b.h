#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL2B_H
#define __DOPPELGANGERPORTAL2B_H

class DoppelgangerPortal2b : public NPCstructure{
public:   
  DoppelgangerPortal2b();
  ~DoppelgangerPortal2b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
