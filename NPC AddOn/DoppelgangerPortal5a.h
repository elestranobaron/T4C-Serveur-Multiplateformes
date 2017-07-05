#include <NPCStructure.h>

#ifndef __DOPPELGANGERPORTAL5A_H
#define __DOPPELGANGERPORTAL5A_H

class DoppelgangerPortal5a : public NPCstructure{
public:   
  DoppelgangerPortal5a();
  ~DoppelgangerPortal5a();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
