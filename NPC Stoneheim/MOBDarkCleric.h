#include "NPCStructure.h"

#ifndef __MOBDARKCLERIC_H
#define __MOBDARKCLERIC_H

class MOBDarkCleric : public NPCstructure{
public:    
    MOBDarkCleric();
   ~MOBDarkCleric();
    void Create( void ); 
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
