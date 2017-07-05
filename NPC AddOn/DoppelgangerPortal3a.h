#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL3A_H
#define __DOPPELGANGERPORTAL3A_H

class DoppelgangerPortal3a : public NPCstructure{
public:   
  DoppelgangerPortal3a();
  ~DoppelgangerPortal3a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
