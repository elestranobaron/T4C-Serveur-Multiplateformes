#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL6A_H
#define __DOPPELGANGERPORTAL6A_H

class DoppelgangerPortal6a : public NPCstructure{
public:   
  DoppelgangerPortal6a();
  ~DoppelgangerPortal6a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
