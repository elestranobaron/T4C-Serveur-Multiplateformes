#include "SimpleMonster.h"

#ifndef __MOBGAUZECORPSE_H
#define __MOBGAUZECORPSE_H

class MOBGauzeCorpse : public SimpleMonster{
public:   
    MOBGauzeCorpse();
   ~MOBGauzeCorpse();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE ); 
};
#endif
