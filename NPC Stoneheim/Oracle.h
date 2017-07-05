#include "NPCStructure.h"

#ifndef __ORACLE_H
#define __ORACLE_H

class Oracle : public NPCstructure{
public:   
    Oracle();
   ~Oracle();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );
    
};

#endif
