#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL8B_H
#define __DOPPELGANGERPORTAL8B_H

class DoppelgangerPortal8b : public NPCstructure{
public:   
  DoppelgangerPortal8b();
  ~DoppelgangerPortal8b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
