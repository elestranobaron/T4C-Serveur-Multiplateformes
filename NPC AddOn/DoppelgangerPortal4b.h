#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL4B_H
#define __DOPPELGANGERPORTAL4B_H

class DoppelgangerPortal4b : public NPCstructure{
public:   
  DoppelgangerPortal4b();
  ~DoppelgangerPortal4b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
