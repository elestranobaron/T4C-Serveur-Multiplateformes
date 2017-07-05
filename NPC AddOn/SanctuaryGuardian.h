#include "NPCStructure.h"

#ifndef __SANCTUARYGUARDIAN_H
#define __SANCTUARYGUARDIAN_H

class SanctuaryGuardian : public NPCstructure{
public:
  SanctuaryGuardian();
  ~SanctuaryGuardian();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
