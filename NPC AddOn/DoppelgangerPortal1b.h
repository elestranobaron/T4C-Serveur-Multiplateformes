#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL1B_H
#define __DOPPELGANGERPORTAL1B_H

class DoppelgangerPortal1b : public NPCstructure{
public:   
  DoppelgangerPortal1b();
  ~DoppelgangerPortal1b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
