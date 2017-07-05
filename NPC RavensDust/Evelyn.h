#include "NPCStructure.h"

#ifndef __EVELYN_H
#define __EVELYN_H

class Evelyn : public NPCstructure{
public:   
    Evelyn();
   ~Evelyn();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif
