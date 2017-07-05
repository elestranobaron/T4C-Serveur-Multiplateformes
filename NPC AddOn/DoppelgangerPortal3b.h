#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL3B_H
#define __DOPPELGANGERPORTAL3B_H

class DoppelgangerPortal3b : public NPCstructure{
public:   
  DoppelgangerPortal3b();
  ~DoppelgangerPortal3b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
