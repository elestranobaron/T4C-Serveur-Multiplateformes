#include "SimpleMonster.h"

#ifndef __MOBNEOFLARE_H
#define __MOBNEOFLARE_H

class MOBNeoflare : public SimpleMonster{
public:   
    MOBNeoflare();
   ~MOBNeoflare();
    void Create( void );
    void OnPopup( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
 