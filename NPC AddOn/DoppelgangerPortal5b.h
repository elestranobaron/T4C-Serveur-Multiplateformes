#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL5B_H
#define __DOPPELGANGERPORTAL5B_H

class DoppelgangerPortal5b : public NPCstructure{
public:   
  DoppelgangerPortal5b();
  ~DoppelgangerPortal5b();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
