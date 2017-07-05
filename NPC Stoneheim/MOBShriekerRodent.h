#include "SimpleMonster.h"

#ifndef __MOBSHRIEKERRODENT_H
#define __MOBSHRIEKERRODENT_H

class MOBShriekerRodent : public SimpleMonster{
public:   
    MOBShriekerRodent();
   ~MOBShriekerRodent();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
};


#endif
 