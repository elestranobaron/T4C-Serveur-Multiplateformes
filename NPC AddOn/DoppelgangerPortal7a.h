#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL7A_H
#define __DOPPELGANGERPORTAL7A_H

class DoppelgangerPortal7a : public NPCstructure{
public:   
  DoppelgangerPortal7a();
  ~DoppelgangerPortal7a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
