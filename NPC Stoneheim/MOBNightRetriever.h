#include "SimpleMonster.h"

#ifndef __MOBNIGHTRETRIEVER_H
#define __MOBNIGHTRETRIEVER_H

class MOBNightRetriever : public SimpleMonster{
public:   
    MOBNightRetriever();
   ~MOBNightRetriever();
    void Create( void );
    void OnAttackHit( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
