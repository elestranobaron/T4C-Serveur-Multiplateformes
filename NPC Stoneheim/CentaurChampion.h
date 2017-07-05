#include "SimpleMonster.h"

#ifndef __CENTAURCHAMPION_H
#define __CENTAURCHAMPION_H

class CentaurChampion : public  SimpleMonster{
public:   
    CentaurChampion();
   ~CentaurChampion();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif
