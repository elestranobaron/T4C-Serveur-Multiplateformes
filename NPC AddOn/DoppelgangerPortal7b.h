#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL7B_H
#define __DOPPELGANGERPORTAL7B_H

class DoppelgangerPortal7b : public NPCstructure{
public:   
  DoppelgangerPortal7b();
  ~DoppelgangerPortal7b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
