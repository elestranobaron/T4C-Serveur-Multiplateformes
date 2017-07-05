#include "SimpleMonster.h"

#ifndef __MOBSHADOWSTALKER_H
#define __MOBSHADOWSTALKER_H

class MOBShadowstalker : public SimpleMonster{
public:   
    MOBShadowstalker();
   ~MOBShadowstalker();
    void Create( void );
    void OnInitialise( UNIT_FUNC_PROTOTYPE ); 
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttackHit( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
