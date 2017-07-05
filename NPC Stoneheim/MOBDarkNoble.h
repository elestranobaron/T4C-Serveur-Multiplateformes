#include "NPCStructure.h"

#ifndef __MOBDARKNOBLE_H
#define __MOBDARKNOBLE_H

class MOBDarkNoble : public NPCstructure{
public:   
    MOBDarkNoble(); 
   ~MOBDarkNoble(); 
    void Create( void );
	  void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
