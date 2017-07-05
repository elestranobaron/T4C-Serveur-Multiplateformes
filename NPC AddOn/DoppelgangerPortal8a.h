#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL8A_H
#define __DOPPELGANGERPORTAL8A_H

class DoppelgangerPortal8a : public NPCstructure{
public:   
  DoppelgangerPortal8a();
  ~DoppelgangerPortal8a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
