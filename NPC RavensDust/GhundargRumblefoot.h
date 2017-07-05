#include "NPCStructure.h"

#ifndef __GHUNDARGRUMBLEFOOT_H
#define __GHUNDARGRUMBLEFOOT_H

class GhundargRumblefoot : public NPCstructure
{
public:   
    GhundargRumblefoot();
   ~GhundargRumblefoot();
    void Create( void );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
	 void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
  
 
};

#endif
