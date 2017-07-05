#include "NPCStructure.h"

#ifndef __MOBMERCENARYLIEUTENANTB_H
#define __MOBMERCENARYLIEUTENANTB_H

class MOBMercenaryLieutenantB : public NPCstructure{
public:   
    MOBMercenaryLieutenantB();
   ~MOBMercenaryLieutenantB();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
