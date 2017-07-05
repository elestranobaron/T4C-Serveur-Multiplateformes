#include "NPCStructure.h"

#ifndef __MOBBLACKPROPHET_H
#define __MOBBLACKPROPHET_H

class MOBBlackProphet : public NPCstructure{
public:   
    MOBBlackProphet();
   ~MOBBlackProphet(); 
    void Create( void ); 
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
