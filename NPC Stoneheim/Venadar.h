#include "NPCStructure.h"

#ifndef __VENADAR_H
#define __VENADAR_H

class Venadar : public NPCstructure{
public:   
    Venadar();
   ~Venadar();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnDeath( UNIT_FUNC_PROTOTYPE );
    
};

#endif
