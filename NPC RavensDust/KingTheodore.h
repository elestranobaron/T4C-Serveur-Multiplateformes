#include "NPCStructure.h"

#ifndef __KINGTHEODORE_H
#define __KINGTHEODORE_H

class KingTheodore : public NPCstructure{
public:   
    KingTheodore();
   ~KingTheodore();
    void Create( void );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif
