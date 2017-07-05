#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL1A_H
#define __DOPPELGANGERPORTAL1A_H

class DoppelgangerPortal1a : public NPCstructure{
public:   
  DoppelgangerPortal1a();
  ~DoppelgangerPortal1a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
