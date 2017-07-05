#include "NPCStructure.h"

#ifndef __MOBMERCENARYLIEUTENANTA_H
#define __MOBMERCENARYLIEUTENANTA_H

class MOBMercenaryLieutenantA : public NPCstructure{
public:   
    MOBMercenaryLieutenantA();
   ~MOBMercenaryLieutenantA();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
