#include "SimpleMonster.h"

#ifndef __GABRIELARCHONIS_H
#define __GABRIELARCHONIS_H

class GabrielArchonis : public SimpleMonster{
public:   
    GabrielArchonis();
   ~GabrielArchonis();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnHit( UNIT_FUNC_PROTOTYPE );   
    
};

#endif
