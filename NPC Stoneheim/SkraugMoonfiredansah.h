#include "SimpleMonster.h"

#ifndef __SKRAUGMOONFIREDANSAH_H
#define __SKRAUGMOONFIREDANSAH_H

class SkraugMoonfiredansah : public SimpleMonster{
public:   
    SkraugMoonfiredansah();
   ~SkraugMoonfiredansah();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnDeath( UNIT_FUNC_PROTOTYPE);
};

#endif
