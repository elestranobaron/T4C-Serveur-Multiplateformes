#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL4A_H
#define __DOPPELGANGERPORTAL4A_H

class DoppelgangerPortal4a : public NPCstructure{
public:   
  DoppelgangerPortal4a();
  ~DoppelgangerPortal4a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
