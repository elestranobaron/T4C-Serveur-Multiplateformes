#include "NPCStructure.h"

#ifndef __MOBMERCENARYLIEUTENANTC_H
#define __MOBMERCENARYLIEUTENANTC_H

class MOBMercenaryLieutenantC : public NPCstructure{
public:   
    MOBMercenaryLieutenantC();
   ~MOBMercenaryLieutenantC();
    void Create( void );    
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
